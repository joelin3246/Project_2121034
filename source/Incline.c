//==================================================================
// ���ɰ��F�����{��
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
//  GPIO �]�w
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
//      ADC ��l��
//==============================================================================
void F_InitialADC(void)
{
  ADC_InitTypeDef          ADC_InitStructure;
  GPIO_InitTypeDef         GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;	// �n���w�ɾ���l�Ƶ��c��
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
        F_IncAuto();        //���ɦ۰ʮե�
      else
        F_IncControl();	//���ɱ���
    }
    else
      F_RelayMoveStop();
  }
}
//====================================================
//���ɱ���
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
        IncParagraph=R_IncMax;    //  �̤j���ɬq��
        IncNumTemp=R_IncNum;      //  �ثe���ɬq��
        if(IncUpDownFlg==0)       //  �ϴ���
        IncNumTemp=IncParagraph-IncNumTemp;
        R_IncNumAdBuf=(R_IncMaxAd)-(((R_IncMaxAd-R_IncMinAd)/IncParagraph)*IncNumTemp);
        */
        IncParagraph=R_IncMax;          //  �̤j���ɬq��
        if(R_IncNum)
        {
          IncNumTemp=R_IncNum-1;        //  �ثe���ɬq��
          if(IncUpDownFlg==0)           //  �ϴ���
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
      F_IncAd(R_IncNumAdBuf);     //  �ݭn��AD��m  R_IncNumAdBuf
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
  F_IncIoDownControl(0);        //�����U���~�q��
  if(RelayUpDownFlg)            //�W�@�����U����
  {
    R_IncErrTime=0;
    R_RelayWaitTime++;
    if(R_RelayWaitTime >= 10)   //�ݭn��1����,�~���ন�W�ɼҦ�
    {
      R_RelayWaitTime=0;
      RelayUpDownFlg=0;         //���ɤW��
    }
  }
  else
  {
    F_IncIoUpControl(1);        //�}�ҤW���~�q��
    F_IncErrDetection();
  }
}
//=========================================
void  F_RelayMoveDown(void)
{
  F_IncIoUpControl(0);          //�����W���~�q��
  if(RelayUpDownFlg)
  {
    F_IncIoDownControl(1);      //�}�ҤU���~�q��
    F_IncErrDetection();
  }
  else
  {
    R_IncErrTime=0;
    R_RelayWaitTime++;
    if(R_RelayWaitTime >= 10)   //�ݭn��1����,�~���ন�W�ɼҦ�
    {
      R_RelayWaitTime=0;
      RelayUpDownFlg=1;         //���ɤU��
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
  if(R_IncErrTime<120)          //  ����R_IncErrTime ����
    R_IncErrTime++;
  
  if(R_IncErrTime==1)
  {
    R_IncErrAd=R_IncNumAd;			
  }		
  if(R_IncErrTime==40)       //  4��� ad �ȨS�����󪺰ʧ@ error
  {
    R_IncErrTime=0;
    //==================
    if(R_IncNumAd>R_IncErrAd)
      i=R_IncNumAd-R_IncErrAd;
    else
      i=R_IncErrAd-R_IncNumAd;
    //==================
    if(i<5)                   //  AD �� ���\�� ���t 5 ���~�t
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
    AdTemp = ADC_GetConversionValue(ADC1);  	//  �}�l�i��ADC�ഫ
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
//�۰ʮե�
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
  switch(R_IncAutoCnt)          //  ���ɮշǳB�z
  {	
  case  0:
    F_IncIoUpControl(1);        //  �}�ҤW���~�q��
    F_IncIoDownControl(0);      //  �����U���~�q��
    R_IncAutoTime=0;
    R_IncAutoCnt=1;
    break;
    //===================================
  case  1:
    if((R_IncNumAd>=R_IncAutoTemp2)&&(R_IncNumAd<=R_IncAutoTemp1))
    {
      if(R_IncAutoTime>60)      //  í�w�W�L6��
      {
        R_IncAutoTime=0;	
        F_IncIoUpControl(0);    //  �����W���~�q��
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
    if(R_IncAutoTime>=30)       //�ݭn��3����,�~���ন�U���Ҧ�
    {
      R_IncAutoTime=0;
      F_IncIoDownControl(1);    //�}�ҤU���~�q��
      R_IncAutoCnt=3;
    }
    break;
    //===================================
  case  3:
    if((R_IncNumAd>=R_IncAutoTemp2)&&(R_IncNumAd<=R_IncAutoTemp1))
    {
      if(R_IncAutoTime>60)      //í�w�W�L6�� 
      {
        R_IncAutoTime=0;
        R_IncMaxAd=R_IncNumAd;
        F_RelayMoveStop();
        IncStopFlg=1;           //��������
        IncAutoFlg=0;
        if(R_IncMaxAd>R_IncMinAd)
        {   //  ���V	
          IncUpDownFlg=1;
          i=R_IncMaxAd-R_IncMinAd;
        }
        else
        {
          IncUpDownFlg=0;   //  �ϦV
          i=R_IncMinAd-R_IncMaxAd;
        }
        if(i<80)
        {         //  ���ɮե����~
          //R_FaultData=7;	
        }
        else
        {       //  ���ɮե� OK
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
            i=R_IncMaxAd;			//Max �P Min ���
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