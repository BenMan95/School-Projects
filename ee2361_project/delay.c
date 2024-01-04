#include "xc.h"
#include "delay.h"

void delay_ms(unsigned int ms) {
    while (ms--) {
        asm("repeat #15998");
        asm("nop");
    }
}
