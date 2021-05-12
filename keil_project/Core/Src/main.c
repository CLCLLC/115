/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : ����׷��װ�ó���
  * @LastChangeTime : 2021.4.24 6:11
  * @version        : V2.0.0
  * @author         : MengCheng
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * ��Ϊ�人����ѧ��������E�⼤���й����ļ������̲���stm32f103c8t6Ϊ���أ���
  * ��������ʶ���openmv���д�������ͨ�ţ��Ӷ��ﵽ׷�����岢�ɹ���е�Ч����˼·����ΪPID����
  * ��������ϲ����޸�
  ******************************************************************************
  */
  
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "servo.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/**
  * @brief  ���ڷ��ͺ���
  * @retval None
  */
#include "stdio.h"
#include "stdarg.h"
#include "string.h"

#define    TXBUF_SIZE_MAX    100

void uartx_printf(UART_HandleTypeDef huartx, const char *format, ...)
{
    va_list args;
    uint32_t length;
    uint8_t txbuf[TXBUF_SIZE_MAX] = {0};
 
    va_start(args, format);
    length = vsnprintf((char *)txbuf, sizeof(txbuf), (char *)format, args);
    va_end(args);
    HAL_UART_Transmit(&huartx, (uint8_t *)txbuf, length, HAL_MAX_DELAY);
    memset(txbuf, 0, TXBUF_SIZE_MAX);
};

/**
  * @brief  ���ڵ���
  * @retval None
  */
#define DEBUG
#ifdef DEBUG
#define DBG(format, ...) fprintf(stdout, "[\tDBG](File:%s, Func:%s(), Line:%d): " \
                                 , __FILE__, __FUNCTION__, __LINE__);             \
                         fprintf(stdout, format"\r\n", ##__VA_ARGS__)
#else
#define DBG(format, ...)  do {} while (0)
#endif
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t UART1_RxBuffer, UART2_RxBuffer;
uint8_t buffer1[8] = "\0";
uint16_t Real_x, Real_y, Rx_x, Rx_y;
uint8_t adjustment_flag = 0;
uint8_t Target_Flag = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int fputc(int ch, FILE *f){
    uint8_t temp[1] = {ch};
    HAL_UART_Transmit(&huart2, temp, 1, 2);//huart1 ���������޸�
    return ch;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
//	uint8_t angle1 = 60;
//	uint8_t angle2 = 60;
//	int8_t angle_delta = 30;
  
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  
  //DBG("have received successfully!\r\n");
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_TIM1_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
	//system_init();
  HAL_TIM_Base_Start_IT(&htim2); //������ʱ���ж�
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1); //����pwm
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2); //����PWM
	HAL_UART_Receive_IT(&huart1, (uint8_t*)&UART1_RxBuffer, 1); //���������ж�
  PID_Init();
//  DBG("hello");
  Servo_Init(); //��̨��ʼ���������ɶȾ�Ϊ90��
  PID_Init(); //PID��ʼ��
//  DBG("hello");
  //DBG("have received successfully!\r\n");
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    //DBG("have received successfully!\r\n");
    /*���ڷ���һServo_Platform_Search() == HAL_OK*/
//      while(Target_Flag == Target_Detected && Target_Location_Error > 1) //��̨Ѳ��
//        Servo_Platform_Track(Real_x, Real_y); 
      
//    angle_delta =~ angle_delta;
//		
//		Servo_SetAngles(1, 1, angle1+angle_delta, 1);
//		HAL_Delay(500);
//		Servo_SetAngles(1, 2, angle2+angle_delta, 1);
//		HAL_Delay(500);
//    uint8_t dt;  
      //DBG("have received successfully!\r\n");
      
      
    /****      ���ڷ���������ת�Ǻ͸�����PID���ڴ���(Ӧ���ڶ�ʱ����)      *****/
//    positionx_pid.measured_value =  Real_x;
//    positionx_pid.error          =  positionx_pid.measured_value - positionx_pid.set_value;
//    positionx_pid.integral       =  positionx_pid.integral + positionx_pid.error * dt; //dtΪ����Ƶ��
//    positionx_pid.derival        =  (positionx_pid.error - positionx_pid.passive_error) / dt; //dtΪ����Ƶ�ʣ��ö�ʱ���жϣ�
//    positionx_pid.output         =  positionx_pid.kp * positionx_pid.error + positionx_pid.ki * positionx_pid.integral + positionx_pid.kd * positionx_pid.derival;
//    positionx_pid.passive_error  =  positionx_pid.error;
//     
//    positiony_pid.measured_value =  Real_y;
//    positiony_pid.error          =  positiony_pid.measured_value - positiony_pid.set_value;
//    positiony_pid.integral       =  positiony_pid.integral + positiony_pid.error * dt; //dtΪ����Ƶ��
//    positiony_pid.derival        =  (positiony_pid.error - positiony_pid.passive_error) / dt; //dtΪ����Ƶ�ʣ��ö�ʱ���жϣ�
//    positiony_pid.output         =  positiony_pid.kp * positiony_pid.error + positiony_pid.ki * positiony_pid.integral + positiony_pid.kd * positiony_pid.derival;
//    positiony_pid.passive_error  =  positiony_pid.error;
//    
//    Servo_Platform_Track(positionx_pid.output, positiony_pid.output);  
    /****      ��ת�Ǻ͸�����PID���ڴ���END      *****/
      
