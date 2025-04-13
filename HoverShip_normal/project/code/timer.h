/*
 * timer.h
 *
 *  Created on: 2024Äê3ÔÂ1ÈÕ
 *      Author: 86173
 */
#ifndef _TIMER_H
#define _TIMER_H


#include "zf_driver_encoder.h"
#include "zf_driver_timer.h"
#include "zf_common_interrupt.h"
#include "ch32v30x_tim.h"
#include "ch32v30x_misc.h"

void TIM5_Int_Init(uint16_t arr, uint16_t psc);
void TIM6_Int_Init(uint16_t arr, uint16_t psc);
void TIM3_Int_Init(uint16_t arr, uint16_t psc);
void Key_Tim7_Init(uint16_t arr, uint16_t psc);
void Bluetooth_Tim9_Init(uint16_t arr, uint16_t psc);

#endif /* TIMER_H */

