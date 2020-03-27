#ifndef PCINT0_H
#define PCINT0_H

#define ISR(interrupt) void interrupt(void)
#define sei() 

uint8_t PCICR;
#define PCIE0 0

uint8_t PCMSK0;
#define PCINT0 0

ISR(PCINT0_vect);
#endif
