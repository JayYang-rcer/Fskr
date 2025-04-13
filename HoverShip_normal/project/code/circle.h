/*
 * circle.h
 *
 *  Created on: 2024��4��19��
 *      Author: 86173
 */

#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "zf_common_headfile.h"


enum circle_type_e {
    CIRCLE_NONE = 0,       // ��Բ��ģʽ
    CIRCLE_LEFT_ENTER,          // Բ����ʼ��ʶ�𵽵��༫��ֵ����һ�೤ֱ����
    CIRCLE_RIGHT_ENTER,
    CIRCLE_ENTERING,
    CIRCLE_IN,                // Բ�����룬ʶ�𵽵���յ���һ�೤ֱ�������ߵ�һ��ֱ����һ��Բ����λ�á�
    CIRCLE_OUTING,    // Բ���ڲ���
    CIRCLE_END,              // Բ�����������ٴ��ߵ�����ֱ����λ�á�
};


void circle_check(enum trace_t* posision);
void circle_handle(msg_t* msg,enum trace_t* posision);


#endif /* CIRCLE_H_ */
