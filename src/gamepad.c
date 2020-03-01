#include "gamepad.h"

const char usbHidReportDescriptor[] PROGMEM = {
0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
0x09, 0x04,        // Usage (Joystick)
0xA1, 0x01,        // Collection (Application)
0x05, 0x02,        //   Usage Page (Sim Ctrls)
0x09, 0xC8,        //   Usage (Steering)
0x15, 0x00,        //   Logical Minimum (0)
0x26, 0x00, 0x01,  //   Logical Maximum (256)
0x75, 0x08,        //   Report Size (8)
0x95, 0x01,        //   Report Count (1)
0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
0x05, 0x01,        //   Usage Page (Generic Desktop Ctrls)
0x09, 0x01,        //   Usage (Pointer)
0xA1, 0x00,        //   Collection (Physical)
0x09, 0x30,        //     Usage (X)
0x15, 0x00,        //     Logical Minimum (0)
0x26, 0x00, 0x01,  //     Logical Maximum (256)
0x75, 0x08,        //     Report Size (8)
0x95, 0x01,        //     Report Count (1)
0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
0xC0,              //   End Collection
0xC0,              // End Collection

// 42 bytes
};
uint8_t report[8];
void initGamepad(void)
{
	initSteering();
}
void closeGamepad(void)
{
	closeSteering();
}

uint8_t *getPointerToReport(void)
{
	return report;
}

void updateGamepad(void)
{
	report[0] = getSteeringValue();
	report[1] = 127;
}
