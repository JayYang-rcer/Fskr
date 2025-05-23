/*
 * attitude_solution.c
 *
 *  Created on: Mar 5, 2022
 *      Author: LENOVO
 */


#include "attitude_solution.h"


float I_ex, I_ey, I_ez;  // 误差积分
float yaw_revise_data;
uint8_t yaw_revise_flag = 0;
quater_param_t Q_info = {1, 0, 0};  // 全局四元数
euler_param_t eulerAngle; //欧拉角
#if ICM2062_EN
icm_param_t icm_data;
#endif
#if IMU660RA_EN
imu660ra_param_t imu660ra_data;
#endif
gyro_param_t GyroOffset;

uint8_t GyroOffset_init = 0;

float param_Kp = 0.17;   // 加速度计的收敛速率比例增益
float param_Ki = 0.004;   //陀螺仪收敛速率的积分增益 0.004


float fast_sqrt(float x) {
    float halfx = 0.5f * x;
    float y = x;
    long i = *(long *) &y;
    i = 0x5f3759df - (i >> 1);
    y = *(float *) &i;
    y = y * (1.5f - (halfx * y * y));
    return y;
}


/************************************************************************************************************************
 *@brief......陀螺仪零飘初始化
 *@return.....无
 ***********************************************************************************************************************/
void gyroOffset_init(void)
{
    GyroOffset.Xdata = 0;
    GyroOffset.Ydata = 0;
    GyroOffset.Zdata = 0;
    for (uint16_t i = 0; i < 100; ++i) {
#if ICM2062_EN
    icm20602_get_gyro();
    icm20602_get_acc();
    GyroOffset.Xdata += icm_gyro_x;
    GyroOffset.Ydata += icm_gyro_y;
    GyroOffset.Zdata += icm_gyro_z;
    system_delay_ms(10);
#endif
#if IMU660RA_EN
    imu660ra_get_gyro();
    imu660ra_get_acc();
    GyroOffset.Xdata += imu660ra_gyro_x;
    GyroOffset.Ydata += imu660ra_gyro_y;
    GyroOffset.Zdata += imu660ra_gyro_z;
    system_delay_ms(10);
#endif

    }

    GyroOffset.Xdata /= 100;
    GyroOffset.Ydata /= 100;
    GyroOffset.Zdata /= 100;
    GyroOffset_init = 1;
}

/************************************************************************************************************************
 *@brief......陀螺仪零飘初始化
 *@return.....无
 ***********************************************************************************************************************/
void yaw_revise_init(void){
    yaw_revise_data = eulerAngle.yaw;
    yaw_revise_flag = 1;
}


#define alpha           0.3f

/************************************************************************************************************************
 *@brief......将数据转化为实际物理值
 *@return.....无
 ***********************************************************************************************************************/
void getValues() {
#if ICM2062_EN
        //一阶低通滤波，单位g/s
        icm_data.acc_x = (((float) icm_acc_x) * alpha) * 8 / 4096 + icm_data.acc_x * (1 - alpha);
        icm_data.acc_y = (((float) icm_acc_y) * alpha) * 8 / 4096 + icm_data.acc_y * (1 - alpha);
        icm_data.acc_z = (((float) icm_acc_z) * alpha) * 8 / 4096 + icm_data.acc_z * (1 - alpha);


        //陀螺仪角度转弧度
        icm_data.gyro_x = ((float) icm_gyro_x - GyroOffset.Xdata) * PI / 180 / 16.4f;
        icm_data.gyro_y = ((float) icm_gyro_y - GyroOffset.Ydata) * PI / 180 / 16.4f;
        icm_data.gyro_z = ((float) icm_gyro_z - GyroOffset.Zdata) * PI / 180 / 16.4f;
#endif
#if IMU660RA_EN
        //一阶低通滤波，单位g/s
        imu660ra_data.acc_x = (((float) imu660ra_acc_x) * alpha) * 8 / 4096 + imu660ra_data.acc_x * (1 - alpha);
        imu660ra_data.acc_y = (((float) imu660ra_acc_y) * alpha) * 8 / 4096 + imu660ra_data.acc_y * (1 - alpha);
        imu660ra_data.acc_z = (((float) imu660ra_acc_z) * alpha) * 8 / 4096 + imu660ra_data.acc_z * (1 - alpha);


        //陀螺仪角度转弧度
        imu660ra_data.gyro_x = ((float) imu660ra_gyro_x - GyroOffset.Xdata) * PI / 180 / 16.4f;
        imu660ra_data.gyro_y = ((float) imu660ra_gyro_y - GyroOffset.Ydata) * PI / 180 / 16.4f;
        imu660ra_data.gyro_z = ((float) imu660ra_gyro_z - GyroOffset.Zdata) * PI / 180 / 16.4f;
#endif

}

/************************************************************************************************************************
 *@brief......互补滤波
 *@return.....无
 ***********************************************************************************************************************/
