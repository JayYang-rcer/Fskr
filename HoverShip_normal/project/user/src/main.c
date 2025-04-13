            /*********************************************************************************************************************
* CH32V307VCT6 Opensourec Library 即（CH32V307VCT6 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
*
* 本文件是CH32V307VCT6 开源库的一部分
*
* CH32V307VCT6 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
*
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
*
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
*
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
*
* 文件名称          main
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          MounRiver Studio V1.8.1
* 适用平台          CH32V307VCT6
* 店铺链接          https://seekfree.taobao.com/
*
* 修改记录
* 日期                                      作者                             备注
* 2022-09-15        大W            first version
********************************************************************************************************************/
#include "zf_common_headfile.h"
#include "key.h"
//-------------------------------------------------------------------------------------------------------------------
#define ENCODER_1                   (TIM1_ENCOEDER)
#define ENCODER_1_DIR               (TIM1_ENCOEDER_MAP3_CH1_E9)
#define ENCODER_1_LSB               (TIM1_ENCOEDER_MAP3_CH2_E11)

#define     WIFI_transfer      0                        //为1时使用WIFi图传
//#define     WIFI_SSID_TEST       "NETGEAR_306"
//#define     WIFI_PASSWORD_TEST      "gdutelc4306"
#define     WIFI_SSID_TEST       "iken"
#define     WIFI_PASSWORD_TEST        "kt123456"
// 如果需要连接的WIFI 没有密码则需要将 这里 替换为 NULL
//需要修改网络是，改这里的WIFI_SSID_TEST和WIFI_PASSWORD_TEST，同时还有zf_device_wifi_spi.h文件里的WIFI_SPI_TARGET_IP

#define     WIRELESS_UART_transfer       1               //为1时使用无线串口调参
#define PIT                         (TIM5_PIT )                                 // 使用的周期中断编号 如果修改 需要同步对应修改周期中断编号与 isr.c 中的调用


//-------------------------------------------------------------------------------------------------------------------

extern uint8_t mt9v03x_image[MT9V03X_DVP_H][MT9V03X_DVP_W];   //灰度图
extern uint8_t middle_line[MT9V03X_DVP_H];

extern uint8_t left_line[MT9V03X_DVP_H];                //边线数组
extern uint8_t right_line[MT9V03X_DVP_H];
extern uint8_t middle_line[MT9V03X_DVP_H];

//三个元素标志位
extern bool circle_flag;
extern bool cross_flag;
extern bool barrier_flag;



enum trace_t trace_position = normal;
imag_t imag = {NULL, MT9V03X_DVP_H, MT9V03X_DVP_W};
straight_t L_stra;           //拟合直线
straight_t R_stra;
straight_t M_stra;
point_t longest_white;    //最长白列
point_t L_down_seed;         //左右下方巡线种子
point_t R_down_seed;
point_t L_up_seed;         //左右下方巡线种子
point_t R_up_seed;
msg_t msg;                //赛道信息
float mid_deviation=0;  //中线偏差
float real = 0;             //推进电机差速值
float real_cw = 0;      //横向电机PID输出值
float real_imu660 = 0;  //陀螺仪PID输出值
uint8_t real_limit = 10 ;            //差速值限幅
// 图像备份数组，在发送前将图像备份再进行发送，这样可以避免图像出现撕裂的问题
uint8 image_copy[MT9V03X_H][MT9V03X_W];

//赛道情况
bool acc_flag = 0;
bool Stop_Flag = 1;
uint8_t curve_dir = 0;
uint16_t mid_state = 255;         //中点黑白状态
void curve_exam();
void ele_exam();
void control();



//-------------------------------------------------------------------------------------------------------------------

