
#include "fsl_debug_console.h"
#include "board.h"

#include "pin_mux.h"
#include "clock_config.h"

#include "gsc_sch_core/gsc_sch_core.h"
#include "gsc_sch_core_tick_isr.h"
#include "core_cm0plus.h"

#include "periodic_tasks_init.h"

#include "fsl_pit.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_tpm.h"
#include "fsl_adc16.h"

#include "system.h"
#include "tasks.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define LED_INIT() LED_RED_INIT(LOGIC_LED_ON)
#define LED_TOGGLE() LED_RED_TOGGLE()

#define LED_HIGH_STATE 1U
#define LED_LOW_STATE  0U

#define dutycycleInicial 1U

tpm_config_t tpmInfo;
tpm_chnl_pwm_signal_param_t tpmParam;


pit_config_t pitConfig;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile unsigned int sys_tick_counter = 0;

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Main function
 */
int main(void)
{

	/*Estructuras y variables de la función main*/


    /* Define the init structure for the output LED pin*/
    gpio_pin_config_t led_config = {
        kGPIO_DigitalOutput, LED_LOW_STATE,
    };

    /* Define the init structure for the interrupt pin*/
    gpio_pin_config_t int_config = {
            kGPIO_DigitalInput, 0,
    };
    tpm_pwm_level_select_t pwmLevel = kTPM_HighTrue;

    //////////////////////////////////////////////

    system_inicializacionPinesClock(&led_config, &int_config);

    system_configTPM(&tpmInfo, &tpmParam, pwmLevel, dutycycleInicial);


	/* SysTick Configuration */
	SysTick_Config(48000000U/1000U); //This only applies for ARM Cores with SysTick capability

	/* Scheduler Initialization and tasks initialization  */
	gsc_sch_core_Init();

	/* Execute Scheduler */
	gsc_sch_core_exec();
}

void SysTick_Handler(void)
 {
 	sys_tick_counter++;
 	gsc_sch_core_tick_isr();
 }
