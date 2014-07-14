#include "connect.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
//SPD IN
#define P_SPD_IN_PIN                    GPIO_Pin_9                            
#define P_SPD_IN_GPIO_PORT              GPIOA
#define P_SPD_IN_GPIO_CLK               RCC_AHBPeriph_GPIOA

 //Speed Up
#define P_Speed_UP_PIN                 GPIO_Pin_12                        
#define P_Speed_UP_GPIO_PORT           GPIOB
#define P_Speed_UP_GPIO_CLK            RCC_AHBPeriph_GPIOB
#define M_Speed_UP_SetHigh             P_Speed_UP_GPIO_PORT -> BSRR = P_Speed_UP_PIN   
#define M_Speed_UP_SetLow              P_Speed_UP_GPIO_PORT -> BRR = P_Speed_UP_PIN 


 //Speed Down
#define P_Speed_DOWN_PIN                GPIO_Pin_13        
#define P_Speed_DOWN_GPIO_PORT          GPIOB
#define P_Speed_DOWN_GPIO_CLK           RCC_AHBPeriph_GPIOB
#define M_Speed_DOWN_SetHigh            P_Speed_DOWN_GPIO_PORT -> BSRR = P_Speed_DOWN_PIN   
#define M_Speed_DOWN_SetLow             P_Speed_DOWN_GPIO_PORT -> BRR = P_Speed_DOWN_PIN


  //Sw Ctrl
