//==================================================================
// 揚升馬達相關程式
//==================================================================
#include "connect.h"

/* Private macro -------------------------------------------------------------*/
 //M2-
 #define P_M2_DOWN_PIN                  GPIO_Pin_15              
 #define P_M2_DOWN_GPIO_PORT            GPIOB
 #define P_M2_DOWN_GPIO_CLK             RCC_AHBPeriph_GPIOB

 //M2+
 #define P_M2_UP_PIN                    GPIO_Pin_14                         
 #define P_M2_UP_GPIO_PORT              GPIOB
 #define P_M2_UP_GPIO_CLK               RCC_AHBPeriph_GPIOB

 //VR2
 #define P_VR2_PIN                      GPIO_Pin_1                              
 #define P_VR2_GPIO_PORT                GPIOB
 #define P_VR2_GPIO_CLK                 RCC_AHBPeriph_GPIOB
 #define P_VR2_Channel                  ADC_Channel_9

/* Private variables ---------------------------------------------------------*/

//==============================================================================
//  GPIO 設定
//==============================================================================
void  F_InitialIncline_Gpio(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  /* Enable the M2- */
  RCC_AHBPeriphClockCmd(P_M2_DOWN_GPIO_CLK, ENABLE);
  
  /* Configure the M2- pin */
  GPIO_InitStructure.GPIO_Pin = P_M2_DOWN_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(P_M2_DOWN_GPIO_PORT, &GPIO_InitStructure);
  
  /* Enable the M2+ */
  RCC_AHBPeriphClockCmd(P_M2_UP_GPIO_CLK, ENABLE);
  
  /* Configure the M2+ pin */
  GPIO_InitStructure.GPIO_Pin = P_M2_UP_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(P_M2_UP_GPIO_PORT, &GPIO_InitStructure);
}
//==============================================================================
//      ADC 初始化
//==============================================================================
void F_InitialADC(void)
{
  ADC_InitTypeDef          ADC_InitStructure;
  GPIO_InitTypeDef         GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;	// 聲明定時器初始化結構體
  TIM_OCInitTypeDef        TIM_OCInitStructure; 
  
  /* GPIOC Periph clock enable */
  RCC_AHBPeriphClockCmd(P_VR2_GPIO_CLK, ENABLE);
  
  /* ADC1 Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  
  /* TIM3 Periph clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  
  /* Configure ADC Channel0 as analog input */
  GPIO_InitStructure.GPIO_Pin = P_VR2_PIN ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(P_VR2_GPIO_PORT, &GPIO_InitStructure);
  
  /* TIM3 Configuration *******************************************************/
  TIM_DeInit(TIM3);
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  
  TIM_OCStructInit(&TIM_OCInitStructure);
  
  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 0xFF;
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
  
  /* TIM3 TRGO selection */
  TIM_SelectOutputTrigger(TIM3, TIM_TRGOSource_Update);
  
  /* ADC2 Configuration *******************************************************/
  /* ADCs DeInit */  
  ADC_DeInit(ADC1);
  
  /* Configure the ADC1 in continous mode withe a resolutuion equal to 8 bits*/
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_8b;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising;    
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T3_TRGO;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
  ADC_Init(ADC1, &ADC_InitStructure); 
  
  /* Convert the ADC1 Channel 0 with 239.5 Cycles as sampling time */ 
  ADC_ChannelConfig(ADC1, P_VR2_Channel , ADC_SampleTime_28_5Cycles);   
  
  /* ADC Calibration */
  ADC_GetCalibrationFactor(ADC1);
  
  /* Enable the auto delay feature */    
  ADC_WaitModeCmd(ADC1, ENABLE); 
  
  /* Enable the Auto power off mode */
  ADC_AutoPowerOffCmd(ADC1, ENABLE); 
  
  /* Enable ADCperipheral[PerIdx] */
  ADC_Cmd(ADC1, ENABLE);     
  
  /* Wait the ADCEN falg */
  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADEN)); 
  
  /* TIM2 enable counter */
  TIM_Cmd(TIM3, ENABLE);
  
  /* ADC1 regular Software Start Conv */ 
  ADC_StartOfConversion(ADC1);
}
//=============================================================================
void  F_IncTimeCnt(void)
{
  R_IncStartCnt++;
  if(R_IncStartCnt>99)
  {	//  100mS
    R_IncStartCnt=0;
    IncStartDetectFlg=1;
  }
}

