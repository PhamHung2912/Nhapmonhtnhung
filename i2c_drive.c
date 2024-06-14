#include "i2c_drive.h"


void i2c_init(char i2c,unsigned short speed_mode)
{
	 
		
	RCC->APB2ENR |= 1; 
	
	if(i2c==1)
	{


    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
		GPIOB->CRL &= ~(GPIO_CRL_MODE6 | GPIO_CRL_MODE7);
    GPIOB->CRL |= GPIO_CRL_MODE6_1 | GPIO_CRL_MODE7_1;
    GPIOB->CRL |= GPIO_CRL_CNF6_1 | GPIO_CRL_CNF7_1;
		GPIOB->ODR |= ((1<<6 | 1<<7)); 
		
		I2C1->CR1 |= 0x8000;
		I2C1->CR1 &= ~0x8000;
		I2C1->CR2 =0x8;
		I2C1->CCR = speed_mode;
		I2C1->TRISE = 0x9;
		I2C1->CR1 |= 1;
	}
	else if(i2c==2)
	{

    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
		I2C2->CR1 |= 0x8000;
		I2C2->CR1 &= ~0x8000;
		I2C2->CR2 =0x8;
		I2C2->CCR = speed_mode;
		I2C2->TRISE = 0x9;
		I2C2->CR1 |= 1;
	}

}

void i2c_start(char i2c)
{
	if(i2c==1)
	{
		I2C1->CR1 |= 0x100;
		while (!(I2C1->SR1 & 1)){};
	}
	else if(i2c==2)
	{
		I2C2->CR1 |= 0x100;
		while (!(I2C2->SR1 & 1)){};
	}
}

void i2c_add(char i2c, char address,char RW)
{
	volatile int tmp;
	if(i2c==1)
	{
		I2C1->DR = (address|RW);
		while((I2C1->SR1 & 2)==0){};
		while((I2C1->SR1 & 2)){
			tmp = I2C1->SR1;
			tmp = I2C1->SR2;
			if((I2C1->SR1 & 2)==0)
			{
				break;
			}
		}
	}
	else if(i2c==2)
	{
		I2C2->DR = (address|RW);
		while((I2C2->SR1 & 2)==0){};
		while((I2C2->SR1 & 2)){
			tmp = I2C2->SR1;
			tmp = I2C2->SR2;
			if((I2C2->SR1 & 2)==0)
			{
				break;
			}
		}
	}

}

void i2c_data(char i2c,char data)
{
	if(i2c==1)
	{
		while((I2C1->SR1 & 0x80) == 0){}
			I2C1->DR = data;
		while((I2C1->SR1 & 0x80) == 0){}
	}
	else if(i2c==2)
	{
		while((I2C2->SR1 & 0x80) == 0){}
			I2C2->DR = data;
		while((I2C2->SR1 & 0x80) == 0){}
	}
}

void i2c_stop(char i2c)
{
	volatile int tmp;
	if(i2c==1)
	{
		tmp = I2C1->SR1;
		tmp = I2C1->SR2;
		I2C1->CR1 |= 0x200;
	}
	else if(i2c==2)
	{
		tmp = I2C2->SR1;
		tmp = I2C2->SR2;
		I2C2->CR1 |= 0x200;
	}
}

void i2c_write(char i2c, char address,char data[])
{
	int i = 0;
	
	i2c_start(i2c);
	
	i2c_add(i2c, address,0);
	
	while(data[i])
		{
			i2c_data(i2c,data[i]);
			i++;
		}
	i2c_stop(i2c);
}

char i2c_rx(char i2c, char ACK_NACK)
{
	char temp;
	if(i2c==1)
	{
		I2C1->CR1 |= 0x0400;
		while((I2C1->SR1 & 0x40)==0){}
			temp = I2C1->DR;
		if(ACK_NACK)
		{
			I2C1->CR1 &= ~0x0400;
		}
		
	}
	else if(i2c==2)
	{
		I2C2->CR1 |= 0x0400;
		while((I2C2->SR1 & 0x40)==0){}
			temp = I2C2->DR;
		if(ACK_NACK)
		{
			I2C2->CR1 &= ~0x0400;
		}
		
	}
	return temp;
}