void AHRSupdate(float gx, float gy, float gz, float ax, float ay, float az) {
    float halfT = 0.5 * delta_T;
    float vx, vy, vz;    //当前的机体坐标系上的重力单位向量
    float ex, ey, ez;    //四元数计算值与加速度计测量值的误差
    float q0 = Q_info.q0;
    float q1 = Q_info.q1;
    float q2 = Q_info.q2;
    float q3 = Q_info.q3;
    float q0q0 = q0 * q0;
    float q0q1 = q0 * q1;
    float q0q2 = q0 * q2;
    //float q0q3 = q0 * q3;
    float q1q1 = q1 * q1;
    //float q1q2 = q1 * q2;
    float q1q3 = q1 * q3;
    float q2q2 = q2 * q2;
    float q2q3 = q2 * q3;
    float q3q3 = q3 * q3;
    // float delta_2 = 0;

    //对加速度数据进行归一化 得到单位加速度
    float norm = fast_sqrt(ax * ax + ay * ay + az * az);
    ax = ax * norm;
    ay = ay * norm;
    az = az * norm;

    //根据当前四元数的姿态值来估算出各重力分量。用于和加速计实际测量出来的各重力分量进行对比，从而实现对四轴姿态的修正
    vx = 2 * (q1q3 - q0q2);
    vy = 2 * (q0q1 + q2q3);
    vz = q0q0 - q1q1 - q2q2 + q3q3;
    //vz = (q0*q0-0.5f+q3 * q3) * 2;

    //叉积来计算估算的重力和实际测量的重力这两个重力向量之间的误差。
    ex = ay * vz - az * vy;
    ey = az * vx - ax * vz;
    ez = ax * vy - ay * vx;

    //用叉乘误差来做PI修正陀螺零偏，
    //通过调节 param_Kp，param_Ki 两个参数，
    //可以控制加速度计修正陀螺仪积分姿态的速度。
    I_ex += halfT * ex;   // integral error scaled by Ki
    I_ey += halfT * ey;
    I_ez += halfT * ez;

    gx = gx + param_Kp * ex + param_Ki * I_ex;
    gy = gy + param_Kp * ey + param_Ki * I_ey;
    gz = gz + param_Kp * ez + param_Ki * I_ez;


    /*数据修正完成，下面是四元数微分方程*/


    //四元数微分方程，其中halfT为测量周期的1/2，gx gy gz为陀螺仪角速度，以下都是已知量，这里使用了一阶龙哥库塔求解四元数微分方程
    q0 = q0 + (-q1 * gx - q2 * gy - q3 * gz) * halfT;
    q1 = q1 + (q0 * gx + q2 * gz - q3 * gy) * halfT;
    q2 = q2 + (q0 * gy - q1 * gz + q3 * gx) * halfT;
    q3 = q3 + (q0 * gz + q1 * gy - q2 * gx) * halfT;
    //    delta_2=(2*halfT*gx)*(2*halfT*gx)+(2*halfT*gy)*(2*halfT*gy)+(2*halfT*gz)*(2*halfT*gz);
    // 整合四元数率    四元数微分方程  四元数更新算法，二阶毕卡法
    //    q0 = (1-delta_2/8)*q0 + (-q1*gx - q2*gy - q3*gz)*halfT;
    //    q1 = (1-delta_2/8)*q1 + (q0*gx + q2*gz - q3*gy)*halfT;
    //    q2 = (1-delta_2/8)*q2 + (q0*gy - q1*gz + q3*gx)*halfT;
    //    q3 = (1-delta_2/8)*q3 + (q0*gz + q1*gy - q2*gx)*halfT


    // normalise quaternion
    norm = fast_sqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
    Q_info.q0 = q0 * norm;
    Q_info.q1 = q1 * norm;
    Q_info.q2 = q2 * norm;
    Q_info.q3 = q3 * norm;
}

char Gyroscope_Init()
{
#if ICM2062_EN
    return icm20602_init();
#endif
#if IMU660RA_EN
    return imu660ra_init();
#endif
    return 0;
}


/************************************************************************************************************************
 *@brief......把四元数转换成欧拉角
 *@return.....无
 ***********************************************************************************************************************/
void getEulerianAngles(void) {

    //采集陀螺仪数据
#if ICM2062_EN
    icm20602_get_gyro();
    icm20602_get_acc();
    getValues();
    AHRSupdate(icm_data.gyro_x, icm_data.gyro_y, icm_data.gyro_z, icm_data.acc_x, icm_data.acc_y, icm_data.acc_z);
#endif
#if IMU660RA_EN
    imu660ra_get_gyro();
    imu660ra_get_acc();
    getValues();
    AHRSupdate(imu660ra_data.gyro_x, imu660ra_data.gyro_y, imu660ra_data.gyro_z, imu660ra_data.acc_x, imu660ra_data.acc_y, imu660ra_data.acc_z);
#endif

    float q0 = Q_info.q0;
    float q1 = Q_info.q1;
    float q2 = Q_info.q2;
    float q3 = Q_info.q3;

    //四元数计算欧拉角
    eulerAngle.pitch = asin(-2 * q1 * q3 + 2 * q0 * q2) * 180 / PI; // pitch
    eulerAngle.roll = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2 * q2 + 1) * 180 / PI; // roll
    eulerAngle.yaw = atan2(2 * q1 * q2 + 2 * q0 * q3, -2 * q2 * q2 - 2 * q3 * q3 + 1) * 180 / PI; // yaw

/*   姿态限制*/
    if (eulerAngle.roll > 90 || eulerAngle.roll < -90) {
        if (eulerAngle.pitch > 0) {
            eulerAngle.pitch = 180 - eulerAngle.pitch;
        }
        if (eulerAngle.pitch < 0) {
            eulerAngle.pitch = -(180 + eulerAngle.pitch);
        }
    }

    if (eulerAngle.yaw > 360) {
        eulerAngle.yaw -= 360;
    } else if (eulerAngle.yaw < 0) {
        eulerAngle.yaw += 360;
    }
    if (yaw_revise_flag == 1) {
        eulerAngle.yaw -= yaw_revise_data;
        eulerAngle.yaw = (eulerAngle.yaw <= 0.0) ? (360 + eulerAngle.yaw) : eulerAngle.yaw;
    }
}
