/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : S32K3XX
*   Dependencies         : none
*
*   Autosar Version      : 4.7.0
*   Autosar Revision     : ASR_REL_4_7_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 3.0.0
*   Build Version        : S32K3_RTD_3_0_0_D2303_ASR_REL_4_7_REV_0000_20230331
*
*   Copyright 2020 - 2023 NXP Semiconductors
*
*   NXP Confidential. This software is owned or controlled by NXP and may only be
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

/**
*   @file main.c
*
*   @addtogroup main_module main module documentation
*   @{
*/

/* Including necessary configuration files. */
#include "Mcal.h"

volatile int exit_code = 0;
/* User includes */

#include <Clock_Ip.h>
#include <Siul2_Port_Ip.h>
#include <Siul2_Dio_Ip.h>
#include <Swt_Ip.h>

void TestDelay(uint32 delay);
void TestDelay(uint32 delay)
{
	static volatile uint32 DelayTimer = 0;
	while (DelayTimer < delay)
	{
		DelayTimer++;
	}
	DelayTimer=0;
}

void Swt_CallbackNotification0(void)
{

}

/*!
  \brief The main function for the project.
  \details The startup initialization sequence is the following:
 * - startup asm routine
 * - main()
*/
int main(void)
{
	// initialize clock driver
    Clock_Ip_Init(Clock_Ip_aClockConfig);

    Siul2_Port_Ip_Init(NUM_OF_CONFIGURED_PINS0, g_pin_mux_InitConfigArr0);

    Swt_Ip_Init(0, &Swt_Ip_Cfg0);

    uint8 i = 0;

    for(;;)
    {
    	Siul2_Dio_Ip_WritePin(LED0_PORT, LED0_PIN, 1U);
    	Siul2_Dio_Ip_WritePin(LED1_PORT, LED1_PIN, 0U);

    	TestDelay(4800000);

    	Swt_Ip_Service(0);

    	Siul2_Dio_Ip_WritePin(LED0_PORT, LED0_PIN, 0U);
    	Siul2_Dio_Ip_WritePin(LED1_PORT, LED1_PIN, 1U);

    	TestDelay(4800000);

    	Swt_Ip_Service(0);

        if(exit_code != 0)
        {
            break;
        }
    }
    return exit_code;
}

/** @} */
