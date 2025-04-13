/*
 * my_math.h
 *
 *  Created on: 2024年2月25日
 *      Author: 86173
 */
#include "Img_proc.h"
#include "stdint.h"


#ifndef MY_MATH_H_
#define MY_MATH_H_




//绝对值
double my_abs(double x);
//最小二乘法
void regression(uint8_t startline, uint8_t endline, const uint8_t* line, straight_t *stra);
//计算边界方差
void calculate_variance(uint8_t start, uint8_t end, uint8_t* line, straight_t *stra);
//根据拟合的直线给边线赋值
void line_assignment(uint8_t startline, uint8_t endline, uint8_t *line, const straight_t *stra);
//两点拟合直线
void two_points_fitting_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, straight_t* stra);
uint16_t regression2(uint8_t startline, uint8_t endline);

#endif

