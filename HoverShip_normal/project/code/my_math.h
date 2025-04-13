/*
 * my_math.h
 *
 *  Created on: 2024��2��25��
 *      Author: 86173
 */
#include "Img_proc.h"
#include "stdint.h"


#ifndef MY_MATH_H_
#define MY_MATH_H_




//����ֵ
double my_abs(double x);
//��С���˷�
void regression(uint8_t startline, uint8_t endline, const uint8_t* line, straight_t *stra);
//����߽緽��
void calculate_variance(uint8_t start, uint8_t end, uint8_t* line, straight_t *stra);
//������ϵ�ֱ�߸����߸�ֵ
void line_assignment(uint8_t startline, uint8_t endline, uint8_t *line, const straight_t *stra);
//�������ֱ��
void two_points_fitting_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, straight_t* stra);
uint16_t regression2(uint8_t startline, uint8_t endline);

#endif

