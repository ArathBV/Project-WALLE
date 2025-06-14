/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : romiMotor.h
  * @brief          : File containing the class to the ROMI Motors class
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


#ifndef INC_ROMIMOTOR_H_
#define INC_ROMIMOTOR_H_

#include "stm32f4xx_hal.h"

/**
 * @brief WALL-E motor driver class that uses pololu Romi Motors
 */
class RomiMotor{
	public:
		RomiMotor(GPIO_TypeDef* enPort, uint16_t enPin,
				GPIO_TypeDef* phPort, uint16_t phPin,
				GPIO_TypeDef* slPort, uint16_t slPin);

		void setSpeed(int8_t);
		void updatePWM();
		void enable();
		void disable();
		int8_t getDuty();

	private:
		/**
		 * Private variable enPort that takes in the enable Port definition from the STM32 Config
		 */	
		GPIO_TypeDef* en_Port;

		/**
     	* Private variable en_Pin that takes in the enable GPIO pin value 
     	*/
		uint16_t en_Pin;

		/**
		 * Private variable ph_Port that takes in the phase Port definition from the STM32 Config
		 */	
		GPIO_TypeDef* ph_Port;

		/**
     	* Private variable ph_Pin that takes in the Phase GPIO pin value 
     	*/
		uint16_t ph_Pin;

		/**
		 * Private variable sl_Port that takes in the Sleep Port definition from the STM32 Config
		 */	
		GPIO_TypeDef* sl_Port;

		/**
     	* Private variable sl_Pin that takes in the Sleep GPIO pin value 
     	*/
		uint16_t sl_Pin;

		/**
		 * Private variable duty_cycle that sets the duty cycle that goes into the motor driver based from the setSpeed function
		 */
		int8_t duty_Cycle;

		/**
		 * Private variable pwm_Counter that helps set the requested duty cycle utilizing Timer 5 to set the en_Pin high and low.
		 */
		uint8_t pwm_Counter;
};

#endif /* INC_ROMIMOTOR_C_ */
