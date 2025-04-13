/*
 * circle.h
 *
 *  Created on: 2024年4月19日
 *      Author: 86173
 */

#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "zf_common_headfile.h"


enum circle_type_e {
    CIRCLE_NONE = 0,       // 非圆环模式
    CIRCLE_LEFT_ENTER,          // 圆环开始，识别到单侧极大值点另一侧长直道。
    CIRCLE_RIGHT_ENTER,
    CIRCLE_ENTERING,
    CIRCLE_IN,                // 圆环进入，识别到单侧拐点另一侧长直道，即走到一侧直道，一侧圆环的位置。
    CIRCLE_OUTING,    // 圆环内部。
    CIRCLE_END,              // 圆环结束，即再次走到单侧直道的位置。
};


void circle_check(enum trace_t* posision);
void circle_handle(msg_t* msg,enum trace_t* posision);


#endif /* CIRCLE_H_ */
