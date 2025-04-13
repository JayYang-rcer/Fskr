#include "zf_common_headfile.h"

#define White 255         //��ɫ��ֵ
#define Black 0

#ifndef _IMG_PROC_H
#define _IMG_PROC_H

//#include "zf_common_headfile.h"
#include "stdint.h"



#define AT(img,x,y)      (img->pixel[y * img->width + x])


//ͼ��ṹ��
typedef struct{
    uint8_t *pixel;
    uint8_t height;
    uint8_t width;
}imag_t;


//��ṹ��
typedef struct{
    uint8_t x;
    uint8_t y;
    uint8_t find;
}point_t;

//ֱ�߽ṹ��
typedef struct{
    float k;
    float b;
    float variance;
    int var_cal;
}straight_t;

//����ö��
enum dir{
    left_down=0,
    right_down,
    left_up,
    right_up
};

//����ö��
enum trace_t{
    normal,
    circle,
    cross,
    barrier,
    garage,
};

//������Ϣ�ṹ��
typedef struct{
    uint8_t left_grow[128][4];           //������Ϣ
    uint8_t right_grow[128][4];
    uint8_t L_back_grow;
    uint8_t R_back_grow;
    uint8_t up_left_grow;
    uint8_t up_right_grow;
    uint8_t down_left_grow;
    uint8_t down_right_grow;
    uint8_t left_growth;
    uint8_t right_growth;
    point_t L_down_inf;                  //ֱ�ǹյ�
    point_t R_down_inf;
    point_t L_up_inf;
    point_t R_up_inf;
    point_t L_down_point;                //��ͨ�յ�
    point_t R_down_point;
    point_t L_up_point;
    point_t R_up_point;
    point_t v_L_point;                //V����յ�
    point_t v_R_point;                //V���ҹյ�
    point_t L_maximum;                   //����ֵ��
    point_t R_maximum;
    point_t R_lose_line;
    point_t L_lose_line;
    point_t R_start_line;                //��Ч���
    point_t L_start_line;
    point_t max_point;
}msg_t;

extern uint8_t dynamic_foresight;

/*��ʼ������*/
//��ṹ���ʼ��
void point_init(point_t* point);
//ͼ�������ʼ��
void imag_var_init(msg_t* msg);

//��򷨼��㶯̬ȫ����ֵ
uint8_t getOSTUthreshold(imag_t *img);
//��ֵ��ͼ��
void binarization(imag_t *img, uint8_t Threshold);
//Ѱ�������
point_t  find_longest_white_column(const imag_t* imag,uint8_t interval);
//Ѱ������
void find_L_down_seed(point_t longest_white,point_t *seed, const imag_t* imag);
void find_R_down_seed(point_t longest_white,point_t *seed, const imag_t* imag);
void find_R_up_seed(point_t longest_white,point_t *seed, const imag_t* imag);
void find_L_up_seed(point_t longest_white,point_t *seed, const imag_t* imag);
//�Թ�������Ѳ��
void findline_lefthand_up(const point_t *seed,uint16_t num,const imag_t* imag, msg_t* msg);
void findline_righthand_up(const point_t *seed,uint16_t num,const imag_t* imag, msg_t* msg);
void findline_lefthand_down(const point_t *seed, uint16_t num,const imag_t* imag, msg_t* msg);
void findline_righthand_down(const point_t *seed, uint16_t num,const imag_t* imag, msg_t* msg);
void show_borderLine(void);
//Ѱ��ֱ�ǹյ�
void find_L_down_straight_inflection(uint8_t start, uint8_t end, msg_t *msg);
void find_R_down_straight_inflection(uint8_t start, uint8_t end, msg_t *msg);
void find_L_up_straight_inflection(uint8_t start, uint8_t end, msg_t *msg);
void find_R_up_straight_inflection(uint8_t start, uint8_t end, msg_t *msg);
//Ѱ��V�ιյ�
void V_point_check(uint8_t start, uint8_t end,uint8_t *left_line,uint8_t *right_line,msg_t* msg);
//Բ����Բ����ڼ��
uint8_t L_circle_entry_check(uint8_t *left_line);
//����� Բ�������
uint8_t R_circle_entry_check(uint8_t *right_line);
//��Բ���յ��ж�
void find_circle_L_up(uint8_t *line, msg_t* msg);
void find_circle_R_down(uint8_t start, uint8_t end,msg_t* msg);
//��Բ���յ��ж�
void find_circle_L_down(uint8_t start, uint8_t end, msg_t* msg);
void find_circle_R_up(uint8_t *line, msg_t* msg);

//��ȡ���ߴ���
uint8_t get_lose_line(uint8_t *line, uint8_t start, uint8_t end);
//�������
void match_mid_line(uint8_t start, uint8_t end,uint8_t *m_line, const uint8_t *l_line, const uint8_t *r_line);
//����ƫ��
float get_mid_deviation(uint8_t mid_value);
void Angle_Process(uint8_t val_line);
//������
uint8_t rush_check(imag_t* imag,point_t l_w );

//����δ��
//�������ұ���
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

//�������
//��������
void calculate_mid_line(uint8_t startline, uint8_t endline);

//������
uint8 Curve_exam(void);

#endif
