#ifndef SPY_USBDRV
#define SPY_USBDRV
#include<stdbool.h>
#define USB_PUBLIC
#define PROGMEM 
typedef unsigned char uchar;
typedef unsigned char usbRequest_t;

//USB_PUBLIC uchar usbFunctionSetup(uchar data[8]);
typedef enum wtdflag {WDTO_1S}WTDFLAG;
void wdt_enable(WTDFLAG);
void usbInit(void);
void usbDeviceDisconnect(void);
void _delay_ms(unsigned long);
void usbDeviceConnect(void);
void sei(void);
void wdt_reset(void);
void usbPoll(void);
bool usbInterruptIsReady();
void usbSetInterrupt(void *, unsigned short);


#endif
