#include "Img_proc.h"

uint8_t left_line[MT9V03X_DVP_H];                       //��������
uint8_t right_line[MT9V03X_DVP_H];
uint8_t middle_line[MT9V03X_DVP_H];

//��Ļ��ʾ�õ���ɨ������
uint8_t L_down_border[200][2];
uint8_t R_down_border[200][2];
uint8_t lose_line_thres = 40;       //������ֵ�����������ʱ�ҵ���������Ч
uint8_t fore_sight = 60;            //ǰհ
//��̬ǰհ
uint8_t dynamic_foresight = 75;
uint8_t is_check_cricle = 1;
uint8_t is_check_fork = 0;
uint8_t is_check_transversals = 1;
uint8_t is_check_stop = 1;          //ͣ����⣬Ĭ�Ͽ���
uint8_t is_fixed_flag = 0;          //�̶���ֵ��Ĭ�ϲ�����

extern enum cross_type_e cross_type;
extern straight_t L_stra;           //ֱ��
extern straight_t R_stra;
extern straight_t M_stra;
extern point_t L_down_seed;         //�·�Ѳ������
extern point_t R_down_seed;
extern point_t longest_white;       //�����
extern imag_t imag;
extern float mid_deviation;
extern enum trace_t trace_position;
//��Ļ��ʾ�õ���ɨ������
uint8_t L_down_border[200][2];
uint8_t R_down_border[200][2];
uint8_t L_up_border[200][2];
uint8_t R_up_border[200][2];

uint8_t lose_cnt =0;
int16_t encoder_count = 0;
uint8_t encoder_switch = 0;  //��������������

uint8_t half_width[60] = {58,59,60,61,61,62,63,64,64,65,
                           66,66,66,68,68,69,70,70,71,72,
                           72,73,74,74,75,75,75,76,76,76,
                           77,77,77,78,78,78,79,79,79,79,
                           79,79,79,79,79,79,79,79,79,79,
                           79,79,79,79,79,79,79,79,79,79};

//-------------------------------------------------------------------------------------------------------------------




/************************************************************************************************************************
 *@brief....������ĳ�ʼ��
 ***********************************************************************************************************************/
void point_init(point_t* point) {
    point->find = 0;
    point->x = 0;
    point->y = 0;
}

/************************************************************************************************************************
 *@brief......ͼ��ṹ������ĳ�ʼ��
 ***********************************************************************************************************************/
void imag_var_init(msg_t* msg)
{
    L_stra.b = 0.;
    L_stra.k = 0.;
    L_stra.variance = 0.;
    L_stra.var_cal = 0;

    R_stra.b = 0.;
    R_stra.k = 0.;
    R_stra.variance = 0.;
    R_stra.var_cal = 0;

    for(uint8_t i=0;i<MT9V03X_DVP_H;i++) {
        left_line[i] = 0;
        right_line[i] = MT9V03X_DVP_W-1;
        middle_line[i] = MT9V03X_DVP_W/2;
        for(uint8_t j=0;j<4;j++) {
            msg->left_grow[i][j]=0;
            msg->right_grow[i][j]=0;
        }

    }
    msg->L_back_grow=0;
    msg->R_back_grow=0;
    msg->up_left_grow=0;
    msg->up_right_grow=0;
    msg->down_left_grow=0;
    msg->down_right_grow=0;
    msg->left_growth=0;
    msg->right_growth=0;

    point_init(&(msg->L_down_inf));
    point_init(&(msg->R_down_inf));
    point_init(&(msg->L_up_inf));
    point_init(&(msg->R_up_inf));
    point_init(&(msg->L_down_point));
    point_init(&(msg->R_down_point));
    point_init(&(msg->L_up_point));
    point_init(&(msg->R_up_point));
    point_init(&(msg->L_maximum));
    point_init(&(msg->R_maximum));
    point_init(&(msg->v_L_point));
    point_init(&(msg->v_R_point));
}


/**********************************************************************************************************************
 *@brief......���ô�򷨵ó�ͼ����ֵ
 *@param      img        ͼ�������飬���ÿ�����ص�ĻҶ�ֵ
 *@return.....����ó�����ֵ
**********************************************************************************************************************/
uint8_t getOSTUthreshold(imag_t *img)
{
    uint8_t Histogram[256] = {0};//�Ҷ�ֱ��ͼ
    uint16_t OstuThreshold = 0;

    uint8_t *ptr = img->pixel;
    uint8_t *ptr_end = img->pixel + img->height * img->width; //ָ�����һ�����ص����һ��


    while (ptr != ptr_end){						//����ÿ���Ҷȼ�������
       ++Histogram[*ptr++];
    }


    uint8_t MinGrayVal, MaxGrayVal;

    for(MinGrayVal = 0; MinGrayVal<255 && Histogram[MinGrayVal] == 0; ++MinGrayVal);//�ҵ�ĳ�Ҷȼ����ص���Ϊ0����С�Ҷȼ�
    for(MaxGrayVal = 255; MaxGrayVal > MinGrayVal && Histogram[MaxGrayVal] == 0; --MaxGrayVal);//�ҵ�ĳ�Ҷȼ����ص���Ϊ0�����Ҷȼ�

    if(MaxGrayVal == MinGrayVal)//ֻ��һ����ɫ
        return MaxGrayVal;

    if(MaxGrayVal == MinGrayVal + 1)//ֻ��������ɫ
        return MinGrayVal;

    uint16_t Pixel_Intergral =0;
    uint64_t All_GrayIntegral = 0;
    for(uint16_t i = MinGrayVal; i <= MaxGrayVal; i++)
    {
        Pixel_Intergral += Histogram[i];  //���ص��ܺ�
        All_GrayIntegral += i*Histogram[i]; //ͼ��Ҷ��ܺ�
    }

    uint32_t ForePixel = 0;
    uint32_t Fore_GrayIntergral = 0;
    uint32_t Back_GrayIntergral = 0;

    float w0 = 0.0;//ǰ�����ص�ռ����ͼ��ı���
    float w1 = 0.0;//�����ص�ռ����ͼ��ı���
    int32_t u0 = 0;//ǰ������ƽ���Ҷ�
    int32_t u1 = 0;//��������ƽ���Ҷ�
    uint64_t MaxVariance = 0;//��󷽲�


    for (uint16_t i = MinGrayVal; i <= MaxGrayVal; i++) 
    {
        ForePixel += Histogram[i];
        w0 = (float)ForePixel/Pixel_Intergral;
        w1 = 1- w0;

        Fore_GrayIntergral += i * Histogram[i];
        u0 = (int32_t)Fore_GrayIntergral / w0;//ǰ��ƽ���Ҷ�(����Pixel_Intergral�ı���������ȶ���)
        Back_GrayIntergral = All_GrayIntegral - Fore_GrayIntergral;
        u1 = (int32_t)Back_GrayIntergral / w1;//����ƽ���Ҷ�(����Pixel_Intergral�ı���������ȶ���)

        uint64_t Variance = (uint64_t)(w0*w1*(u0-u1)*(u0-u1));
        if(Variance > MaxVariance){
            MaxVariance = Variance;
            OstuThreshold = i;
        }
//        if(Variance < MaxVariance)      //�����½�ʱ�˳�������������С,�ŵ��Ǽ���������
//        {
//            break;
//        }
    }
    return OstuThreshold;

}


