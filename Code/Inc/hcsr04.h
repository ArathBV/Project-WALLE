/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : HCSR04.h
  * @brief          : File containing the class to the HCSR04 Ultrasonic Sensor
  *  class
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

#ifndef INC_HCSR04_H_
#define INC_HCSR04_H_

#include "stm32f4xx_hal.h"

/**
 * @brief WALL-E Ultrasonic Sensor Class for range and distance detection from an object
 */
class HCSR04 {
	public:
		HCSR04(GPIO_TypeDef* trigPort, uint16_t trigPin,
			   GPIO_TypeDef* echoPort, uint16_t echoPin,
			   TIM_HandleTypeDef* htim);

		void trigger();             // Triggers a measurement
		bool measure();             // Performs blocking measurement
		uint32_t getDistanceCm();   // Returns distance in cm

	private:
    /**
     * Private variable trigPort that takes in the trigger Port definition from the STM32 Config
     */
		GPIO_TypeDef* trigPort;

    /**
     * Private variable trigPin that takes in the trigger GPIO pin value 
     */
		uint16_t trigPin;

    /**
     * Private variable trigPort that takes in the trigger Port definition from the STM32 Config
     */
		GPIO_TypeDef* echoPort;

    /**
     *  Private variable echoPin that takes in the Echo GPIO pin value  
     */
		uint16_t echoPin;

    /**
     * Private variable htim that takes in the Timer definition from the STM32 Config
     */
		TIM_HandleTypeDef* htim;

    /**
     * Private variable distanceCm that holds the centimeter readings from the HCSR04 Sensor
     */
		uint32_t distanceCm;
};

#endif /* INC_HCS04_H_ */
