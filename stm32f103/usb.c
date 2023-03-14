#include "usb.h"
#include <libopencm3/usb/usbd.h>
#include <libopencm3/usb/hid.h>
#include <stddef.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/usb/cdc.h>

static usbd_device * usbd_dev;
static const struct usb_device_descriptor dev_descriptor = {
	.bLength = USB_DT_DEVICE_SIZE,
	.bDescriptorType = USB_DT_DEVICE,
	.bcdUSB = 0x0200,
	.bDeviceClass = 0,
	.bDeviceSubClass = 0,
	.bDeviceProtocol = 0,
	.bMaxPacketSize0 = 64,
	.idVendor = 0x0483,
	.idProduct = 0x5710,
	.bcdDevice = 0x0200,
	.iManufacturer = 1,
	.iProduct = 2,
	.iSerialNumber = 3,
	.bNumConfigurations = 1
};
//usb dcm stuffs
static const struct usb_endpoint_descriptor comm_endp[] = {{
	.bLength = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType = USB_DT_ENDPOINT,
	.bEndpointAddress = 0x83,
	.bmAttributes = USB_ENDPOINT_ATTR_INTERRUPT,
	.wMaxPacketSize = 16,
	.bInterval = 255,
}};

static const struct usb_endpoint_descriptor data_endp[] = {{
	.bLength = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType = USB_DT_ENDPOINT,
	.bEndpointAddress = 0x01,
	.bmAttributes = USB_ENDPOINT_ATTR_BULK,
	.wMaxPacketSize = 64,
	.bInterval = 1,
}, {
	.bLength = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType = USB_DT_ENDPOINT,
	.bEndpointAddress = 0x82,
	.bmAttributes = USB_ENDPOINT_ATTR_BULK,
	.wMaxPacketSize = 64,
	.bInterval = 1,
}};
static const struct {
	struct usb_cdc_header_descriptor header;
	struct usb_cdc_call_management_descriptor call_mgmt;
	struct usb_cdc_acm_descriptor acm;
	struct usb_cdc_union_descriptor cdc_union;
} __attribute__((packed)) cdcacm_functional_descriptors = {
	.header = {
		.bFunctionLength = sizeof(struct usb_cdc_header_descriptor),
		.bDescriptorType = CS_INTERFACE,
		.bDescriptorSubtype = USB_CDC_TYPE_HEADER,
		.bcdCDC = 0x0110,
	},
	.call_mgmt = {
		.bFunctionLength = 
			sizeof(struct usb_cdc_call_management_descriptor),
		.bDescriptorType = CS_INTERFACE,
		.bDescriptorSubtype = USB_CDC_TYPE_CALL_MANAGEMENT,
		.bmCapabilities = 0,
		.bDataInterface = 1,
	},
	.acm = {
		.bFunctionLength = sizeof(struct usb_cdc_acm_descriptor),
		.bDescriptorType = CS_INTERFACE,
		.bDescriptorSubtype = USB_CDC_TYPE_ACM,
		.bmCapabilities = 0,
	},
	.cdc_union = {
		.bFunctionLength = sizeof(struct usb_cdc_union_descriptor),
		.bDescriptorType = CS_INTERFACE,
		.bDescriptorSubtype = USB_CDC_TYPE_UNION,
		.bControlInterface = 0,
		.bSubordinateInterface0 = 1, 
	 }
};
static const struct usb_interface_descriptor comm_iface[] = {{
	.bLength = USB_DT_INTERFACE_SIZE,
	.bDescriptorType = USB_DT_INTERFACE,
	.bInterfaceNumber = 1,
	.bAlternateSetting = 0,
	.bNumEndpoints = 1,
	.bInterfaceClass = USB_CLASS_CDC,
	.bInterfaceSubClass = USB_CDC_SUBCLASS_ACM,
	.bInterfaceProtocol = USB_CDC_PROTOCOL_AT,
	.iInterface = 0,

	.endpoint = comm_endp,

	.extra = &cdcacm_functional_descriptors,
	.extralen = sizeof(cdcacm_functional_descriptors)
}};

static const struct usb_interface_descriptor data_iface[] = {{
	.bLength = USB_DT_INTERFACE_SIZE,
	.bDescriptorType = USB_DT_INTERFACE,
	.bInterfaceNumber = 2,
	.bAlternateSetting = 0,
	.bNumEndpoints = 2,
	.bInterfaceClass = USB_CLASS_DATA,
	.bInterfaceSubClass = 0,
	.bInterfaceProtocol = 0,
	.iInterface = 0,

	.endpoint = data_endp,
}};