/**********************************************************************************************************************
 *@brief......��ÿ�����ص���ж�ֵ��
 *@param img......ͼ������
 *@param Threshold......���бȽϵ���ֵ
 *@return.....��
 **********************************************************************************************************************/
void binarization(imag_t *img, uint8_t Threshold)
{
    uint8_t* ptr = img->pixel;
    uint8_t* ptr_end = img->pixel + img->height * img->width; //ָ�����һ�����ص�

    while(ptr != ptr_end)
        *ptr++ =  (((*ptr) > Threshold)? White:Black);
}


/**********************************************************************************************************************
 *@brief......Ѱ�������
 *@param      imag        ��ֵ��ͼ��ָ��
 *@param      interval    ÿ��ɨ��ĸ�������
 *@return.....��
**********************************************************************************************************************/
point_t  find_longest_white_column(const imag_t* imag,uint8_t interval)
{
    point_t tmp_point;
    point_init(&tmp_point);  //��ʼ��
    uint8_t max_len = 0;
    uint8_t white_num = 0;
    uint8_t jump = 0;
//    uint8_t width = imag->width;
//    if(cross_type == CROSS_IN)   width = 50;

    for (uint8_t i = 5; i < imag->width && jump == 0; i += interval) //ÿ��10��ȡһ�Σ��ӵ�4�п�ʼ
    {
        if (i + interval < imag->width && imag->pixel[127 * imag->width + i] == 255 && imag->pixel[127 * imag->width + i + interval] &&
            imag->pixel[126 * imag->width + i + interval] == 0) break; //��ֹ���ұ߽�

        white_num = 0;

        for (int8_t j = 127; j >= 0 && imag->pixel[127 * imag->width + i] == 255; j--) //ÿ��1��ȡһ�Σ��ӵ�127�п�ʼ
        {
            if (imag->pixel[j * imag->width + i] == 255)
            {
                white_num++;

                if (white_num >= 127)
                {
                    max_len = 127;
                    tmp_point.x = i;
                    tmp_point.y = j;
                    tmp_point.find = 1;//�ҵ�����
                    jump = 1;
                    break;
                }
            }
            if (j-3 >= 0 && imag->pixel[j * imag->width + i] == 255 && imag->pixel[(j - 1) * imag->width + i] == 0 &&
                imag->pixel[(j - 2) * imag->width + i] == 0 && imag->pixel[(j - 3) * imag->width + i] == 0)
            {
                uint8_t len = 128 - j;
                if (len > max_len)
                {
                    max_len = len;
                    tmp_point.x = i;
                    tmp_point.y = j;
                    tmp_point.find = 1;//�ҵ�����
                }
                break;
            }

        }
    }
    if(tmp_point.find)
    {
        if(cross_type == CROSS_ENTERING)
        {
            uint8_t sum = 0;
            for(uint8 x = 10;x < 51;x++)
            {
                if(imag->pixel[x*(MT9V03X_DVP_W)] == 255)   sum++;
            }
            if(tmp_point.x < 30 &&  sum > 38)
            {
                for(; tmp_point.x + 3 < MT9V03X_DVP_W; tmp_point.x++)
                {
                    if (imag->pixel[3*(MT9V03X_DVP_W) + tmp_point.x] == 0 && imag->pixel[3*(MT9V03X_DVP_W) + tmp_point.x + 1] == 255 && imag->pixel[3*(MT9V03X_DVP_W) + tmp_point.x + 2] == 255 && imag->pixel[3*(MT9V03X_DVP_W) + tmp_point.x + 3] == 255)
                    {
                        tmp_point.x += 3;
                        break;
                    }
                }
            }
        }

    }
    return tmp_point;

}


/**********************************************************************************************************************
*  @brief      Ѱ����������
*  @param      longest_white  ���������
*  @param      seed           �����ҵ�������
*  @param      imag           ��ֵ��ͼ��ָ��
*  @return     void
***********************************************************************************************************************/
void find_L_down_seed(point_t longest_white,point_t *seed, const imag_t* imag) {
    point_init(&L_down_seed);

    for(uint8_t i = MT9V03X_DVP_H - 2; i >= lose_line_thres  && seed->find == 0; i--) {
        for(uint8_t j = longest_white.x; j - 3 >= 0; j--) {
            if (imag->pixel[i*(MT9V03X_DVP_W) + j] == 255 && imag->pixel[i*(MT9V03X_DVP_W) + j - 1] == 0 &&
                imag->pixel[i*(MT9V03X_DVP_W) + j - 2] == 0 && imag->pixel[i*(MT9V03X_DVP_W) + j - 3] == 0) {
                seed->x = j;
                seed->y = i;
                seed->find = 1;
                break;
            }
        }
    }
}


