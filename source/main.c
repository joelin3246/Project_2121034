//===========================================================================		
// �W       �� : 21210034
// �t �� �N �� : 
// �� �q �W �� : �^�F���
// �� �� �� �� : STM32051c8
// ��       �� : �~��8MHz
//    CLOCK    : 
// �� �g �� �� : 
// �� �� �s �X : 
// �t �X �w �� : 
// �@       �� : Chandler
// �\ �� ² �� : 
// �N �� �� �� :
// CLOCK Source:
// CHECK SUM   :	
// �� �� �� �e 
/*
  �쪩�{�� ��2121012 �\�ಾ�ӹL�ӡA�ȥ[�Jeup��ac���W������]�w����
	�䥦�ާ@�W�\��ݸ�2121012�P�B�ץ�
	
	2012/4/26 
	1. �u�{�Ҧ�1�[�J����AC �BDC��������
	
	2012/5/09
	1. �ק�^��b���D��ơA�v�T�i��ɶ������������p
	2. �ק�����speed prog�n���inc prog���\��
	
	2012/5/14
	1. �ק�P-1~5 �����SPEED PROG�A�ؼгt�ת��w�]���ܫK�����x
			�̧C�t�A��b���^SPEED PROG�ɥؼгt�צ^�_��ӹw�]�� (�^��62�B����10)
			
	2012/6/27
	1. �ק�b10�����H�W���ɭԡA�����ɳt���ɶ��אּ1�� 	
	
	2012/10/16 
	1. Chandler�]�w��pin�����q���|���j���A�N�q����T���j������
	2. �w��pin�����A���ݭn��i�J�ٹq�Ҧ�
	3. �����ܧ�v1.1
        //========================  
  �H�W�O�������e���ӭק�O��
      2013 / 11 / 8 �����e�ˡA�׶��ئp�U
        1. �NSTM8105S�A�אּSTM32051C�A�[�J�t�׸򴭤ɧֳt��AUI�ާ@�򤧫e���ؤ@��
        
      2014 / 5 / 28 
      1. �}���� �bMANUAL�ݾ��Ҧ��U�A�N���@����L15  �A��START���@�|�ۤv�^��L0    ���ӭn���bL15���a��Ұ�
          
*/
//==========================================================
/* Includes ------------------------------------------------------------------*/
#include "connect.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
// io define
//BZ
#define P_BZ_PIN                        GPIO_Pin_15
#define P_BZ_GPIO_PORT                  GPIOA
#define P_BZ_GPIO_CLK                   RCC_AHBPeriph_GPIOA
#define M_BZ_SetHigh                    P_BZ_GPIO_PORT->BSRR = P_BZ_PIN   
#define M_BZ_SetLow                     P_BZ_GPIO_PORT->BRR = P_BZ_PIN 
//ERP
#define P_ERP_PIN                       GPIO_Pin_3
#define P_ERP_GPIO_PORT                 GPIOB
#define P_ERP_GPIO_CLK                  RCC_AHBPeriph_GPIOB
#define M_ERP_SetHigh                   P_ERP_GPIO_PORT->BSRR = P_ERP_PIN   
#define M_ERP_SetLow                    P_ERP_GPIO_PORT->BRR = P_ERP_PIN 

//BackLight
#define P_BackLight_PIN                 GPIO_Pin_7
#define P_BackLight_GPIO_PORT           GPIOF
#define P_BackLight_GPIO_CLK            RCC_AHBPeriph_GPIOF
#define M_BackLight_SetHigh             P_BackLight_GPIO_PORT->BSRR = P_BackLight_PIN   
#define M_BackLight_SetLow              P_BackLight_GPIO_PORT->BRR = P_BackLight_PIN 

