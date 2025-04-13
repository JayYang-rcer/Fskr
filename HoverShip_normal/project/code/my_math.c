#include "my_math.h"


#define R_BORDER    160
#define MAX_ROW     128

//extern uint8_t middle_line[MT9V03X_DVP_H];
float parameterA=0,parameterB=0;

/**********************************************************************************************************************
*  @brief      ����ֵ
*  @param      x            �������ֵ
*  @return     double
***********************************************************************************************************************/
double my_abs(double x) {
    return x >= 0 ? x : -x;
}

/**********************************************************************************************************************
*  @brief      ��С���˷����ֱ��
*  @param      startline            ��ʼ��
*  @param      endline              ������
*  @param      line                 ��������
*  @param      stra                 ֱ�߽ṹ��
*  @return     void
***********************************************************************************************************************/
void regression(uint8_t startline, uint8_t endline, const uint8_t* line, straight_t *stra) {
    stra->b = 0.0;
    stra->k = 0.0;

    if(startline < endline) {
        uint8_t temp = startline;
        startline = endline;
        endline = temp;
    }
    uint8_t sumlines = 0;
    uint16_t sumX = 0,sumY = 0;
    float averageX = 0,averageY = 0,sumUp = 0,sumDown = 0;
    float parameterA=0,parameterB=0;

    for (int16_t i = startline; i >= endline; i-=4)
    {
        if(line[i] != 0 && line[i] != R_BORDER-1) {
            sumX += i;
            sumY += line[i];
            sumlines++;
        }

    }
    if (sumlines == 0) return;
    averageX = (float)(sumX / sumlines);     //x��ƽ��ֵ
    averageY = (float)(sumY / sumlines);     //y��ƽ��ֵ
    for (int16_t i = startline; i >= endline; i-=4)
    {
        if(line[i] != 0 && line[i] != R_BORDER-1) {
            sumUp += (line[i] - averageY) * (i - averageX);
            sumDown += (float)((i - averageX) * (i - averageX));
        }

    }
    if  (sumDown == 0) return;
    else parameterB = sumUp / sumDown;//б��
    parameterA = averageY - parameterB * averageX;//�ؾ�

    stra->k = parameterB;
    stra->b = parameterA;
}


/**********************************************************************************************************************
*  @brief      ����߽緽��
*  @param      line                 ��������
*  @param      stra                 ֱ�߽ṹ��
*  @return     void
***********************************************************************************************************************/
void calculate_variance(uint8_t start, uint8_t end, uint8_t* line, straight_t *stra) {
    uint8_t sum_line = 0;
    long long int deviation = 0;
    long long int sum_deviation = 0;

    stra->variance = 0.0;
    stra->var_cal = 0;

    for(int16_t i=start; i>=end; i--) {
        if(line[i] != 0 && line[i] != R_BORDER-1) {
            deviation = (line[i] - (stra->k * i + stra->b)) * (line[i] - (stra->k * i + stra->b));
            sum_deviation += deviation;
            sum_line++;
        }
    }
    if(sum_line != 0)
    {
        stra->variance = (float)sum_deviation / sum_line;
        stra->var_cal = 1;
    }

}

/**********************************************************************************************************************
*  @brief      ������ϵ�ֱ�߸����߸�ֵ
*  @param      startline            ��ʼ��
*  @param      endline              ������
*  @param      line                 ��������
*  @param      stra                 ֱ�߽ṹ��
*  @return     void
***********************************************************************************************************************/
void line_assignment(uint8_t startline, uint8_t endline, uint8_t *line, const straight_t *stra) {
    if(stra->k != 0.0) {
        int16_t value = 0;
        if(startline < endline) {
            uint8_t temp = startline;
            startline = endline;
            endline = temp;
        }
        for(int16_t i = startline; i >= endline; i--) {
            value = (stra->k * i + stra->b);
            if(0 <= value && value <= MT9V03X_DVP_W-1) {
                line[i] = (uint8_t)value;
            }
        }
    }
}

/**********************************************************************************************************************
*  @brief     �������ֱ��
*  @param     x1             ��1����ĺ�����
*  @param     y1             ��1�����������
*  @param     x2             ��2����ĺ�����
*  @param     y2             ��2�����������
*  @param     stra           ֱ�߽ṹ��
*  @return    void
***********************************************************************************************************************/
void two_points_fitting_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, straight_t* stra) {
    if (0 <= x1 && x1 < MAX_ROW && 0 <= x2 && x2 < MAX_ROW &&
        x1 !=x2 && 0 <= y1 && y1 < R_BORDER && 0 <= y2 && y2 < R_BORDER) {
        stra->k = (float)(y1 - y2) / (x1 - x2);
        stra->b = (float)y1 - stra->k * x1;
    }
}