/**********************************************************************************************************************
*  @brief      Ѱ����������
*  @param      longest_white  ���������
*  @param      seed           �����ҵ�������
*  @param      imag           ��ֵ��ͼ��ָ��
*  @return     void
***********************************************************************************************************************/
void find_R_down_seed(point_t longest_white,point_t *seed, const imag_t* imag) {
    point_init(&R_down_seed);
    for(uint8_t i = MT9V03X_DVP_H - 2; i >= lose_line_thres && seed->find == 0; i--) {
        for(uint8_t j = longest_white.x; j + 3 < MT9V03X_DVP_W; j++) {
            if (imag->pixel[i*(MT9V03X_DVP_W) + j] == 255 && imag->pixel[i*(MT9V03X_DVP_W) + j + 1] == 0 &&
                imag->pixel[i*(MT9V03X_DVP_W) + j + 2] == 0 && imag->pixel[i*(MT9V03X_DVP_W) + j + 3] == 0) {
                seed->x = j;
                seed->y = i;
                seed->find = 1;
                break;
            }
        }
    }
}

/**********************************************************************************************************************
*  @brief      Ѱ����������
*  @param      longest_white  ���������
*  @param      seed           �����ҵ�������
*  @param      imag           ��ֵ��ͼ��ָ��
*  @return     void
***********************************************************************************************************************/
void find_L_up_seed(point_t longest_white,point_t *seed, const imag_t* imag) {
    point_init(seed);

    for(uint8_t i = longest_white.y; i <= 30  && seed->find == 0; i++) {
        for(uint8_t j = longest_white.x; j - 3 >= 0; j--) {
            if (imag->pixel[i*(MT9V03X_DVP_W) + j] == 255 && imag->pixel[i*(MT9V03X_DVP_W) + j - 1] == 0 && imag->pixel[i*(MT9V03X_DVP_W) + j - 2] == 0 && imag->pixel[i*(MT9V03X_DVP_W) + j - 3] == 0) {
                seed->x = j;
                seed->y = i;
                seed->find = 1;
                break;
            }
        }
    }
}

/**********************************************************************************************************************
*  @brief      Ѱ����������
*  @param      longest_white  ���������
*  @param      seed           �����ҵ�������
*  @param      imag           ��ֵ��ͼ��ָ��
*  @return     void
***********************************************************************************************************************/
void find_R_up_seed(point_t longest_white,point_t *seed, const imag_t* imag) {
    point_init(seed);

    for(uint8_t i = longest_white.y; i <= 30  && seed->find == 0; i++) {
        for(uint8_t j = longest_white.x; j + 3 < MT9V03X_DVP_W; j++) {
            if (imag->pixel[i*(MT9V03X_DVP_W) + j] == 255 && imag->pixel[i*(MT9V03X_DVP_W) + j + 1] == 0 && imag->pixel[i*(MT9V03X_DVP_W) + j + 2] == 0 && imag->pixel[i*(MT9V03X_DVP_W) + j + 3] == 0) {
                seed->x = j;
                seed->y = i;
                seed->find = 1;
                break;
            }
        }
    }
}




int8_t dir_front[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
int8_t dir_frontleft[4][2] = {{-1, -1}, {1, -1}, {1, 1}, {-1, 1}};
int8_t dir_frontright[4][2] = {{1, -1}, {1, 1}, {-1, 1}, {-1, -1}};

/**********************************************************************************************************************
*  @brief      ���������Թ�ɨ��
*  @param      seed           ��ʼ����
*  @param      num            Ѱ�ҵ�ĸ���
*  @param      imag           ��ֵ��ͼ��ָ��
*  @param     msg             ������Ϣ�ṹ��
*  @return     void
***********************************************************************************************************************/
void findline_lefthand_up(const point_t *seed,uint16_t num, const imag_t* imag, msg_t* msg) {
    uint16_t step = 0, dir = 0, turn = 0;
    uint8_t x=seed->x, y=seed->y;
    if(y<100)   return;

    while (step < num && 0 < x && x < MT9V03X_DVP_W - 1 && 0 < y && y < MT9V03X_DVP_H - 1 && turn < 4){
        uint8_t front_value = imag->pixel[(y + dir_front[dir][1])*(MT9V03X_DVP_W) + (x + dir_front[dir][0])];
        uint8_t frontleft_value = imag->pixel[(y + dir_frontleft[dir][1])*(MT9V03X_DVP_W) + (x + dir_frontleft[dir][0])];
        if (front_value == 0) {
            dir = (dir + 1) % 4;
            turn++;
        } else if (frontleft_value == 0) {
            x += dir_front[dir][0];
            y += dir_front[dir][1];
            msg->left_grow[y][dir]++;
            if(dir == 3)
                msg->up_left_grow++;
            if(left_line[y] == 0)
                left_line[y] = x;
            L_down_border[step][0]=x;
            L_down_border[step][1]=y;
            step++;
            turn = 0;
        } else {
            x += dir_frontleft[dir][0];
            y += dir_frontleft[dir][1];
            msg->left_grow[y][dir]++;
            if(dir == 3)
                msg->up_left_grow++;
            dir = (dir + 3) % 4;
            if(left_line[y] == 0)
                left_line[y] = x;
            L_down_border[step][0]=x;
            L_down_border[step][1]=y;
            step++;
            turn = 0;
        }
    }


}

/**********************************************************************************************************************
*  @brief      ���������Թ�ɨ��
*  @param      seed           ��ʼ����
*  @param      num            Ѱ�ҵ�ĸ���
*  @param      imag           ��ֵ��ͼ��ָ��
*  @param      msg            ������Ϣ�ṹ��
*  @return     void
***********************************************************************************************************************/
void findline_righthand_up(const point_t *seed,uint16_t num,const imag_t* imag,msg_t* msg) {
    uint16_t step = 0, dir = 0, turn = 0;
    uint8_t x=seed->x, y=seed->y;
    if(y<100)   return;

    while (step < num && 0 < x && x < MT9V03X_DVP_W - 1 && 0 < y && y < MT9V03X_DVP_H - 1 && turn < 4){
        uint8_t front_value = imag->pixel[(y + dir_front[dir][1])*(MT9V03X_DVP_W) + (x + dir_front[dir][0])];
        uint8_t frontright_value = imag->pixel[(y + dir_frontright[dir][1])*(MT9V03X_DVP_W) + (x + dir_frontright[dir][0])];
        if (front_value == 0) {
            dir = (dir + 3) % 4;
            turn++;
        } else if (frontright_value == 0) {
            x += dir_front[dir][0];
            y += dir_front[dir][1];
            msg->right_grow[y][dir]++;
            if(dir == 1)
                msg->up_right_grow++;
            if(right_line[y] == MT9V03X_DVP_W - 1)
                right_line[y] = x;
            R_down_border[step][0]=x;
            R_down_border[step][1]=y;
            step++;
            turn = 0;
        } else {
            x += dir_frontright[dir][0];
            y += dir_frontright[dir][1];
            msg->right_grow[y][dir]++;
            if(dir == 1)
                msg->up_right_grow++;
            dir = (dir + 1) % 4;
            if(right_line[y] == MT9V03X_DVP_W - 1)
                right_line[y] = x;
            R_down_border[step][0]=x;
            R_down_border[step][1]=y;
            step++;
            turn = 0;
        }
    }


}


int8_t dir_down[4][2] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};
int8_t dir_downright[4][2] = {{-1, 1}, {-1, -1}, {1, -1}, {1, 1}};
int8_t dir_downleft[4][2] = {{1, 1}, {-1, 1}, {-1, -1}, {1, -1}};

