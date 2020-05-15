/*
 * tasks.h
 *
 *  Created on: 14 may. 2020
 *      Author: -_Alex_-
 */

#ifndef TASKS_H_
#define TASKS_H_

#define R1_Maxima				210000U
#define R2						56000U
#define muestrasADC 			10U
#define mayorValorADC 			4095U
#define menorValorADC 			R2*mayorValorADC/(R2+R1_Maxima)
#define reproduccionRapida    5U    /* Valor a sumarse a conteoMuestreo en estado ADELANTAR */
#define reproduccionRevertida -5	/* Valor a sumarse a conteoMuestreo en estado ATRASAR */
#define reproduccionNormal    1U	/* Valor a sumarse a conteoMuestreo en estado PLAY */
#define thousandMiliseconds     20U
#define fiftyMiliseconds        1U

typedef enum	/* Definición de tipo para valores de retorno de la SM de debounce */
{
	PPS_NORMAL,				/* Play/Pause/Stop presionado normal */
	PPS_PROLONGADO_RELEASE,	/* PPS presionado prolongado on release */
	NF_NORMAL,				/* Next/Forward presionado normal */
	NF_PROLONGADO,			/* NF prolongado para adelantar canción */
	NF_PROLONGADO_RELEASE,	/* NF prolongado on release para volver a velocidad estándar */
	PB_NORMAL,				/* Previous/Backward presionado normal */
	PB_PROLONGADO,			/* PB prolongado para atrasar canción */
	PB_PROLONGADO_RELEASE,	/* PB prolongado on release para volver a velocidad estándar */
	NO_ACTION				/* Default */
} TIPOS_PRESIONADO;

void conteoPush_actualizacionPWM(void);
void task_1ms(void);
void maquinaEstadosReproductor(void);
TIPOS_PRESIONADO maquinaEstadosPush(void);

#endif /* TASKS_H_ */
