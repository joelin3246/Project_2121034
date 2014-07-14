#include "connect.h"
void	F_ManualSportMode(void)
{
  if(T20msFlg==1)
  {			
    T20msFlg=0;
    F_ReadKey();
    F_CheckGetKey();
    F_ManualSportMode_key();
  }	
  //=================
  if(ShowLcdTimeFlg==1)
  {
    ShowLcdTimeFlg=0;	
    F_AllLCDRam(0x00);
    F_ManualSportMode_lcd();
    F_Display();
  }
  //=================
  if(T1sFlg==1)
  {
    T1sFlg=0;
    if(R_SportMode==SportNormalVal)
    {
      F_TimeCount();
      F_Calorie();
      F_DisttanceComputing();
      F_TotalTimeDisCount();
    }
    else
      F_SleepTime();				
  }
}
//===================================================
//	Key
//===================================================
void	F_ManualSportMode_key(void)
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
    case	QuickSpd_1_KeyVal:
      KeyCode=0;
      F_MenualSpdQuickKey(10);
      break;		
    //======================
    case	QuickSpd_4_KeyVal:
      KeyCode=0;
      F_MenualSpdQuickKey(40);
      break;
    //======================
    case	QuickSpd_7_KeyVal:
      KeyCode=0;
      F_MenualSpdQuickKey(70);
      break;
    //======================
    case	QuickSpd_10_KeyVal:
      KeyCode=0;
      F_MenualSpdQuickKey(100);
      break; 
    //======================
    case	QuickSpd_13_KeyVal:
      KeyCode=0;
      F_MenualSpdQuickKey(130);
      break;
    //======================
    case	QuickSpd_16_KeyVal:
      KeyCode=0;
      F_MenualSpdQuickKey(160);
      break;
    //======================
    case	QuickInc_2_KeyVal:
      KeyCode=0;
      F_IncQuickKey(3);
      break;		
    //======================
    case	QuickInc_4_KeyVal:
      KeyCode=0;
      F_IncQuickKey(5);
      break;
    //======================
    case	QuickInc_6_KeyVal:
      KeyCode=0;
      F_IncQuickKey(7);
      break; 
    //======================
    case	QuickInc_8_KeyVal:
      KeyCode=0;
      F_IncQuickKey(9);
      break;
    //======================
    case	QuickInc_10_KeyVal:
      KeyCode=0;
      F_IncQuickKey(11);
      break;
    //======================
    case	QuickInc_12_KeyVal:
      KeyCode=0;
      F_IncQuickKey(13);
      break;
    //======================
    case	Mode_KeyVal:
      KeyCode=0;
      if(R_SportMode != SportNormalVal)
      {
        F_ProgSetInit();
        R_BzCnt=0x04;		
      }	
      break;		
      //======================
      case	start_stop_KeyVal:
	KeyCode=0;
	F_SportStartSet();
        break;
	//=============
	case	SpeedUp_KeyVal:
          KeyCode=0;	
          F_SpdSetControlUp();
          break;	
          //=============
          case	SpeedDown_KeyVal:
            KeyCode=0;
            F_SpdSetControlDown();
            break;
            //=============
            case	InclineUp_KeyVal:
              KeyCode=0;
              F_IncSetControlUp();
              break;
              //=============
              case	InclineDown_KeyVal:
                KeyCode=0;
                F_IncSetControlDown();
		break;			
  }
  
}
//===================================================
//	LCD
//===================================================
void	F_ManualSportMode_lcd(void)
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
  switch(R_SportMode)
  {
    case	SportNormalVal:
      F_ShowTrackLed();
      break;
      //============
      case	SportTimeEndVal:
        F_ShowStringMove(midM09);		//	END OF WORKOUT
        break;
        //============
        case	SportDisEndVal:
          F_ShowStringMove(midM09);		//	END OF WORKOUT
          break;
          //============
          case	SportCalEndVal:
            F_ShowStringMove(midM09);		//	END OF WORKOUT
            break;
  }
}
//=================================
void    F_MenualSpdQuickKey(unsigned char Data)
{
  if((Data <= R_SpeedMax) || (Data >= R_SpeedMin)) {
    R_SpeedNum = Data;
  }
  R_BzCnt=0x04;	
}
//=================================
void	F_SpdSetControlUp(void)
{
  if(R_SportMode==SportNormalVal)
  {
    if(R_SpeedNum<R_SpeedMax)
    {
      R_SpeedNum++;
      if(R_LongKeyStopBz==0)	
        R_BzCnt=0x04;	
    }
    else
      R_SpeedNum=R_SpeedMax;
  }
}
//=================================
void	F_SpdSetControlDown(void)
{
  if(R_SportMode==SportNormalVal)
  {
    if(R_SpeedNum>R_SpeedMin)
    {
      R_SpeedNum--;		
      if(R_LongKeyStopBz==0)	
        R_BzCnt=0x04;
    }
    else
      R_SpeedNum=R_SpeedMin;
  }
}
//=======================================
void	F_SportStartSet(void)
{
  if(R_SportMode==SportNormalVal)
  {
    F_PassModeInit();
    R_BzCnt=0x04;
  }
  else
  {
    if(SpeedMoveFlg==0)
    {			
      switch(R_SportMode)
      {
        case	SportTimeEndVal:
          R_SportMode=SportNormalVal;
          TimeStatusFlg=0;
          R_ProgTimeBase=60;
          R_ProgTime=0;
          F_CountDownModeInit();
          break;
          //==============
          case	SportDisEndVal:
            R_SportMode=SportNormalVal;
            DisStatusFlg=0;
            F_CountDownModeInit();
            break;
            //==============
            case	SportCalEndVal:
              R_SportMode=SportNormalVal;
              CalStatusFlg=0;
              F_CountDownModeInit();
              break;
              //==============
      }
      R_BzCnt=0x04;				
    }
  }
}


