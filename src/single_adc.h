


/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/
#define BSP_CLK_HFXO_PRESENT                          (1)
#define BSP_CLK_HFXO_FREQ                             (38400000UL)
#define BSP_CLK_HFXO_INIT                              CMU_HFXOINIT_DEFAULT
#define BSP_CLK_HFXO_CTUNE                            (129)
#define BSP_CLK_LFXO_PRESENT                          (1)
#define BSP_CLK_LFXO_INIT                              CMU_LFXOINIT_DEFAULT
#define BSP_CLK_LFXO_FREQ                             (32768U)
#define BSP_CLK_LFXO_CTUNE                            (79U)

// Set HFRCOEM23 to lowest frequency (1MHz)
#define HFRCOEM23_FREQ          cmuHFRCOEM23Freq_1M0Hz

// Set HFRCODLL clock to 80MHz
#define HFRCODPLL_FREQ            cmuHFRCODPLLFreq_80M0Hz

// Set CLK_ADC to 40MHz
#define CLK_SRC_ADC_FREQ          40000000 // CLK_SRC_ADC
#define CLK_ADC_FREQ              10000000 // CLK_ADC - 10MHz max in normal mode


// When changing GPIO port/pins above, make sure to change xBUSALLOC macro's
// accordingly.
#define IADC_INPUT_BUS          CDBUSALLOC
#define IADC_INPUT_BUSALLOC     GPIO_CDBUSALLOC_CDEVEN0_ADC0

/*******************************************************************************
 ***************************   GLOBAL VARIABLES   ******************************
 ******************************************************************************/

// Stores latest ADC sample and converts to volts
static volatile IADC_Result_t sample;
static volatile double singleResult;




/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/



// Set CLK_ADC to 10MHz (this corresponds to a sample rate of 833ksps)
#define CLK_SRC_ADC_FREQ          10000000 // CLK_SRC_ADC
#define CLK_ADC_FREQ	          10000000 // CLK_ADC

// When changing GPIO port/pins above, make sure to change xBUSALLOC macro's
// accordingly.
#define IADC_INPUT_0_BUS          CDBUSALLOC
#define IADC_INPUT_0_BUSALLOC     GPIO_CDBUSALLOC_CDEVEN0_ADC0
#define IADC_INPUT_1_BUS          CDBUSALLOC
#define IADC_INPUT_1_BUSALLOC     GPIO_CDBUSALLOC_CDODD0_ADC0

/*******************************************************************************
 ***************************   GLOBAL VARIABLES   *******************************
 ******************************************************************************/


// How many samples to capture
#define NUM_SAMPLES               100

/**************/
// DMA channel used for the example
#define LDMA_CHANNEL        0
#define LDMA_CH_MASK        (1 << LDMA_CHANNEL)

// Descriptor linked list for LDMA transfer
LDMA_Descriptor_t descLink[2];

uint16_t pingBuffer[NUM_SAMPLES];
uint16_t pongBuffer[NUM_SAMPLES];



void  initHFXO(void);
void initSingleIADC (void);
void LDMAPingPongHandler(void);
void initLdmaPingPong(void);

uint8_t singleFlag;
