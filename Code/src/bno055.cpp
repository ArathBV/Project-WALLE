/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : bno055.h
  * @brief          : File containing the functions to the BNO055 IMU class
  * @author Arath Villanueva (abvillan@calpoly.edu) Devon Bolt (dwbolt@calpoly.edu)
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#include "bno055.h"

#define OPR_MODE_ADDR     0x3D
#define EULER_H_LSB       0x1A
#define UNIT_SEL_ADDR     0x3B
#define SYS_TRIGGER_ADDR  0x3F
#define PWR_MODE_ADDR     0x3E
#define PAGE_ID_ADDR      0x07
#define CALIB_STAT        0x35
#define GYRO_DATA_LSB     0x14


/**
 * @brief Constructor Function to initialize the BNO055 Class
 */
BNO055::BNO055(I2C_HandleTypeDef* hi2c, uint8_t addr)
    : hi2c(hi2c), addr(addr << 1){}


/**
 * @brief Function handles the configuration and initialization of the BNO055 IMU
 * @param mode Parameter for determining what mode to operate the IMU at see REG modes
 * @return Boolean
 */
bool BNO055::init_imu(REG mode) {
    HAL_Delay(650);
    writeByte(OPR_MODE_ADDR, static_cast<uint8_t>(REG::CONFIG_MODE));
    HAL_Delay(20);

    writeByte(SYS_TRIGGER_ADDR, 0x00);
    writeByte(PWR_MODE_ADDR, 0x00);
    HAL_Delay(10);

    writeByte(PAGE_ID_ADDR, 0);
    writeByte(UNIT_SEL_ADDR, 0x00);

    writeByte(OPR_MODE_ADDR, static_cast<uint8_t>(mode));
    HAL_Delay(20);
    return true;
}

/**
 * @brief Function Updates the Euler values based on the IMU's current readings. Roll
 * Pitch, and Yaw are updated within the class.
 * @return Boolean
 */
bool BNO055::updateEuler() {
    uint8_t buffer[6];
    if (!readLen(EULER_H_LSB, buffer, 6))
    	return false;

    int16_t rawYaw   = (int16_t)((buffer[1] << 8) | buffer[0]);
    int16_t rawRoll  = (int16_t)((buffer[3] << 8) | buffer[2]);
    int16_t rawPitch = (int16_t)((buffer[5] << 8) | buffer[4]);

    yaw   = rawYaw / 16.0f;
    roll  = rawRoll / 16.0f;
    pitch = rawPitch / 16.0f;
    return true;
}

/** 
 * @brief Function pull they data from the gyroscope retrieving angular velocities.
 * @return Boolean
 */
bool BNO055::updateGyro() {
    uint8_t buffer[6];
    if (!readLen(GYRO_DATA_LSB, buffer, 6))
        return false;

    gyroX = (int16_t)((buffer[1] << 8) | buffer[0]);
    gyroY = (int16_t)((buffer[3] << 8) | buffer[2]);
    gyroZ = (int16_t)((buffer[5] << 8) | buffer[4]);

    return true;
}

/**
 * @brief Function allows users to retrieve the yaw rate around the Z axis
 * @return int16_t
 */
int16_t BNO055::getYawRateZ() {
    return gyroZ / 16.0f;  // BNO055 gyro units = LSB/16 dps (degrees per second)
}

/**
 * @brief Function allows for the user to get the current yaw value
 * @return int16_t
 */
int16_t BNO055::getYaw(){
	return yaw;
}

/**
 * @brief Function allows for the user to get the current roll value
 * @return int16_t
 */
int16_t BNO055::getRoll(){
	return roll;
}

/** 
 * @brief Function allows for the user to get the current pitch value
 * @return int16_t
 */
int16_t BNO055::getPitch(){
	return pitch;
}

/**
 * @brief Function Checks the Calibration status of the IMU and individual sensors.
 * @param sys Parameter for a reference to the system calibration status
 * @param gyro Parameter for a reference to the gyro calibration status
 * @param accel Parameter for a reference to the accel calibration status
 * @param mag Parameter for a reference to the mag calibration status
 * @return True upon successful readings
 */
bool BNO055::readCalibStatus(uint8_t& sys, uint8_t& gyro, uint8_t& accel, uint8_t& mag){
	uint8_t calib;

	if(!readLen(0x35, &calib, 1))
			return false;
	sys   = (calib >> 6) & 0x03;
	gyro  = (calib >> 4) & 0x03;
	accel = (calib >> 2) & 0x03;
	mag   = calib & 0x03;
	return true;
}

/**
 * @brief Function writes values to the specified register given by the user.
 * @param reg Parameter that takes in a register value to write to
 * @param value Parameter that takes in the data to write to the specified register
 * @return Boolean
 */
bool BNO055::writeByte(uint8_t reg, uint8_t value) {
    return HAL_I2C_Mem_Write(hi2c, addr, reg, I2C_MEMADD_SIZE_8BIT, &value, 1, HAL_MAX_DELAY) == HAL_OK;
}

/**
 * @brief Function reads the current value of the specified register given by the user.
 * @param reg Parameter that takes in a register to read from
 * @param buffer Parameter that takes in a data buffer to read the data from the select register
 * @param len Parameter that specifies the length of the incoming data
 * @return Boolean
 */
bool BNO055::readLen(uint8_t reg, uint8_t* buffer, uint8_t len) {
    return HAL_I2C_Mem_Read(hi2c, addr, reg, I2C_MEMADD_SIZE_8BIT, buffer, len, HAL_MAX_DELAY) == HAL_OK;
}
