/*
 * barrier.h
 *
 *  Created on: 2024年5月21日
 *      Author: 86173
 */

#ifndef BARRIER_H_
#define BARRIER_H_

#include "zf_common_headfile.h"

enum barrier_type_e {
    BARRIER_NONE = 0,       // 非避障模式
    BARRIER_LEFT,                // 识别到左障碍
    BARRIER_RIGHT,                // 识别到右障碍
};

void barrier_check(msg_t* msg,enum trace_t* posision);
void barrier_handle(enum trace_t* posision);


#endif /* BARRIER_H_ */
