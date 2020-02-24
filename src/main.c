#include "main.h"

USB_PUBLIC uchar usbFunctionSetup(uchar data[8]) {
	return 0; // do nothing for now
}
#ifndef TEST
int main(void)
{
	return mainApp();
}
#endif
int mainApp(void) {
	uchar i;

    wdt_enable(WDTO_1S); // enable 1s watchdog timer

    usbInit();
	
    usbDeviceDisconnect(); // enforce re-enumeration
    for(i = 0; i<250; i++) { // wait 500 ms
        wdt_reset(); // keep the watchdog happy
        _delay_ms(2);
    }
    usbDeviceConnect();
	
    sei(); // Enable interrupts after re-enumeration
	
	LOOP{
        wdt_reset(); // keep the watchdog happy
        usbPoll();
    }
	
    return 0;
}