/**********************************************************************************************************************
*  @brief      ���������Թ�ɨ��
*  @param      seed           ��ʼ����
*  @param      num            Ѱ�ҵ�ĸ���
*  @param      imag           ��ֵ��ͼ��ָ��
*  @param      msg             ������Ϣ�ṹ��
*  @return     void
***********************************************************************************************************************/
void findline_righthand_down(const point_t *seed, uint16_t num, const imag_t* imag, msg_t* msg) {
    uint16_t step = 0, dir = 0, turn = 0;
    uint8_t *ptr = imag->pixel;
    uint8_t x=seed->x, y=seed->y;
    uint8_t last_y = 0;

    while (step < num && 0 < x && x < MT9V03X_DVP_W - 1 && 0 < y && y < MT9V03X_DVP_H - 1 && turn < 4){
        uint8_t down_value = ptr[(y + dir_down[dir][1])*(MT9V03X_DVP_W) + (x + dir_down[dir][0])];
        uint8_t downright_value = ptr[(y + dir_downright[dir][1])*(MT9V03X_DVP_W) + (x + dir_downright[dir][0])];
        if (down_value == 0) {
            dir = (dir + 3) % 4;
            turn++;
        } else if (downright_value == 0) {
            last_y = y;
            x += dir_down[dir][0];
            y += dir_down[dir][1];
            if(last_y > y)  msg->L_back_grow++;
            if(dir == 0){
                msg->left_grow[y][2]++;
            }else {
                msg->left_grow[y][dir]++;
            }
            if(left_line[y] == 0)
                left_line[y] = x;
            L_up_border[step][0]=x;
            L_up_border[step][1]=y;
            step++;
            turn = 0;
        } else {
            last_y = y;
            x += dir_downright[dir][0];
            y += dir_downright[dir][1];
            if(last_y > y)  msg->L_back_grow++;
            if(dir == 0){
                msg->left_grow[y][2]++;
            }else {
                msg->left_grow[y][dir]++;
            }
            dir = (dir + 1) % 4;
            if(left_line[y] == 0)
                left_line[y] = x;
            L_up_border[step][0]=x;
            L_up_border[step][1]=y;
            step++;
            turn = 0;
        }
    }
}

/**********************************************************************************************************************
*  @brief      ���������Թ�ɨ��
*  @param      seed           ��ʼ����
*  @param      num            Ѱ�ҵ�ĸ���
*  @param      imag           ��ֵ��ͼ��ָ��
*  @param     msg            ������Ϣ�ṹ��
*  @return     void
***********************************************************************************************************************/
void findline_lefthand_down(const point_t *seed, uint16_t num,const imag_t* imag,msg_t* msg) {
    uint16_t step = 0, dir = 0, turn = 0;
    uint8_t *ptr = imag->pixel;
    uint8_t x=seed->x, y=seed->y;
    uint8_t last_y = 0;

    while (step < num && 0 < x && x < MT9V03X_DVP_W - 1 && 0 < y && y < MT9V03X_DVP_H - 1 && turn < 4){
        uint8_t down_value = ptr[(y + dir_down[dir][1])*(MT9V03X_DVP_W) + (x + dir_down[dir][0])];
        uint8_t downleft_value = ptr[(y + dir_downleft[dir][1])*(MT9V03X_DVP_W) + (x + dir_downleft[dir][0])];
        if (down_value == 0) {
            dir = (dir + 1) % 4;
            turn++;
        } else if (downleft_value == 0) {
            last_y = y;
            x += dir_down[dir][0];
            y += dir_down[dir][1];
            if(last_y > y)  msg->R_back_grow++;
            if(dir == 0){
                msg->right_grow[y][2]++;
            }else {
                msg->right_grow[y][dir]++;
            }
            if(right_line[y] == MT9V03X_DVP_W-1)
                right_line[y] = x;
            R_up_border[step][0]=x;
            R_up_border[step][1]=y;

            step++;
            turn = 0;
        } else {
            last_y = y;
            x += dir_downleft[dir][0];
            y += dir_downleft[dir][1];
            if(last_y > y)  msg->R_back_grow++;
            if(dir == 0){
                msg->right_grow[y][2]++;
            }else {
                msg->right_grow[y][dir]++;
            }
            dir = (dir + 3) % 4;
            if(right_line[y] == MT9V03X_DVP_W-1)
                right_line[y] = x;
            R_up_border[step][0]=x;
            R_up_border[step][1]=y;
            step++;
            turn = 0;
        }
    }
}


