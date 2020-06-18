/**************************************************************************//**
 * @file
 * @brief Uses the IADC repeated nonblocking measurements on a single input
 * while asleep. Sample rate is 1 ksps, and the ADC reads GPIO pins PC4
 * (P25 on BRD4001 J102) as input.
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
 * @brief  IADC Initializer
 *****************************************************************************/
void initSingleIADC (void)
{
  // Declare init structs
  IADC_Init_t init = IADC_INIT_DEFAULT;
  IADC_AllConfigs_t initAllConfigs = IADC_ALLCONFIGS_DEFAULT;
  IADC_InitSingle_t initSingle = IADC_INITSINGLE_DEFAULT;
  IADC_SingleInput_t initSingleInput = IADC_SINGLEINPUT_DEFAULT;

#if 0
  // Set HFRCODPLL band and the tuning value based on the value in the calibration table made during production.
  CMU_HFRCODPLLBandSet(HFRCODPLL_FREQ);

  // Select HFRCODPLL as the EM01GRPA clock
  CMU_ClockSelectSet(cmuClock_EM01GRPACLK, cmuSelect_HFRCODPLL);
#endif


  // Select clock for IADC
  CMU_ClockSelectSet(cmuClock_IADCCLK, cmuSelect_EM01GRPACLK);
  // Enable IADC0 clock branch
  CMU_ClockEnable(cmuClock_IADC0, true);
  // Reset IADC to reset configuration in case it has been modified
  IADC_reset(IADC0);



  // Modify init structs and initialize
  init.warmup = iadcWarmupKeepWarm;

  // Set the HFSCLK prescale value here
   init.srcClkPrescale = IADC_calcSrcClkPrescale(IADC0, CLK_SRC_ADC_FREQ, 0);

   // 25ns per cycle, 73 cycles make a 1.824us period (548Khz)for the ADC sample
   init.timerCycles = 73;

   // Configuration 0 is used by both scan and single conversions by default
   // Use unbuffered AVDD as reference
   initAllConfigs.configs[0].reference = iadcCfgReferenceVddx;

   // Divides CLK_SRC_ADC to set the CLK_ADC frequency
   initAllConfigs.configs[0].adcClkPrescale = IADC_calcAdcClkPrescale(IADC0,CLK_ADC_FREQ,0,iadcCfgModeNormal,init.srcClkPrescale);

  initSingle.triggerSelect= iadcTriggerSelTimer;
  initSingle.dataValidLevel = _IADC_SINGLEFIFOCFG_DVL_VALID4;

  initSingle.fifoDmaWakeup = true;

  // Configure Input sources for single ended conversion
  initSingleInput.posInput = iadcPosInputPortCPin4;
  initSingleInput.negInput = iadcNegInputGnd;

  // Initialize IADC
  IADC_init(IADC0, &init, &initAllConfigs);

  // Initialize Scan
  IADC_initSingle(IADC0, &initSingle, &initSingleInput);

  // Enable the IADC timer - can only be done after the IADC has been enabled
  IADC_command(IADC0, iadcCmdEnableTimer);

  // Allocate the analog bus for ADC0 inputs
  GPIO->IADC_INPUT_BUS |= IADC_INPUT_BUSALLOC;

  // Enable interrupts on data valid level
 // IADC_enableInt(IADC0, IADC_IF_SINGLEFIFODVL);

  // Enable ADC interrupts
//  NVIC_ClearPendingIRQ(IADC_IRQn);
//  NVIC_EnableIRQ(IADC_IRQn);
}



/***************************************************************************//**
 * @brief
 *   Initialize the LDMA controller for ping-pong transfer
 ******************************************************************************/
void initLdmaPingPong(void)
{
  uint32_t i;

  // Initialize ping-pong buffers
  for (i = 0; i < NUM_SAMPLES; i++)
  {
    pingBuffer[i] = 0;
    pongBuffer[i] = 0;
  }

  LDMA_Init_t init = LDMA_INIT_DEFAULT;
  LDMA_Init(&init);


  // Configure LDMA for transfer from IADC to memory
   // LDMA will loop continuously
   LDMA_TransferCfg_t transferCfg = LDMA_TRANSFER_CFG_PERIPHERAL(ldmaPeripheralSignal_IADC0_IADC_SINGLE);


  // LINK descriptor macros for ping-pong transfer
  descLink[0] = (LDMA_Descriptor_t)LDMA_DESCRIPTOR_LINKREL_P2M_BYTE(&IADC0->SINGLEFIFODATA, &pingBuffer, NUM_SAMPLES, 1);

  descLink[1] = (LDMA_Descriptor_t)LDMA_DESCRIPTOR_LINKREL_P2M_BYTE(&IADC0->SINGLEFIFODATA, &pongBuffer,NUM_SAMPLES, -1);

  // Enable interrupts
  descLink[0].xfer.doneIfs = true;
  descLink[1].xfer.doneIfs = true;

  // Disable automatic transfers
  descLink[0].xfer.structReq = false;
  descLink[1].xfer.structReq = false;

  LDMA_StartTransfer(LDMA_CHANNEL, (void*)&transferCfg, (void*)&descLink);

  // Software request to start transfer
  LDMA->SWREQ |= LDMA_CH_MASK;
}

void LDMAPingPongHandler(void)
{
  uint32_t pending;

  // Read interrupt source
  pending = LDMA_IntGet();

  // Clear interrupts
  LDMA_IntClear(pending);

  // Check for LDMA error
  if (pending & LDMA_IF_ERROR)
  {
    // Loop here to enable the debugger to see what has happened
    while (1);
  }

  // Request next transfer
  LDMA->SWREQ |= LDMA_CH_MASK;

}