int main (void)
{
    uint8_t Threshold;


//初始化---------------------------------------------------------------------------------------------------------------
    clock_init(SYSTEM_CLOCK_144M);                                              // 初始化芯片时钟 工作频率为 144MHz
    debug_init();                                                               // 初始化默认 Debug UART

//    tft180_set_dir(TFT180_CROSSWISE);                                         // 需要先横屏 不然显示不下
//    tft180_init();
//    tft180_show_string(0, 0, "mt9v03x init.");

    encoder_dir_init(ENCODER_1, ENCODER_1_DIR, ENCODER_1_LSB);                  // 初始化编码器模块与引脚 方向解码编码器模式


    motor_init();                                                               //电机初始化
    TIM6_Int_Init((150-1),(14400-1));                                           //周期15ms，电机中断



    while(1)                                                                    //陀螺仪初始化
    {
        if(imu660ra_init())
            printf("\r\nIMU660RA init error.");                                 // IMU660RA 初始化失败
        else
            break;
    }
    pit_ms_init(PIT, 5);                                                        //陀螺仪中断，5ms中断


    gpio_init(D9,GPO,0,GPIO_PIN_CONFIG);                                        //蜂鸣器初始化
    key_gpio_init();                                                            //按键初始化

//    interrupt_global_enable(0);                                                 // 开启总中断

    while(1)                                                                    //摄像头初始化
        {

            if(mt9v03x_init())
                printf("mt9v03x reinit.\r\n");
            else
                break;
            system_delay_ms(1000);
        }
                printf("init success.\r\n");


#if(WIFI_transfer)                                                              //wifi图传初始化代码
    while(wifi_spi_init(WIFI_SSID_TEST, WIFI_PASSWORD_TEST))
    {
        printf("\r\n connect wifi failed. \r\n");
        system_delay_ms(100);                                                   // 初始化失败 等待 100ms
    }

    printf("\r\n module version:%s",wifi_spi_version);                          // 模块固件版本
    printf("\r\n module mac    :%s",wifi_spi_mac_addr);                         // 模块 MAC 信息
    printf("\r\n module ip     :%s",wifi_spi_ip_addr_port);                     // 模块 IP 地址

    // zf_device_wifi_spi.h 文件内的宏定义可以更改模块连接(建立) WIFI 之后，是否自动连接 TCP 服务器、创建 UDP 连接、创建 TCP 服务器等操作
    if(1 != WIFI_SPI_AUTO_CONNECT)                                              // 如果没有开启自动连接 就需要手动连接目标 IP
    {
        while(wifi_spi_socket_connect(                                          // 向指定目标 IP 的端口建立 TCP 连接
            "TCP",                                                              // 指定使用TCP方式通讯
            WIFI_SPI_TARGET_IP,                                                 // 指定远端的IP地址，填写上位机的IP地址
            WIFI_SPI_TARGET_PORT,                                               // 指定远端的端口号，填写上位机的端口号，通常上位机默认是8080
            WIFI_SPI_LOCAL_PORT))                                               // 指定本机的端口号
        {
            // 如果一直建立失败 考虑一下是不是没有接硬件复位
            printf("\r\n Connect TCP Servers error, try again.");
            system_delay_ms(100);                                               // 建立连接失败 等待 100ms
        }
    }
    seekfree_assistant_interface_init(SEEKFREE_ASSISTANT_WIFI_SPI); // 逐飞助手初始化 数据传输使用高速WIFI SPI
    //逐飞助手图像信息配置函数
   seekfree_assistant_camera_information_config(SEEKFREE_ASSISTANT_MT9V03X, image_copy[0], MT9V03X_W, MT9V03X_H);
   // 逐飞助手图像边线发送配置函数，X_BOUNDARY->发送的图像中边界信息只包含X，也就是只有横坐标信息，纵坐标根据图像高度得到
   seekfree_assistant_camera_boundary_config(X_BOUNDARY, MT9V03X_H, left_line, right_line, middle_line, NULL, NULL,  NULL);


#endif

#if(WIRELESS_UART_transfer)                                                     //无线串口初始化
    if(wireless_uart_init())                                                    // 判断是否通过初始化
    {
        while(1)                                                                // 初始化失败就在这进入死循环
        {
            system_delay_ms(100);                                               // 短延时快速闪灯表示异常
        }
    }
    wireless_uart_send_byte('\r');
    wireless_uart_send_byte('\n');
    wireless_uart_send_string("SEEKFREE wireless uart demo.\r\n");              // 初始化正常 输出测试信息

#endif



//---------------------------------------------------------------------------------------------------------------

//开始轮循-----------------------------------------------------------------------------------------------------------
    while(1)
    {
        if (mt9v03x_finish_flag )
        {
            imag.pixel = mt9v03x_image[0];
            Threshold = getOSTUthreshold(&imag);                                /*大津法计算阈值*/
            binarization(&imag,Threshold);                                      /*二值化*/
            imag_var_init(&msg);                                                //图像结构体初始化
            longest_white = find_longest_white_column(&imag,10);                //寻找最长白列

            find_L_down_seed(longest_white, &L_down_seed, &imag);               //寻找种子
            find_R_down_seed(longest_white, &R_down_seed, &imag);
            find_L_up_seed(longest_white, &L_up_seed, &imag);
            find_R_up_seed(longest_white, &R_up_seed, &imag);

            findline_righthand_down(&L_up_seed, 1.5*MT9V03X_DVP_H, &imag, &msg);    //迷宫扫线
            findline_lefthand_down(&R_up_seed, 1.5*MT9V03X_DVP_H, &imag, &msg);
            findline_lefthand_up(&L_down_seed, 1.5*MT9V03X_DVP_H, &imag, &msg);
            findline_righthand_up(&R_down_seed, 1.5*MT9V03X_DVP_H, &imag, &msg);

            mid_deviation = 80 - middle_line[dynamic_foresight];                //中线像素偏差
            mid_state = imag.pixel[dynamic_foresight*(MT9V03X_DVP_W) + middle_line[dynamic_foresight]];         //中点黑白状态
//            if((my_abs(mid_deviation) > 45) || ((mid_state == 0) && middle_line[dynamic_foresight] == 80))
//            {
//                camera_servo_PID.o_max = 15;
//            }
//            else{
//                camera_servo_PID.o_max = 10;
//            }

            curve_exam();                                                            //弯道检测
            if(trace_position == normal)
                ele_exam();                                                     //元素识别
            control();                                                          //实行操作


#if(WIFI_transfer)                                                              //wifi传输图像
           // 在发送前将图像备份再进行发送，这样可以避免图像出现撕裂的问题
           memcpy(image_copy[0], mt9v03x_image[0], MT9V03X_IMAGE_SIZE);
           // 发送图像
           seekfree_assistant_camera_send();
#endif


            mt9v03x_finish_flag = 0;
        }

    }
}


