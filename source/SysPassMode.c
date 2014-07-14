#include "connect.h"
void	F_SysSportPassMode(void)
{
  if(T20msFlg==1)
  {			
    T20msFlg=0;	
    F_ReadKey();
    F_CheckGetKey();
    F_SysSportPassMode_Key();
  }	
  //=================	
  if(T80msFlg==1)
  {
    T80msFlg=0;
    F_AllLCDRam(0x00);
    F_SysSportPassMode_lcd();
    F_Display();
  }
  //=================
  if(T1sFlg==1)
  {		
    T1sFlg=0;	
    F_SleepTime();
  }	
}

//====================================================
//	Key
//====================================================
void	F_SysSportPassMode_Key(void)
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
    //==========
    case	InclineUp_KeyVal:
      KeyCode=0;
      F_IncSetControlUp();		
      break;	
      //==========
      case	InclineDown_KeyVal:
        KeyCode=0;
        F_IncSetControlDown();
        break;			
        //==========
        case	start_stop_KeyVal:
          KeyCode=0;
          if(SpeedMoveFlg==0)
          {
            F_CountDownModeInit();
            R_BzCnt=0x04;
          }
          break;
          //==========
          case	Mode_KeyVal:
            KeyCode=0;
            F_ProgSetInit();
            R_BzCnt=0x04;
            break;
  }
}
//====================================================
//	Lcd
//====================================================
void	F_SysSportPassMode_lcd(void)
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
  F_ShowStringMove(midM02);		//	PAUSE. PRESS START TO RESUME
}
//==============================
void	F_PassModeInit(void)
{
  R_SysMode=SysSportPassModeVal;
  R_SpeedBuf=R_SpeedNum;
  R_IncBuf=R_IncNum;
  R_SpeedNum=0;
  IncStopFlg=1;
  F_SaveTotalTimeDis();
  F_StringInit();
  F_ClearTimeBase();
}