#define P_Sw_Ctrl_PIN                   GPIO_Pin_6        
#define P_Sw_Ctrl_GPIO_PORT             GPIOF
#define P_Sw_Ctrl_GPIO_CLK              RCC_AHBPeriph_GPIOF
#define M_Sw_Ctrl_SetHigh            P_Sw_Ctrl_GPIO_PORT -> BSRR = P_Sw_Ctrl_PIN   
#define M_Sw_Ctrl_SetLow             P_Sw_Ctrl_GPIO_PORT -> BRR = P_Sw_Ctrl_PIN

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
//==============================================================================
//  GPIO 設定
//==============================================================================
void F_InitialSPD_GPIO(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  /* Enable the Speed Up */
  RCC_AHBPeriphClockCmd(P_Speed_UP_GPIO_CLK, ENABLE);
  
  /* Configure the Speed Up pin */
  GPIO_InitStructure.GPIO_Pin = P_Speed_UP_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(P_Speed_UP_GPIO_PORT, &GPIO_InitStructure);
  
  /* Enable the Speed Down */
  RCC_AHBPeriphClockCmd(P_Speed_DOWN_GPIO_CLK, ENABLE);
  
  /* Configure the Speed Down pin */
  GPIO_InitStructure.GPIO_Pin = P_Speed_DOWN_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(P_Speed_DOWN_GPIO_PORT, &GPIO_InitStructure);
  
  /* Enable the Sw Ctrl */
  RCC_AHBPeriphClockCmd(P_Sw_Ctrl_GPIO_CLK, ENABLE);
  
  /* Configure the Sw Ctrl pin */
  GPIO_InitStructure.GPIO_Pin = P_Sw_Ctrl_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  //GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(P_Sw_Ctrl_GPIO_PORT, &GPIO_InitStructure);
  
  
  // Input SPD IN  on PA9  
  // Enable the SPD IN 
  RCC_AHBPeriphClockCmd(P_SPD_IN_GPIO_CLK, ENABLE);
  // Configure the SPD IN pin 
  GPIO_InitStructure.GPIO_Pin = P_SPD_IN_PIN ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(P_SPD_IN_GPIO_PORT, &GPIO_InitStructure);
} 
//==============================================================================
// 
//==============================================================================
void	F_PwmCntSend(void)
{
  //========================================
  //	轉速偵測
  R_SpeedCntBuf++;
  if((GPIO_ReadInputDataBit(P_SPD_IN_GPIO_PORT, P_SPD_IN_PIN))==0x00)
  {
    if(SpeedStatusFlg==0)	//low-->Hi
    {
      SpeedStatusFlg=1;
      if((R_SpeedCntBuf<3000)&&(R_SpeedCntBuf>20))
      {
        if(FriestSpeedFlg)
        {
          if(R_SpeedCntBuf<2000)
            SpeedMoveFlg=1;
          else
            SpeedMoveFlg=0;
          R_SpeedCnt=R_SpeedCntBuf;
          R_SpeedCntBuf=0;
        }
        else
        {
          FriestSpeedFlg=1;
          R_SpeedCntBuf=0;
        }
      }
      else
      {
        R_SpeedCntBuf=0;
        FriestSpeedFlg=0;
      }
    }
  }
  else
    SpeedStatusFlg=0;
  //==============	
  if(R_SpeedCntBuf>3000)
  {
    R_SpeedCntBuf=0;			
    R_SpeedCnt=0;
    FriestSpeedFlg=0;	
    SpeedMoveFlg=0;
  }
  //==================================================
  R_SpeedDetectTime++;
  if(R_SpeedDetectTime>30)
  {	// 每 31ms 執行一次
    R_SpeedDetectTime=0;
    //===== 送出 Speed Count ========
    if(R_SpeedPwmCnt==0)				// Speed 傳送階數
    {
      M_Speed_UP_SetLow;
      M_Speed_DOWN_SetLow;
      //BitClr(PE_ODR,BIT0);		//	PwmUp_P
      //BitClr(PD_ODR,BIT0);		//	PwmDown_P
    }
    else
    {
      if(MotoUpDownFlg==0)
      {	// 0:馬達加速 / 1:馬達減速
        if( !GPIO_ReadInputDataBit( P_Speed_UP_GPIO_PORT , P_Speed_UP_PIN ))
          M_Speed_UP_SetHigh;
        else
        {
          M_Speed_UP_SetLow;
          R_SpeedPwmCnt--;       // 送出 speed count
          if(R_SpeedPwmCntSave<475)
            R_SpeedPwmCntSave++;	
        }
      }
      else
      {
        if( !GPIO_ReadInputDataBit( P_Speed_DOWN_GPIO_PORT , P_Speed_DOWN_PIN ))
          M_Speed_DOWN_SetHigh;
        else
        {
          M_Speed_DOWN_SetLow;
          R_SpeedPwmCnt--;       // 送出 speed count
          if(R_SpeedPwmCntSave!=0)
            R_SpeedPwmCntSave--;
        }
      }
    }
  }
  //=============================
  R_SpdFbTime++;
  if(R_SpdFbTime>R_SpdFbTimeEnd)	// 2 秒
  {
    R_SpdFbTime=0;	
    SpdFbTimeFlg=1;
  }
}
//=======================================
//速度回授
//=======================================
void	F_SpeedFeedback(void)
{
  unsigned	char	SpeedTemp;
  unsigned	int	RpmTemp;
    float Temp,i;
  if(SpdFbTimeFlg)
  {
    SpdFbTimeFlg=0;
    if(R_SpeedCnt==0)
      RpmTemp=0;
    else
      RpmTemp=(60000/R_SpeedCnt);
    
      if(ChangeUnitFlg==1)
        i=0.0002971;
        else
          i=0.0004785;
      Temp=(float)(i*RpmTemp*R_WheelSize);   // 單位  60*RpmTemp*R_WheelSize*3.14*2.54)/1000000
      SpeedTemp=(unsigned char)Temp;
    //===========================
    if(SpeedTemp<99)
      R_SpdFbTimeEnd=1999;  //  2秒
    else
      R_SpdFbTimeEnd=999;
    //===========================				
    if(SpeedAutoFlg)
      F_SpeedAuto(SpeedTemp);
    else
      F_SpeedControl(SpeedTemp);
  }
}
//=====================================
void	F_SpeedAutoInit(void)
{
  R_SpdFbTime=0;
  SpdFbTimeFlg=0;
  SpeedAutoFlg=1;
  MotoUpDownFlg=0;
  R_SpeedAutoCnt=0;
  R_SpeedPwmCnt=13;
  F_SpeedSwCotrol(1);
  R_SpeedBuf=0;
}
//=====================================
void	F_SpeedAuto(unsigned	char	Speed)
{
  unsigned	char	i;
  R_SpeedBuf=Speed;
  switch(R_SpeedAutoCnt)
  {
    case	0:	//	低速校正
      if((Speed>=R_SpeedMin) &&(Speed<=R_SpeedMin+2))
      {	//	低速校正結束
        R_LowSpeedCntDelay++;
        if(R_LowSpeedCntDelay>2)
        {
          R_LowSpeedCntDelay=0;
          R_PwmLowSpeed=R_SpeedPwmCntSave;
          EE_Write(EE_PwmLowSpeed,R_PwmLowSpeed);
          R_SpeedAutoCnt=1;
        }
      }
      else	if(R_SpeedMin>Speed)
      {
        R_LowSpeedCntDelay=0;					
        MotoUpDownFlg=0;			//	馬達加速 
        R_SpeedPwmCnt=1;
      }
      else
      {
        R_LowSpeedCntDelay=0;		
        MotoUpDownFlg=1;		//	馬達減速
        R_SpeedPwmCnt=1;
      }
      break;
      //============================
      case	1:	//	高速確認 
        if(R_SpeedMax<=Speed)		//校正完成
        {	
          SpeedAutoFlg=0;		//速度校正完成
          R_SpeedPwmCnt=0;
          F_SpeedSwCotrol(0);
        }
        else
        {
          if(R_SpeedMax>Speed)
          {
            MotoUpDownFlg=0;			//	馬達加速
            i=R_SpeedMax-Speed;
          }
          else
          {
            MotoUpDownFlg=1;		//	馬達減速
            i=Speed-R_SpeedMax;
          }
          if(i>99)            // > ±5.0Km
            R_SpeedPwmCnt = 25;
          else if(i>49)     // > ±4.0Km 
            R_SpeedPwmCnt = 20;
          else if(i>39)     // > ±3.0Km
            R_SpeedPwmCnt = 13;
          else if(i>19)     // > ±2.0Km
            R_SpeedPwmCnt = 10;
          else if(i>9)       // > ±1.0Km
            R_SpeedPwmCnt = 8;
          else if(i>2)       // > ±0.5Km
            R_SpeedPwmCnt = 3;
          else if(i>0)       // > ±0.1Km
            R_SpeedPwmCnt = 1;  				// 1 階
        }
        break;
  }
}
//=====================================
void	F_SpeedFirstInit(void)
{
  F_SpeedSwCotrol(1);
  R_SpdFbTime=0;
  SpdFbTimeFlg=0;
  MotoUpDownFlg=0;			//	馬達加速
  R_SpeedPwmCnt=R_PwmLowSpeed;
  R_SpeedNum=R_SpeedBuf;
}
//=====================================
void	F_SpeedControl(unsigned	char	Speed)
{
  unsigned	char	i;
  if(R_SpeedNum)
  {
    F_SpeedSwCotrol(1);
    if(R_SpeedNum>Speed)
    {
      MotoUpDownFlg=0;			//	馬達加速
      i=R_SpeedNum-Speed;
    }
    else
    {
      MotoUpDownFlg=1;		//	馬達減速
      i=Speed-R_SpeedNum;
    }
    if(i>99)            // > ±5.0Km
      R_SpeedPwmCnt = 20;
    else if(i>49)     // > ±4.0Km 
      R_SpeedPwmCnt = 17;
    else if(i>39)     // > ±3.0Km
      R_SpeedPwmCnt = 13;
    else if(i>19)     // > ±2.0Km
      R_SpeedPwmCnt = 9; 
    else if(i>9)       // > ±1.0Km
      R_SpeedPwmCnt = 8;
    else if(i>2)       // > ±0.5Km
      R_SpeedPwmCnt = 3;
    else if(i>0)       // > ±0.1Km
      R_SpeedPwmCnt = 1;
    //====================
    //速度信號偵側
    if(SpeedMoveFlg==0)
    {
      R_SpeedErrTime++;
      if(R_SpeedErrTime>8)		// 8秒後無信號錯誤
      {
        R_SpeedErrTime=0;	
        R_SysMode=SysErrModeVal;
        R_ErrData=2;
      }
    }
    else
      R_SpeedErrTime=0;
    //====================	
  }
  else
  {
    R_SpeedErrTime=0;
    if(R_SpeedPwmCntSave>50)
    {
      MotoUpDownFlg=1;		//	馬達減速
      R_SpeedPwmCnt = 50;
    }
    else
      F_SpeedSwCotrol(0);	
  }
}
//=====================================
void F_SpeedSwCotrol(unsigned char Data)
{
  /*
    if(Data)	
      M_Sw_Ctrl_SetHigh;
    else
      M_Sw_Ctrl_SetLow;
  */  
  if(AcDcMotorFlg)
  {
    if(Data)	
      M_Sw_Ctrl_SetHigh;
    else
      M_Sw_Ctrl_SetLow;
  }
  else
  {
    if(Data)	
      M_Sw_Ctrl_SetLow;
    else
      M_Sw_Ctrl_SetHigh;
  }
  /*
#if O_A2121034	//	DC控制
  //======================
  if(Data)	
  BitSet(PC_ODR,BIT2);		//	SW
		else
  BitClr(PC_ODR,BIT2);		//	SW
  //======================	
#else		//	AC 控制
  //======================
  if(Data)	
  BitClr(PC_ODR,BIT2);		//	SW	
				else
  BitSet(PC_ODR,BIT2);		//	SW
  //======================		
#endif  
  */
}
//=====================================

