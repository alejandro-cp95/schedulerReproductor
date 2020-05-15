/*============================================================================*/
/*                     AZOR - EMBEDDED SYSTEMS SOFTWARE                       */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:        periodic_tasks_exec.c
* version:         1.0 
* created_by:      MDRR
* date_created:    July 31 2013 
*=============================================================================*/
/* DESCRIPTION :  This file contains the periodic tasks definition.           */
/*============================================================================*/
/* FUNCTION COMMENT : Add here the user functionality, inside a periodic task */
/* according to the desired execution period.                                 */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 31/jul/2013 |                               | MDRR             */
/* This file is created based on apptask module from the old version of this  */
/* scheduler.                                                                 */
/*============================================================================*/

/* Includes */
/* -------- */
#include "periodic_tasks_exec.h"
#include "periodic_tasks_modules.h"
#include "fsl_gpio.h"
#include "tasks.h"



 
 /**************************************************************
 *  Name                 : periodic_tasks_exec_1Mtks
 *	ID					 : TASK_1MTKS
 *  Description          : Container for functionality that is 
                           executed periodically.
 *  Parameters           : none
 *  Return               : none
 *  Critical/explanation : no
 **************************************************************/
 void periodic_tasks_exec_1Mtks(void)
 {
	 app_rgb_led_fsm();
 }
 
 /**************************************************************
 *  Name                 : periodic_tasks_exec_1Mtks
 *	ID					 : TASK_1MTKS
 *  Description          : Container for functionality that is
                           executed periodically.
 *  Parameters           : none
 *  Return               : none
 *  Critical/explanation : no
 **************************************************************/
 void periodic_task_500ms(void)
 {
	 GPIO_TogglePinsOutput(GPIOE, 1);
 }

 /**************************************************************
 *  Name                 : periodic_task_1ms
 *	ID					 : TASK_1MTKS
 *  Description          : Container for functionality that is
                           executed periodically.
 *  Parameters           : none
 *  Return               : none
 *  Critical/explanation : no
 **************************************************************/
 void periodic_task_1ms(void)
 {
	 task_1ms();
 }

 /**************************************************************
 *  Name                 : periodic_task_1ms
 *	ID					 : TASK_1MTKS
 *  Description          : Container for functionality that is
                           executed periodically.
 *  Parameters           : none
 *  Return               : none
 *  Critical/explanation : no
 **************************************************************/
 void periodic_task_50ms(void)
 {
	 conteoPush_actualizacionPWM();
 }

