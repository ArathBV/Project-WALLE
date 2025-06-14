/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : camera.h
  * @brief          : File containing the initialization class to the OV2640 (Camera)
  * @author			: Arath Villanueva (abvillan@calpoly.edu) Devon Bolt (dwbolt@calpoly.edu)
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
#ifndef INC_CAMERA_H_
#define INC_CAMERA_H_

#include "stm32f4xx_hal.h"
#include <cstring>
#include <cstdio>

#define BLUE_THRESHOLD 200   // Adjust based on lighting and distance
#define STEP 4               // Read every 2 bytes = 1 pixel, STEP=4 = every other pixel
#define ROW_WIDTH 160
#define SAMPLE_WIDTH (ROW_WIDTH / 2)  // Because we skip every other pixel

/**
 * @brief Enumeration for Color Detection
 */
enum DominantColor {
    COLOR_UNKNOWN,  /**<COLOR_UNKOWN color is usually dark or too bright unspecified by thresholds*/
    COLOR_RED,      /**<COLOR_RED pixels are dominantly RED heavy*/
    COLOR_GREEN,    /**<COLOR_GREEN pixels are dominantly GREEN heavy*/
    COLOR_BLUE      /**<COLOR_BLUE pixels are dominantly BLUE heavy*/
};

/**
 * @brief WALL-E Camera class used for object and color detection
 */
class OV2640Camera {
public:
    OV2640Camera(I2C_HandleTypeDef* i2c, SPI_HandleTypeDef* spi, GPIO_TypeDef* cs_port, uint16_t cs_pin);

    bool initialize();
    bool captureFrame();
    void printCaptureReport(UART_HandleTypeDef* huart);
    void printBlueDetectionMap(UART_HandleTypeDef* huart);
    DominantColor analyzeColor();
    DominantColor analyzeColorCenter();

private:
    /**
	* Private Variable i2c_. Sets the I2C definition from the STM32 HAL Config 
	*/
    I2C_HandleTypeDef* i2c_;

    /**
	* Private Variable spi_. Sets the SPI definition from the STM32 HAL Config 
	*/
    SPI_HandleTypeDef* spi_;

    /**
	* Private Variable cs_port_. Sets the Chip Select GPIO Port definition from the STM32 HAL Config 
	*/
    GPIO_TypeDef* cs_port_;

    /**
	* Private Variable cs_pin. Sets the Chip Select GPIO definition from the STM32 HAL Config 
	*/
    uint16_t cs_pin_;

    /**
	* Private Variable FRAME_SIZE. Sets the camera's fixed Frame Capture Size 
	*/
    static constexpr size_t FRAME_SIZE = 160 * 120 * 2; // QQVGA RGB565

    /**
	* Private Variable frame_buffer_. Sets the buffer for frame analysis 
	*/
    uint8_t frame_buffer_[FRAME_SIZE];

    void writeRegister(uint8_t reg, uint8_t val);
    void csHigh();
    void csLow();
};



#endif /* INC_CAMERA_H_ */
