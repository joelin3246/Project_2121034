#include "connect.h"
void	F_SysCountDownMode(void)
{
    if(T80msFlg==1)
    {
      T80msFlg=0;	
      F_AllLCDRam(0x00);
      F_SysCountDownMode_lcd();
      F_Display();		
    }
    //=================		
    if(T1sFlg==1)
    {
      T1sFlg=0;
      F_CountDown();
    }
}
//====================================================
//Lcd 
//====================================================
void F_SysCountDownMode_lcd(void)
{
    unsigned char i;
    F_ShowPowerLed();
    if(R_CountDownCnt==0)
    {
      for(i=0;i<5;i++)
      {
        F_ShowMatrixLcd(i+10,MatrixAsciiCode['G'-' '][i]);
        F_ShowMatrixLcd(i+16,MatrixAsciiCode['O'-' '][i]);
      }
    }
    else
    {
      for(i=0;i<5;i++)
        F_ShowMatrixLcd(i+13,MatrixAsciiCode[R_CountDownCnt+16][i]);
    }
}
//====================================================
//
//====================================================
void F_CountDown(void)
{
  if(R_CountDownCnt==0)
  {
    R_IncNum=R_IncBuf;
    switch(R_PorgMode)
    {
      case ManualVal:
        R_SysMode=ManualSportModeVal;
        break;
      //============		
      case Prog1Val:
      case Prog2Val:
      case Prog3Val:		
      case Prog4Val:		
      case Prog5Val:
        R_SysMode=ProgSportModeVal;
        break;
      //============		
      case	User1Val:
      case	User2Val:
      case	User3Val:
        R_SysMode=UserSportModeVal;
        break;
      //============
      case Hrc1Val:
      case Hrc2Val:
        R_SysMode=HrcSportModeVal;	
        break;
      //============
    }
    IncStopFlg=0;
    LongBzFlg=1;
    F_SpeedFirstInit();
    F_StringInit();
  }
  else
  {
    R_CountDownCnt--;		
    R_BzCnt=0x04;			
  }
}
//=================================
void F_CountDownModeInit(void)
{
    R_HrcSpdIncTime=0;
    R_SysMode=SysCountDownModeVal;
    R_CountDownCnt=3;
    F_ClearTimeBase();
}