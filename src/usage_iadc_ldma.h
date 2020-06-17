


/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/


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
 ***************************   GLOBAL VARIABLES   *******************************
 ******************************************************************************/


// How many samples to capture
#define NUM_SAMPLES               1000

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
