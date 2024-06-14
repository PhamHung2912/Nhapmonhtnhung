#include "systick_time.h"
#include "lcd_1602_drive.h"
#include "mpu6050.h"
#include "stdio.h"


int16_t Accel_X_RAW = 0;
int16_t Accel_Y_RAW = 0;
int16_t Accel_Z_RAW = 0;

int16_t Gyro_X_RAW = 0;
int16_t Gyro_Y_RAW = 0;
int16_t Gyro_Z_RAW = 0;
float Ax=0, Ay, Az, Gx, Gy, Gz;

uint8_t sw= 0;
uint8_t mode=0;
uint8_t on=0;

void check(void);
void ledxanh(uint16_t bat);
void leddo(uint16_t bat);
void hienthi(uint8_t m, uint8_t o);

void ledxanh(uint16_t bat)
{
		if( bat == 1) GPIOB->ODR |= 1;
		else GPIOB->ODR &= ~1;
}

void leddo(uint16_t bat)
{
	if( bat == 1) GPIOB->ODR |= (1<<1);
		else GPIOB->ODR &= ~(1<<1);

}

void accel()
{
	uint8_t Rx_data[6];
	mpu6050_accel(1,Rx_data);
	
	Accel_X_RAW = (int16_t)(Rx_data[0] << 8 | Rx_data [1]);
	Accel_Y_RAW = (int16_t)(Rx_data[2] << 8 | Rx_data [3]);
	Accel_Z_RAW = (int16_t)(Rx_data[4] << 8 | Rx_data [5]);
	
	Ax = Accel_X_RAW/16384.0;
	Ay = Accel_Y_RAW/16384.0;
	Az = Accel_Z_RAW/16384.0;
}

void gyro()
{
	uint8_t Rx_data[6];
	mpu6050_gyro(1,Rx_data);
	
	Gyro_X_RAW = (int16_t)(Rx_data[0] << 8 | Rx_data [1]);
	Gyro_Y_RAW = (int16_t)(Rx_data[2] << 8 | Rx_data [3]);
	Gyro_Z_RAW = (int16_t)(Rx_data[4] << 8 | Rx_data [5]);

	Gx = Gyro_X_RAW/131.0;
	Gy = Gyro_Y_RAW/131.0;
	Gz = Gyro_Z_RAW/131.0;
}	


int main(void)
{
		systick_init();
	lcd_i2c_init(2);
	mpu6050_init(1);
	
	RCC->APB2ENR |= (1<<2); 
	RCC->APB2ENR |= (1<<3);
	RCC->APB2ENR |= (1<<4);
	
	
	GPIOA->CRL &= ~(( 1<<0) | (1<<1)| (1<<2)) ;
	GPIOA->CRL |= (1<<3);
		
	GPIOA->CRL &= ~(( 1<<4) | (1<<5)| (1<<6)) ; 
	GPIOA->CRL |= (1<<7);
	
	GPIOB->CRL &= ~((1 << 2)| (1 << 3)) ;
	GPIOB->CRL |= ( 1<<1) | (1<<0);
	
	GPIOB->CRL &= ~((1<<6)|(1<<7));
	GPIOB->CRL |= (1<<5)| (1<<4);
	
	
	GPIOA->CRL &= ~(( 1<<8) | (1<<9)| (1<<10)) ;
	GPIOA->CRL |= (1<<11);
	

		__disable_irq();
	
	AFIO->EXTICR[0] &= ~(0xff); 
	
	EXTI->IMR |= (1<<0);
	EXTI->IMR |= (1<<1);

	EXTI->RTSR |=(1<<0); 
	EXTI->RTSR |= (1<<1);
	
	NVIC_EnableIRQ(EXTI0_IRQn); 
	NVIC_EnableIRQ (EXTI1_IRQn);
	
		__enable_irq();
		
	while(1)
	{
		hienthi(mode,on);



	}
	
}
void EXTI0_IRQHandler() 
{
	EXTI->PR |=1;
	if (on) on = 0;
	else on = 1;
	DelayMs(50);
}

void EXTI1_IRQHandler() 
{
	
	EXTI->PR |= (1<<1);
	if (mode) mode=0;
	DelayMs(50);

}
void hien1()
{
			ledxanh(1);
			leddo(1);
			DelayMs(500);
			leddo(0);
			DelayMs(500);
			ledxanh(0);
			leddo(1);
			DelayMs(500);
			leddo(0);
			DelayMs(500);	
}

void hienthi(uint8_t m, uint8_t o)
{
	if ( on == 1)
		{
			if ( mode == 1)
			{	
				lcd_blank_12(2);
				lcd_i2c_msg(2,0,0, "1");
				hien1();
			}
			else
			{
				lcd_blank_12(2);
				lcd_i2c_msg(2,0,0, "0");
				ledxanh(1);
				check();
				ledxanh(0);
				check();
			}
		}
		else
		{	
			lcd_blank_12(2);
			ledxanh(0);		
			leddo(0);
			
		}
}

void check()
{
	uint8_t i = 0;
	while ((i<50)&&(mode!=0))
	{ 	
		float fallcheck=6.5;
		accel();
		float paccel = Ax*Ax + Ay*Ay + Az*Az;
		if( paccel > fallcheck) mode= 1;	
		DelayMs(5);
		i++;
	}
	
}