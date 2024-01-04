#include <stdio.h>
#include <stdlib.h>
#include "xc.h"
#include "lcd.h"
#include "display.h"
#include "joystick.h"
#include "delay.h"
#include "game.h"

// CW1: FLASH CONFIGURATION WORD 1 (see PIC24 Family Reference Manual 24.1)
#pragma config ICS = PGx1          // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF        // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF          // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF           // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF        // JTAG Port Enable (JTAG port is disabled)


// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config I2C1SEL = PRI       // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF       // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON       // Primary Oscillator I/O Function (CLKO/RC15 functions as I/O pin)
#pragma config FCKSM = CSECME      // Clock Switching and Monitor (Clock switching is enabled, 
                                       // Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL      // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))

#define DEADZONE 0.5  // the size of the zone where joystick movements are not registered
#define SAFETIME 1    // the number of consecutive hits allowed before you lose
#define MQSIZE   2    // the size of the move queue

// if the game has ended, its value is -1
// otherwise, its value is the current number of consecutive collisions
volatile char status = 0;

// saves the current joystick cardinal direction
volatile char dirX = 0;
volatile char dirY = 0;

volatile char dir; // the current move direction
volatile char rollover = 0; // checks for rollovers on timer 2

static game_t *game; // the game being played

void display_game(game_t *gm) {
    // print score to LCD screen
    char str[9];
    sprintf(str,"Score:%2d",game_getScore(gm));
    lcd_setCursor(0,0);
    lcd_printStr(str);
    
    // display the game to the LED screen
    display_draw(game_getSnake(gm) | game_getFood(gm));
}

// determing the current joystick cardinal direction after each ADC reading
// if the joystick is in a diagonal direction, leave at previous direction
void __attribute__ ((interrupt,auto_psv)) _ADC1Interrupt(void) {
    _AD1IF = 0;
    
    double x = joystick_decX();
    double y = joystick_decY();
    
    if (x*x + y*y < DEADZONE) return;
    
    double ax = x < 0 ? -x : x;
    double ay = y < 0 ? -y : y;
    
         if (x > ay)  dir = -8;
    else if (x < -ay) dir = 8;
    else if (y > ax)  dir = -1;
    else if (y < -ax) dir = 1;
}

// pause/unpause the game on joystick clicks
void __attribute__((interrupt,auto_psv)) _IC1Interrupt() {
    _IC1IF = 0;
    if (rollover && PORTBbits.RB15) {
        if (T1CONbits.TON) {
            T1CONbits.TON = 0;
            lcd_setCursor(0,1);
            lcd_printStr("Paused");
        } else {
            if (status < 0) {
                game_init(game);
                display_game(game);
            }
            TMR1 = 0;
            T1CONbits.TON = 1;
            lcd_setCursor(0,1);
            lcd_printStr("        ");
            dir = 0;
        }
    }
    rollover = 0;
    TMR2 = 0;
}

// use timer 1 to do game actions
void __attribute__((interrupt,auto_psv)) _T1Interrupt() {
    _T1IF = 0;
    
    char result = game_step(game,dir); // get result of performing move
    
    // if it results in a collision
    if (result == 1) {
        if (status < SAFETIME) status++;
        else {
            T1CONbits.TON = 0;
            lcd_setCursor(0,1);
            lcd_printStr("You lose");
            status = -1;
        }
    } else status = 0;
    
    // if it results in a win
    if (result == 2) {
        T1CONbits.TON = 0;
        lcd_setCursor(0,1);
        lcd_printStr("You win!");
        status = -1;
    }
    
    display_game(game); // display the game
}

// use timer 2 to track rollovers for debouncing
void __attribute__((interrupt,auto_psv)) _T2Interrupt() {
    _T2IF = 0;
    rollover = 1;
}

void setup(void) {
    CLKDIVbits.RCDIV = 0;  //Set RCDIV=1:1 (default 2:1) 32MHz or FCY/2=16M
    AD1PCFG = 0x9fff;
    
    // initialize timer 1 for 250 ms
    T1CON = 0;
    TMR1 = 0;
    PR1 = 62499;
    T1CONbits.TCKPS = 0b10;
    T1CONbits.TON = 1;
    _T1IF = 0;
    _T1IE = 1;
    
    // initialize timer 2 for .01 seconds
    T2CON = 0;
    TMR2 = 0;
    PR2 = 19999;
    T2CONbits.TCKPS = 0b01;
    T2CONbits.TON = 1;
    _T2IF = 0;
    _T2IE = 1;
    
    display_init();
    display_setBrightness(0xF);
    display_setBlink(0);
    
    lcd_init();
    joystick_initMov();
    joystick_initClick();
    
    game = malloc(sizeof(game_t));
    game_init(game);
    display_game(game);
}

int main(void) {
    setup();
    while (1);
    return 0;
}
