            /*********************************************************************************************************************
* CH32V307VCT6 Opensourec Library ����CH32V307VCT6 ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2022 SEEKFREE ��ɿƼ�
*
* ���ļ���CH32V307VCT6 ��Դ���һ����
*
* CH32V307VCT6 ��Դ�� ��������
* �����Ը��������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù������֤��������
* �� GPL �ĵ�3�棨�� GPL3.0������ѡ��ģ��κκ����İ汾�����·�����/���޸���
*
* ����Դ��ķ�����ϣ�����ܷ������ã�����δ�������κεı�֤
* ����û�������������Ի��ʺ��ض���;�ı�֤
* ����ϸ����μ� GPL
*
* ��Ӧ�����յ�����Դ���ͬʱ�յ�һ�� GPL �ĸ���
* ���û�У������<https://www.gnu.org/licenses/>
*
* ����ע����
* ����Դ��ʹ�� GPL3.0 ��Դ���֤Э�� �����������Ϊ���İ汾
* �������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
* ���֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
*
* �ļ�����          main
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          MounRiver Studio V1.8.1
* ����ƽ̨          CH32V307VCT6
* ��������          https://seekfree.taobao.com/
*
* �޸ļ�¼
* ����                                      ����                             ��ע
* 2022-09-15        ��W            first version
********************************************************************************************************************/
#include "zf_common_headfile.h"
#include "key.h"
//-------------------------------------------------------------------------------------------------------------------
#define ENCODER_1                   (TIM1_ENCOEDER)
#define ENCODER_1_DIR               (TIM1_ENCOEDER_MAP3_CH1_E9)
#define ENCODER_1_LSB               (TIM1_ENCOEDER_MAP3_CH2_E11)

#define     WIFI_transfer      0                        //Ϊ1ʱʹ��WIFiͼ��
//#define     WIFI_SSID_TEST       "NETGEAR_306"
//#define     WIFI_PASSWORD_TEST      "gdutelc4306"
#define     WIFI_SSID_TEST       "iken"
#define     WIFI_PASSWORD_TEST        "kt123456"
// �����Ҫ���ӵ�WIFI û����������Ҫ�� ���� �滻Ϊ NULL
//��Ҫ�޸������ǣ��������WIFI_SSID_TEST��WIFI_PASSWORD_TEST��ͬʱ����zf_device_wifi_spi.h�ļ����WIFI_SPI_TARGET_IP

#define     WIRELESS_UART_transfer       1               //Ϊ1ʱʹ�����ߴ��ڵ���
#define PIT                         (TIM5_PIT )                                 // ʹ�õ������жϱ�� ����޸� ��Ҫͬ����Ӧ�޸������жϱ���� isr.c �еĵ���


//-------------------------------------------------------------------------------------------------------------------

extern uint8_t mt9v03x_image[MT9V03X_DVP_H][MT9V03X_DVP_W];   //�Ҷ�ͼ
extern uint8_t middle_line[MT9V03X_DVP_H];

extern uint8_t left_line[MT9V03X_DVP_H];                //��������
extern uint8_t right_line[MT9V03X_DVP_H];
extern uint8_t middle_line[MT9V03X_DVP_H];

//����Ԫ�ر�־λ
extern bool circle_flag;
extern bool cross_flag;
extern bool barrier_flag;



enum trace_t trace_position = normal;
imag_t imag = {NULL, MT9V03X_DVP_H, MT9V03X_DVP_W};
straight_t L_stra;           //���ֱ��
straight_t R_stra;
straight_t M_stra;
point_t longest_white;    //�����
point_t L_down_seed;         //�����·�Ѳ������
point_t R_down_seed;
point_t L_up_seed;         //�����·�Ѳ������
point_t R_up_seed;
msg_t msg;                //������Ϣ
float mid_deviation=0;  //����ƫ��
float real = 0;             //�ƽ��������ֵ
float real_cw = 0;      //������PID���ֵ
float real_imu660 = 0;  //������PID���ֵ
uint8_t real_limit = 10 ;            //����ֵ�޷�
// ͼ�񱸷����飬�ڷ���ǰ��ͼ�񱸷��ٽ��з��ͣ��������Ա���ͼ�����˺�ѵ�����
uint8 image_copy[MT9V03X_H][MT9V03X_W];

//�������
bool acc_flag = 0;
bool Stop_Flag = 1;
uint8_t curve_dir = 0;
uint16_t mid_state = 255;         //�е�ڰ�״̬
void curve_exam();
void ele_exam();
void control();



//-------------------------------------------------------------------------------------------------------------------