/**********************************************************************************************************************
*  @brief      Ѱ������ֱ�ǹյ�
*  @param      msg            ������Ϣ�ṹ��
*  @param      start          ��Ѱ����ʼ��
*  @return     void
***********************************************************************************************************************/
void find_L_down_straight_inflection(uint8_t start, uint8_t end, msg_t *msg) {
    point_init(&(msg->L_down_inf));

    for(int16_t i = start; i >= end; i--) {
        if(msg->left_grow[i][3] >= 4){
            //�����ҵ��Ĺյ�����
            msg->L_down_inf.y = i+4;
            msg->L_down_inf.x = left_line[msg->L_down_inf.y];
            msg->L_down_inf.find = 1;
            break;
        }
    }
}

/**********************************************************************************************************************
*  @brief      Ѱ������ֱ�ǹյ�
*  @param      msg            ������Ϣ�ṹ��
*  @param      start          ��Ѱ����ʼ��
*  @return     void
***********************************************************************************************************************/
void find_R_down_straight_inflection(uint8_t start, uint8_t end, msg_t *msg) {
    point_init(&(msg->R_down_inf));

    for(int16_t i = start; i >= end; i--) {
        if(msg->right_grow[i][1] >= 4){
            //�����ҵ��Ĺյ�����
            msg->R_down_inf.y = i+4;
            msg->R_down_inf.x = right_line[msg->R_down_inf.y];
            msg->R_down_inf.find = 1;
            break;
        }
    }
}

/**********************************************************************************************************************
*  @brief      Ѱ������ֱ�ǹյ�
*  @param      msg            ������Ϣ�ṹ��
*  @param      start          ��Ѱ����ʼ��
*  @return     void
***********************************************************************************************************************/
void find_L_up_straight_inflection(uint8_t start, uint8_t end, msg_t* msg)
{
    point_init(&(msg->L_up_inf));
    //�����Ϲյ�
    for (int i = start; i < end; i++)
    {
        if (msg->left_grow[i][1] >= 4)
        {
            msg->L_up_inf.y = i-4;
            msg->L_up_inf.x = left_line[msg->L_up_inf.y];
            msg->L_up_inf.find = 1;//�ҵ���־λ
            break;
        }
    }
}

/**********************************************************************************************************************
*  @brief      Ѱ������ֱ�ǹյ�
*  @param      msg            ������Ϣ�ṹ��
*  @param      start          ��Ѱ����ʼ��
*  @return     void
***********************************************************************************************************************/
void find_R_up_straight_inflection(uint8_t start, uint8_t end, msg_t* msg)
{
    point_init(&(msg->R_up_inf));
    //�����Ϲյ�
    for (int i = start; i < end; i++)
    {
        if (msg->right_grow[i][3] >= 4)
        {
            msg->R_up_inf.y = i-4;
            msg->R_up_inf.x = right_line[msg->R_up_inf.y];
            msg->R_up_inf.find = 1;
            break;
        }
    }
}

/**********************************************************************************************************************
*  @brief      Ѱ��������ͨ�յ�
*  @param      msg            ������Ϣ�ṹ��
*  @return     void
***********************************************************************************************************************/
void find_L_down_point(uint8_t start, uint8_t end, msg_t *msg, enum trace_t type) {
    point_init(&(msg->L_down_point));

    if(type == circle){
        for(int16_t i = start; i-3 >= end && msg->L_down_point.find == 0; i--) {
             if(left_line[i] > left_line[i-1] && left_line[i] > left_line[i-2] && left_line[i] > left_line[i-3] &&
                left_line[i] != 0 && left_line[i-1] != 0 && left_line[i-2] !=0 && left_line[i-3] != 0) {
                //�������ң���������Ѱ�����кڰ�����ĵ㣨�����¹յ㣩
                 uint8_t sum = 0;
                 for(int16_t j=i-3-1; j>=i-3-5 && j>=end; j--) {
                     if(left_line[j] == 0) sum++;
                     if(sum>=2){
                         msg->L_down_point.y = i;
                         msg->L_down_point.x = left_line[msg->L_down_point.y];
                         msg->L_down_point.find = 1;
                         break;
                     }
                 }
            }
        }
    }
}

/**********************************************************************************************************************
*  @brief      Ѱ��������ͨ�յ�
*  @param      msg            ������Ϣ�ṹ��
*  @return     void
***********************************************************************************************************************/
void find_R_down_point(uint8_t start, uint8_t end, msg_t *msg, enum trace_t type) {
    point_init(&(msg->R_down_point));

    if(type == circle){
        for(int16_t i = start-3; i - 3 >= end && msg->R_down_point.find == 0; i--) {
            if(right_line[i] < right_line[i-1] && right_line[i] < right_line[i-2] && right_line[i] < right_line[i-3] &&
               right_line[i] != 159 && right_line[i-1] != 159 && right_line[i-2] !=159 && right_line[i-3] != 159)
                 {
                //�������󣬴������ϣ�Ѱ�����кڰ�����ĵ㣨�����¹յ㣩
                    uint8_t sum=0;
                    for(int16_t j=i-3-1; j>=i-3-5 && j>=end; j--) {
                         if(right_line[j] == 159) sum++;
                         if(sum>=2){
                             msg->R_down_point.y = i;
                             msg->R_down_point.x = right_line[msg->R_down_point.y];
                             msg->R_down_point.find = 1;
                             break;
                         }
                     }
                 }
            }
        }
}