//Safe Key
#define P_SafeKey_PIN                      GPIO_Pin_10 
#define P_SafeKey_GPIO_PORT                GPIOA
#define P_SafeKey_GPIO_CLK                 RCC_AHBPeriph_GPIOA

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
extern void F_InitialHT1625_GPIO(void);
//==============================================================================
//io�]�w
//==============================================================================
void F_GpioSetup(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
 
  RCC_AHBPeriphClockCmd(P_SafeKey_GPIO_CLK, ENABLE);
  // Configure the KBSense pin 
  GPIO_InitStructure.GPIO_Pin = P_SafeKey_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(P_SafeKey_GPIO_PORT, &GPIO_InitStructure);
  
  // Output BZ on PA15
  // Enable the BZ
  RCC_AHBPeriphClockCmd(P_BZ_GPIO_CLK, ENABLE);
  // Configure the BZ  pin 
  GPIO_InitStructure.GPIO_Pin = P_BZ_PIN ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(P_BZ_GPIO_PORT, &GPIO_InitStructure);
  
  // Output EUP on PB3 
  // Enable the EUP 
  RCC_AHBPeriphClockCmd(P_ERP_GPIO_CLK, ENABLE);
  // Configure the EUP  pin
  GPIO_InitStructure.GPIO_Pin = P_ERP_PIN ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(P_ERP_GPIO_PORT, &GPIO_InitStructure);
  
  // Output P_BackLight on PF7
  // Enable the BackLight 
  RCC_AHBPeriphClockCmd(P_BackLight_GPIO_CLK, ENABLE);
  // Configure the P_BackLight  pin
  GPIO_InitStructure.GPIO_Pin = P_BackLight_PIN ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(P_BackLight_GPIO_PORT, &GPIO_InitStructure);  
  F_InitialHT1625_GPIO();
  F_InitialKB_GPIO();
  F_InitialEEPROM_GPIO();
  F_InitialIncline_Gpio();
  F_InitialADC();
  F_InitialPulse_GPIO();
  F_InitialSPD_GPIO();
  /*

  F_InitialADC2();
  F_InitialMotor_Gpio();
  F_InitialADC1();
  */
}
//==============================================================================
// 
//==============================================================================
void F_BackLight(unsigned char data)	
{															
  if(data)
    M_BackLight_SetHigh;
    else
      M_BackLight_SetLow;
}
//=========================
void F_BzOn(void)
{
    if(LongBzFlg==1)
    {
      M_BZ_SetHigh;
    }
    else 
    {
      if((R_BzCnt&0x02)==0x02)
      {
        M_BZ_SetHigh;
      }
      else
        M_BZ_SetLow;
      //=====================
      if(R_BzCnt==0)
      {
        M_BZ_SetLow;
      }
    }
}
//==============================================================================
// Tick Timer �]�w :
//==============================================================================
void F_Tick_Config(void)
{
  RCC_ClocksTypeDef RCC_ClockFreq;
  
  /* This function fills the RCC_ClockFreq structure with the current
  frequencies of different on chip clocks (for debug purpose) */
  RCC_GetClocksFreq(&RCC_ClockFreq);
  
  /* Setup SysTick Timer for 1 m sec interrupts  */
  if (SysTick_Config(RCC_ClockFreq.SYSCLK_Frequency / 1000))
  { 
    /* Capture error */ 
    while(1);
  }
}
//==============================================================================
// �ݪ����]�w : �Ψӷ�RESET ��
//==============================================================================
void IWDG_Config(unsigned char timeout)
{
  /* IWDG timeout equal to 250 ms (the timeout may varies due to LSI frequency
  dispersion) */
  /* Enable write access to IWDG_PR and IWDG_RLR registers */
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
  
  /* IWDG counter clock: LSI/32 */
  //IWDG_SetPrescaler(IWDG_Prescaler_32);
  /* IWDG counter clock: LSI/256 */
  IWDG_SetPrescaler(IWDG_Prescaler_256);
  
  /* Set counter reload value to obtain 250ms IWDG TimeOut.
  Counter Reload Value = 250ms/IWDG counter clock period
  = 250ms / (LSI/32)
  = 0.25s / (LsiFreq/32)
  = LsiFreq/(32 * 4)
  = LsiFreq/128
  */
  // IWDG_SetReload(LsiFreq/128);
  
  IWDG_SetReload(timeout);
  
  /* Reload IWDG counter */
  IWDG_ReloadCounter();
  
  /* Enable IWDG (the LSI oscillator will be enabled by hardware) */
  IWDG_Enable();
}
//==============================================================================
//  �]�m�~�����_
//==============================================================================
void EXTI_Config(void)
{
  EXTI_InitTypeDef   EXTI_InitStructure;
  NVIC_InitTypeDef   NVIC_InitStructure;
  
  /* Enable SYSCFG clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  
  //=======================================================
  /* Connect EXTI0 Line to PA0 pin */
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);
  
  /* Configure EXTI0 line */
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  
  /* Enable and set EXTI1 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0x00;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  EXTI_GenerateSWInterrupt(EXTI_Line0);
  
  /* Connect EXTI1 Line to PA1 pin */
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource1);
  
  /* Configure EXTI1 line */
  EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  
  /* Enable and set EXTI1 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0x00;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  EXTI_GenerateSWInterrupt(EXTI_Line1);
  
  /* Connect EXTI2 Line to PA2 pin */
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource2);
  
  /* Configure EXTI2 line */
  EXTI_InitStructure.EXTI_Line = EXTI_Line2;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  
  /* Enable and set EXTI2 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI2_3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0x00;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  EXTI_GenerateSWInterrupt(EXTI_Line2);
  //=======================================================
  
  /* Connect EXTI3 Line to PA3 pin */
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource3);
  
  /* Configure EXTI3 line */
  EXTI_InitStructure.EXTI_Line = EXTI_Line3;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  
  /* Enable and set EXTI3 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI2_3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0x00;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  EXTI_GenerateSWInterrupt(EXTI_Line3);
  //----------------------------------------------------------------------------
  /* Connect EXTI4 Line to PA4 pin */
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource4);
  
  /* Configure EXTI4 line */
  EXTI_InitStructure.EXTI_Line = EXTI_Line4;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  
  /* Enable and set EXTI4 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI4_15_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0x00;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  EXTI_GenerateSWInterrupt(EXTI_Line4);
  //----------------------------------------------------------------------------  
  /* Connect EXTI5 Line to PA5 pin */
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource5);
  
  /* Configure EXTI5 line */
  EXTI_InitStructure.EXTI_Line = EXTI_Line5;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  
  /* Enable and set EXTI5 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI4_15_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0x00;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  EXTI_GenerateSWInterrupt(EXTI_Line5);
  //----------------------------------------------------------------------------  
  /* Connect EXTI6 Line to PA6 pin */
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource6);
  
  /* Configure EXTI3 line */
  EXTI_InitStructure.EXTI_Line = EXTI_Line6;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  
  /* Enable and set EXTI6 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI4_15_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0x00;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  EXTI_GenerateSWInterrupt(EXTI_Line6);
  //----------------------------------------------------------------------------
  /* Connect EXTI7 Line to PA7 pin */
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource7);
  
  /* Configure EXTI7 line */
  EXTI_InitStructure.EXTI_Line = EXTI_Line7;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  
  /* Enable and set EXTI7 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI4_15_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0x00;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  EXTI_GenerateSWInterrupt(EXTI_Line7);
}
//==============================================================================
//  ��_ CLK
//==============================================================================
void SYSCLKConfig_AfterWakeup (void)
{  
  /* After wake-up from STOP reconfigure the system clock */
  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);
  
  /* Wait till HSE is ready */
  while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET)
  {}
  
  /* Enable PLL */
  RCC_PLLCmd(ENABLE);
  
  /* Wait till PLL is ready */
  while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
  {}
  
  /* Select PLL as system clock source */
  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
  
  /* Wait till PLL is used as system clock source */
  while (RCC_GetSYSCLKSource() != 0x08)
  {}
}
//==============================================================================
//  Sleep �]�w (EUP)
//==============================================================================
void F_Sleep_Init(void)
{
  F_AllLCDRam(0);
  F_Display();
  
  F_1625CS_1(0);
  F_1625WR(0);
  F_1625DATA(0);
  F_BackLight(0);
  F_IncControlUp(0);
  F_IncControlDown(0);
  F_EUP_EEPROM_GPIO();
  // EUP
  //M_ERP_SetHigh;
  M_ERP_SetLow;
  
  EXTI_Config();
  F_ERP_KBSet(); 
  /* Request to enter STOP mode with regulator in low power mode */
  PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);
  
  EXTI_DeInit();
  IWDG_Config(0);
}
//==============================================================================
//system �]�w
//==============================================================================
void F_SysInit(void)
{
    F_GpioSetup();
    F_Tick_Config();
}
//==============================================================================
//�D�{��
//==============================================================================
int main(void)
{
  // Configure System 
  F_SysInit();
  M_ERP_SetHigh;
  LongBzFlg=1;                  // �}�� B 1�n
  IncStopFlg=1;                 // ��������
  R_IncNum=1;                   // ���ɹw�]��
  F_EE_init();          // �pEEPROM���~�i�JEER�Ҧ�	  
  F_BackLight(1);
  while(1)
  {
    switch(R_SysMode)
    {
      case SysStartModeVal:
        F_SysStartMode();
        break;
      case ProgSetModeVal:
        F_ProgSetMode();
        break;
      case SysCountDownModeVal:
        F_SysCountDownMode();					
        break;
      case ManualSportModeVal:
        F_ManualSportMode();
        break;
      case ProgSportModeVal:
        F_ProgSportMode();
        break;
      case UserSportModeVal:	
        F_UserSportMode();
        break;
      case HrcSportModeVal:	
        F_HrcSportMode();
        break;	
      case SysSportPassModeVal:	
        F_SysSportPassMode();	
        break;
      case SysSportModeEndVal:
        F_SysSportModeEnd();
        break;	
      case SysErrModeVal:
        F_SysErrMode();			
        break;
      case EngMode1Val:
        F_EngMode1();
        break;
      case EngMode2Val:
        F_EngMode2();
        break;
      case EngMode3Val:
        F_EngMode3();
        break;
      case EngMode4Val:
        F_EngMode4();
        break;
      case SysSleepModeVal:
        F_SysSleepMode();
        break;
    }
    if(R_SysMode != SysErrModeVal)
      F_SpeedFeedback();
    if(R_SysMode != SysStartModeVal)
      F_IncludeProcess();
    F_PluseFunction1();		//�ⴤ�߽u�T���p��
    F_PluseFunction2();		//�L�u�߸��T���p��
    F_Safety();
  }
}
//====================================================
//SafetyOnFg:1 have safe pin�ASafetyOnFg:0 No safe pin
//====================================================
void    F_Safety(void)
{
  if(T40msFlg==1)
  {
    T40msFlg=0;
    if(GPIO_ReadInputDataBit( P_SafeKey_GPIO_PORT, P_SafeKey_PIN))	//Safety_P==1
    {
      if(SafetyOnFg==1)
      {
        R_Safety++;
        if(R_Safety>4)
        {	
          R_Safety=0;
          SafetyOnFg=0;
          F_Rest();			
        }
      }
    }
    else
    {
      if(SafetyOnFg==0)
      {
        R_Safety++;
        if(R_Safety>4)
        {				
          R_Safety=0;
          R_SleepTime=0;
          SafetyOnFg=1;	
          IncStopFlg=1;			//	��������
          R_SysMode=SysErrModeVal;	
          R_ErrData=0;
        }
      }
    }
  }
}
#ifdef  USE_FULL_ASSERT
/**
* @brief  Reports the name of the source file and the source line number
*         where the assert_param error has occurred.
* @param  file: pointer to the source file name
* @param  line: assert_param error line source number
* @retval None
*/
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
  ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  
  /* Infinite loop */
  while (1)
  {
  }
}
#endif



