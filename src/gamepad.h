#ifndef GAMEPAD_H
#define GAMEPAD_H
#ifndef TEST
	#include<avr/pgmspace.h>
	#include"usbdrv.h"
#else
	#include"spy_usbdrv.h"
#endif
#include<stdint.h>
#include<stdlib.h>
#include"steering.h"
#include"throttle.h"
#include"brake.h"

void initGamepad(void);
void closeGamepad(void);
uint8_t *getPointerToReport(void);
void updateGamepad(void);

#endif // GAMEPAD_H