/**********************************************************************************************************************
*  @brief      ��ʱ�����󻷵����Ϲյ�
*  @param      imag           ͼ����Ϣ
*              msg            ������Ϣ�ṹ��
*  @return     void
***********************************************************************************************************************/
void find_circle_L_up(uint8_t *line, msg_t* msg)
{
    point_init(&(msg->L_up_point));
    int16_t len = 0;
    for (int8_t y = 80; y > 0; y--)
    {
        len = line[y] - line[y+1];
        if (len >= 30)
        {
            msg->L_up_point.find = 1;
            msg->L_up_point.x = line[y];
            msg->L_up_point.y = y;
            break;
        }
    }
}

/**********************************************************************************************************************
*  @brief      ��ʱ�����󻷵����¹յ�
*  @param      imag           ͼ����Ϣ
*              msg            ������Ϣ�ṹ��
*  @return     void
***********************************************************************************************************************/
void find_circle_R_down(uint8_t start, uint8_t end, msg_t* msg) {
    point_init(&(msg->R_down_point));

    for (int16_t i = start; i >= end; i--) {
        if (right_line[i - 1] - right_line[i] > 0 && right_line[i - 2] - right_line[i] > 0 &&
                right_line[i - 3] - right_line[i] > 0  && right_line[i - 4] - right_line[i] > 0  &&
                right_line[i + 1] - right_line[i] >= 0 && right_line[i + 2] - right_line[i] >= 0 &&
                right_line[i + 3] - right_line[i] >= 0  && right_line[i + 4] - right_line[i] >= 0 &&
                right_line[i] != 159 && right_line[i + 4] != 159)
        {
            msg->R_down_point.y = i;
            msg->R_down_point.x = right_line[msg->R_down_point.y];
            msg->R_down_point.find = 1;
            break;
        }
    }
}

/**********************************************************************************************************************
*  @brief      ����� Բ�������
*  @param      msg            ������Ϣ�ṹ��
*  @return     void
***********************************************************************************************************************/
uint8_t L_circle_entry_check(uint8_t *left_line)
{
    uint8_t lose_start = MT9V03X_DVP_H - 5;
    uint8_t lose_end = 0;
    uint8_t increase_nums = 0;

    while(left_line[lose_start] == 0 && lose_start > 0) lose_start--;
    if (lose_start <= 80) //80
        return 0;

    while(left_line[lose_start] && lose_start > 0) lose_start--;
    if (lose_start <= 70)
            return 0;
    lose_end = lose_start;
    while(!left_line[lose_end] && lose_end >= 15) lose_end--;
    if (lose_start - lose_end >= 40)//
    {
        for (uint8_t row = lose_end; row-1 >= 0; row--)
        {
            if (left_line[row-1] > left_line[row])
                increase_nums++;
            if (increase_nums >= 3)
            {
                return 1;
            }
        }
    }


    return 0;
}

/**********************************************************************************************************************
*  @brief      �һ�ʱ�����һ������¹յ�
*  @param      msg            ������Ϣ�ṹ��
*  @return     void
***********************************************************************************************************************/
void find_circle_L_down(uint8_t start, uint8_t end, msg_t* msg) {
    point_init(&(msg->L_down_point));

    for (int16_t i = start; i >= end; i--) {
        if (left_line[i - 1] - left_line[i] < 0 && left_line[i - 2] - left_line[i] < 0 &&
            left_line[i - 3] - left_line[i] < 0  && left_line[i - 4] - left_line[i] < 0  &&
            left_line[i + 1] - left_line[i] <= 0 && left_line[i + 2] - left_line[i] <= 0 &&
            left_line[i + 3] - left_line[i] <= 0  && left_line[i + 4] - left_line[i] <= 0 &&
            left_line[i] != 0 && left_line[i + 4] != 0)
        {
            msg->L_down_point.y = i;
            msg->L_down_point.x = left_line[msg->L_down_point.y];
            msg->L_down_point.find = 1;
            break;
        }
    }
}

/**********************************************************************************************************************
*  @brief      �һ�ʱ�����һ������Ϲյ�
*  @param      msg            ������Ϣ�ṹ��
*  @return     void
***********************************************************************************************************************/

void find_circle_R_up(uint8_t *line,  msg_t* msg)
{
    point_init(&(msg->R_up_point));
    int16_t len = 0;
    for (int8_t y = 80; y > 0; y--)
    {
        len = line[y+1] - line[y];
        if (len >= 30)
        {
            msg->R_up_point.find = 1;
            msg->R_up_point.x = line[y];
            msg->R_up_point.y = y;
            break;
        }
    }
}

