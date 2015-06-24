#include "connect.h"

void	F_SysStartMode(void)
{
  if(T20msFlg==1)
  {
    T20msFlg=0;
    F_ReadKey();
    F_CheckGetKey();
    switch(R_Mode)
    {
      case 1:
        F_SysStartMode_Key1();	
        break;
      //======
      case 2:
        F_SysStartMode_Key2();	
        break;
      //======
      case 3:

        break;	
    }
  }
  //=================
  if(ShowLcdTimeFlg==1)
  {
    ShowLcdTimeFlg=0;
    
  }
  //=================		
  if(T1sFlg==1)
  {
    T1sFlg=0;
    F_BackLight(1);  
    F_AllLCDRam(0x00);
    F_SysStartMode_Lcd();
    F_Display();	
    F_SysStartTime();						
  }
}
//==================
void	F_SysStartMode_Key1(void)
{
  switch(KeyCode)
  {
    case EepromClear_KeyVal:
      KeyCode=0;
      EE_Write(0xFD,0xfe);
      F_Rest();	
      break;
    //==========
  }
}
//==================
void	F_SysStartMode_Key2(void)
{
  switch(KeyCode)
  {
    case EepromClear_KeyVal:
      KeyCode=0;
      EE_Write(0xFD,0xfe);
      F_Rest();	
      break;
    //==========
    case Eng1_KeyVal:
      KeyCode=0;
      R_Mode=0;
      R_SysMode=EngMode1Val;
      R_BzCnt=0x04;		
      break;
    //==========
    case Eng2_KeyVal:
      KeyCode=0;
      R_Mode=0;
      R_SysMode=EngMode2Val;
      R_BzCnt=0x04;		
      break;
    //==========
    case Eng3_KeyVal:
      KeyCode=0;
      R_Mode=0;
      R_SysMode=EngMode3Val;
      R_BzCnt=0x04;		
      break;
    //==========
    case Eng4_KeyVal:
      KeyCode=0;
      R_Mode=0;
      R_SysMode=EngMode4Val;
      R_BzCnt=0x04;		
      break;
    //==========
  }
}
//==================
void	F_SysStartMode_Lcd(void)
{
  switch(R_Mode)
  {
    case 0:	
    case 1:
      F_AllLCDRam(0xFF);	//開機畫面全顯
      //R_Seg[15]=0x80;		//	M
      //R_Seg[15]=0x40;		// Km
      //R_Seg[15]=0x20;		// 6 >
      //R_Seg[15]=0x10;		// 5 >
      //R_Seg[43]=0x01;			// 1 <
      //R_Seg[43]=0x02;			// 2 <
      //R_Seg[43]=0x04;			// 3 <
      //R_Seg[43]=0x08;			// 4 <
      break;
    //========
    case 2:
      F_ShowPowerLed();
      F_ShowVer();
      F_ShowTotalDis();
      F_ShowTotalTime();
      F_ShowWheelSize();
      F_ShowSpeed(R_SpeedMax);
      break;
    //========
    case 3:
     /* 
      R_Seg[27] |= 0x1F;		//	P
      R_Seg[26] |= 0x08;		//	-
      F_Show_8_FontLcd(25,0);
      F_ShowPowerLed();	
      F_ShowInc(R_IncNum);
      F_ShowSpeed(0);
      F_ShowTime();
      F_ShowDis();
      F_ShowCal();
      F_ShowPulse();
      F_ShowStringMove(midM01);
      */
      break;
  }
}
//============================
void F_SysStartTime(void)
{
    if(R_SysStartTime<200)	//限制數字超過255
      R_SysStartTime++;
    switch(R_SysStartTime)
    {
      case 0:					
        
        break;
      //============				
      case 1:						
      R_Mode=1;	
        break;
      //============				
      case 2:		
      R_Mode=2;	    
        break;
      //============		
      case 3:

        break;
      //============		
      case 4:
        R_PorgMode=ManualVal;
        F_ProgSetInit();
        break;
      //============	
      default:
      
        break;
    }
}