//    positionx_pid.measured_value =  Real_x;
//    positionx_pid.error          =  positionx_pid.set_value - positionx_pid.measured_value;
//    positionx_pid.integral       =  positionx_pid.integral + positionx_pid.error * dt; //dtΪ����Ƶ��
//    positionx_pid.derival        =  (positionx_pid.error - positionx_pid.passive_error) / dt; //dtΪ����Ƶ�ʣ��ö�ʱ���жϣ�
//    output_temp                  =  positionx_pid.kp * positionx_pid.error + positionx_pid.ki * positionx_pid.integral + positionx_pid.kd * positionx_pid.derival + Real_x;
//    positionx_pid.output         =  output_temp > 2500 ? 2500 : output_temp;
//    positionx_pid.output         =  output_temp <  500 ?  500 : output_temp;
//    positionx_pid.passive_error  =  positionx_pid.error;
//    //DBG("have received successfully!\r\n"); 
//    positiony_pid.measured_value =  Real_y;
//    positiony_pid.error          =  positiony_pid.set_value - positiony_pid.measured_value;
//    positiony_pid.integral       =  positiony_pid.integral + positiony_pid.error * dt; //dtΪ����Ƶ��
//    positiony_pid.derival        =  (positiony_pid.error - positiony_pid.passive_error) / dt; //dtΪ����Ƶ�ʣ��ö�ʱ���жϣ�
//    output_temp                  =  Real_y - positiony_pid.kp * positiony_pid.error + positiony_pid.ki * positiony_pid.integral + positiony_pid.kd * positiony_pid.derival ;
//    positionx_pid.output         =  output_temp > 2500 ? 2500 : output_temp;
//    positionx_pid.output         =  output_temp <  500 ?  500 : output_temp;
//    positiony_pid.passive_error  =  positiony_pid.error;
    /*ÿ20ms����һ��*/
    // DBG("have received successfully!\r\n");
      //DBG("have received successfully!\r\n");
    
//    while(buffer1[i] != '\0'){
//      HAL_UART_Transmit(&huart2, buffer1+i, 1, HAL_MAX_DELAY);
//      i++;
//    }
    if(Target_Flag){
      Tim_SetPWM(1, 1, positionx_pid.output); //
      Tim_SetPWM(1, 2, positiony_pid.output);
    }  
//      Tim_SetPWM(1,1,2500);
//      HAL_Delay(1000);
//      Tim_SetPWM(1,1,500);
//      HAL_Delay(1000);
    //DBG("have received successfully!\r\n");    
  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
/**
  * @brief  ϵͳ��ʼ��
  * @param  None
  * @retval None
  */
//void system_init()
//{
////	servo_init();
//	
//}

/**
  * @brief  �����жϻص�����
  * @param  huart:����
  * @retval �ⲿ�������õľ���x,y����
  * @claim  ���Ȳ���һ�����ֽ��շ�ʽ�Ŀ����ԣ�Ȼ���ٿ��Ǽ���ָ����������������
  */
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//  uint8_t temp = 0;
//  static uint8_t flag = 0, count = 0;
//  static uint32_t sum = 0;