//usb hid stuffs
static const struct usb_endpoint_descriptor hid_endpoint = {
	.bLength = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType = USB_DT_ENDPOINT,
	.bEndpointAddress = 0x81,
	.bmAttributes = USB_ENDPOINT_ATTR_INTERRUPT,
	.wMaxPacketSize = 4,
	.bInterval = 0x20,
};
static const uint8_t hid_report_descriptor[] = {
	0x05, 0x01, /* USAGE_PAGE (Generic Desktop)         */
	0x09, 0x02, /* USAGE (Mouse)                        */
	0xa1, 0x01, /* COLLECTION (Application)             */
	0x09, 0x01, /*   USAGE (Pointer)                    */
	0xa1, 0x00, /*   COLLECTION (Physical)              */
	0x05, 0x09, /*     USAGE_PAGE (Button)              */
	0x19, 0x01, /*     USAGE_MINIMUM (Button 1)         */
	0x29, 0x03, /*     USAGE_MAXIMUM (Button 3)         */
	0x15, 0x00, /*     LOGICAL_MINIMUM (0)              */
	0x25, 0x01, /*     LOGICAL_MAXIMUM (1)              */
	0x95, 0x03, /*     REPORT_COUNT (3)                 */
	0x75, 0x01, /*     REPORT_SIZE (1)                  */
	0x81, 0x02, /*     INPUT (Data,Var,Abs)             */
	0x95, 0x01, /*     REPORT_COUNT (1)                 */
	0x75, 0x05, /*     REPORT_SIZE (5)                  */
	0x81, 0x01, /*     INPUT (Cnst,Ary,Abs)             */
	0x05, 0x01, /*     USAGE_PAGE (Generic Desktop)     */
	0x09, 0x30, /*     USAGE (X)                        */
	0x09, 0x31, /*     USAGE (Y)                        */
	0x09, 0x38, /*     USAGE (Wheel)                    */
	0x15, 0x81, /*     LOGICAL_MINIMUM (-127)           */
	0x25, 0x7f, /*     LOGICAL_MAXIMUM (127)            */
	0x75, 0x08, /*     REPORT_SIZE (8)                  */
	0x95, 0x03, /*     REPORT_COUNT (3)                 */
	0x81, 0x06, /*     INPUT (Data,Var,Rel)             */
	0xc0,       /*   END_COLLECTION                     */
	0x09, 0x3c, /*   USAGE (Motion Wakeup)              */
	0x05, 0xff, /*   USAGE_PAGE (Vendor Defined Page 1) */
	0x09, 0x01, /*   USAGE (Vendor Usage 1)             */
	0x15, 0x00, /*   LOGICAL_MINIMUM (0)                */
	0x25, 0x01, /*   LOGICAL_MAXIMUM (1)                */
	0x75, 0x01, /*   REPORT_SIZE (1)                    */
	0x95, 0x02, /*   REPORT_COUNT (2)                   */
	0xb1, 0x22, /*   FEATURE (Data,Var,Abs,NPrf)        */
	0x75, 0x06, /*   REPORT_SIZE (6)                    */
	0x95, 0x01, /*   REPORT_COUNT (1)                   */
	0xb1, 0x01, /*   FEATURE (Cnst,Ary,Abs)             */
	0xc0        /* END_COLLECTION                       */
};
static const struct {
	struct usb_hid_descriptor hid_descriptor;
	struct {
		uint8_t bReportDescriptorType;
		uint16_t wDescriptorLength;
	} __attribute__((packed)) hid_report;
} __attribute__((packed)) hid_function = {
	.hid_descriptor = {
		.bLength = sizeof(hid_function),
		.bDescriptorType = USB_DT_HID,
		.bcdHID = 0x0100,
		.bCountryCode = 0,
		.bNumDescriptors = 1,
	},
	.hid_report = {
		.bReportDescriptorType = USB_DT_REPORT,
		.wDescriptorLength = sizeof(hid_report_descriptor),
	}
};

static const struct usb_interface_descriptor hid_iface = {
	.bLength = USB_DT_INTERFACE_SIZE,
	.bDescriptorType = USB_DT_INTERFACE,
	.bInterfaceNumber = 0,
	.bAlternateSetting = 0,
	.bNumEndpoints = 1,
	.bInterfaceClass = USB_CLASS_HID,
	.bInterfaceSubClass = 0,
	.bInterfaceProtocol = 0,
	.iInterface = 0,
	.endpoint = &hid_endpoint,

	.extra = &hid_function,
	.extralen = sizeof(hid_function)
};
static const struct usb_interface ifaces[] = {
	{.num_altsetting = 1,
	.altsetting = &hid_iface},
	{.num_altsetting = 1,
	.altsetting = comm_iface},
	{.num_altsetting = 1,
	.altsetting = data_iface}
};
static const struct usb_config_descriptor conf_descriptor = {
	.bLength = USB_DT_CONFIGURATION_SIZE,
	.bDescriptorType = USB_DT_CONFIGURATION,
	.wTotalLength = 0,
	.bNumInterfaces = 2,
	.bConfigurationValue = 1,
	.iConfiguration = 0,
	.bmAttributes = 0xC0,
	.bMaxPower = 0x32,
	.interface = ifaces,
};
static const char * usb_strings[] = {
	"Steering wheel",
	"Hid device",
	"os",
};

