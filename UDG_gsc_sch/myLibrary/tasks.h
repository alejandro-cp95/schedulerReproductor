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

void conteoPush_actualizacionPWM(void);
void task_1ms(void);
void maquinaEstadosReproductor(void);

#endif /* TASKS_H_ */