int main (void)
{
    uint8_t Threshold;


//��ʼ��---------------------------------------------------------------------------------------------------------------
    clock_init(SYSTEM_CLOCK_144M);                                              // ��ʼ��оƬʱ�� ����Ƶ��Ϊ 144MHz
    debug_init();                                                               // ��ʼ��Ĭ�� Debug UART

//    tft180_set_dir(TFT180_CROSSWISE);                                         // ��Ҫ�Ⱥ��� ��Ȼ��ʾ����
//    tft180_init();
//    tft180_show_string(0, 0, "mt9v03x init.");

    encoder_dir_init(ENCODER_1, ENCODER_1_DIR, ENCODER_1_LSB);                  // ��ʼ��������ģ�������� ������������ģʽ


    motor_init();                                                               //�����ʼ��
    TIM6_Int_Init((150-1),(14400-1));                                           //����15ms������ж�



    while(1)                                                                    //�����ǳ�ʼ��
    {
        if(imu660ra_init())
            printf("\r\nIMU660RA init error.");                                 // IMU660RA ��ʼ��ʧ��
        else
            break;
    }
    pit_ms_init(PIT, 5);                                                        //�������жϣ�5ms�ж�


    gpio_init(D9,GPO,0,GPIO_PIN_CONFIG);                                        //��������ʼ��
    key_gpio_init();                                                            //������ʼ��

//    interrupt_global_enable(0);                                                 // �������ж�

    while(1)                                                                    //����ͷ��ʼ��
        {

            if(mt9v03x_init())
                printf("mt9v03x reinit.\r\n");
            else
                break;
            system_delay_ms(1000);
        }
                printf("init success.\r\n");


#if(WIFI_transfer)                                                              //wifiͼ����ʼ������
    while(wifi_spi_init(WIFI_SSID_TEST, WIFI_PASSWORD_TEST))
    {
        printf("\r\n connect wifi failed. \r\n");
        system_delay_ms(100);                                                   // ��ʼ��ʧ�� �ȴ� 100ms
    }

    printf("\r\n module version:%s",wifi_spi_version);                          // ģ��̼��汾
    printf("\r\n module mac    :%s",wifi_spi_mac_addr);                         // ģ�� MAC ��Ϣ
    printf("\r\n module ip     :%s",wifi_spi_ip_addr_port);                     // ģ�� IP ��ַ

    // zf_device_wifi_spi.h �ļ��ڵĺ궨����Ը���ģ������(����) WIFI ֮���Ƿ��Զ����� TCP ������������ UDP ���ӡ����� TCP �������Ȳ���
    if(1 != WIFI_SPI_AUTO_CONNECT)                                              // ���û�п����Զ����� ����Ҫ�ֶ�����Ŀ�� IP
    {
        while(wifi_spi_socket_connect(                                          // ��ָ��Ŀ�� IP �Ķ˿ڽ��� TCP ����
            "TCP",                                                              // ָ��ʹ��TCP��ʽͨѶ
            WIFI_SPI_TARGET_IP,                                                 // ָ��Զ�˵�IP��ַ����д��λ����IP��ַ
            WIFI_SPI_TARGET_PORT,                                               // ָ��Զ�˵Ķ˿ںţ���д��λ���Ķ˿ںţ�ͨ����λ��Ĭ����8080
            WIFI_SPI_LOCAL_PORT))                                               // ָ�������Ķ˿ں�
        {
            // ���һֱ����ʧ�� ����һ���ǲ���û�н�Ӳ����λ
            printf("\r\n Connect TCP Servers error, try again.");
            system_delay_ms(100);                                               // ��������ʧ�� �ȴ� 100ms
        }
    }
    seekfree_assistant_interface_init(SEEKFREE_ASSISTANT_WIFI_SPI); // ������ֳ�ʼ�� ���ݴ���ʹ�ø���WIFI SPI
    //�������ͼ����Ϣ���ú���
   seekfree_assistant_camera_information_config(SEEKFREE_ASSISTANT_MT9V03X, image_copy[0], MT9V03X_W, MT9V03X_H);
   // �������ͼ����߷������ú�����X_BOUNDARY->���͵�ͼ���б߽���Ϣֻ����X��Ҳ����ֻ�к�������Ϣ�����������ͼ��߶ȵõ�
   seekfree_assistant_camera_boundary_config(X_BOUNDARY, MT9V03X_H, left_line, right_line, middle_line, NULL, NULL,  NULL);


#endif

#if(WIRELESS_UART_transfer)                                                     //���ߴ��ڳ�ʼ��
    if(wireless_uart_init())                                                    // �ж��Ƿ�ͨ����ʼ��
    {
        while(1)                                                                // ��ʼ��ʧ�ܾ����������ѭ��
        {
            system_delay_ms(100);                                               // ����ʱ�������Ʊ�ʾ�쳣
        }
    }
    wireless_uart_send_byte('\r');
    wireless_uart_send_byte('\n');
    wireless_uart_send_string("SEEKFREE wireless uart demo.\r\n");              // ��ʼ������ ���������Ϣ

#endif



//---------------------------------------------------------------------------------------------------------------

//��ʼ��ѭ-----------------------------------------------------------------------------------------------------------
    while(1)
    {
        if (mt9v03x_finish_flag )
        {
            imag.pixel = mt9v03x_image[0];
            Threshold = getOSTUthreshold(&imag);                                /*��򷨼�����ֵ*/
            binarization(&imag,Threshold);                                      /*��ֵ��*/
            imag_var_init(&msg);                                                //ͼ��ṹ���ʼ��
            longest_white = find_longest_white_column(&imag,10);                //Ѱ�������

            find_L_down_seed(longest_white, &L_down_seed, &imag);               //Ѱ������
            find_R_down_seed(longest_white, &R_down_seed, &imag);
            find_L_up_seed(longest_white, &L_up_seed, &imag);
            find_R_up_seed(longest_white, &R_up_seed, &imag);

            findline_righthand_down(&L_up_seed, 1.5*MT9V03X_DVP_H, &imag, &msg);    //�Թ�ɨ��
            findline_lefthand_down(&R_up_seed, 1.5*MT9V03X_DVP_H, &imag, &msg);
            findline_lefthand_up(&L_down_seed, 1.5*MT9V03X_DVP_H, &imag, &msg);
            findline_righthand_up(&R_down_seed, 1.5*MT9V03X_DVP_H, &imag, &msg);

            mid_deviation = 80 - middle_line[dynamic_foresight];                //��������ƫ��
            mid_state = imag.pixel[dynamic_foresight*(MT9V03X_DVP_W) + middle_line[dynamic_foresight]];         //�е�ڰ�״̬
//            if((my_abs(mid_deviation) > 45) || ((mid_state == 0) && middle_line[dynamic_foresight] == 80))
//            {
//                camera_servo_PID.o_max = 15;
//            }
//            else{
//                camera_servo_PID.o_max = 10;
//            }

            curve_exam();                                                            //������
            if(trace_position == normal)
                ele_exam();                                                     //Ԫ��ʶ��
            control();                                                          //ʵ�в���


#if(WIFI_transfer)                                                              //wifi����ͼ��
           // �ڷ���ǰ��ͼ�񱸷��ٽ��з��ͣ��������Ա���ͼ�����˺�ѵ�����
           memcpy(image_copy[0], mt9v03x_image[0], MT9V03X_IMAGE_SIZE);
           // ����ͼ��
           seekfree_assistant_camera_send();
#endif


            mt9v03x_finish_flag = 0;
        }

    }
}