/**********************************************************************************************************************
*  @brief      ����� Բ�������
*  @param      msg            ������Ϣ�ṹ��
*  @return     void
***********************************************************************************************************************/
uint8_t R_circle_entry_check(uint8_t *right_line)
{
    uint8_t lose_start = MT9V03X_DVP_H - 5;
    uint8_t lose_end = 0;
    uint8_t decrease_nums = 0;

    while(right_line[lose_start] == 159 && lose_start > 0) lose_start--;
    if (lose_start <= 80) //80
        return 0;

    while(right_line[lose_start] != 159 && lose_start > 0) lose_start--;
    if (lose_start <= 70)
        return 0;
    lose_end = lose_start;
    while(right_line[lose_end] == 159 && lose_end >= 20) lose_end--;
    if (lose_start - lose_end >= 40)
    {
        for (uint8_t row = lose_end; row-1 >= 0; row--)
        {
            if (right_line[row-1] < right_line[row])
                decrease_nums++;
            if (decrease_nums >= 3)
            {
                return 1;
            }
        }
    }

    return 0;
}
/**********************************************************************************************************************
*  @brief      Ѱ��V�͹յ�
*  @param      l_line               ��߽�����
*  @param      r_line               �ұ߽�����
*  @param      msg            ������Ϣ�ṹ��
*  @return     void
***********************************************************************************************************************/
void V_point_check(uint8_t start, uint8_t end,uint8_t *left_line,uint8_t *right_line,msg_t* msg)
{
    point_init(&(msg->v_L_point));
    point_init(&(msg->v_R_point));
    for(uint8 x = start;x < end;x++)
    {
        if(left_line[x] != 0 && left_line[x+1] == 0 && left_line[x+2] == 0 && left_line[x+3] == 0)
        {
            if(msg->L_back_grow > 5)
            {
                msg->v_L_point.x = left_line[x];
                msg->v_L_point.y = x;
                msg->v_L_point.find = 1;
                break;
            }
        }
    }
    for(uint8 x = start;x < end;x++)
    {
        if(right_line[x] != 159 && right_line[x+1] == 159 && right_line[x+2] == 159 && right_line[x+3] == 159)
        {
            if(msg->R_back_grow > 5)
            {
                msg->v_R_point.x = right_line[x];
                msg->v_R_point.y = x;
                msg->v_R_point.find = 1;
                break;
            }
        }
    }
}

/**********************************************************************************************************************
*  @brief      ��ȡ���ߴ���
*  @param      line               �߽�����
*  @return     void
***********************************************************************************************************************/

uint8_t get_lose_line(uint8_t *line, uint8_t start, uint8_t end){
    uint8_t lose_sum=0;
    for(int16_t i=start; i>=end; i--){
        if(line[i] == 0 || line[i] == MT9V03X_DVP_W-1) lose_sum++;
    }
    return lose_sum;
}


/**********************************************************************************************************************
*  @brief      �������
*  @param      startline            ��ʼ��
*  @param      endline              ������
*  @param      m_line               ��������
*  @param      l_line               ��߽�����
*  @param      r_line               �ұ߽�����
*  @return     void
***********************************************************************************************************************/
void match_mid_line(uint8_t startline, uint8_t endline, uint8_t *m_line, const uint8_t *l_line, const uint8_t *r_line)
{
    if (startline < 40 || endline < 40)
        return;

    if (startline < endline) {
        uint8_t temp = startline;
        startline = endline;
        endline = temp;
    }

    for (int16_t i = startline; i >= endline; i--) {
        m_line[i] = (int)((l_line[i] + r_line[i]) / 2);
    }

}

/************************************************************************************************************************
 *@brief......��������
 ***********************************************************************************************************************/
void calculate_mid_line(uint8_t startline, uint8_t endline)
{
    for(int8_t i=startline; i>= endline; i--)
    {
        middle_line[i] = (uint8_t)((left_line[i]+right_line[i])/2);
    }
}



/**********************************************************************************************************************
*  @brief      ����ƫ��
*  @param      mid_value            ���߼���ֵ
*  @return     total;
***********************************************************************************************************************/
#define WEIGHT_1  0.35
#define WEIGHT_2  0.4
#define WEIGHT_3  0.35
#define WEIGHT_4  0.25
#define WEIGHT_5  0.2
#define WEIGHT_6  0.1

float normal_wight[6]={0.35, 0.4, 0.35, 0.25, 0.2, 0.1};
float fork_weight[6] = {0.35, 0.35, 0.30, 0.20, 0.1, 0.1};

uint8_t weight_type = 0;

#define MID_VALUE  80


float get_mid_deviation(uint8_t mid_value) {
    float dev1 = 0.0, dev2 = 0.0, dev3 = 0.0, dev4 = 0.0, dev5 = 0.0, dev6 = 0.0;
    float total = 0.0;
    for(uint8_t i=MT9V03X_DVP_H-1; i>=60; i--){
        if(i>=110) dev1 += mid_value - middle_line[i];
        if(100 <= i && i < 110) dev2 += mid_value - middle_line[i];
        if(90 <= i && i < 100) dev3 += mid_value - middle_line[i];
        if(80 <= i && i < 90) dev4 += mid_value - middle_line[i];
        if(70 <= i && i < 80) dev5 += mid_value - middle_line[i];
        if(60 <= i && i < 70) dev6 += mid_value - middle_line[i];
    }

    dev1 /= 10;
    dev2 /= 10;
    dev3 /= 10;
    dev4 /= 10;
    dev5 /= 10;
    dev6 /= 10;

    total =  WEIGHT_1 * dev1 +
             WEIGHT_2 * dev2 +
             WEIGHT_3 * dev3 +
             WEIGHT_4 * dev4 +
             WEIGHT_5 * dev5 +
             WEIGHT_6 * dev6;
    return total;
}

/**********************************************************************************************************************
*  @brief      ����Ƕ�λ��
*  @param      val_value            ���߼���ֵ
*  @return     total;
***********************************************************************************************************************/
float   mid_now = 0.000f;        //ȫͼ�������ĵ�ǰ���

float   mid_f = 0.000f, mid_ff = 0.000f;

void Angle_Process(uint8_t val_line)
{
    mid_now = MID_VALUE-middle_line[val_line];
    mid_ff = mid_f;
    mid_f =  mid_now;


    if(my_abs(mid_f-mid_ff) <= 5)
    {
        mid_deviation = 0.5*mid_f+0.5*mid_ff;
    }
    else if(5 < my_abs(mid_f-mid_ff) && my_abs(mid_f-mid_ff) <= 10)
    {
        if((mid_f >= 0 && mid_ff >= 0) || (mid_f < 0 && mid_ff < 0))
        {
            mid_deviation = 0.8*mid_f+0.2*mid_ff;
        }
        else {
            mid_deviation = mid_f;
        }
    }
    else if(10 < my_abs(mid_f-mid_ff))
    {
        mid_deviation = mid_f;
    }

}

