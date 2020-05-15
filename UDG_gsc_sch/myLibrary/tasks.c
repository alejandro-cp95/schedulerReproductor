/*
 * tasks.c
 *
 *  Created on: 14 may. 2020
 *      Author: -_Alex_-
 */

#include "tasks.h"
#include "system.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/
uint32_t counterPush = 0U;	   /* Ayuda a determinar por cuánto tiempo se presiona
								  un botón */
uint32_t pasoPWM = 0U;
const uint16_t diferenciaMayorMenorADC = mayorValorADC-menorValorADC;

adc16_channel_config_t adc16ChannelConfigStruct;
adc16_config_t adc16ConfigStruct;

int8_t   baseSuma = 1;		   /* Cuánto se suma a la variable conteoMuestreo en
 	 	 	 	 	 	 	 	  interrupción del PIT0 */
uint32_t conteoMuestreo = 0U;  /* Esta variable es incrementada en cada interrupción
                                  del PIT0, simulando el progreso de la canción
                                  a una frecuencia cercana a los 44.1 kHz. Además
                                  ayuda a ahorrarse la máquina de estados de rotabit */
uint8_t numCancion = 0U;
typedef struct _cancion
{
	uint8_t titulo[50];
	uint32_t duracion_segundos;
} cancion;
cancion cancion_num[4] = {{"Cancion 1", 20}, {"Cancion 2",21}, {"Cancion 3",22}, {"Cancion 4", 4}};

void conteoPush_actualizacionPWM(void)
{
	uint8_t dutycycleActualizado = 1U;
	if(counterPush!=0xFFFFFFFF)
	{
		counterPush++; /* Conteo para determinar cuántos ms se presiona un botón */
	}
	else
	{

	}
	system_configADC(&adc16ConfigStruct, &adc16ChannelConfigStruct);
	ADC16_SetChannelConfig(DEMO_ADC16_BASE, DEMO_ADC16_CHANNEL_GROUP, &adc16ChannelConfigStruct);
    while (0U == (kADC16_ChannelConversionDoneFlag &
    		ADC16_GetChannelStatusFlags(DEMO_ADC16_BASE, DEMO_ADC16_CHANNEL_GROUP)))
    {

    }

    pasoPWM=0;
    for(uint8_t i=0;i<muestrasADC;i++){
    	pasoPWM += ((4095-ADC16_GetChannelConversionValue(DEMO_ADC16_BASE, DEMO_ADC16_CHANNEL_GROUP))*10)/diferenciaMayorMenorADC;
    }
    pasoPWM /= muestrasADC;
    dutycycleActualizado = pasoPWM*10;
	/* Update PWM duty cycle */
	TPM_UpdatePwmDutycycle(BOARD_TPM_BASEADDR, (tpm_chnl_t)BOARD_TPM_CHANNEL, kTPM_CenterAlignedPwm,
			dutycycleActualizado);
}

void task_1ms(void)
{
	uint32_t cambioLed=0;	/* Ayuda a determinar qué LED de avance encender */
	maquinaEstadosReproductor();	/* Entra a la máquina de estados del reproductor */
	/* Si al disminuir (al ATRASAR) */
	if(baseSuma==-5)
	{		/* el contador de progreso no hiciera underflow */
		if(conteoMuestreo>5)
		{
			conteoMuestreo+=baseSuma;	/* Se suma -5 para atrasar canción */
		}
		else		/* Si se alcanzó el inicio de canción */
		{
			conteoMuestreo=0;	/* Se limpia el conteo de progreso de canción */
			/* Se apagan LEDs de avance de canción */
			GPIO_ClearPinsOutput(BOARD_LED0_GPIO,BOARD_LED0_GPIO_PIN_MASK);
			GPIO_ClearPinsOutput(BOARD_LED1_GPIO,BOARD_LED1_GPIO_PIN_MASK);
			GPIO_ClearPinsOutput(BOARD_LED2_GPIO,BOARD_LED2_GPIO_PIN_MASK);
		}
	}
	else		/* Si al incrementar */
	{  	/* el contador de progreso no sobrepasara la duración de la canción al incrementar */
		if((conteoMuestreo+baseSuma)<=(1000u*cancion_num[numCancion].duracion_segundos))
		{
			conteoMuestreo+=baseSuma;	/* Se incrementa contador de progreso de canción */
		}
		else
		{
			conteoMuestreo=0;	/* Se limpia el conteo de progreso de canción */
			if(numCancion<3)	/* Se incrementa o hace overflow el número de canción */
			{
				numCancion++;
			}
			else
			{
				numCancion = 0;
			}
			/* Se muestra número de canción */
			GPIO_SetPinsOutput(BOARD_LED4_GPIO, 0x0000000C&((uint32_t)(numCancion << 2)));
			GPIO_ClearPinsOutput(BOARD_LED4_GPIO, 0x0000000C&(~((uint32_t)(numCancion << 2))));
		}
	}
	PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, kPIT_TimerFlag);
	cambioLed=conteoMuestreo%1500; /* Se hace división por módulo con el número
	 	 	 	                       de muestras que corresponderían a 1.5s */
	cambioLed/=500;				/* Y se divide sobre un tercio de dicha
	 	 	 	 	 	 	 	 	   cantidad, pues cada LED enciende por 0.5s */
	if(conteoMuestreo!=0)
	{
		switch(cambioLed)
		{
			case 0:			/* Si da como resultado 0, enciende el primer LED */
				GPIO_SetPinsOutput(BOARD_LED0_GPIO,BOARD_LED0_GPIO_PIN_MASK);
				GPIO_ClearPinsOutput(BOARD_LED1_GPIO,BOARD_LED1_GPIO_PIN_MASK);
				GPIO_ClearPinsOutput(BOARD_LED2_GPIO,BOARD_LED2_GPIO_PIN_MASK);
				break;
			case 1:			/* Segundo LED */
				GPIO_ClearPinsOutput(BOARD_LED0_GPIO,BOARD_LED0_GPIO_PIN_MASK);
				GPIO_SetPinsOutput(BOARD_LED1_GPIO,BOARD_LED1_GPIO_PIN_MASK);
				GPIO_ClearPinsOutput(BOARD_LED2_GPIO,BOARD_LED2_GPIO_PIN_MASK);
				break;
			case 2:			/* Tercer LED */
				GPIO_ClearPinsOutput(BOARD_LED0_GPIO,BOARD_LED0_GPIO_PIN_MASK);
				GPIO_ClearPinsOutput(BOARD_LED1_GPIO,BOARD_LED1_GPIO_PIN_MASK);
				GPIO_SetPinsOutput(BOARD_LED2_GPIO,BOARD_LED2_GPIO_PIN_MASK);
				break;
			default:
				break;
		}
	}
}

void maquinaEstadosReproductor(void)
{

}
