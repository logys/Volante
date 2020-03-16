#include "main.h"

#ifndef TEST
int main(void)
{
	return mainApp();
}
#endif
int mainApp(void) {
	//uchar i;

    //wdt_enable(WDTO_1S); // enable 1s watchdog timer

    usbInit();
	
    //usbDeviceDisconnect(); // enforce re-enumeration
    //for(i = 0; i<250; i++) { // wait 500 ms
        //wdt_reset(); // keep the watchdog happy
      //  _delay_ms(2);
    //}
    //usbDeviceConnect();
	
    sei(); // Enable interrupts after re-enumeration
    initGamepad();
	LOOP{
      //  wdt_reset(); // keep the watchdog happy
        usbPoll();
	updateGamepad();
	if(usbInterruptIsReady()){
		usbSetInterrupt((unsigned char *)getPointerToReport(), 4);
	}
    }
	
    return 0;
}

uint8_t usbFunctionSetup( uint8_t data [8] )
{
/*
	usbRequest_t const* rq = (usbRequest_t const*) data;

	if ( (rq->bmRequestType & USBRQ_TYPE_MASK) != USBRQ_TYPE_CLASS )
		return 0;
	
	switch ( rq->bRequest )
	{
	case USBRQ_HID_GET_REPORT: // HID joystick only has to handle this

		return 0;//getPad(&usbMsgPtr);
	
	//case USBRQ_HID_SET_REPORT: // LEDs on joystick?
	
	default:
		return 0;
	}*/
}
