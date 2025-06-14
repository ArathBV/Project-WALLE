/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : WALLE_FSM.cpp
  * @brief          : File containing the Class for the WALL_E Functionality
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
#ifndef INC_WALLE_FSM_H_
#define INC_WALLE_FSM_H_


#include "bno055.h"
#include "hcsr04.h"
#include "romiMotor.h"
#include "servos.h"
#include "camera.h"
#include "pidController.h"
#include <cmath>

/**
 * @brief WALL-E class that holds all necessary peripherals and devices in order to control WALL-E and complete it's goal and objective.
 */
class WALLE {
public:
    WALLE(BNO055& imu, HCSR04& range, RomiMotor& leftMotor, RomiMotor& rightMotor, OV2640Camera& camera,
    		Servo& LArm, Servo&LHand, Servo& RArm, Servo&RHand);

    void init();            // Initializes internal state, resets PIDs
    void update(float dt);  // FSM update function, called in main loop
    void simpleUpdate(float dt, float yaw, uint16_t distance);
    void closeHands();
    void liftArms();
    void computerVision();

private:

    /**
    * @brief Enumeration for Color Detection
    */
    enum class State {
    	  START_SCAN,     /**<START_SCAN FSM State to begin scans and data collection*/
		    TURN_SEGMENT,   /**<TURN_SEGMENT FSM State to turn to the next angle for data collection*/
		    STOP_MEASURE,   /**<STOP_MEASURE FSM State to record angle data and distance data*/
        FINISH_SCAN,    /**<FINISH_SCAN FSM State that indicates all angles and distances have been recorded */
        TURN,           /**<TURN FSM State to turn to the angle which has the closest object detected*/
        FORWARD,        /**<FORWARD FSM State to move forward towards the object*/
        STOP,           /**<STOP FSM State to stop in front of object after a certain threshold*/
		    IDENTIFY        /**<IDENTIFY FSM State to utilize computer vision to detect the color*/
    }state;

    // References to hardware peripherals
    BNO055& imu;
    HCSR04& rangeSensor;
    RomiMotor& leftMotor;
    RomiMotor& rightMotor;
    OV2640Camera& camera;
    Servo& leftArm;
    Servo& leftHand;
    Servo& rightArm;
    Servo& rightHand;

    // PID controllers
    PIDController turnPID;
    PIDController drivePID;

    // FSM control variables
    float targetYaw;        // Yaw to turn to after scan
    float initialYaw;       // Yaw to hold while driving forward
    int currentSegment;
    int totalSegments;
    float segmentAngle;
    int stopTimer;
    float scanYawStart;
    int distances[16];
    int candidateAngles[16];

    //FSM Estimation Variables
    uint32_t actionDuration;
    uint32_t actionStartTime;


    // Constants
    const float yawTolerance = 2.0f;       // Degrees of error allowed when turning
    const uint16_t distanceThreshold = 7; // Distance to stop at (cm)

    // Internal helpers
    void stopMotors();
    float normalizeAngle(float angle); // Keeps angles within [-180, 180]
};

#endif /* INC_WALLE_FSM_H_ */