//---------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------
// �������     PIT ���жϴ����� ����������� PIT ��Ӧ�Ķ�ʱ���жϵ��� ��� isr.c
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     pit_hanlder();
//-------------------------------------------------------------------------------------------------------------------
void pit_hanlder (void)
{
//    getEulerianAngles();
//    imu660ra_get_acc();
    imu660ra_get_gyro();                                                        // ��ȡ IMU660RA �Ľ��ٶȲ�����ֵ

}


void curve_exam()
{
    regression(120, 40, left_line, &L_stra);         //������ֱ��
    calculate_variance(119, 40, left_line, &L_stra); //���㷽��
    regression(120, 40, right_line, &R_stra);         //����ұ�ֱ��
    calculate_variance(119, 40, right_line, &R_stra); //���㷽��

    regression(120, 80, left_line, &L_stra);         //������ֱ��
    regression(120, 80, right_line, &R_stra);         //����ұ�ֱ��

    //ֱ������
    if(L_stra.variance < 1 && R_stra.variance < 1)
    {
        acc_flag = 1;
        curve_dir = 0;

    }
    //����ʱ����Ư��   �����
    else if(get_lose_line(left_line, 70, 20) > get_lose_line(right_line, 70, 20) && R_stra.k > 0 && (L_stra.variance > 1 || R_stra.variance  > 1))
    {
        acc_flag = 0;
        curve_dir = 1;
    }
    //����ʱ����Ư��   �����
    else if(get_lose_line(left_line, 70, 20) < get_lose_line(right_line, 70, 20) && L_stra.k < 0 && (L_stra.variance > 1 || R_stra.variance  > 1))
    {
        acc_flag = 0;
        curve_dir = 2;
    }
    //���ü��٣�������ʻ
    else{
        acc_flag = 0;
        curve_dir = 0;
    }

}

void normal_handle()
{
    calculate_mid_line(MT9V03X_DVP_H-1, dynamic_foresight);             /*��������ÿ�����ֵ*/
    PID_Calc(&camera_servo_PID, 80,middle_line[dynamic_foresight]);             /*�������������*/
    PID_Calc(&crosswise_pid, 80, middle_line[120]);       /*Ϊ������������ר��pid*/

    real = camera_servo_PID.output;
    real_cw = crosswise_pid.output;
}

void ele_exam()
{
//    regression(120, 10, left_line, &L_stra);         //������ֱ��
//    calculate_variance(119, 10, left_line, &L_stra); //���㷽��
//    regression(120, 10, right_line, &R_stra);         //����ұ�ֱ��
//    calculate_variance(119, 10, right_line, &R_stra); //���㷽��

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