//  //__HAL_UART_CLEAR_PEFLAG(huart); //���ڽ�����մ����־
//  if(huart -> Instance == USART1 ) //����Ǵ���1
//  {
//      //DBG("have received successfully!\r\n");
//      temp = UART1_RxBuffer;
//      if(flag)
//        count++;
//      if((count == 0) && (temp == 0xff)){
//        flag = 1;
//        buffer1[0] = temp;
//        //DBG("have received successfully!\r\n");
//      }
//      //DBG("have received successfully!\r\n");
//      else if(count == 1 && temp < 0xff){
//          buffer1[1] = temp;
//          Rx_x = temp << 8;
//      }
//      
//      else if(count == 2){
//        if(temp == 0){
//          Target_Flag = 0; 
//          buffer1[2] = temp;
//          //DBG("have received successfully!\r\n");
//        }
//        else{
//          Target_Flag = 1;
//          buffer1[2] = temp;
//          Rx_x |= temp;
//          sum = Rx_x;
//        }
//      }
//      
//      else if(count == 3){
//        buffer1[3] = temp;
//        Rx_y = temp << 8;
//        
//      }
//      else if(count == 4){
//        buffer1[4] = temp;
//        Rx_y |= temp;
//        Real_y = Rx_y;
//        sum += temp;
//      }
//      else if(count == 5 && sum%254 == temp){
//        buffer1[5] = temp;
//        if(Target_Flag == 1){
//         Real_x = Rx_x;
//         Real_y = Rx_y; 
//        }
////        buffer1[6] = temp;
//        //DBG("have received successfully!\r\n");
////        Target_Flag = Target_Detected;
//        //DBG("have received successfully!\r\n");
//      }
//      //DBG("have received successfully!\r\n");
//     else if((count == 6) && (temp == 0xfe))
//     {
//       count = 0;
//       flag = 0;
//       //DBG("have received successfully!\r\n");
//     }
//       
////        //�Ӹ����ݴ���
//     //uartx_printf(huart2, "%x %x %x %x %x\r\n", 0xff, Real_x, Real_y, buffer1[5], 0xfe);
//     HAL_UART_Receive_IT(&huart1, (uint8_t*)&UART1_RxBuffer, 1); //���¿����ж�   
//        //HAL_UART_Transmit(&huart2, &Real_x, 1, HAL_MAX_DELAY);
//   }
//      
//}
 /*���*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  static uint8_t count = 0;
  static uint32_t sum = 0;
  if(huart -> Instance == USART1) //����Ǵ���1
  {
      if((count == 0) && (UART1_RxBuffer == 0xff))
      {    
        count++;
        buffer1[0] = UART1_RxBuffer;
      }
      else if(count == 1 && UART1_RxBuffer < 0xff)
        {
          buffer1[1] = UART1_RxBuffer;
          count++;
        }
      else if(count == 2 && UART1_RxBuffer <= 0xff)
      {
          buffer1[2] = UART1_RxBuffer;
          count++;
        if(UART1_RxBuffer == 0)
        {
          Target_Flag = 0; 
        }
        else
        {
          Target_Flag = 1;
        }
      }
      else if(count == 3 && UART1_RxBuffer < 0xff)
      {
          buffer1[3] = UART1_RxBuffer;
          count++;
      }
      else if(count == 4 && UART1_RxBuffer <= 0xff)
      {
          buffer1[4] = UART1_RxBuffer;
          count++;
          sum= ((buffer1[1]<<8|buffer1[2])+(buffer1[3]<<8|buffer1[4]))%254;
      }
      else if(count == 5 && UART1_RxBuffer==sum)
      {
          buffer1[5] = UART1_RxBuffer;
          count++;
      }
      else if((count == 6) && (UART1_RxBuffer == 0xfe))
      {
          count = 0;
          buffer1[6] = UART1_RxBuffer;
          Real_x=buffer1[1]<<8|buffer1[2];
          Real_y=buffer1[3]<<8|buffer1[4];
          //HAL_UART_Transmit(&huart2, buffer1, 7, HAL_MAX_DELAY);
      }
      else
      {
         count = 0;
         Target_Flag =0;
      }
//        //�Ӹ����ݴ���
     //uartx_printf(huart2, "%x %x %x %x %x\r\n", 0xff, Real_x, Real_y, buffer1[5], 0xfe);
     HAL_UART_Receive_IT(&huart1, (uint8_t*)&UART1_RxBuffer, 1); //���¿����ж�   
     
   }    
}

/*20msΪ���ڿ�ʼ���ж�*/
/**
  * @brief  ��ʱ���жϻص�����
  * @param  xxxx
  * @retval xxxx
  * @claim  ����ֻ��Ҫ�������ֵ��������Ҫ�����pulses,�������Ƶ�ʹ�����Ժ�������
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {

  //DBG("have received successfully!\r\n");
  //DBG("have received successfully!\r\n");
//  uint32_t output_temp;
  if (htim->Instance == htim2.Instance){
    positionx_pid.measured_value =  Real_x;
    positionx_pid.error          =  positionx_pid.measured_value - positionx_pid.set_value;
    positionx_pid.integral       =  positionx_pid.integral + positionx_pid.error * 0.02; //dtΪ����Ƶ��
    positionx_pid.derival        =  (positionx_pid.error - positionx_pid.passive_error) / 0.02; //dtΪ����Ƶ�ʣ��ö�ʱ���жϣ�
    positionx_pid.output         =  current_pulses_x - (positionx_pid.kp * positionx_pid.error + positionx_pid.ki * positionx_pid.integral + positionx_pid.kd * positionx_pid.derival);

    //    positionx_pid.output         =  output_temp > 1500 ? 1500 : output_temp;
//    positionx_pid.output         =  output_temp <  500 ?  500 : output_temp;
    positionx_pid.passive_error  =  positionx_pid.error;
    //DBG("have received successfully!\r\n"); 
    positiony_pid.measured_value =  Real_y;
    positiony_pid.error          =  positiony_pid.measured_value - positiony_pid.set_value;
    positiony_pid.integral       =  positiony_pid.integral + positiony_pid.error * 0.02; //dtΪ����Ƶ��
    positiony_pid.derival        =  (positiony_pid.error - positiony_pid.passive_error) / 0.02; //dtΪ����Ƶ�ʣ��ö�ʱ���жϣ�
    positiony_pid.output         =  current_pulses_y + (positiony_pid.kp * positiony_pid.error + positiony_pid.ki * positiony_pid.integral + positiony_pid.kd * positiony_pid.derival) ;

    //    positionx_pid.output         =  output_temp > 1500 ? 1500 : output_temp;
//    positionx_pid.output         =  output_temp <  500 ?  500 : output_temp;
    positiony_pid.passive_error  =  positiony_pid.error;

  }
  //HAL_TIM_Base_Start_IT(&htim2); //������ʱ���ж�
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
