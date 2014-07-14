#include "connect.h"

void  F_HrcSportMode(void)
{
  if(T20msFlg==1)
  {			
    T20msFlg=0;	
    F_ReadKey();
    F_CheckGetKey();
    if(R_Mode==0)
      F_HrcSportMode_Key();
  }	
  //=================	
  if(ShowLcdTimeFlg==1)
  {
    ShowLcdTimeFlg=0;
    F_AllLCDRam(0x00);
    F_HrcSportMode_Lcd();
    F_Display();
  }
  //=================
  if(T1sFlg==1)
  {	
    T1sFlg=0;
    if(R_SportMode==SportNormalVal)
    {					
      F_TimeCount();
      F_HrcSpdIncCount();
      F_TotalTimeDisCount();
      F_Calorie();
      F_DisttanceComputing();
    }
    else
      F_SleepTime();
  }
}
//===================================================
//  HRC���{���b����U,�s�W��S������USER���߸���, 
//  �b30���,�C5��0.4KMPH,����̧C�t,
//  ��b�̧C�t�U�����1�����٬O�S�߸���J,�Φ۰ʶi�JIDLE MODE
//===================================================
void  F_HrcSpdIncCount(void)
{
  unsigned  char  ThrTemp,HeartTemp;
  if((R_W_Pluse!=0) || (R_Pluse!=0))
  {
    R_HrcSpdIncTime++;
    R_HrcNoPulse=0;
    if(R_HrcSpdIncTime>14)
    {
      R_HrcSpdIncTime=0;
      //==================================
      if(R_W_Pluse==0)	//	�L�u�u��
        HeartTemp=R_Pluse;
      else
        HeartTemp=R_W_Pluse;
      //==================================
      if(HrcSpdIncFlg==1)
      { //  Speed
        HrcSpdIncFlg=0;
      }
      else
      { //  Inc
        HrcSpdIncFlg=1;
        if(IncErrFlg==0)
        {
          //==============================
          if(HeartTemp>R_Thr)
          {
            ThrTemp=HeartTemp-R_Thr;
            if(ThrTemp>=25)					
              F_IncControlDown(2);      //	��ڤ߸��ȡ٥ؼФ߸���25��
            else  if(ThrTemp>=15)						
              F_IncControlDown(1);   	//	��ڤ߸��ȡ٥ؼФ߸���15��
            else  if(ThrTemp>=5)
              F_IncControlDown(1);      //	��ڤ߸��ȡ٥ؼФ߸���5��
          }
          else
          {  
            ThrTemp=R_Thr-HeartTemp;
            if(ThrTemp>=25) 
              F_IncControlUp(1);        //  �ؼФ߸���>=��ڤ߸���  25  �W�[1�q
            else  if(ThrTemp>=15)
              F_IncControlUp(1);        //  �ؼФ߸���>=��ڤ߸���  15  �W�[1�q
            else  if(ThrTemp>=5)
              F_IncControlUp(1);        //  �ؼФ߸���>=��ڤ߸���  5   �W�[1�q
          }
        }
        //===============================
      }
    }
  }
  else
  {  // �L�߸��T��
    R_HrcSpdIncTime=0;
    R_HrcNoPulse++;
    if(R_HrcNoPulse>29)   // 30 ���}�l��
    {
      R_HrcNoPulse=25;    // �C5���1
      F_IncControlDown(1);
      if(R_SpeedNum>4)
        R_SpeedNum=R_SpeedNum-4;
      if(R_SpeedNum<=R_SpeedMin)
      {
        R_SpeedNum=R_SpeedMin;
      }
    }
  }
}
//===========================================================
void  F_HrcSpeedShowUp(unsigned char  Speed)
{
  R_SpeedNum=R_SpeedNum+Speed;
  if(R_SpeedNum>R_SpeedMax)
    R_SpeedNum=R_SpeedMax;
}
//==========================
void  F_HrcSpeedShowDown(unsigned char  Speed)
{
  R_SpeedNum=R_SpeedNum-Speed;
  if(R_SpeedNum<R_SpeedMin)
    R_SpeedNum=R_SpeedMin;
}
//===========================
void  F_IncControlUp(unsigned char  inc)
{
  if(R_IncNum<R_IncMax)
    R_IncNum=R_IncNum+inc;
  else
    R_IncNum=R_IncMax;
}
//===========================
void  F_IncControlDown(unsigned char  inc)
{
  if(R_IncNum<=inc)
  {
    R_IncNum=IncDefVal;
  }
  else
  {
    if(R_IncNum>IncDefVal)
      R_IncNum=R_IncNum-inc;
    else
      R_IncNum=IncDefVal;
  }
}
//====================================================
//  Key
//====================================================
void  F_HrcSportMode_Key(void)
{
  if(KeyCode != 0)
  {
    if(R_LongKeyStopBz==0)	
      R_BzCnt=0x08;		//�L�ĭ�			
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
      F_HrcIncQuickKey(3);
      break;		
    //======================
    case	QuickInc_4_KeyVal:
      KeyCode=0;
      F_HrcIncQuickKey(5);
      break;
    //======================
    case	QuickInc_6_KeyVal:
      KeyCode=0;
      F_HrcIncQuickKey(7);
      break; 
    //======================
    case	QuickInc_8_KeyVal:
      KeyCode=0;
      F_HrcIncQuickKey(9);
      break;
    //======================
    case	QuickInc_10_KeyVal:
      KeyCode=0;
      F_HrcIncQuickKey(11);
      break;
    //======================
    case	QuickInc_12_KeyVal:
      KeyCode=0;
      F_HrcIncQuickKey(13);
      break;
    //=======================		
    case	Mode_KeyVal:
      KeyCode=0;
      if(R_SportMode != SportNormalVal)
      {
        F_ProgSetInit();
        R_BzCnt=0x04;		
      }	
      break;				
      //=======================	
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
              F_HrcSportModeIncUp();
              break;	
              //=============
              case	InclineDown_KeyVal:
              KeyCode=0;
              F_HrcSportModeIncDown();
		break;
  }	
}
//===================================================
void    F_HrcSportModeIncUp(void)
{
    if(IncErrFlg==0)
    {
      if(R_IncNum<R_IncMax)
      {
        R_IncNum++;
        if(R_LongKeyStopBz==0)	
          R_BzCnt=0x04;	
      }
      else
        R_IncNum=R_IncMax;
    }
}
//===================================================
void    F_HrcSportModeIncDown(void)
{
    if(IncErrFlg==0)
    {	
      if(R_IncNum>IncDefVal)
      {
        R_IncNum--;
        if(R_LongKeyStopBz==0)	
          R_BzCnt=0x04;	
      }
      else
        R_IncNum=IncDefVal;
    } 
}
//===================================================
//
//===================================================
void    F_HrcIncQuickKey(unsigned char Data)
{
  if(IncErrFlg==0) {
    R_IncNum = Data;
    R_BzCnt=0x04;	
  }
}
//====================================================
//  LCD
//====================================================
void  F_HrcSportMode_Lcd(void)
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
      if((R_W_Pluse!=0) || (R_Pluse!=0))
      {
        if(R_PorgMode==Hrc1Val)
          F_ShowHrc1HeartFlash();
        else
          F_ShowHrc2HeartFlash();
      }
      else
        F_ShowNoHeart();
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

