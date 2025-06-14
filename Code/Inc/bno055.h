/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : bno055.h
  * @brief          : Header file containing the class to the BNO055 IMU
  * @author
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
#ifndef INC_BNO055_H_
#define INC_BNO055_H_

#include "stm32f4xx_hal.h"
#include <cstdint>
#include <iostream>
#include <stdbool.h>


/**
 * @brief BNO055 class for the IMU containing modes of operation, initialization, and reading
 * data
 */
class BNO055{
	public:
		/**
		 * @brief Enumerated class REG of the IMU modes that will be used
		 */
		enum class REG: uint8_t{
			CONFIG_MODE = 0x00, /**<Configuration Mode CONFIG_MODE*/
			IMU = 0x08,			/**<Normal IMU Mode IMU*/
			NDOF = 0x0C			/**<Fusion Mode NDOF*/
		};

		BNO055(I2C_HandleTypeDef *hi2c, uint8_t addr = 0x28);

		bool init_imu(REG mode = REG::NDOF);
		bool updateEuler();
		bool readCalibStatus(uint8_t& sys, uint8_t& gyro, uint8_t& accel, uint8_t&mag);
		bool updateGyro();
		int16_t getYawRateZ();
		int16_t getYaw();
		int16_t getRoll();
		int16_t getPitch();


	private:
		/**
		 * Private Variable hi2c. Sets the I2C definition fromt the STM32 HAL Config 
		 */
		I2C_HandleTypeDef* hi2c;

		/**
		 * Private variable addr. Holds the imu device specific address (0x28 or 0x29)
		 */
		uint8_t addr;

		/**
		 * Private variable pitch. Holds the pitch data read from the IMU
		 */
		int16_t pitch;

		/**
		 * Private variable yaw. Holds the yaw data read from the IMU
		 */
		int16_t  yaw;

		/**
		 * Private variable roll. Holds the roll data read from the IMU
		 */
		int16_t roll;

		/**
		 * Private variable gyroX. Holds the X data read from the IMU's gyroscope
		 */
		int16_t gyroX;

		/**
		 * Private variable gyroY. Holds the Y data read from the IMU's gyroscope
		 */
		int16_t gyroY;

		/**
		 * Private variable gyroZ. Holds the Z data read from the IMU's gyroscope
		 */
		int16_t gyroZ;

		bool writeByte(uint8_t reg, uint8_t value);
		bool readLen(uint8_t reg, uint8_t* buffer, uint8_t len);
};


#endif /* INC_BNO055_H_ */