void  F_IncludeProcess(void)
{
  if(IncStartDetectFlg)
  {
    IncStartDetectFlg=0;
    //F_InitialIncline_Gpio();
    if(IncErrFlg==0)
    {
      if(IncAutoFlg)
        F_IncAuto();        //揚升自動校正
      else
        F_IncControl();	//揚升控制
    }
    else
      F_RelayMoveStop();
  }
}
//====================================================
//揚升控制
//====================================================
void  F_IncControl(void)
{
  unsigned  char  IncNumTemp,IncParagraph;
  if(IncStopFlg==0)
  {
    if(R_IncNumDetect!=R_IncNum)
    {  
      R_IncNumDetect=R_IncNum;
      IncSetFlag=1;
    }
    if(IncSetFlag==1)
    {
      if(R_SysMode==EngMode4Val)
      {
        
        
      }
      else
      {
        //=======================
        /*
        IncParagraph=R_IncMax;    //  最大揚升段數
        IncNumTemp=R_IncNum;      //  目前揚升段數
        if(IncUpDownFlg==0)       //  反揚升
        IncNumTemp=IncParagraph-IncNumTemp;
        R_IncNumAdBuf=(R_IncMaxAd)-(((R_IncMaxAd-R_IncMinAd)/IncParagraph)*IncNumTemp);
        */
        IncParagraph=R_IncMax;          //  最大揚升段數
        if(R_IncNum)
        {
          IncNumTemp=R_IncNum-1;        //  目前揚升段數
          if(IncUpDownFlg==0)           //  反揚升
            IncNumTemp=IncParagraph-IncNumTemp;
          //R_IncNumAdBuf=(R_IncMaxAd)-((float)(R_IncMaxAd-R_IncMinAd)*IncNumTemp/IncParagraph);
          R_IncNumAdBuf=(R_IncMaxAd)-((R_IncMaxAd-R_IncMinAd)*IncNumTemp/IncParagraph);
        }
        else
        {
          R_IncNumAdBuf=R_IncCarryAd;
        }
        //=======================
      }
      F_IncAd(R_IncNumAdBuf);     //  需要的AD位置  R_IncNumAdBuf
      if(R_IncNumAd<R_IncAutoTemp2)
      {
        if(IncUpDownFlg)
          F_RelayMoveDown();
        else
          F_RelayMoveUp();
      }
      else  if(R_IncNumAd>R_IncAutoTemp1)
      {
        if(IncUpDownFlg)
          F_RelayMoveUp();
        else
          F_RelayMoveDown();
      }
      else
        F_RelayMoveStop();
    }
    else
      F_RelayMoveStop();
  }
  else
  {
    F_RelayMoveStop();
    R_IncNumDetect=0xff;
  }
}
//=========================================
void  F_RelayMoveUp(void)
{ 
  F_IncIoDownControl(0);        //關閉下降繼電器
  if(RelayUpDownFlg)            //上一次為下降時
  {
    R_IncErrTime=0;
    R_RelayWaitTime++;
    if(R_RelayWaitTime >= 10)   //需要等1秒鐘,才能轉成上升模式
    {
      R_RelayWaitTime=0;
      RelayUpDownFlg=0;         //揚升上升
    }
  }
  else
  {
    F_IncIoUpControl(1);        //開啟上升繼電器
    F_IncErrDetection();
  }
}
//=========================================
void  F_RelayMoveDown(void)
{
  F_IncIoUpControl(0);          //關閉上升繼電器
  if(RelayUpDownFlg)
  {
    F_IncIoDownControl(1);      //開啟下降繼電器
    F_IncErrDetection();
  }
  else
  {
    R_IncErrTime=0;
    R_RelayWaitTime++;
    if(R_RelayWaitTime >= 10)   //需要等1秒鐘,才能轉成上升模式
    {
      R_RelayWaitTime=0;
      RelayUpDownFlg=1;         //揚升下降
    }
  }
}
//=========================================
void  F_RelayMoveStop(void)
{
  F_IncIoUpControl(0);
  F_IncIoDownControl(0);
  IncSetFlag=0;
  R_RelayWaitTime=0;
  R_IncErrTime=0;
  IncAutoFlg=0;
  R_IncAutoTime=0;
  R_IncAutoCnt=0;
}
//=========================================
void  F_IncErrDetection(void)
{	//100mS
  unsigned  char  i;
  if(R_IncErrTime<120)          //  限制R_IncErrTime 溢位
    R_IncErrTime++;
  
  if(R_IncErrTime==1)
  {
    R_IncErrAd=R_IncNumAd;			
  }		
  if(R_IncErrTime==40)       //  4秒後 ad 值沒有任何的動作 error
  {
    R_IncErrTime=0;
    //==================
    if(R_IncNumAd>R_IncErrAd)
      i=R_IncNumAd-R_IncErrAd;
    else
      i=R_IncErrAd-R_IncNumAd;
    //==================
    if(i<5)                   //  AD 值 允許有 正負 5 的誤差
      IncErrFlg=1;
  }
}
//======================================================
void  F_IncAd(unsigned	char  Data)
{
  unsigned  int   AdTemp=0,IncAdTemp=0;
  unsigned  char  i;	
  for(i=0;i<5;i++)
  {
    AdTemp = ADC_GetConversionValue(ADC1);  	//  開始進行ADC轉換
    IncAdTemp=AdTemp+IncAdTemp;	    
  }
  R_IncNumAd=IncAdTemp/5;
  //=================
  if(Data<=253)
    R_IncAutoTemp1=Data+2;
  else
    R_IncAutoTemp1=Data;
  if(Data>=2)	
    R_IncAutoTemp2=Data-2;
  else
    R_IncAutoTemp2=Data;
}
//==========================================================
//自動校正
//==========================================================
void  F_IncAuto(void)
{
  unsigned  char  i;
  R_IncAutoTime++;
  F_IncAd(R_IncAutoAd);
  //=====================
  if(R_IncAutoTemp1<=253)
    R_IncAutoTemp1=R_IncAutoTemp1+2;
  else
    R_IncAutoTemp1=R_IncAutoTemp1;
  if(R_IncAutoTemp2>=2)	
    R_IncAutoTemp2=R_IncAutoTemp2-2;
  else
    R_IncAutoTemp2=R_IncAutoTemp2;
  //=====================
  switch(R_IncAutoCnt)          //  揚升校準處理
  {	
  case  0:
    F_IncIoUpControl(1);        //  開啟上升繼電器
    F_IncIoDownControl(0);      //  關閉下降繼電器
    R_IncAutoTime=0;
    R_IncAutoCnt=1;
    break;
    //===================================
  case  1:
    if((R_IncNumAd>=R_IncAutoTemp2)&&(R_IncNumAd<=R_IncAutoTemp1))
    {
      if(R_IncAutoTime>60)      //  穩定超過6秒
      {
        R_IncAutoTime=0;	
        F_IncIoUpControl(0);    //  關閉上升繼電器
        R_IncMinAd=R_IncNumAd;
        R_IncAutoCnt=2;
      }
    }
    else
    {
      R_IncAutoAd=R_IncNumAd;
      R_IncAutoTime=0;
    }
    break;
    //===================================
  case  2:
    if(R_IncAutoTime>=30)       //需要等3秒鐘,才能轉成下降模式
    {
      R_IncAutoTime=0;
      F_IncIoDownControl(1);    //開啟下降繼電器
      R_IncAutoCnt=3;
    }
    break;
    //===================================
  case  3:
    if((R_IncNumAd>=R_IncAutoTemp2)&&(R_IncNumAd<=R_IncAutoTemp1))
    {
      if(R_IncAutoTime>60)      //穩定超過6秒 
      {
        R_IncAutoTime=0;
        R_IncMaxAd=R_IncNumAd;
        F_RelayMoveStop();
        IncStopFlg=1;           //揚升關閉
        IncAutoFlg=0;
        if(R_IncMaxAd>R_IncMinAd)
        {   //  正向	
          IncUpDownFlg=1;
          i=R_IncMaxAd-R_IncMinAd;
        }
        else
        {
          IncUpDownFlg=0;   //  反向
          i=R_IncMinAd-R_IncMaxAd;
        }
        if(i<80)
        {         //  揚升校正錯誤
          //R_FaultData=7;	
        }
        else
        {       //  揚升校正 OK
          if(IncUpDownFlg==1)
          {
            EE_Write(EE_IncUpDown,1);	
            R_IncMaxAd=R_IncMaxAd-2;
            R_IncNumAdBuf=R_IncMaxAd;
            EE_Write(EE_IncMaxAd,R_IncMaxAd);
            EE_Write(EE_IncMinAd,R_IncMinAd);	
          }
          else
          {
            EE_Write(EE_IncUpDown,0);
            i=R_IncMaxAd;			//Max 與 Min 對調
            R_IncMaxAd=R_IncMinAd;
            R_IncMinAd=i;
            R_IncMinAd=R_IncMinAd+2;
            R_IncNumAdBuf=R_IncMinAd;
            EE_Write(EE_IncMaxAd,R_IncMaxAd);
            EE_Write(EE_IncMinAd,R_IncMinAd);
          }
        }
      }
    }
    else
    {
      R_IncAutoAd=R_IncNumAd;
      R_IncAutoTime=0;
    }
    break;
  }
}
//===================================================
void F_IncIoUpControl(unsigned char     Data)
{  
    /*
    if(Data)
      P_M2_UP_GPIO_PORT -> BSRR = P_M2_UP_PIN;  
      else
        P_M2_UP_GPIO_PORT -> BRR = P_M2_UP_PIN;  
    */   
  if(AcDcMotorFlg)
  {
    if(Data)
      P_M2_UP_GPIO_PORT -> BSRR = P_M2_UP_PIN;  
      else
        P_M2_UP_GPIO_PORT -> BRR = P_M2_UP_PIN;   
  }
  else
  {
    if(Data)
      P_M2_UP_GPIO_PORT -> BRR = P_M2_UP_PIN;   
      else
        P_M2_UP_GPIO_PORT -> BSRR = P_M2_UP_PIN;  
  }
}
//===================================================
void F_IncIoDownControl(unsigned char   Data)
{
  /*
    if(Data)
      P_M2_DOWN_GPIO_PORT -> BSRR = P_M2_DOWN_PIN;   
      else
        P_M2_DOWN_GPIO_PORT->BRR = P_M2_DOWN_PIN; 
  */
  if(AcDcMotorFlg)
  {
    if(Data)
      P_M2_DOWN_GPIO_PORT -> BSRR = P_M2_DOWN_PIN;   
      else
        P_M2_DOWN_GPIO_PORT->BRR = P_M2_DOWN_PIN;  
  }
  else
  {
    if(Data)
      P_M2_DOWN_GPIO_PORT->BRR = P_M2_DOWN_PIN;  
      else
        P_M2_DOWN_GPIO_PORT -> BSRR = P_M2_DOWN_PIN;   
  }
}