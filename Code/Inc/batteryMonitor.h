/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           batteryMonitor.h
  * @brief          File containing the class to a Battery Monitor via the ADC
  * @author			Arath Villanueva (abvillan@calpoly.edu) Devon Bolt (dwbolt@calpoly.edu)
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

#ifndef INC_BATTERYMONITOR_H_
#define INC_BATTERYMONITOR_H_

#include "stm32f4xx_hal.h"

/**
 * @brief WALL-E Battery Monitor Class that utilized the ADC to keep record of the current battery voltage
 * to prevent low battery usage and battery life drain. 
 * */
class BatteryMonitor {
	public:
    /** 
     * @brief Constructor Function for the Battery Monitor Class
     * @param hadc ADC definition from the STM32 HAL Config
     * @param threshold_mV Default value 7000 for 7V, indicates when battery levels are too low
     */
		BatteryMonitor(ADC_HandleTypeDef* hadc, uint16_t threshold_mV = 7000);

    /**
    * @brief Function allows for the user to retrieve the voltage of the battery
    * @param None
    * @return uint16_t
    */
		uint16_t getVoltage_mV();

    /*
    * @brief Function indicates and raises the flag if the voltage is below the threshold
    * provided to the class indicating to charge the LiPo Battery.
    * @return Boolean
    */
		bool isLow();

	private:
    /**
     * Private Variable hadc
     * Assigns the hadc ADC typedef fromt he STM32 HAL Definition
     */
		ADC_HandleTypeDef* hadc;

    /**
     * Private Variable threshold_mV
     * Assigns the threshold voltage to indicate low voltage
     */
		uint16_t threshold_mV;

    /** 
    * @brief Function calculates the voltage in mV by reading the ADC and applying
    * the conversion to step up to the appropriate input voltage.
    * @return uint16_t
    */
		uint16_t readVoltageRaw_mV();
};



#endif /* INC_BATTERYMONITOR_H_ */
