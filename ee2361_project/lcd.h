#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    void lcd_init(void);
    void lcd_cmd(char cmd);
    void lcd_setCursor(char x,char y);
    void lcd_printChar(char ch);
    void lcd_printStr(char *str);
    
#ifdef	__cplusplus
}
#endif

#endif
