#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h> //delay header
#define LCD_DPRT PORTD //LCD DATA PORT
#define LCD_DDDR DDRD //LCD DATA DDR
#define LCD_CPRT PORTC //LCD COMMANDS PORT
#define LCD_CDDR DDRC //LCD COMMANDS DDR

#define LCD_RS 0
#define LCD_RW 6
#define LCD_EN 7


void lcdCommand( unsigned char cmnd )
{
	LCD_DPRT = cmnd;
	LCD_CPRT &= ~ ((1<<LCD_RS)|(1<<LCD_RW)); //RS = 0 RW = 0
	LCD_CPRT |= (1<<LCD_EN); //EN = 1
	_delay_us(100);
	LCD_CPRT &= ~ (1<<LCD_EN); //EN = 0 for H-to-L pulse
	_delay_us(100);
}
void lcdData( unsigned char data )
{
	LCD_DPRT = data; //send data
	LCD_CPRT &= ~ (1<<LCD_RW); //RW = 0 for write
	LCD_CPRT |= ((1<<LCD_RS)|(1<<LCD_EN)); //RS = 1 for data //EN = 1
	_delay_us(100);
	LCD_CPRT &= ~ (1<<LCD_EN); //EN = 0 for H-to-L pulse
	_delay_us(100);
}

void lcd_init()
{
	LCD_DDDR = 0xFF;
	LCD_CDDR = 0xFF;
	LCD_CPRT &=~(1<<LCD_EN); //LCD_EN = 0
	_delay_us(2000);
	lcdCommand(0x38); //init. LCD 2 line, 5 × 7 matrix
	lcdCommand(0x0E); //display on, cursor on
	lcdCommand(0x01); //clear LCD
	_delay_us(2000);
	lcdCommand(0x06); //shift cursor right
}
void lcd_print(char *str)
{
	
	unsigned int i=0;
	while(str[i]!='\0')
	{
		lcdData(str[i++]);
	}
}
int main(void)
{
	lcd_init();
	lcd_print("Welcome to KLE ");
	lcdCommand(0XC0);
	lcd_print("TECH");
	
	
	
	while(1);
}