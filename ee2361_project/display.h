#ifndef DISPLAY_H
#define	DISPLAY_H

#ifdef	__cplusplus
extern "C" {
#endif

    void display_init(void); // initialize display
    void display_setBrightness(char dim); // set brightness level (0-15)
    void display_setBlink(char blink); // set blinking (0-3)
    void display_draw(long long bits); // draw the given pixels to the display
    long long display_toPixel(char x,char y); // converts coords to a pixel
    
#ifdef	__cplusplus
}
#endif

#endif
