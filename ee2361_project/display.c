#include "xc.h"
#include "display.h"

#define ADDRESS 0b11100000;

void display_cmd(char cmd) {
    I2C1CONbits.SEN = 1;
    while (I2C1CONbits.SEN);
    IFS1bits.MI2C1IF = 0;
    
    I2C1TRN = ADDRESS;
    while (!IFS1bits.MI2C1IF);
    IFS1bits.MI2C1IF = 0;
    
    I2C1TRN = cmd;
    while (!IFS1bits.MI2C1IF);
    IFS1bits.MI2C1IF = 0;
    
    I2C1TRN = 0;
    while (!IFS1bits.MI2C1IF);
    IFS1bits.MI2C1IF = 0;
    
    I2C1CONbits.PEN = 1;
    while (I2C1CONbits.PEN);
}

void display_init(void) {
    I2C1BRG = 157;         // set baud rate
    IFS1bits.MI2C1IF = 0;  // set interrupt flag
    I2C1CONbits.I2CEN = 1; // enable i2c
    
    display_cmd(0x21); // internal system clock enable
}

void display_setBrightness(char dim) {
    dim &= 0xF;
    display_cmd(0xE0 | dim);
}

void display_setBlink(char blink) {
    blink &= 0x3;
    display_cmd(0x81 | (blink << 1));
}

void display_draw(long long bits) {
    I2C1CONbits.SEN = 1;
    while (I2C1CONbits.SEN);
    IFS1bits.MI2C1IF = 0;
    
    I2C1TRN = ADDRESS;
    while (!IFS1bits.MI2C1IF);
    IFS1bits.MI2C1IF = 0;
    
    I2C1TRN = 0;
    while (!IFS1bits.MI2C1IF);
    IFS1bits.MI2C1IF = 0;
    
    int i = 8;
    while (i--) {
        unsigned char row = (char) bits;
        
        I2C1TRN = (row << 7) | (row >> 1);
        while (!IFS1bits.MI2C1IF);
        IFS1bits.MI2C1IF = 0;
        
        I2C1TRN = 0;
        while (!IFS1bits.MI2C1IF);
        IFS1bits.MI2C1IF = 0;
        
        bits >>= 8;
    }
    
    I2C1CONbits.PEN = 1;
    while (I2C1CONbits.PEN);
}

long long display_toPixel(char x,char y) {
    x = 7-x;
    y = 7-y;
    return 1LL << (8*x + y);
}