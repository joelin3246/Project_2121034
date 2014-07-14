#include "connect.h"

void  F_UserSportMode(void)
{
  if(T20msFlg==1)
  {			
    T20msFlg=0;	
    F_ReadKey();
    F_CheckGetKey();
    F_UserSportMode_Key();
  }	
  //=================
  if(ShowLcdTimeFlg==1)
  {
    ShowLcdTimeFlg=0;
    F_AllLCDRam(0x00);
    F_UserSportMode_Lcd();
    F_Display();
  }
  //=================
  if(T1sFlg==1)
  {
    T1sFlg=0;
    if(R_SportMode==SportNormalVal)
    {
      F_ProgTimeCount();
      F_TimeCount();
      F_Calorie();
      F_DisttanceComputing();
      F_TotalTimeDisCount();
    }
    else
      F_SleepTime();
  }
}
//====================================================
//  Key
//====================================================
void  F_UserSportMode_Key(void)
{
  if(KeyCode != 0)
  {
    if(R_LongKeyStopBz==0)	
      R_BzCnt=0x08;		//無效音			
  }		
  switch(KeyCode)
  {
  default :	
    KeyCode=0;
    
    break;
    //======================
    case	QuickSpd_1_KeyVal:
      KeyCode=0;
      F_ProgSportSpdQuickKey(10);
      break;		
    //======================
    case	QuickSpd_4_KeyVal:
      KeyCode=0;
      F_ProgSportSpdQuickKey(40);
      break;
    //======================
    case	QuickSpd_7_KeyVal:
      KeyCode=0;
      F_ProgSportSpdQuickKey(70);
      break;
    //======================
    case	QuickSpd_10_KeyVal:
      KeyCode=0;
      F_ProgSportSpdQuickKey(100);
      break; 
    //======================
    case	QuickSpd_13_KeyVal:
      KeyCode=0;
      F_ProgSportSpdQuickKey(130);
      break;
    //======================
    case	QuickSpd_16_KeyVal:
      KeyCode=0;
      F_ProgSportSpdQuickKey(160);
      break;
    //======================
    case	QuickInc_2_KeyVal:
      KeyCode=0;
      F_ProgSportIncQuickKey(3);
      break;		
    //======================
    case	QuickInc_4_KeyVal:
      KeyCode=0;
      F_ProgSportIncQuickKey(5);
      break;
    //======================
    case	QuickInc_6_KeyVal:
      KeyCode=0;
      F_ProgSportIncQuickKey(7);
      break; 
    //======================
    case	QuickInc_8_KeyVal:
      KeyCode=0;
      F_ProgSportIncQuickKey(9);
      break;
    //======================
    case	QuickInc_10_KeyVal:
      KeyCode=0;
      F_ProgSportIncQuickKey(11);
      break;
    //======================
    case	QuickInc_12_KeyVal:
      KeyCode=0;
      F_ProgSportIncQuickKey(13);
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
      case	Set_KeyVal:
	KeyCode=0;
        if(R_SportMode==SportNormalVal)
        {
          if(R_CholeIncSpdMode==0)
          {
            R_Mode++;
            if(R_Mode>2)
              R_Mode=0;
          }
          else
          {
            R_Mode++;
            if(R_Mode>1)
              R_Mode=0;
          }
          R_BzCnt=0x04;
        }
        break;
	//=============				
	case	start_stop_KeyVal:
          KeyCode=0;
          F_SportStartSet();
          break;
          //=============
          case	SpeedUp_KeyVal:
            KeyCode=0;
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
              F_ChangeShowSpeed();			
              F_PorgWriteSpeed();
            }
            break;	
            //=============
            case	SpeedDown_KeyVal:
              KeyCode=0;
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
                F_ChangeShowSpeed();			
                F_PorgWriteSpeed();
              }
              break;
              //=============
              case	InclineUp_KeyVal:
                KeyCode=0;
                F_ProgSportModeIncUp();
                F_ChangeShowInc();
		break;	
                //=============
                case	InclineDown_KeyVal:
                  KeyCode=0;
                  F_ProgSportModeIncDown();
                  F_ChangeShowInc();
                  break;			
  }
}
//====================================================
//  LCD
//====================================================
void  F_UserSportMode_Lcd(void)
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
  //=======================================
  switch(R_SportMode)
  {
    case	SportNormalVal:
      switch(R_CholeIncSpdMode)
      {
        case	0:		//	速度 揚升 Prog
          switch(R_Mode)
          {
            case	0:
              R_LedSegBuf |= 0x02;		//	Speed Led
              ChangeSpdIncProgFlg=0;	//	速度
              F_ShowSpeedIncProg();
              if(SetModeFlashFlg==0)
                F_ShowProfileFlash();			
              break;
              //==========	
              case	1:
                R_LedSegBuf |= 0x01;		//	Inc	Led	
                ChangeSpdIncProgFlg=1;	//	揚升
                F_ShowSpeedIncProg();
                if(SetModeFlashFlg==0)
                  F_ShowProfileFlash();
                break;
                //==========	
                case	2:	
                  F_ShowTrackLed();	
                  break;
                  //==========		
          }
          break;
          //=================================
          case	1:		//	速度 Prog
            switch(R_Mode)
            {
              case	0:
                R_LedSegBuf |= 0x02;		//	Speed Led
                ChangeSpdIncProgFlg=0;	//	速度
                F_ShowSpeedIncProg();
                if(SetModeFlashFlg==0)
                  F_ShowProfileFlash();	
                break;
                //==========
                case	1:	
                  //R_LedSegBuf |= 0x01;
                  F_ShowTrackLed();	
                  break;		 
            }
            break;
            //=================================
            case	2:		//	揚升 Prog
              switch(R_Mode)
              {
                case	0:
                  F_ShowTrackLed();	
                  break;
                  //==========
                  case	1:	
                    R_LedSegBuf |= 0x01;		//	Inc	Led	
                    ChangeSpdIncProgFlg=1;	//	揚升
                    F_ShowSpeedIncProg();
                    if(SetModeFlashFlg==0)
                      F_ShowProfileFlash();	
                    break;		 
              }
              break;
      }
      break;
      //============================
      case	SportTimeEndVal:
        F_ShowStringMove(midM09);		//	END OF WORKOUT
        break;
        //============================
        case	SportDisEndVal:
          F_ShowStringMove(midM09);		//	END OF WORKOUT
          break;
          //============================
          case	SportCalEndVal:
            F_ShowStringMove(midM09);		//	END OF WORKOUT
            break;
  }
}