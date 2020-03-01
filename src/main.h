#ifndef MAIN_H
#define MAIN_H
#ifndef TEST
	#include "usbdrv.h"
	#include <avr/io.h>
	#include <avr/interrupt.h>
	#include <avr/wdt.h>
	#include <util/delay.h>
	#define LOOP while(1)
#else
	#define LOOP
	#include "spy_usbdrv.h"
#endif

#include<stdint.h>
#include"gamepad.h"

int main(void);
int mainApp(void);

#endif // MAIN_H
