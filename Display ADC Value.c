#include<p18f4580.h>
void lcd_ini();
void lcd_data(char);
void lcd_com(char);
void lcd_str(const rom char *str);
void Delay(int);

#define rs PORTCbits.RC0
#define e PORTCbits.RC1

void main()
{
	int temp, i;
	int data[4];

	TRISD = 0x00;
	TRISCbits.RC0 = 0;
	TRISCbits.RC1 = 0;
	ADCON0 = 0x03;
	ADCON1 = 0x0e;
	ADCON2 = 0x88;

	lcd_ini();
	lcd_str("ADC Value : ");
	while(1)
	{
		lcd_com(0xc0);
		ADCON0bits.GO = 1;
		while(ADCON0bits.GO==1);

		temp = ADRESH;
		temp = (temp<<8) + ADRESL;

		for(i=0 ; i<4 ;i++)
		{
			data[i]=temp%10+'0';
			temp = temp/10;
		}
		for(i=3 ; i>=0 ; i--)	lcd_data(data[i]);
	}

}

void lcd_str(const rom char *str)
{
	while(*str !='\0')
	{
		lcd_data(*str);
		str++;
	}
}

void lcd_ini()
{
	lcd_com(0x0e); //lcd on , cursor on
	lcd_com(0x01); //clear screen
	lcd_com(0x06); //inc cursor
	lcd_com(0x38); //2 line, 5x7 matrix
	lcd_com(0x80); //1st row, 1st position
}
void lcd_com(char cm)
{
	rs=0;
	PORTD = cm;
	e=1;
	Delay(10);
	e=0;
	Delay(10);
}
void lcd_data(char dt)
{
	rs=1;
	PORTD = dt;
	e=1;
	Delay(100);
	e=0;
	Delay(10);
}
void Delay(int a)
{
	int i, j;
	for(i=0; i<a; i++)
		for(j=0; j<a; j++);
}