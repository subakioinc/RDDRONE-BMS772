/* Copyright 2020 NXP
 * All rights reserved.
 *
 * BSD 3-Clause License
 * 
 * Copyright (c) 2020, NXP Drone and Rover Team
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ** ###################################################################
 **     Filename    : ledState.h
 **     Project     : SmartBattery_RDDRONE_BMS772
 **     Processor   : S32K144
 **     Version     : 1.00
 **     Date   		: 2020-04-03
 **     Abstract    :
 **        ledState module.
 **        This module contains all functions needed for shared ledState
 **
 ** ###################################################################*/
/*!
 ** @file ledState.h
 **
 ** @version 01.00
 **
 ** @brief
 **        ledState module. this module contains the functions to control the LED
 **
 */
#ifndef LEDSTATE_H_
#define LEDSTATE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include <string.h>
#include "BMS_data_types.h"

/*******************************************************************************
 * defines
 ******************************************************************************/
#define LED_BLINK_ON   					true 	// use with the ledState_setLedColor function to blink the LED
#define LED_BLINK_OFF  					false	// use with the ledState_setLedColor to not blink the LED

//#define LED_INDICATION_DEFINED_WAIT 	 		//<! if this is defined, after the state indication it will wait with a defined time

#ifdef LED_INDICATION_DEFINED_WAIT
#define LED_DEFINED_WAIT 				2		//<! amount of sec. to wait after the indication
#else
#define LED_PERIOD_INDICATION_S			6		// the period of the state of charge indication
#endif

#define LED_BLINK_TIME_S 				1		// the blinking time in s (the time the LED is on and off)
#define LED_BLINK_TIME_MS 				500		// the blinking time in ms (the time the LED is on and off), green
//#define LED_BLINK_TIME_INDICATION_MS	500		// the blinking time in s (the time the LED is on and off) in normal mode to indicate

#define LED_4_BLINK_PERCENTAGE			80		// the percentage from which (upwards) the BMS will blink 4 times
#define LED_3_BLINK_PERCENTAGE			60		// the percentage from which (upwards) the BMS will blink 4 times
#define LED_2_BLINK_PERCENTAGE			40		// the percentage from which (upwards) the BMS will blink 4 times
#define LED_1_BLINK_PERCENTAGE			0		// the percentage from which (upwards) the BMS will blink 4 times


#ifndef UINT8_MAX
#define UINT8_MAX						255
#endif

/*******************************************************************************
 * types
 ******************************************************************************/

//! @brief 	this enum can be used to set certain LED colors
typedef enum {
	OFF = 0, RED = 1, GREEN = 2, YELLOW = 3, BLUE = 4, MAGENTA = 5, CYAN = 6, WHITE = 7, RED_BLUE = 8 
}LEDColor_t;

/*******************************************************************************
 * public functions
 ******************************************************************************/
/*!
 * @brief 	this function initialized the RGB LED and it will set the LED to green blinking
 * 			
 * @param 	None
 *
 * @return 	If successful, the function will return zero (OK). Otherwise, an error number will be returned to indicate the error:
 * @example if(ledState_initialize())
 *			{
 *				// do something with the error
 *			}
 */
int ledState_initialize(void);


/*!
 * @brief 	This function will set the color of the LED that can be entered from the LEDColor_t enum.
 * 			This function can also be used to set the LED off. using the OFF enum.
 * 			ledState_initialize(); should be called before using this function
 * 			This function can be used by multiple threads
 * 			
 * @param 	The new color is should have from the LEDColor_t enum, it will change imidiatly 
 * @param 	if the LED should blink at the rate of BLINK_TIME, LED_BLINK_ON or LED_BLINK_OFF could be used
 *
 * @return 	If successful, the function will return zero (OK). Otherwise, an error number will be returned to indicate the error:
 * @example if(ledState_setLedColor(GREEN, LED_BLINK_ON))
 *			{
 *				// do something with the error
 *			}
 */
int ledState_setLedColor(LEDColor_t newColor, bool BlinkOn);

/*!
 * @brief 	This function will used to set the blinking indication, the number of blinks
 * 			
 * @param 	newStateOfCharge the new state of charge, value of 0-100.
 *
 * @return 	the new state indication number of blinks, UINT8_MAX if error  
 */
uint8_t ledState_calcStateIndication(uint8_t newStateOfCharge);

/*!
 * @brief 	This function will used to get the blinking indication, the number of blinks
 * 			
 * @param 	none
 *
 * @return 	the new state indication number of blinks, UINT8_MAX if error 
 */
uint8_t ledState_getStateIndication(void);

/*******************************************************************************
 * EOF
 ******************************************************************************/

#endif /* LEDSTATE_H_ */
