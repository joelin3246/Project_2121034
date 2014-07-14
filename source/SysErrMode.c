#include "connect.h"

void	F_SysErrMode(void)
{
  if(T20msFlg==1)
  {		
    T20msFlg=0;
    R_SpeedNum=0;
    IncStopFlg=1;	
  }
  //=================	
  if(ShowLcdTimeFlg==1)
  {
    ShowLcdTimeFlg=0;	
    F_AllLCDRam(0x00);
    F_SysErrMode_Lcd();
    F_Display();		
  }
  //=================
  if(T1sFlg==1)
  {
    T1sFlg=0;
    if(R_ErrData==0)
      F_SleepTime();
  }
}
//==========================================
//LED
//==========================================
void	F_SysErrMode_Lcd(void)
{
  F_ShowPowerLed();
  switch(R_ErrData)
  {
    case	0:
      F_ShowMatrixPicture(3,PidSafe);
      F_SpeedSwCotrol(1);			//	2012/10/16 Chandler因安全pin移除電源會有迴路，將電晶體訊號強制關閉
      break;
      //==========
      case	1:		//	Eeprom Err
        R_Seg[49]=0x5B;		//	E
        R_Seg[50]=0x24;		//	1
        break;
        //==========
        case	2:		//	Ls
          F_SpeedSwCotrol(0);			//	2012/10/16 當LS強制馬達停止
          R_Seg[49]=0x52;						//	L
          F_Show_8_FontLcd(50,5);		//	5
          break;
  }
}