//---------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     PIT 的中断处理函数 这个函数将在 PIT 对应的定时器中断调用 详见 isr.c
// 参数说明     void
// 返回参数     void
// 使用示例     pit_hanlder();
//-------------------------------------------------------------------------------------------------------------------
void pit_hanlder (void)
{
//    getEulerianAngles();
//    imu660ra_get_acc();
    imu660ra_get_gyro();                                                        // 获取 IMU660RA 的角速度测量数值

}


void curve_exam()
{
    regression(120, 40, left_line, &L_stra);         //拟合左边直线
    calculate_variance(119, 40, left_line, &L_stra); //计算方差
    regression(120, 40, right_line, &R_stra);         //拟合右边直线
    calculate_variance(119, 40, right_line, &R_stra); //计算方差

    regression(120, 80, left_line, &L_stra);         //拟合左边直线
    regression(120, 80, right_line, &R_stra);         //拟合右边直线

    //直道加速
    if(L_stra.variance < 1 && R_stra.variance < 1)
    {
        acc_flag = 1;
        curve_dir = 0;

    }
    //低速时抑制漂移   左弯道
    else if(get_lose_line(left_line, 70, 20) > get_lose_line(right_line, 70, 20) && R_stra.k > 0 && (L_stra.variance > 1 || R_stra.variance  > 1))
    {
        acc_flag = 0;
        curve_dir = 1;
    }
    //低速时抑制漂移   右弯道
    else if(get_lose_line(left_line, 70, 20) < get_lose_line(right_line, 70, 20) && L_stra.k < 0 && (L_stra.variance > 1 || R_stra.variance  > 1))
    {
        acc_flag = 0;
        curve_dir = 2;
    }
    //不用加速，正常行驶
    else{
        acc_flag = 0;
        curve_dir = 0;
    }

}

void normal_handle()
{
    calculate_mid_line(MT9V03X_DVP_H-1, dynamic_foresight);             /*计算中线每个点的值*/
    PID_Calc(&camera_servo_PID, 80,middle_line[dynamic_foresight]);             /*带入误差计算差速*/
    PID_Calc(&crosswise_pid, 80, middle_line[120]);       /*为横向电机所做的专属pid*/

    real = camera_servo_PID.output;
    real_cw = crosswise_pid.output;
}

void ele_exam()
{
//    regression(120, 10, left_line, &L_stra);         //拟合左边直线
//    calculate_variance(119, 10, left_line, &L_stra); //计算方差
//    regression(120, 10, right_line, &R_stra);         //拟合右边直线
//    calculate_variance(119, 10, right_line, &R_stra); //计算方差

    cross_check(&msg,&trace_position);
    circle_check(&trace_position);
    barrier_check(&msg,&trace_position);
//    if(circle_flag && cross_flag && barrier_flag)
    garage_check(&imag,&trace_position);

}

void control()
{
    switch(trace_position)
    {
        case normal:
            normal_handle();
            break;
        case circle:
            circle_handle(&msg,&trace_position);
            break;
        case cross:
            cross_handle(&imag,&msg,&trace_position);
            break;
        case barrier:
            barrier_handle(&trace_position);
            break;
        case garage:
            garage_handle(&trace_position);
            break;
        default:
            break;

    }

}

