#include "lcd_1602_drive.h"



void lcd_i2c_data(char i2c,unsigned char data)
{
	

	PCF8574_tx_byte(i2c,0x09);
	DelayUs(10);
	PCF8574_tx_byte(i2c,0x0D);
	DelayUs(5);
	PCF8574_tx_byte(i2c, ((data & 0x00f0) | 0x0D));
	DelayUs(10);
	PCF8574_tx_byte(i2c, ((data & 0x00f0) | 0x09));
	DelayUs(20);
	PCF8574_tx_byte(i2c,0x0D);
	DelayUs(5);
	PCF8574_tx_byte(i2c, (((data << 4) & 0x00f0) | 0x0D));
	DelayUs(10);

	PCF8574_tx_byte(i2c, (((data << 4) & 0x00f0) | 0x09));
}

void lcd_i2c_cmd(char i2c,unsigned char data)
{
	PCF8574_tx_byte(i2c,0x08);
	DelayUs(10);
	PCF8574_tx_byte(i2c,0x0C);
	DelayUs(5);
	PCF8574_tx_byte(i2c, ((data & 0x00f0) | 0x0C));
	DelayUs(10);
	PCF8574_tx_byte(i2c, ((data & 0x00f0) | 0x08));
	DelayUs(20);
	PCF8574_tx_byte(i2c,0x0C);
	DelayUs(5);
	PCF8574_tx_byte(i2c, (((data << 4) & 0x00f0) | 0x0C));
	DelayUs(10);
	PCF8574_tx_byte(i2c, (((data << 4) & 0x00f0) | 0x08));
}


void lcd_i2c_init(char i2c)
{
  i2c_init(i2c, i2c_FM);
	DelayMs(20);

	PCF8574_tx_byte(i2c,0x08);
	DelayUs(10);

	PCF8574_tx_byte(i2c,0x0C);
	DelayUs(5);
	PCF8574_tx_byte(i2c,0x3C);
	DelayUs(10);
	PCF8574_tx_byte(i2c,0x38);
	
	DelayMs(10);
	
	PCF8574_tx_byte(i2c,0x08);
	DelayUs(10);
	PCF8574_tx_byte(i2c,0x0C);
	DelayUs(5);
	PCF8574_tx_byte(i2c,0x3C);
	DelayUs(10);
	PCF8574_tx_byte(i2c,0x38);	
	DelayMs(1);
	PCF8574_tx_byte(i2c,0x08);
	DelayUs(10);
	PCF8574_tx_byte(i2c,0x0C);
	DelayUs(5);
	PCF8574_tx_byte(i2c,0x3C);
	DelayUs(10);
	PCF8574_tx_byte(i2c,0x38);
	DelayMs(1);
	PCF8574_tx_byte(i2c,0x08);
	DelayUs(10);
	PCF8574_tx_byte(i2c,0x0C);
	DelayUs(5);
	PCF8574_tx_byte(i2c,0x2C);
	DelayUs(10);
	PCF8574_tx_byte(i2c,0x28);
	lcd_i2c_cmd(i2c,0x2C);
	DelayMs(5);
	lcd_i2c_cmd(i2c,0x0C); 
	DelayMs(5);
	lcd_i2c_cmd(i2c,0x01); 
	DelayMs(5);
	lcd_i2c_cmd(i2c,0x02); 
	DelayMs(5);
}
void lcd_i2c_send(char i2c, char str[])
{
	int i = 0;
		while(str[i])
		{
			lcd_i2c_data(i2c,str[i]);
			i++;
			DelayUs(100);
		}
}
void lcd_i2c_msg(char i2c,unsigned char line_1_2, unsigned char pos_0_16, char msg[])
{
	short pos = 0;
	if(line_1_2==1)
	{
		pos = 0;
	}
	else if(line_1_2==2)
	{
		pos = 0x40;
	}
	lcd_i2c_cmd(i2c,0x80 +pos + pos_0_16);
	DelayUs(100);
	lcd_i2c_send(i2c,msg);
}
void lcd_blank_1(char i2c)
{
	lcd_i2c_msg(i2c,1, 0, "                ");
}
void lcd_blank_2(char i2c)
{
	lcd_i2c_msg(i2c,2, 0, "                ");
}
void lcd_blank_12(char i2c)
{
	lcd_blank_1(i2c);
	lcd_blank_2(i2c);
}
