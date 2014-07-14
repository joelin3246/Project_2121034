#include "connect.h"

void	F_SysSportModeEnd(void)
{
  if(T20msFlg==1)
  {		
    T20msFlg=0;	
    F_ReadKey();
    F_CheckGetKey();
    F_SysSportModeEnd_Key();
  }	
  //=================	
  if(T80msFlg==1)
  {
    T80msFlg=0;
    F_AllLCDRam(0x00);
    F_SysSportModeEnd_Lcd();
    F_Display();		
  }
  //=================
  if(T1sFlg==1)
  {		
    T1sFlg=0;	
    F_SleepTime();
  }	
}
//==========================================
//	Key
//==========================================
void	F_SysSportModeEnd_Key(void)
{
  if(KeyCode != 0)
  {
    if(R_LongKeyStopBz==0)	
      R_BzCnt=0x08;		//µL®Ä­µ			
  }		
  switch(KeyCode)
  {
  default :	
    KeyCode=0;
    
    break;
    //======================
    case	Mode_KeyVal:
      KeyCode=0;
      F_ProgSetInit();
      R_BzCnt=0x04;
      break;
  }
}
//==========================================
//	LCD
//==========================================
void	F_SysSportModeEnd_Lcd(void)
{
  F_ShowPowerLed();	
  F_ShowLube();		
  F_ShowPulse();
  F_ShowLaps();
  F_ShowDis();
  F_ShowCal();
  F_ShowTime();		
  F_ShowSpeed(R_SpeedNum);		
  F_ShowInc(R_IncNum);
  F_ShowStringMove(midM09);		//	END OF WORKOUT
  
}
//=============================
void	F_SportModeEndInit(void)
{
  R_SysMode=SysSportModeEndVal;
  R_SpeedNum=0;
  R_IncNum=IncDefVal;
  LongBzFlg=1;
  F_StringInit();
}