static uint8_t usbd_control_buffer[128];

static enum usbd_request_return_codes hid_control_request(usbd_device * dev,
		struct usb_setup_data *req, uint8_t **buf, uint16_t *len,
		void (**complete)(usbd_device *dev, struct usb_setup_data *req))
{
	(void)complete;
	(void)dev;

	if((req->bmRequestType != 0x81) ||
			(req->bRequest != USB_REQ_GET_DESCRIPTOR) ||
			(req->wValue != 0x2200))
		return USBD_REQ_NOTSUPP;
	*buf = (uint8_t *)hid_report_descriptor;
	*len = sizeof(hid_report_descriptor);

	return USBD_REQ_HANDLED;
}

static enum usbd_request_return_codes cdcacm_control_request(usbd_device *usbd_dev, struct usb_setup_data *req, uint8_t **buf,
		uint16_t *len, void (**complete)(usbd_device *usbd_dev, struct usb_setup_data *req))
{
	(void)complete;
	(void)buf;
	(void)usbd_dev;

	switch(req->bRequest) {
	case USB_CDC_REQ_SET_CONTROL_LINE_STATE: {
		/*
		 * This Linux cdc_acm driver requires this to be implemented
		 * even though it's optional in the CDC spec, and we don't
		 * advertise it in the ACM functional descriptor.
		 */
		char local_buf[10];
		struct usb_cdc_notification *notif = (void *)local_buf;

		/* We echo signals back to host as notification. */
		notif->bmRequestType = 0xA1;
		notif->bNotification = USB_CDC_NOTIFY_SERIAL_STATE;
		notif->wValue = 0;
		notif->wIndex = 0;
		notif->wLength = 2;
		local_buf[8] = req->wValue & 3;
		local_buf[9] = 0;
		// usbd_ep_write_packet(0x83, buf, 10);
		return USBD_REQ_HANDLED;
		}
	case USB_CDC_REQ_SET_LINE_CODING: 
		if(*len < sizeof(struct usb_cdc_line_coding))
			return USBD_REQ_NOTSUPP;

		return USBD_REQ_HANDLED;
	}
	return USBD_REQ_NOTSUPP;
}

static void cdcacm_data_rx_cb(usbd_device *usbd_dev, uint8_t ep)
{
	(void)ep;

	char buf[64];
	int len = usbd_ep_read_packet(usbd_dev, 0x01, buf, 64);

	if (len) {
		usbd_ep_write_packet(usbd_dev, 0x82, buf, len);
	}
}

static void hid_set_config(usbd_device * dev, uint16_t wValue)
{
	(void)wValue;
	usbd_ep_setup(dev, 0x81, USB_ENDPOINT_ATTR_INTERRUPT, 4, NULL);
	usbd_register_control_callback(
			dev,
			USB_REQ_TYPE_STANDARD | USB_REQ_TYPE_INTERFACE,
			USB_REQ_TYPE_TYPE | USB_REQ_TYPE_RECIPIENT,
			hid_control_request
			);
	usbd_ep_setup(dev, 0x01, USB_ENDPOINT_ATTR_BULK, 64, cdcacm_data_rx_cb);
	usbd_ep_setup(dev, 0x82, USB_ENDPOINT_ATTR_BULK, 64, NULL);
	usbd_ep_setup(dev, 0x83, USB_ENDPOINT_ATTR_INTERRUPT, 16, NULL);
	usbd_register_control_callback(
				dev,
				USB_REQ_TYPE_CLASS | USB_REQ_TYPE_INTERFACE,
				USB_REQ_TYPE_TYPE | USB_REQ_TYPE_RECIPIENT,
				cdcacm_control_request);
}

void usb_init(void)
{
	rcc_periph_clock_enable(RCC_GPIOA);
	gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_2_MHZ,
			GPIO_CNF_OUTPUT_PUSHPULL, GPIO12);
	gpio_clear(GPIOA, GPIO12);
	for (unsigned i = 0; i < 800000; i++) { 
		__asm__("nop");
	}
	usbd_dev = usbd_init(&st_usbfs_v1_usb_driver, &dev_descriptor,
			&conf_descriptor, usb_strings, 3, usbd_control_buffer, 
			sizeof(usbd_control_buffer));
	usbd_register_set_config_callback(usbd_dev, hid_set_config);
}

void usb_poll(void)
{
	usbd_poll(usbd_dev);
}
