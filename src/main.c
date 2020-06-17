/**************************************************************************//**
 * @file
 * @brief Uses the IADC and LDMA to take repeated nonblocking measurements on
 * multiple inputs while asleep without any processor overhead. Sample rate is
 * 833 ksps, and the ADC reads GPIO pins PC4 (P25 on BRD4001 J102) and PC5
 * (P27 on BRD4001 J102) as input.
 * @version 0.0.1
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2018 Silicon Labs, http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silicon Labs Software License Agreement. See
 * "http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt"
 * for details. Before using this software for any purpose, you must agree to the
 * terms of that agreement.
 *
 ******************************************************************************/
 
#include <stdio.h>
#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_iadc.h"
#include "em_ldma.h"
#include "em_gpio.h"
#include "bsp.h"

#include "usage_iadc_ldma.h"

/**************************************************************************//**
 * @brief  GPIO Initializer
 *****************************************************************************/
void initGPIO (void)
{
  // Enable GPIO clock branch
  CMU_ClockEnable(cmuClock_GPIO, true);

  // Configure PB1 as output, will be set when LDMA transfer completes
  GPIO_PinModeSet(BSP_GPIO_LED0_PORT, BSP_GPIO_LED0_PIN, gpioModePushPull, 0);
}

/**************************************************************************//**
 * @brief  LDMA Handler
 *****************************************************************************/
void LDMA_IRQHandler(void)
{
	LDMAPingPongHandler();

  // Set GPIO to notify that transfer is complete
  GPIO_PinOutToggle(BSP_GPIO_LED0_PORT, BSP_GPIO_LED0_PIN);
}

/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int main(void)
{
  CHIP_Init();

  // Initialize GPIO
  initGPIO();

  // Initialize the IADC
  //initIADC();
  initSingleIADC();

  initLdmaPingPong();

  // Start scan

  IADC_command(IADC0, iadcCmdStartSingle);

  // Sleep CPU until LDMA transfer completes
 // EMU_EnterEM2(true);

  // once transfer completes, wake up, handle IRQ, and sit in infinite loop
  while(1);
}
