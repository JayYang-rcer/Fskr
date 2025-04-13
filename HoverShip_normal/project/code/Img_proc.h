#include "zf_common_headfile.h"

#define White 255         //颜色阈值
#define Black 0

#ifndef _IMG_PROC_H
#define _IMG_PROC_H

//#include "zf_common_headfile.h"
#include "stdint.h"



#define AT(img,x,y)      (img->pixel[y * img->width + x])


//图像结构体
typedef struct{
    uint8_t *pixel;
    uint8_t height;
    uint8_t width;
}imag_t;


//点结构体
typedef struct{
    uint8_t x;
    uint8_t y;
    uint8_t find;
}point_t;

//直线结构体
typedef struct{
    float k;
    float b;
    float variance;
    int var_cal;
}straight_t;

//方向枚举
enum dir{
    left_down=0,
    right_down,
    left_up,
    right_up
};

//赛道枚举
enum trace_t{
    normal,
    circle,
    cross,
    barrier,
    garage,
};

//赛道信息结构体
typedef struct{
    uint8_t left_grow[128][4];           //生长信息
    uint8_t right_grow[128][4];
    uint8_t L_back_grow;
    uint8_t R_back_grow;
    uint8_t up_left_grow;
    uint8_t up_right_grow;
    uint8_t down_left_grow;
    uint8_t down_right_grow;
    uint8_t left_growth;
    uint8_t right_growth;
    point_t L_down_inf;                  //直角拐点
    point_t R_down_inf;
    point_t L_up_inf;
    point_t R_up_inf;
    point_t L_down_point;                //普通拐点
    point_t R_down_point;
    point_t L_up_point;
    point_t R_up_point;
    point_t v_L_point;                //V型左拐点
    point_t v_R_point;                //V型右拐点
    point_t L_maximum;                   //极大值点
    point_t R_maximum;
    point_t R_lose_line;
    point_t L_lose_line;
    point_t R_start_line;                //有效起点
    point_t L_start_line;
    point_t max_point;
}msg_t;

extern uint8_t dynamic_foresight;

/*初始化函数*/
//点结构体初始化
void point_init(point_t* point);
//图像变量初始化
void imag_var_init(msg_t* msg);

//大津法计算动态全局阈值
uint8_t getOSTUthreshold(imag_t *img);
//二值化图像
void binarization(imag_t *img, uint8_t Threshold);
//寻找最长白列
point_t  find_longest_white_column(const imag_t* imag,uint8_t interval);
//寻找种子
void find_L_down_seed(point_t longest_white,point_t *seed, const imag_t* imag);
void find_R_down_seed(point_t longest_white,point_t *seed, const imag_t* imag);
void find_R_up_seed(point_t longest_white,point_t *seed, const imag_t* imag);
void find_L_up_seed(point_t longest_white,point_t *seed, const imag_t* imag);
//迷宫法左右巡线
void findline_lefthand_up(const point_t *seed,uint16_t num,const imag_t* imag, msg_t* msg);
void findline_righthand_up(const point_t *seed,uint16_t num,const imag_t* imag, msg_t* msg);
void findline_lefthand_down(const point_t *seed, uint16_t num,const imag_t* imag, msg_t* msg);
void findline_righthand_down(const point_t *seed, uint16_t num,const imag_t* imag, msg_t* msg);
void show_borderLine(void);
//寻找直角拐点
void find_L_down_straight_inflection(uint8_t start, uint8_t end, msg_t *msg);
void find_R_down_straight_inflection(uint8_t start, uint8_t end, msg_t *msg);
void find_L_up_straight_inflection(uint8_t start, uint8_t end, msg_t *msg);
void find_R_up_straight_inflection(uint8_t start, uint8_t end, msg_t *msg);
//寻找V形拐点
void V_point_check(uint8_t start, uint8_t end,uint8_t *left_line,uint8_t *right_line,msg_t* msg);
//圆环左圆环入口检测
uint8_t L_circle_entry_check(uint8_t *left_line);
//检测右 圆环的入口
uint8_t R_circle_entry_check(uint8_t *right_line);
//左圆环拐点判断
void find_circle_L_up(uint8_t *line, msg_t* msg);
void find_circle_R_down(uint8_t start, uint8_t end,msg_t* msg);
//右圆环拐点判断
void find_circle_L_down(uint8_t start, uint8_t end, msg_t* msg);
void find_circle_R_up(uint8_t *line, msg_t* msg);

//获取丢线次数
uint8_t get_lose_line(uint8_t *line, uint8_t start, uint8_t end);
//拟合中线
void match_mid_line(uint8_t start, uint8_t end,uint8_t *m_line, const uint8_t *l_line, const uint8_t *r_line);
//计算偏差
float get_mid_deviation(uint8_t mid_value);
void Angle_Process(uint8_t val_line);
//冲出检测
uint8_t rush_check(imag_t* imag,point_t l_w );

//以下未加
//跟踪左右边线
void trace_rightLine(uint8_t *rightLine, uint8_t *midLine);
void trace_leftLine(uint8_t *leftLine, uint8_t *midLine);
void find_R(uint8_t *right_Line ,uint8_t start, uint8_t end, msg_t* msg);
void find_L(uint8_t *left_Line ,uint8_t start, uint8_t end, msg_t* msg);
void find_L_Start( uint8_t *left_Line,uint8_t start, uint8_t end, msg_t* msg);
void find_R_Start( uint8_t *left_Line,uint8_t start, uint8_t end, msg_t* msg);
uint8_t circle_find_L_lose(uint8_t *left_Line ,uint8_t start, uint8_t end);
void find_L_up_circle_inflection(uint8_t start, uint8_t end, msg_t* msg);
uint8_t transversals_out_check(imag_t* imag);
uint8_t transversals_entry_check(imag_t* imag);

//这个加了
//计算中线
void calculate_mid_line(uint8_t startline, uint8_t endline);

//检测弯道
uint8 Curve_exam(void);

#endif