/**********************************************************************************************************************
*  @brief      ������
*  @param      imag            ͼ����Ϣ
*  @return     total;
***********************************************************************************************************************/
uint8_t rush_check(imag_t* imag,point_t l_w )
{

    if(l_w.y >= 100 && is_check_stop==1)
    {
        return 1;
    }
    else {
        return 0;
    }
}

/**********************************************************************************************************************
*  @brief      �����ұ���
*  @param      Line            �ұ���
*  @return     void
***********************************************************************************************************************/
void trace_rightLine(uint8_t *rightLine, uint8_t *midLine)
{
    for (uint8_t i = 60; i < 120; i++) {
        uint8_t tmp = rightLine[i] - half_width[i-60];
        if (0 <= tmp && tmp <= 159) {
            midLine[i] = tmp;
        }
    }
}

/**********************************************************************************************************************
*  @brief      ���ٵ������
*  @param      msg            ������Ϣ�ṹ��
*  @return     void
***********************************************************************************************************************/
void trace_leftLine(uint8_t *leftLine, uint8_t *midLine)
{
    for (uint8_t i = 60; i < 120; i++) {
        uint8_t tmp = left_line[i] + half_width[i-60];
        if (0 <= tmp && tmp <= 159) {
            midLine[i] = tmp;
        }
    }
}

/**********************************************************************************************************************
*  @brief      ���ұ���
*  @param      msg            ������Ϣ�ṹ��
*  @return     void
***********************************************************************************************************************/
void find_R(uint8_t *right_Line ,uint8_t start, uint8_t end, msg_t* msg)
{//���ұ���Ч��

    uint8_t count_lose = 0;
    uint8_t i=end;

    for(i=end; i >= start+1; i--)
    {
        if( (right_Line[i-1]-right_Line[i]) >= 0)
        {
            if(count_lose++ >= 5)
            {
              msg->R_lose_line.y = i;
              break;
            }
        }

        else {
            count_lose=0;
            msg->R_lose_line.y = 20;
        }
    }

}

/**********************************************************************************************************************
*  @brief      �������
*  @param      msg            ������Ϣ�ṹ��
*  @return     void
***********************************************************************************************************************/
void find_L(uint8_t *left_Line ,uint8_t start, uint8_t end, msg_t* msg)
{//�������Ч��
    uint8_t count_lose = 0;
    uint8_t i=end;

    for(i=end; i >= start+1; i--)
    {
        if( (left_Line[i-1]-left_Line[i]) <= 0)
        {
            if(count_lose++ >= 5)
            {
              msg->L_lose_line.y = i;
              break;
            }
        }
        else {
            count_lose=0;
            msg->L_lose_line.y = 20;
        }
    }
}

/**********************************************************************************************************************
*  @brief      �뻷��߶���
*  @param      msg            ������Ϣ�ṹ��
*  @return     void
***********************************************************************************************************************/
uint8_t circle_find_L_lose(uint8_t *left_Line ,uint8_t start, uint8_t end)
{//�������Ч��
   // point_init(&(msg->R_maximum));
    uint8_t count_lose = 0;
    uint8_t i=end;
//    float sum,l_error_aver=0;
    for(i=end; i >= start+1; i--)
    {
        if(left_Line[i] == 0)
        {
            count_lose++;
        }
        else {
            return count_lose;
        }

    }
    return count_lose;
}

/**********************************************************************************************************************
*  @brief      ��������
*  @param      msg            ������Ϣ�ṹ��
*  @return     void
***********************************************************************************************************************/
void find_L_Start( uint8_t *left_Line,uint8_t start, uint8_t end, msg_t* msg) {

    //������
    for (int8_t i = end; i-1 >= start; i--)
    {
        if (left_Line[i] <= 2 && (left_Line[i-1] - left_Line[i]) != 0)
        {
            msg->L_start_line.y = i;
            break;
        }
        else {
            msg->L_start_line.y = 0;
        }
    }
}

/**********************************************************************************************************************
*  @brief      ���ұ����
*  @param      msg            ������Ϣ�ṹ��
*  @return     void
***********************************************************************************************************************/
void find_R_Start( uint8_t *right_Line,uint8_t start, uint8_t end, msg_t* msg) {
    //�ұ����
    for (int8_t i = end; i-1 >= start; i--)
    {
        if (right_Line[i] >= 158 && (right_Line[i-1] - right_Line[i]) != 0)
        {
            msg->R_start_line.y = i;
            break;
        }
        else {
            msg->R_start_line.y = 0;
        }
    }
}


/*******************************************************************************************************
*  @brief......tft��Ļ��ʾ���ұ���
************************************************************************************************************************/
void show_borderLine(void)
{
    for(uint i=0;i<MT9V03X_DVP_H;i++)    /*������ó��ı߽�����ʾ����*/
    {
        tft180_draw_point(L_down_border[i][0], L_down_border[i][1], RGB565_RED);
    }
    for(uint i=0;i<MT9V03X_DVP_H;i++)    /*������ó��ı߽�����ʾ����*/
    {
        tft180_draw_point(R_down_border[i][0], R_down_border[i][1], RGB565_GREEN);
    }
}



/*******************************************************************************************************
*  @brief......������
************************************************************************************************************************/
uint8 Curve_exam(void)
{
    uint8 i = 80;
    uint8 mid_length = 0;
    for (uint8 j = 127; j >= 0 && imag.pixel[j * imag.width + i] == 255; j--) //ÿ��1��ȡһ�Σ��ӵ�119�п�ʼ
    {
        mid_length++;
    }
    if(mid_length < 60 && (128-longest_white.y) < 127)
    {
        if(longest_white.x < 80)    return 1;
        else return 2;
    }
    else    return 0;
}











