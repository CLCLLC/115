/**
  ******************************************************************************
  * @file    servo.c
  * @author  MengCheng
  * @version V1.0.0
  * @date    2021.4.2
  * @brief   �����������
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */
/*********************************************  includes  *****************************************/
#include "servo.h"
#include "stm32f1xx_hal.h"
#include "tim.h"
#include "math.h"


/*********************************************  defines  *****************************************/
//#define Error_Threshold_BigValue 10                                        //���ϴ���ֵ������ڵ���
//#define Error_Threshold_SmallValue 5                                       //����С��ֵ������ڵ���
//#define rotation_adjust_angle1 Error_Threshold_BigValue * (160 - Real_x)   //������ת��
//#define pitch_adjust_angle1 Error_Threshold_BigValue * (112 - Real_y)      //������ת��
//#define rotation_adjust_angle2 Error_Threshold_SmallValue * (160 - Real_x) / 100 //���㸩����          
//#define pitch_adjust_angle2 Error_Threshold_SmallValue * (112 - Real_y) / 100   //���㸩����                         
//#define speed_allocate_k 100

/*********************************************  variables  *****************************************/
uint8_t Servo_Status = 1;        //���״̬��ֹͣ���˶� 
//uint8_t Target_Flag = No_Target; //���ڽ��յ����ݲ��жϺ�ֵ
//double x, y;                   //���ڼ�������Ƕ�

struct PID positionx_pid = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};  //һ��Ҫ��ʼ�����ⲿ���õ�ʱ��
struct PID positiony_pid = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
 


/*********************************************  functions  *****************************************/

/**
  * @brief  ���������ʼ������
  * @param  None
  * @retval ����ִ��״̬
  */
HAL_StatusTypeDef Servo_Init(void)
{
	//HAL_StatusTypeDef status = (HAL_StatusTypeDef)(Servo_SetAngles(1, 1, 90, 0) || Servo_SetAngles(1, 2, 90, 0)); //֮���Ժ���û��ִ�У�����Ϊ����·��
	HAL_StatusTypeDef status = (HAL_StatusTypeDef)(Tim_SetPWM(1, 1, 1500) || Tim_SetPWM(1, 2, 1500));  
  HAL_Delay(1000);
	return status;
}

///**
//  * @brief  ����Ƕ�ת��pwm����
//  * @param  angles:�Ƕ�
//  * @param  tim����ʱ����
//  * @param  channal:ͨ����
//  * @retval ����ִ��״̬
//  * @claim  ���ֶ��500us~2500us,180�����270�㣬��Ҫ����һ��
//  */
//HAL_StatusTypeDef Servo_SetAngles(uint8_t tim, uint8_t channal, uint32_t pulses)
//{
//  return 
//	if(mode == 1) //ģʽ1��Ѳ��ģʽ������ת��
//	{
//		for(i = 1; i <= speed_allocate_k; i++)
//    {
//			if(Tim_SetPWM(tim, channal, angles / speed_allocate_k * i) == HAL_OK)
//      {
//        HAL_Delay(40);
//        if(!Servo_Status) //�����Ŀ����֣���ô���ֹͣת������̨����΢��ģʽ
//          break;
//      }
//      else
//          return HAL_ERROR;
//        //C��������Ŀ������ı��ʽ1��2�����ͱ���һ��
//        //			HAL_Delay(40);
//			//if(���ں����﷢���˼�⵽�������ָ��)
//			//��ô��ֵTarget_Detected,���򷵻�NO_target
//		}
//		return HAL_OK;
  //}
//	else //ģʽ0������ģʽ������ת��
//		return Tim_SetPWM(tim, channal, angles);
//}

///**
//  * @brief  ��̨Ѳ�캯����Ѱ��Ŀ����
//  * @param  None
//  * @retval HAL_Status: Ŀ������Ѱ���
//  * @claim  ��ʵҲ���Կ�����break,������Ҫwhile()����1
//  */
//HAL_StatusTypeDef Servo_Platform_Search()
//{     
//	uint8_t bit = 0;
//  uint8_t flag = 0;
//  
//	while(flag == 0)
//	{
//		if(Target_Flag == Target_Detected)
//    {
//			//��⵽������ͣת
//			Servo_Status = 0;
//      flag = 1; //����ѭ��
//    }
//    else
//    {
//      Servo_SetAngles(1, 2, 45+90*bit, 1);
//      bit = bit ^ 0x01; //���bit����bool���Ͷ���ģ���ôȡ�����ã�
////      bit = 0;
//      HAL_Delay(500);
//    }
//	}
//  return HAL_OK;
//}


/*����һ*/
/**
  * @brief  ��̨Ŀ����ٺ���
  * @param  target_x: Ŀ����X����
  * @param  target_y: Ŀ����y����
  * @param  current_angle: ��ǰ�Ƕ�
  * @retval None
  */
//void Servo_Platform_Track(uint16_t target_x, uint16_t target_y)
//{
//  /*���ϴ�ʱ�������������׶�*/
////  while(Target_Location_Error >= Error_Threshold_BigValue) //������С����ֵ��������
////  {
////    Servo_SetAngles(1, 1, Global_Current_Angles+rotation_adjust_angle1, 0);
////    Servo_SetAngles(1, 2, Global_Current_Angles+pitch_adjust_angle1, 0);
////  }
//  /*����Сʱ������С���ȵ����׶�*/
//  while(Target_Location_Error >= Error_Threshold_SmallValue) //������С����ֵ��������
//  {
//    Servo_SetAngles(1, 1, Global_Current_Angles_x+rotation_adjust_angle2, 0);
//    Servo_SetAngles(1, 2, Global_Current_Angles_y+pitch_adjust_angle2, 0);
//  }    
//}

/*PID��̬��������*/
void PID_Init()
{
  positionx_pid.kp = 0.15;
  positionx_pid.ki = 0.001;
  positionx_pid.kd = 0.001;
  positionx_pid.passive_error = 0; //��һ�������
  positionx_pid.integral = 0; //��һ�λ�����
  positionx_pid.set_value = 0x9f; //����ƫ��x��0x01
  positionx_pid.output = 1500;
  
  positiony_pid.kp = 0.15;
  positiony_pid.ki = 0;
  positiony_pid.kd = 0;
  positiony_pid.passive_error = 0; //��һ�������
  positiony_pid.integral = 0; //��һ�λ�����
  positiony_pid.set_value = 0x78 - 0x18; //����ƫ��y��0x60
  positiony_pid.output = 1500;
}
	

