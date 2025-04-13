#include "Img_proc.h"

uint8_t left_line[MT9V03X_DVP_H];                       //边线数组
uint8_t right_line[MT9V03X_DVP_H];
uint8_t middle_line[MT9V03X_DVP_H];

//屏幕显示用到的扫描数组
uint8_t L_down_border[200][2];
uint8_t R_down_border[200][2];
uint8_t lose_line_thres = 40;       //丢线阈值，低于这个数时找到的种子无效
uint8_t fore_sight = 60;            //前瞻
//动态前瞻
uint8_t dynamic_foresight = 75;
uint8_t is_check_cricle = 1;
uint8_t is_check_fork = 0;
uint8_t is_check_transversals = 1;
uint8_t is_check_stop = 1;          //停车检测，默认开启
uint8_t is_fixed_flag = 0;          //固定阈值，默认不开启

extern enum cross_type_e cross_type;
extern straight_t L_stra;           //直线
extern straight_t R_stra;
extern straight_t M_stra;
extern point_t L_down_seed;         //下方巡线种子
extern point_t R_down_seed;
extern point_t longest_white;       //最长白列
extern imag_t imag;
extern float mid_deviation;
extern enum trace_t trace_position;
//屏幕显示用到的扫描数组
uint8_t L_down_border[200][2];
uint8_t R_down_border[200][2];
uint8_t L_up_border[200][2];
uint8_t R_up_border[200][2];

uint8_t lose_cnt =0;
int16_t encoder_count = 0;
uint8_t encoder_switch = 0;  //编码器计数开关

uint8_t half_width[60] = {58,59,60,61,61,62,63,64,64,65,
                           66,66,66,68,68,69,70,70,71,72,
                           72,73,74,74,75,75,75,76,76,76,
                           77,77,77,78,78,78,79,79,79,79,
                           79,79,79,79,79,79,79,79,79,79,
                           79,79,79,79,79,79,79,79,79,79};

//-------------------------------------------------------------------------------------------------------------------




/************************************************************************************************************************
 *@brief....点变量的初始化
 ***********************************************************************************************************************/
void point_init(point_t* point) {
    point->find = 0;
    point->x = 0;
    point->y = 0;
}

/************************************************************************************************************************
 *@brief......图像结构体变量的初始化
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
 *@brief......利用大津法得出图像阈值
 *@param      img        图像存放数组，存放每个像素点的灰度值
 *@return.....计算得出的阈值
**********************************************************************************************************************/
uint8_t getOSTUthreshold(imag_t *img)
{
    uint8_t Histogram[256] = {0};//灰度直方图
    uint16_t OstuThreshold = 0;

    uint8_t *ptr = img->pixel;
    uint8_t *ptr_end = img->pixel + img->height * img->width; //指向最后一个像素点的下一个


    while (ptr != ptr_end){						//计算每个灰度级的数量
       ++Histogram[*ptr++];
    }


    uint8_t MinGrayVal, MaxGrayVal;

    for(MinGrayVal = 0; MinGrayVal<255 && Histogram[MinGrayVal] == 0; ++MinGrayVal);//找到某灰度级像素点数为0的最小灰度级
    for(MaxGrayVal = 255; MaxGrayVal > MinGrayVal && Histogram[MaxGrayVal] == 0; --MaxGrayVal);//找到某灰度级像素点数为0的最大灰度级

    if(MaxGrayVal == MinGrayVal)//只有一个颜色
        return MaxGrayVal;

    if(MaxGrayVal == MinGrayVal + 1)//只有两个颜色
        return MinGrayVal;

    uint16_t Pixel_Intergral =0;
    uint64_t All_GrayIntegral = 0;
    for(uint16_t i = MinGrayVal; i <= MaxGrayVal; i++)
    {
        Pixel_Intergral += Histogram[i];  //像素点总和
        All_GrayIntegral += i*Histogram[i]; //图像灰度总和
    }

    uint32_t ForePixel = 0;
    uint32_t Fore_GrayIntergral = 0;
    uint32_t Back_GrayIntergral = 0;

    float w0 = 0.0;//前景像素点占整幅图像的比例
    float w1 = 0.0;//后景像素点占整幅图像的比例
    int32_t u0 = 0;//前景像素平均灰度
    int32_t u1 = 0;//背景像素平均灰度
    uint64_t MaxVariance = 0;//最大方差


    for (uint16_t i = MinGrayVal; i <= MaxGrayVal; i++) 
    {
        ForePixel += Histogram[i];
        w0 = (float)ForePixel/Pixel_Intergral;
        w1 = 1- w0;

        Fore_GrayIntergral += i * Histogram[i];
        u0 = (int32_t)Fore_GrayIntergral / w0;//前景平均灰度(扩大Pixel_Intergral的倍数，提高稳定性)
        Back_GrayIntergral = All_GrayIntegral - Fore_GrayIntergral;
        u1 = (int32_t)Back_GrayIntergral / w1;//背景平均灰度(扩大Pixel_Intergral的倍数，提高稳定性)

        uint64_t Variance = (uint64_t)(w0*w1*(u0-u1)*(u0-u1));
        if(Variance > MaxVariance){
            MaxVariance = Variance;
            OstuThreshold = i;
        }
//        if(Variance < MaxVariance)      //出现下降时退出，需试验误差大小,优点是计算量降低
//        {
//            break;
//        }
    }
    return OstuThreshold;

}


