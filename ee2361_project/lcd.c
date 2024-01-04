#include "xc.h"
#include "lcd.h"
#include "delay.h"

#define ADDRESS 0b01111100;

#define contrast 0b0000

void lcd_init(void) {
    I2C2BRG = 157;
    IFS3bits.MI2C2IF = 0;
    I2C2CONbits.I2CEN = 1;
    
    delay_ms(40);
    lcd_cmd(0b00111000); // function set, normal instruction mode
    lcd_cmd(0b00111001); // function set, extended instruction mode
    lcd_cmd(0b00010100); // interval osc
    lcd_cmd(0b01110000 | contrast); // contrast C3-C0
    lcd_cmd(0b01010110); // Ion, Bon, C5-C4
    lcd_cmd(0b01101100); // follower control
    delay_ms(200);
    lcd_cmd(0b00111000); // function set, normal instruction mode
    lcd_cmd(0b00001100); // Display On
    lcd_cmd(0b00000001); // Clear Display
    delay_ms(1);
}

void lcd_cmd(char cmd) {
    I2C2CONbits.SEN = 1;        // start
    while (I2C2CONbits.SEN);    // wait for SEN to clear
    IFS3bits.MI2C2IF = 0;       // clear interrupt flag
    
    I2C2TRN = ADDRESS;       // send slave address and R/nW bit
    while (!IFS3bits.MI2C2IF);  // wait for ACK
    IFS3bits.MI2C2IF = 0;
    
    I2C2TRN = 0b00000000;       // send control byte
    while (!IFS3bits.MI2C2IF);  // wait for ACK
    IFS3bits.MI2C2IF = 0;
    
    I2C2TRN = cmd;              // send command
    while (!IFS3bits.MI2C2IF);  // wait for ACK
    IFS3bits.MI2C2IF = 0;
    
    I2C2CONbits.PEN = 1;        // end
    while (I2C2CONbits.PEN);    // wait for PEN to clear
}

void lcd_setCursor(char x,char y) {
    y <<= 6;
    lcd_cmd(0x80 | x | y);
}

void lcd_printChar(char ch) {
    I2C2CONbits.SEN = 1;        // start
    while (I2C2CONbits.SEN);    // wait for SEN to clear
    IFS3bits.MI2C2IF = 0;       // clear interrupt flag
    
    I2C2TRN = 0b01111100;       // send slave address and R/nW bit
    while (!IFS3bits.MI2C2IF);  // wait for ACK
    IFS3bits.MI2C2IF = 0;
    
    I2C2TRN = ADDRESS;       // send control byte
    while (!IFS3bits.MI2C2IF);  // wait for ACK
    IFS3bits.MI2C2IF = 0;
    
    I2C2TRN = ch;               // send char
    while (!IFS3bits.MI2C2IF);  // wait for ACK
    IFS3bits.MI2C2IF = 0;
    
    I2C2CONbits.PEN = 1;        // end
    while (I2C2CONbits.PEN);    // wait for PEN to clear
}

void lcd_printStr(char *str) {
    I2C2CONbits.SEN = 1;        // start
    while (I2C2CONbits.SEN);    // wait for SEN to clear
    IFS3bits.MI2C2IF = 0;       // clear interrupt flag
    
    I2C2TRN = ADDRESS;       // send slave address and R/nW bit
    while (!IFS3bits.MI2C2IF);  // wait for ACK
    IFS3bits.MI2C2IF = 0;
    
    char next;
    while ((next = *str++)) { // until null terminator reached

        I2C2TRN = *str?0b11000000
                      :0b01000000;  // send control byte
        while (!IFS3bits.MI2C2IF);  // wait for ACK
        IFS3bits.MI2C2IF = 0;
        
        I2C2TRN = next;             // send char
        while (!IFS3bits.MI2C2IF);  // wait for ACK
        IFS3bits.MI2C2IF = 0;
    }
    
    I2C2CONbits.PEN = 1;        // end
    while (I2C2CONbits.PEN);    // wait for PEN to clear
}
