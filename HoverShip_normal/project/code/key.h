/*
 * key.h
 *
 *  Created on: 2024Äê3ÔÂ6ÈÕ
 *      Author: 86173
 */

#ifndef KEY_H_
#define KEY_H_
#include "zf_common_headfile.h"

#define KEY1_PIN    A8
#define KEY2_PIN    D8
#define KEY3_PIN    B12
#define KEY4_PIN    B0
#define KEY5_PIN    D5
#define KEY6_PIN    D10

#define KEY1 1
#define KEY2 2
#define KEY3 3
#define KEY4 4
#define KEY5 5
#define KEY6 6

#define KEY_UP      1
#define KEY_DOWN    0


//void key_init(void);
void key_gpio_init(void);
uint8_t key_scan(void);

#endif /* KEY_H_ */
