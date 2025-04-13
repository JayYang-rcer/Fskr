/*
 * attitude_solution.h
 *
 *  Created on: Mar 5, 2022
 *      Author: LENOVO
 */

#ifndef ATTITUDE_SOLUTION_H_
#define ATTITUDE_SOLUTION_H_

#include "zf_common_headfile.h"

#define delta_T     0.005f  //5ms¼ÆËãÒ»´Î
#define ICM2062_EN    0
#define IMU660RA_EN   1

typedef struct {
    float gyro_x;
    float gyro_y;
    float gyro_z;
    float acc_x;
    float acc_y;
    float acc_z;
} icm_param_t;

typedef struct {
    float gyro_x;
    float gyro_y;
    float gyro_z;
    float acc_x;
    float acc_y;
    float acc_z;
} imu660ra_param_t;


typedef struct {
    float q0;
    float q1;
    float q2;
    float q3;
} quater_param_t;


typedef struct {
    float pitch;    //¸©Ñö½Ç
    float roll;     //Æ«º½½Ç
    float yaw;       //·­¹ö½Ç
} euler_param_t;


typedef struct {
    float Xdata;
    float Ydata;
    float Zdata;
} gyro_param_t;

extern euler_param_t eulerAngle;

void gyroOffset_init(void);

float fast_sqrt(float x);

void AHRSupdate(float gx, float gy, float gz, float ax, float ay, float az);

void getValues();

void getEulerianAngles(void);

char Gyroscope_Init();

void yaw_revise_init(void);


#endif /* ATTITUDE_SOLUTION_H_ */
