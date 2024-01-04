#ifndef JOYSTICK_H
#define	JOYSTICK_H

#ifdef	__cplusplus
extern "C" {
#endif

    void joystick_initMov(void); // initialize joystick movement
    void joystick_initClick(void); // initialize joystick clicking
    int joystick_intX(void); // get X input as an int from [0,1023]
    int joystick_intY(void); // get Y input as an int from [0,1023]
    double joystick_decX(void); // get X input as a decimal in [-1.0,1.0]
    double joystick_decY(void); // get Y input as a decimal in [-1.0,1.0]
    
#ifdef	__cplusplus
}
#endif

#endif
