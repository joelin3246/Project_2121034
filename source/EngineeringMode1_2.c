#include "connect.h"
//==========================================================
//	工程模式 1
//==========================================================
void	F_EngMode1(void)
{
  if(T20msFlg==1)
  {			
    T20msFlg=0;
    F_ReadKey();
    F_CheckGetKey();
    F_EngMode1_Key();
  }
  //=================	
  if(ShowLcdTimeFlg==1)
  {
    ShowLcdTimeFlg=0;
    F_AllLCDRam(0x00);
    F_EngMode1_Lcd();
    F_Display();
  }
  //=================		
  if(T1sFlg==1)
  {
    T1sFlg=0;
  }
}
//============================================
//
//============================================
void	F_EngMode1_Key(void)
{
  switch(KeyCode)
  {
    case	Enter_KeyVal:
      case	start_stop_KeyVal:
        F_Eng1EntertSet();
        if(KeyCode==start_stop_KeyVal)
          F_Rest();
	KeyCode=0;
	R_BzCnt=0x04;		
        break;
	//=================================
	case	SpeedUp_KeyVal:			
          KeyCode=0;	
          F_Eng1SpeedUpSet();
          break;
          //=================================
          case	SpeedDown_KeyVal:			
            KeyCode=0;	
            F_Eng1SpeedDownSet();
            break;
  }
}
//==============================================================
void	F_Eng1EntertSet(void)
{
  switch(R_Mode)
  {
    case	0:			
      R_Mode=1;
      if(EE_Read(EE_Unit)!=ChangeUnitFlg) 
      { //  切換公英制 需重新清除相關 eeprom
        F_EepromClear_2();
        EE_Write(EE_SaveUserInit,1);
      }
      break;
      //=============	
      case	1:	
        R_Mode=2;		
        F_Write2Byte(EE_WheelSize_L,R_WheelSize);
        break;
        //=============	
        case	2:			
          R_Mode=3;
          if(ChangeUnitFlg)
            EE_Write(EE_SpeedMinMile,R_SpeedMin); 
          else
            EE_Write(EE_SpeedMinKm,R_SpeedMin); 
          break;	
          //=============	
          case	3:			
            R_Mode=4;
            if(ChangeUnitFlg)
              EE_Write(EE_SpeedMaxMile,R_SpeedMax);  
            else
              EE_Write(EE_SpeedMaxKm,R_SpeedMax);
            break;
            //=============	
            case	4:		
              R_Mode=0;
              EE_Write(EE_IncMax,R_IncMax);
              break;
              //=============	
              case	5:		
                R_Mode=0;
                EE_Write(EE_AcDcMotor,ShowAcDcMotorFlg);
                break;
  }
}
//==============================================================
void	F_Eng1SpeedUpSet(void)
{
  
  switch(R_Mode)
  {
    case	0:			
      if(ChangeUnitFlg==1)
        ChangeUnitFlg=0;
      else
        ChangeUnitFlg=1;
      R_BzCnt=0x04;	
      F_ShowFlashInt();	
      break;
      //=============	
      case	1:			
        if(R_WheelSize<350)
        {
          R_WheelSize++;
          F_ShowFlashInt();
          if(R_LongKeyStopBz==0)	//長按時蜂鳴器不叫
            R_BzCnt=0x04;
        }
        else
          R_WheelSize=350;
        break;
        //=============	
        case	2:			
          if(ChangeUnitFlg)
          {
            if(R_SpeedMin<10)
            {
              R_SpeedMin++;
              F_ShowFlashInt();
              if(R_LongKeyStopBz==0)	//長按時蜂鳴器不叫
                R_BzCnt=0x04;
            }
            else
              R_SpeedMin=10;
          }
          else
          {
            if(R_SpeedMin<20)
            {
              R_SpeedMin++;
              F_ShowFlashInt();
              if(R_LongKeyStopBz==0)	//長按時蜂鳴器不叫
                R_BzCnt=0x04;
            }
            else
              R_SpeedMin=20;
          }
          break;	
          //=============	
          case	3:	
            if(ChangeUnitFlg)
            {
              if(R_SpeedMax<120)
              {
                R_SpeedMax++;
                F_ShowFlashInt();
                if(R_LongKeyStopBz==0)	//長按時蜂鳴器不叫
                  R_BzCnt=0x04;
              }
              else
                R_SpeedMax=120;
            }
            else
            {
              if(R_SpeedMax<200)
              {
                R_SpeedMax++;
                F_ShowFlashInt();
                if(R_LongKeyStopBz==0)	//長按時蜂鳴器不叫
                  R_BzCnt=0x04;
              }
              else
                R_SpeedMax=200;
            }
            break;	
            //=============	
            case	4:
              if(R_IncMax<15+1)
              {
                R_IncMax++;
                F_ShowFlashInt();
                if(R_LongKeyStopBz==0)	//長按時蜂鳴器不叫
                  R_BzCnt=0x04;
              }
              else
                R_IncMax=15+1;
              break;
              //============
              case	5:
                if(ShowAcDcMotorFlg)
                  ShowAcDcMotorFlg=0;
                else
                  ShowAcDcMotorFlg=1;
                R_BzCnt=0x04;		
                break;
  }
}
//==============================================================
void	F_Eng1SpeedDownSet(void)
{
  switch(R_Mode)
  {
    case	0:		
      F_ShowFlashInt();
      if(ChangeUnitFlg==1)
        ChangeUnitFlg=0;
      else
        ChangeUnitFlg=1;
      if(R_LongKeyStopBz==0)
        R_BzCnt=0x04;	
      break;
      //=============	
      case	1:			
        if(R_WheelSize>150)
        {
          R_WheelSize--;	
          F_ShowFlashInt();
          if(R_LongKeyStopBz==0)
            R_BzCnt=0x04;
        }
        else
          R_WheelSize=150;
        break;
        //=============	
        case	2:
          if(ChangeUnitFlg)
          {
            if(R_SpeedMin>3)
            {
              R_SpeedMin--;	
              F_ShowFlashInt();
              if(R_LongKeyStopBz==0)
                R_BzCnt=0x04;
            }
            else
              R_SpeedMin=3;
          }
          else
          {
            if(R_SpeedMin>5)
            {
              R_SpeedMin--;	
              F_ShowFlashInt();
              if(R_LongKeyStopBz==0)
                R_BzCnt=0x04;
            }
            else
              R_SpeedMin=5;
          }
          break;	
          //=============	
          case	3:			
            if(ChangeUnitFlg)
            {
              if(R_SpeedMax>100)
              {
                R_SpeedMax--;
                F_ShowFlashInt();
                if(R_LongKeyStopBz==0)
                  R_BzCnt=0x04;
              }
              else
                R_SpeedMax=100;
            }
            else
            {
              if(R_SpeedMax>160)
              {
                R_SpeedMax--;	
                F_ShowFlashInt();
                if(R_LongKeyStopBz==0)
                  R_BzCnt=0x04;
              }
              else
                R_SpeedMax=160;
            }
            break;
            //=============	
            case	4:	
              if(R_IncMax>10+1)
              {
                R_IncMax--;
                F_ShowFlashInt();
                if(R_LongKeyStopBz==0)
                  R_BzCnt=0x04;
              }
              else
                R_IncMax=10+1;
              break;
              //===========
              case	5:
                if(ShowAcDcMotorFlg)
                  ShowAcDcMotorFlg=0;
                else
                  ShowAcDcMotorFlg=1;
                R_BzCnt=0x04;	
                break;
  }
}
//===========================================
//
//
//===========================================
void	F_EngMode1_Lcd(void)
{
  F_ShowMatrixPicture(6,PidSet);	
  switch(R_Mode)
  {
    case	0:
      if(SetModeFlashFlg)
      {
        if(ChangeUnitFlg==1)
          R_Seg[15]=0x80;		// M
        else
          R_Seg[15]=0x40;		// Km
      }
      break;
      //=================
      case	1:	
        if(SetModeFlashFlg)
          F_ShowWheelSize();
        break;
        //=================	
        case	2:
          if(SetModeFlashFlg)
            F_ShowSpeed(R_SpeedMin);
          break;
          //=================	
          case	3:
            if(SetModeFlashFlg)
              F_ShowSpeed(R_SpeedMax);
            break;
            //=================	
            case	4:
              if(SetModeFlashFlg)
                F_Show_8_Lcd(24,23,22,R_IncMax-1);
              break;
              //=================	
              case	5:	
		if(ShowAcDcMotorFlg)
		{	//	DC
                  F_Show_8_Lcd(blankVal,48,49,77);
                  ShowHiByeFlg=1;
                  F_Show_8_Lcd(blankVal,50,51,00);
                  ShowHiByeFlg=0;
		}
                else
                {	//	AC
                  F_Show_8_Lcd(blankVal,48,49,77);
                  ShowHiByeFlg=1;
                  F_Show_8_Lcd(blankVal,50,51,30);
                  ShowHiByeFlg=0;
                }
                break;
		//=================			
  }
}
//==========================================================
//	工程模式 2
//==========================================================
void	F_EngMode2(void)
{
  if(T20msFlg==1)
  {			
    T20msFlg=0;
    F_ReadKey();
    F_CheckGetKey();
    F_EngMode2_Key();
  }
  //=================	
  if(ShowLcdTimeFlg==1)
  {
    ShowLcdTimeFlg=0;
    F_AllLCDRam(0x00);
    F_EngMode2_Lcd();
    F_Display();
  }
  //=================		
  if(T1sFlg==1)
  {
    T1sFlg=0;
    
    
  }
}
//============================================
//
//============================================
void	F_EngMode2_Key(void)
{
  switch(KeyCode)
  {
    //=========================================
  case  Enter_KeyVal:
    KeyCode=0;
    if(R_ClearTotal_TimeDis==4)
    {
      R_ClearTotal_TimeDis=0; 
      F_EepromClear_3();    //  總里程 總時間 清除
    }
    else
      R_ClearTotal_TimeDis=0;   
    R_BzCnt=0x04;
    break;    
    //=========================================
  case  SpeedUp_KeyVal:
    KeyCode=0;
    if(R_ClearTotal_TimeDis==0)
      R_ClearTotal_TimeDis=1;	 
    else  if(R_ClearTotal_TimeDis==2)
      R_ClearTotal_TimeDis=3;
    else
      R_ClearTotal_TimeDis=0;  
    if(R_LongKeyStopBz==0)	
      R_BzCnt=0x04;
    break;
    //=========================================
  case  SpeedDown_KeyVal:
    KeyCode=0;
    if(R_ClearTotal_TimeDis==1)
      R_ClearTotal_TimeDis=2;	 
    else  if(R_ClearTotal_TimeDis==3)
      R_ClearTotal_TimeDis=4;
    else
      R_ClearTotal_TimeDis=0; 
    if(R_LongKeyStopBz==0)	
      R_BzCnt=0x04;
    break;
    //=========================================
  case  start_stop_KeyVal:
    KeyCode=0;
    F_Rest();	
    break;
  }
}
//===========================================
//
//
//===========================================
void	F_EngMode2_Lcd(void)
{
  F_ShowTotalTime();
  F_ShowTotalDis();
}



