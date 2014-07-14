#include "connect.h"

void  F_SysSleepMode(void)
{
  if(T20msFlg==1)
  {		
    T20msFlg=0;	
    F_ReadKey();
    F_CheckGetKey();
    F_SysSleepMode_Key();
  }	
  //=================	
  if(ShowLcdTimeFlg==1)
  {
    ShowLcdTimeFlg=0;
    R_SpeedNum=0;
    IncStopFlg=1;
    R_LedSeg=0;
    //F_AllLCDRam(0x00);
    //F_ShowPowerLed();
    //F_Display();
  }
  //=================
  if(T1sFlg==1)
  {		
    T1sFlg=0;
  }
}
//==============================================================
//  Key
//==============================================================
void  F_SysSleepMode_Key(void)
{
  if(KeyCode!=0)
  {
    KeyCode=0;
    F_Rest();
  }
}
//==========================================
//  LCD
//==========================================
void  F_SysSleepMode_Lcd(void)
{
  
  
}
//=======================================
// 設定模式下 5分鐘進入睡眠
//=======================================
void  F_SleepTime(void)
{
  R_SleepTime++;
  if(R_SleepTime>300)		//	300  
  {
    R_SleepTime=0;	
    F_Sleep_Init();
  }
}
