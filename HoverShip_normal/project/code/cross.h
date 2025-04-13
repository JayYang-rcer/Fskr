/*
 * cross.h
 *
 *  Created on: 2024年4月15日
 *      Author: 86173
 */

#ifndef CROSS_H_
#define CROSS_H_

#include "zf_common_headfile.h"


enum cross_type_e {
    CROSS_NONE = 0,       // 非十字模式
    CROSS_ENTERING,          // 进入十字中
    CROSS_IN,               //在十字里面
    CROSS_OUTING,           //出十字中
};



void cross_check(msg_t* msg,enum trace_t* posision);
void cross_handle(imag_t* imag,msg_t* msg,enum trace_t* posision);


#endif /* CROSS_H_ */
