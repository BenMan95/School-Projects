#include "xc.h"
#include "joystick.h"

// Configures analog input for pins RA0 and RA1
void joystick_initMov(void) {
    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA1 = 1;
    AD1PCFGbits.PCFG0 = 0;
    AD1PCFGbits.PCFG1 = 0;
    
    AD1CON2bits.ALTS = 0;
    AD1CON2bits.CSCNA = 1;
    AD1CON2bits.BUFM = 0;
    AD1CHSbits.CH0NA = 0;
    
    AD1CSSLbits.CSSL0 = 1;
    AD1CSSLbits.CSSL1 = 1;
    
    AD1CON2bits.VCFG = 0b000;
    AD1CON3bits.ADCS = 0b00000001;
    AD1CON1bits.SSRC = 0b010;
    AD1CON3bits.SAMC = 0b00001;
    AD1CON1bits.FORM = 0b00;
    
    AD1CON1bits.ASAM = 0b1;
    AD1CON2bits.SMPI = 0b0001;
    AD1CON1bits.ADON = 1;
    
    _AD1IF = 0;
    _AD1IE = 1;
    
    T3CONbits.TSIDL = 0;
    
    TMR3 = 0;
    T3CON = 0;
    T3CONbits.TCKPS = 0b01;
    PR3 = 15624;
    T3CONbits.TON = 1;
}

// Configure clicking input capture for pin RB15
void joystick_initClick(void) {
    // set input capture pin
    __builtin_write_OSCCONL(OSCCON & 0xbf);
    RPINR7bits.IC1R = 15;
    __builtin_write_OSCCONL(OSCCON | 0x40);
    
    // configure pins
    CNPU1bits.CN11PUE = 1;
    TRISBbits.TRISB15 = 1;
    
    // configure input capture
    IC1CON = 0;
    IC1CONbits.ICM = 0b001;
    IC1CONbits.ICTMR = 1;
    IFS0bits.T2IF = 0;
    IEC0bits.IC1IE = 1;
}

int joystick_intX(void) {
    return ADC1BUF0;
}

int joystick_intY(void) {
    return 1023-ADC1BUF1;
}

double joystick_decX(void) {
    return 2.0*joystick_intX()/1023-1;
}

double joystick_decY(void) {
    return 2.0*joystick_intY()/1023-1;
}