/**********************************************************************************************************************
 *@brief......对每个像素点进行二值化
 *@param img......图像数组
 *@param Threshold......进行比较的阈值
 *@return.....无
 **********************************************************************************************************************/
void binarization(imag_t *img, uint8_t Threshold)
{
    uint8_t* ptr = img->pixel;
    uint8_t* ptr_end = img->pixel + img->height * img->width; //指向最后一个像素点

    while(ptr != ptr_end)
        *ptr++ =  (((*ptr) > Threshold)? White:Black);
}


/**********************************************************************************************************************
 *@brief......寻找最长白列
 *@param      imag        二值化图像指针
 *@param      interval    每次扫描的隔的列数
 *@return.....无
**********************************************************************************************************************/
point_t  find_longest_white_column(const imag_t* imag,uint8_t interval)
{
    point_t tmp_point;
    point_init(&tmp_point);  //初始化
    uint8_t max_len = 0;
    uint8_t white_num = 0;
    uint8_t jump = 0;
//    uint8_t width = imag->width;
//    if(cross_type == CROSS_IN)   width = 50;

    for (uint8_t i = 5; i < imag->width && jump == 0; i += interval) //每隔10列取一次，从第4列开始
    {
        if (i + interval < imag->width && imag->pixel[127 * imag->width + i] == 255 && imag->pixel[127 * imag->width + i + interval] &&
            imag->pixel[126 * imag->width + i + interval] == 0) break; //防止出右边界

        white_num = 0;

        for (int8_t j = 127; j >= 0 && imag->pixel[127 * imag->width + i] == 255; j--) //每隔1行取一次，从第127行开始
        {
            if (imag->pixel[j * imag->width + i] == 255)
            {
                white_num++;

                if (white_num >= 127)
                {
                    max_len = 127;
                    tmp_point.x = i;
                    tmp_point.y = j;
                    tmp_point.find = 1;//找到白列
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
                    tmp_point.find = 1;//找到白列
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
*  @brief      寻找左下种子
*  @param      longest_white  最长白列种子
*  @param      seed           保存找到的种子
*  @param      imag           二值化图像指针
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
*  @brief      寻找右下种子
*  @param      longest_white  最长白列种子
*  @param      seed           保存找到的种子
*  @param      imag           二值化图像指针
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
*  @brief      寻找左上种子
*  @param      longest_white  最长白列种子
*  @param      seed           保存找到的种子
*  @param      imag           二值化图像指针
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
*  @brief      寻找右上种子
*  @param      longest_white  最长白列种子
*  @param      seed           保存找到的种子
*  @param      imag           二值化图像指针
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
*  @brief      左手向上迷宫扫线
*  @param      seed           起始种子
*  @param      num            寻找点的个数
*  @param      imag           二值化图像指针
*  @param     msg             赛道信息结构体
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
*  @brief      右手向上迷宫扫线
*  @param      seed           起始种子
*  @param      num            寻找点的个数
*  @param      imag           二值化图像指针
*  @param      msg            赛道信息结构体
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
*  @brief      右手向下迷宫扫线
*  @param      seed           起始种子
*  @param      num            寻找点的个数
*  @param      imag           二值化图像指针
*  @param      msg             赛道信息结构体
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
*  @brief      左手向下迷宫扫线
*  @param      seed           起始种子
*  @param      num            寻找点的个数
*  @param      imag           二值化图像指针
*  @param     msg            赛道信息结构体
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
*  @brief      寻找左下直角拐点
*  @param      msg            赛道信息结构体
*  @param      start          搜寻的起始行
*  @return     void
***********************************************************************************************************************/
void find_L_down_straight_inflection(uint8_t start, uint8_t end, msg_t *msg) {
    point_init(&(msg->L_down_inf));

    for(int16_t i = start; i >= end; i--) {
        if(msg->left_grow[i][3] >= 4){
            //保存找到的拐点坐标
            msg->L_down_inf.y = i+4;
            msg->L_down_inf.x = left_line[msg->L_down_inf.y];
            msg->L_down_inf.find = 1;
            break;
        }
    }
}

/**********************************************************************************************************************
*  @brief      寻找右下直角拐点
*  @param      msg            赛道信息结构体
*  @param      start          搜寻的起始行
*  @return     void
***********************************************************************************************************************/
void find_R_down_straight_inflection(uint8_t start, uint8_t end, msg_t *msg) {
    point_init(&(msg->R_down_inf));

    for(int16_t i = start; i >= end; i--) {
        if(msg->right_grow[i][1] >= 4){
            //保存找到的拐点坐标
            msg->R_down_inf.y = i+4;
            msg->R_down_inf.x = right_line[msg->R_down_inf.y];
            msg->R_down_inf.find = 1;
            break;
        }
    }
}

/**********************************************************************************************************************
*  @brief      寻找左上直角拐点
*  @param      msg            赛道信息结构体
*  @param      start          搜寻的起始行
*  @return     void
***********************************************************************************************************************/
void find_L_up_straight_inflection(uint8_t start, uint8_t end, msg_t* msg)
{
    point_init(&(msg->L_up_inf));
    //找左上拐点
    for (int i = start; i < end; i++)
    {
        if (msg->left_grow[i][1] >= 4)
        {
            msg->L_up_inf.y = i-4;
            msg->L_up_inf.x = left_line[msg->L_up_inf.y];
            msg->L_up_inf.find = 1;//找到标志位
            break;
        }
    }
}

/**********************************************************************************************************************
*  @brief      寻找右上直角拐点
*  @param      msg            赛道信息结构体
*  @param      start          搜寻的起始行
*  @return     void
***********************************************************************************************************************/
void find_R_up_straight_inflection(uint8_t start, uint8_t end, msg_t* msg)
{
    point_init(&(msg->R_up_inf));
    //找右上拐点
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
*  @brief      寻找左下普通拐点
*  @param      msg            赛道信息结构体
*  @return     void
***********************************************************************************************************************/
void find_L_down_point(uint8_t start, uint8_t end, msg_t *msg, enum trace_t type) {
    point_init(&(msg->L_down_point));

    if(type == circle){
        for(int16_t i = start; i-3 >= end && msg->L_down_point.find == 0; i--) {
             if(left_line[i] > left_line[i-1] && left_line[i] > left_line[i-2] && left_line[i] > left_line[i-3] &&
                left_line[i] != 0 && left_line[i-1] != 0 && left_line[i-2] !=0 && left_line[i-3] != 0) {
                //从左往右，从下往上寻找三列黑白跳变的点（即左下拐点）
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
*  @brief      寻找右下普通拐点
*  @param      msg            赛道信息结构体
*  @return     void
***********************************************************************************************************************/
void find_R_down_point(uint8_t start, uint8_t end, msg_t *msg, enum trace_t type) {
    point_init(&(msg->R_down_point));

    if(type == circle){
        for(int16_t i = start-3; i - 3 >= end && msg->R_down_point.find == 0; i--) {
            if(right_line[i] < right_line[i-1] && right_line[i] < right_line[i-2] && right_line[i] < right_line[i-3] &&
               right_line[i] != 159 && right_line[i-1] != 159 && right_line[i-2] !=159 && right_line[i-3] != 159)
                 {
                //从右往左，从下往上，寻找三列黑白跳变的点（即右下拐点）
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
*  @brief      左环时，找左环的左上拐点
*  @param      imag           图像信息
*              msg            赛道信息结构体
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
*  @brief      左环时，找左环的右下拐点
*  @param      imag           图像信息
*              msg            赛道信息结构体
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
*  @brief      检测左 圆环的入口
*  @param      msg            赛道信息结构体
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
*  @brief      右环时，找右环的左下拐点
*  @param      msg            赛道信息结构体
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
*  @brief      右环时，找右环的右上拐点
*  @param      msg            赛道信息结构体
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
*  @brief      检测右 圆环的入口
*  @param      msg            赛道信息结构体
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
*  @brief      寻找V型拐点
*  @param      l_line               左边界数组
*  @param      r_line               右边界数组
*  @param      msg            赛道信息结构体
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
*  @brief      获取丢线次数
*  @param      line               边界数组
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
*  @brief      拟合中线
*  @param      startline            起始行
*  @param      endline              结束行
*  @param      m_line               中线数组
*  @param      l_line               左边界数组
*  @param      r_line               右边界数组
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
 *@brief......计算中线
 ***********************************************************************************************************************/
void calculate_mid_line(uint8_t startline, uint8_t endline)
{
    for(int8_t i=startline; i>= endline; i--)
    {
        middle_line[i] = (uint8_t)((left_line[i]+right_line[i])/2);
    }
}



/**********************************************************************************************************************
*  @brief      计算偏差
*  @param      mid_value            中线计算值
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
*  @brief      计算角度位置
*  @param      val_value            边线计算值
*  @return     total;
***********************************************************************************************************************/
float   mid_now = 0.000f;        //全图像计算出的当前误差

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
*  @brief      冲出检测
*  @param      imag            图像信息
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
*  @brief      跟踪右边线
*  @param      Line            右边线
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
*  @brief      跟踪的左边线
*  @param      msg            赛道信息结构体
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
*  @brief      找右边线
*  @param      msg            赛道信息结构体
*  @return     void
***********************************************************************************************************************/
void find_R(uint8_t *right_Line ,uint8_t start, uint8_t end, msg_t* msg)
{//找右边无效行

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
*  @brief      找左边线
*  @param      msg            赛道信息结构体
*  @return     void
***********************************************************************************************************************/
void find_L(uint8_t *left_Line ,uint8_t start, uint8_t end, msg_t* msg)
{//找左边无效行
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
*  @brief      入环左边丢线
*  @param      msg            赛道信息结构体
*  @return     void
***********************************************************************************************************************/
uint8_t circle_find_L_lose(uint8_t *left_Line ,uint8_t start, uint8_t end)
{//找左边无效行
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
*  @brief      找左边起点
*  @param      msg            赛道信息结构体
*  @return     void
***********************************************************************************************************************/
void find_L_Start( uint8_t *left_Line,uint8_t start, uint8_t end, msg_t* msg) {

    //左边起点
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
*  @brief      找右边起点
*  @param      msg            赛道信息结构体
*  @return     void
***********************************************************************************************************************/
void find_R_Start( uint8_t *right_Line,uint8_t start, uint8_t end, msg_t* msg) {
    //右边起点
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
*  @brief......tft屏幕显示左右边线
************************************************************************************************************************/
void show_borderLine(void)
{
    for(uint i=0;i<MT9V03X_DVP_H;i++)    /*将计算得出的边界线显示出来*/
    {
        tft180_draw_point(L_down_border[i][0], L_down_border[i][1], RGB565_RED);
    }
    for(uint i=0;i<MT9V03X_DVP_H;i++)    /*将计算得出的边界线显示出来*/
    {
        tft180_draw_point(R_down_border[i][0], R_down_border[i][1], RGB565_GREEN);
    }
}



/*******************************************************************************************************
*  @brief......检测弯道
************************************************************************************************************************/
uint8 Curve_exam(void)
{
    uint8 i = 80;
    uint8 mid_length = 0;
    for (uint8 j = 127; j >= 0 && imag.pixel[j * imag.width + i] == 255; j--) //每隔1行取一次，从第119行开始
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











