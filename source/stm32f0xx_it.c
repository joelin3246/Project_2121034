/**
******************************************************************************
* @file    stm32f0xx_it.c 
* @author  MCD Application Team
* @version V1.0.0
* @date    23-March-2012
* @brief   Main Interrupt Service Routines.
*          This file provides template for all exceptions handler and 
*          peripherals interrupt service routine.
******************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
*
* Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
* You may not use this file except in compliance with the License.
* You may obtain a copy of the License at:
*
*        http://www.st.com/software_license_agreement_liberty_v2
*
* Unless required by applicable law or agreed to in writing, software 
* distributed under the License is distributed on an "AS IS" BASIS, 
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "connect.h"
/** @addtogroup STM32F0_Discovery_Peripheral_Examples
* @{
*/

/** @addtogroup PWR_STANDBY
* @{
*/

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
* @brief  This function handles NMI exception.
* @param  None
* @retval None
*/
void NMI_Handler(void)
{
}

/**
* @brief  This function handles Hard Fault exception.
* @param  None
* @retval None
*/
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
* @brief  This function handles SVCall exception.
* @param  None
* @retval None
*/
void SVC_Handler(void)
{
}

/**
* @brief  This function handles PendSVC exception.
* @param  None
* @retval None
*/
void PendSV_Handler(void)
{
}

/**
* @brief  This function handles SysTick Handler.
* @param  None
* @retval None
*/
void SysTick_Handler(void)
{
  //1 msec
  F_LedKeyScan();
  F_PwmCntSend();
  F_Pluse1sub();	//手握心線訊號偵測
  F_Pluse2sub();	//無線心跳訊號偵側
  F_IncTimeCnt();
  F_BzOn();
  F_EepromDelayTime();
  //===================
  R_TimeBase++;		
  if(R_TimeBase>9)		//10ms	
  {			
    R_TimeBase=0;
    F_Time();
    F_DisplayTime();
    F_StringMoveTime();
    F_ShowFlash();
    F_SportBzControl();
  }
  
  
}

void EXTI0_1_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line0) != RESET)
  {
    EXTI_ClearITPendingBit(EXTI_Line0);
  }
  if(EXTI_GetITStatus(EXTI_Line1) != RESET)
  {
    EXTI_ClearITPendingBit(EXTI_Line1);
  }
}

void EXTI2_3_IRQHandler(void)
{
  
  if(EXTI_GetITStatus(EXTI_Line2) != RESET)
  {
    EXTI_ClearITPendingBit(EXTI_Line2);
  }
  
  if(EXTI_GetITStatus(EXTI_Line3) != RESET)
  {
    EXTI_ClearITPendingBit(EXTI_Line3);
  }
}

void EXTI4_15_IRQHandler(void)
{
  
  if(EXTI_GetITStatus(EXTI_Line4) != RESET)
  {
    EXTI_ClearITPendingBit(EXTI_Line4);
  }  
  if(EXTI_GetITStatus(EXTI_Line5) != RESET)
  {
    EXTI_ClearITPendingBit(EXTI_Line5);
  }  
  if(EXTI_GetITStatus(EXTI_Line6) != RESET)
  {
    EXTI_ClearITPendingBit(EXTI_Line6);
  }  
  if(EXTI_GetITStatus(EXTI_Line7) != RESET)
  {
    EXTI_ClearITPendingBit(EXTI_Line7);
  } 
  if(EXTI_GetITStatus(EXTI_Line9) != RESET)
  {
    EXTI_ClearITPendingBit(EXTI_Line9);
  } 
}

/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0xx.s).                                               */
/******************************************************************************/

/**
* @brief  This function handles PPP interrupt request.
* @param  None
* @retval None
*/
/*void PPP_IRQHandler(void)
{
}*/

/**
* @}
*/

/**
* @}
*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
