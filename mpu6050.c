#include "mpu6050.h"


void mpu6050_add(char i2c, char R_W)
{
	i2c_add(i2c,0x68 << 1,R_W);
}



void mpu6050_tx(char i2c,char reg,char data)
{
	i2c_start(i2c);
	mpu6050_add(i2c,0);
	i2c_data(i2c,reg);
	i2c_data(i2c,data);
	i2c_stop(i2c);
}

void mpu6050_rx(char i2c,char reg,char * str,char data_len)
{
	int i;
	i2c_start(i2c);
	mpu6050_add(i2c,0);
	i2c_data(i2c,reg);
	
	i2c_start(i2c);
	mpu6050_add(i2c,1);
	
	for(i=0;i<(data_len-1);i++)
	{
		str[i] = i2c_rx(i2c,ACK);
	}
	str[i] = i2c_rx(i2c,NACK);
	
	i2c_stop(i2c);

}


void mpu6050_init(char i2c)
{
	systick_init();
	i2c_init(i2c,i2c_FM);
	
	uint8_t check;
	if (check == 0x68)  
	{ 
	 mpu6050_rx(i2c,0x75, &check, 1);
	 mpu6050_tx(i2c, PWR_MGMT_1_REG, 0x01);    
   mpu6050_tx(i2c, SMPLRT_DIV_REG, 0x00);    
   mpu6050_tx(i2c, MPU_CONFIG_REG, 0x00);    
   mpu6050_tx(i2c, GYRO_CONFIG_REG, 0x08);   
   mpu6050_tx(i2c, ACCEL_CONFIG_REG, 0x00); 
	}
	
}




void mpu6050_accel(char i2c,uint8_t * Rx_data )
{

	
	
	mpu6050_rx(i2c,0x3B,Rx_data,6);
	
	
	
	
	
}

void mpu6050_gyro(char i2c,uint8_t * Rx_data)
{
		
	mpu6050_rx(i2c,0x43,Rx_data,6);
	
	
}

