#include "i2c_drive.h"
#include "systick_time.h"

#define ACK 0
#define NACK 1

#define Yaw 0
#define Roll 1
#define Pitch 2

#define PWR_MGMT_1_REG        0x6b
#define SMPLRT_DIV_REG        0x19
#define ACCEL_CONFIG_REG      0x1c
#define GYRO_CONFIG_REG       0x1b
#define MPU_CONFIG_REG        0x1a





void mpu6050_init(char i2c);
void mpu6050_accel(char i2c,uint8_t * Rx_data );
void mpu6050_gyro(char i2c,uint8_t * Rx_data);