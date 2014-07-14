#include "connect.h"
/*
const	unsigned char	T_WarkUpSpeedTabe_Km[]={10,15,20};
const	unsigned char	T_WarkUpSpeedTabe_Mile[]={5,10,15};

const	unsigned char	T_CoolDownSpeedTabe_Km[]= {20,15,10};
const	unsigned char	T_CoolDownSpeedTabe_Mile[]={15,10,5};
*/
const	unsigned char	T_WarkUpSpeedTabe[]={11,20,20};
const	unsigned char	T_CoolDownSpeedTabe[]= {25,20,11};
/*
const unsigned char T_ProgSpeed[5][30]={
10, 30, 40, 60, 80,100, 80, 60, 40, 30, 10, 30, 40, 60, 80,100, 80, 60, 40, 20, 10, 30, 40, 60, 80,100, 80, 60, 30, 10,
20, 40, 60, 80, 60, 60, 40, 40, 20, 20, 20, 40, 60, 80,100, 80, 40, 40, 20, 20, 20, 40, 60, 80, 60, 60, 40, 40, 20, 20,
30, 40, 60, 80,100, 80, 60, 40, 20, 20, 20, 40, 60, 80,100,	80, 60, 40, 20, 20, 20, 40, 60, 80,100, 80, 60, 40, 20, 20,
40, 20, 60, 60, 80,100, 60, 60, 20, 20, 20, 20, 60, 60, 80,100, 60, 60, 20, 20, 20, 20, 60, 60, 80,100, 60, 60, 20, 20,
50,	50,	50,100,100,100,	50,	50,	50,100,100,100,	50,	50,	50,100,100,100,	50,	50,	50,100,100,100,	50,	50,	50,100,100,100
};
*/

const unsigned char T_ProgSpeed[5][30]={
  45,	45,	45,100, 45, 45, 45,100, 45,	45,	45,100, 45,	45,	45,100, 45,	45,	45,100, 45,	45,	45,100, 45,	45,	45,100, 45,	45,
  25,	35,	45,	60, 78, 90,100,100,100,100,100,100,100,100,100,100,	87,	75,	63,	50,100,100,100,100,	90,	78,	60,	45,	35,	25,
  25,	35,	45,	60, 75, 87,100,	87,	75,	60,	45,	35,	35,	35,	35,	35,	35,	35,	35,	45,	60,	75,	87,100,	87,	75,	60,	45,	35,	25,
  35,	60,	60,	60, 45, 45,	45,	70,	70,	70,	55,	55,	55,	85,	85,	60,	60,	60,	87,100,100,	60,	60,	60,	75,	75,	75,	50,	45,	35,
  30,	35,	45,	50, 55, 60,	65,	70,	75,	80,	80,	85,	90, 90,100,90,	90,	85,	80,	80,	75,	70,	65,	60,	55,	50,	45,	40,	35,	30
};

//=====================================
const unsigned char T_ProgInc[][30]={
  1,	1,	3,	3,	5,	5,	7,	7,	9,	9,	11,	11,	13,	13,	15,	15,	15,	15,	15,	10,	10,	10,	10,	5,	5,	5,	5,	0,	0,	0,
  0,	3,	3,	3,	3,	6,	6,	6,	15,	15,	15,	15,	6,	6,	6,	6,	6,	6,	0,	0,	0,	0,	8,	8,	8,	6,	4,	2,	0,	0,
  15,	15,	15,	15,	15,	12,	12,	12,	12,	12,	9,	9,	9,	9,	9,	6,	6,	6,	6,	6,	3,	3,	3,	3,	3,	1,	1,	1,	1,	1,
  0,	1,	2,	6,	10,	15,	13,	10,	8,	6,	4,	4,	6,	8,	12,	12,	8,	4,	1,	0,	5,	5,	7,	9,	13,	13,	9,	5,	1,	0,
  0,	1,	3,	5,	9,	2,	5,	11,	3,	5,	13,	2,	4,	15,	2,	4,	8,	4,	1,	0,	12,	2,	4,	15,	3,	5,	9,	5,	1,	0
};

void  F_ProgSportMode(void)
{
  if(T20msFlg==1)
  {			
    T20msFlg=0;	
    F_ReadKey();
    F_CheckGetKey();
    F_ProgSportMode_Key();
  }
  //=================	
  if(ShowLcdTimeFlg==1)
  {
    ShowLcdTimeFlg=0;
    F_AllLCDRam(0x00);
    F_ProgSportMode_Lcd();
    F_Display();
  }
  //=================
  if(T1sFlg==1)
  {		
    T1sFlg=0;
    if(R_WarkUpCoolDownMode==SportVal)
    {
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
    else
    {
      F_WarkUpTime();	
      F_TotalTimeDisCount();							
    }
  }
}
//===================================================
//
//===================================================
void	F_ProgTimeCount(void)
{
  if(R_ProgTime>=R_ProgTimeBase-3)     //換段前1秒，警示聲
  {
    if(R_ProgramIndex!=29)	//	最後1段不響
      R_BzCnt=0x04;
  }
  R_ProgTime++;
  if(R_ProgTime>=R_ProgTimeBase)
  {
    R_ProgTime=0;
    R_ProgramIndex++;
    if(R_ProgramIndex>=30)
    {	
      R_ProgramIndex=0;	
      F_ReadProgData();
    }
    else
      F_ReadProgData();
  }
}
//=============================
void	F_ReadProgData(void)
{
  switch(R_CholeIncSpdMode)
  {
    case	0:		//	Speed Inc混合
      R_SpeedNum=R_SaveSpeedProg[R_ProgramIndex];	
      F_ChangeGraphSpeed(R_ProgramIndex,R_SpeedNum);
      R_IncNum=R_SaveIncProg[R_ProgramIndex];
      F_ChangeGraphInc(R_ProgramIndex,R_IncNum);
      break;
      //==============
      case	1:	//	Speed
        R_SpeedNum=R_SaveSpeedProg[R_ProgramIndex];	
        F_ChangeGraphSpeed(R_ProgramIndex,R_SpeedNum);		
        break;
        //==============
        case	2:		//	Inc
          R_IncNum=R_SaveIncProg[R_ProgramIndex];
          F_ChangeGraphInc(R_ProgramIndex,R_IncNum);
          break;
  }
}
//=============================
void  F_WarkUpTime(void)
{
  if(R_TimeL==0)
  {
    R_TimeH--;
    R_TimeL=59;
  }
  else
  {
    R_TimeL--;
    if((R_TimeH==0) && (R_TimeL==0))
    { //時間倒數結束 
      if(R_WarkUpCoolDownMode==WarkUpVal)
        F_ProgWarkUpEnd();
      else
        F_ProgCoolDownEnd();
    }
    else
    {  
      if(R_TimeL<3)
        R_BzCnt=0x04;
      if(R_TimeL==0)
        F_ReadWarkUpProg();
    }
  }
}
//=======================
void  F_ProgWarkUpEnd(void)
{
  unsigned	char	i,SpeedTemp,IncTemp,Porg=0;
  R_WarkUpCoolDownMode=SportVal;
  R_ProgramIndex=0;
  switch(R_PorgMode)
  {
    case	Prog1Val:
      Porg=0;
      break;
      //======
      case	Prog2Val:
        Porg=1;
        break;
        //======
        case	Prog3Val:	
          Porg=2;
          break;	
          //======	
          case	Prog4Val:	
            Porg=3;
            break;
            //======		
            case	Prog5Val:
              Porg=4;
              break;
  }
  for(i=0;i<30;i++)
  {
    switch(R_CholeIncSpdMode)
    {
      case	0:		//	Speed Inc混合
        SpeedTemp=F_TargetSpdCount(T_ProgSpeed[Porg][i]);
        IncTemp=(T_ProgInc[Porg][i])+1;
        break;
        //==============
        case	1:	//	Speed
          SpeedTemp=F_TargetSpdCount(T_ProgSpeed[Porg][i]);
          IncTemp=IncDefVal;				
          break;
          //==============	
          case	2:		//	Inc
            IncTemp=(T_ProgInc[Porg][i])+1;
            SpeedTemp=F_FristSportSpeed();
            break;
    }
    R_SaveSpeedProg[i]=SpeedTemp;	
    F_ChangeGraphSpeed(i,SpeedTemp);
    R_SaveIncProg[i]=IncTemp;
    F_ChangeGraphInc(i,IncTemp);
  }
  if(R_CholeIncSpdMode==2)
  {
    R_SpeedNum=F_FristSportSpeed();		//初始值設定	
  }
  F_ReadProgData();
  R_TimeH=R_TimeHBuf;
  R_TimeL=0;
  R_BzCnt=0x04;
}
//=======================
void  F_ProgSportEnd(void)
{
  R_WarkUpCoolDownMode=CoolDownVal;
  R_ProgAdr=0;
  SportEndBzFlg=1;
  R_TimeH=3;
  R_TimeL=0;
  F_ReadWarkUpProg();
}
//=======================
void	F_ProgCoolDownEnd(void)
{
  F_SportModeEndInit();
}
//=======================
void  F_ReadWarkUpProg(void)
{
  if(R_ProgAdr<3)   //限制最多3段
  {
    if(R_WarkUpCoolDownMode==WarkUpVal)
      R_SpeedNum=F_TargetSpdCount(T_WarkUpSpeedTabe[R_ProgAdr]);
    else  if(R_WarkUpCoolDownMode==CoolDownVal)
      R_SpeedNum=F_TargetSpdCount(T_CoolDownSpeedTabe[R_ProgAdr]);
    R_IncNum=IncDefVal;
  }
  else
    R_ProgAdr=0;
  R_ProgAdr++; 	
} 
//====================================================
//  Key
//====================================================
void  F_ProgSportMode_Key(void)
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
      if(R_WarkUpCoolDownMode==WarkUpVal)
      {		
        F_ProgWarkUpEnd();
        R_BzCnt=0x04;
      }
      else
      {
        if(R_SportMode != SportNormalVal)
        {
          F_ProgSetInit();
          R_BzCnt=0x04;		
        }
      }
      break;
      //======================
      case	Set_KeyVal:
	KeyCode=0;
	if(R_WarkUpCoolDownMode==SportVal)
	{
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
//=====================================
void    F_ProgSportModeIncUp(void)
{
    F_IncSetControlUp();
    R_SaveIncProg[R_ProgramIndex]=R_IncNum;
    F_ChangeGraphInc(R_ProgramIndex,R_IncNum);
}
//=====================================
void    F_ProgSportModeIncDown(void)
{
    F_IncSetControlDown();
    R_SaveIncProg[R_ProgramIndex]=R_IncNum;
    F_ChangeGraphInc(R_ProgramIndex,R_IncNum);		
}
//=====================================
void    F_ProgSportIncQuickKey(unsigned char Data)
{
  if(IncErrFlg==1)
    IncErrFlg=0;		//發生揚升錯誤，在按下揚升動作需要能解除錯誤
  IncStopFlg=0;
  R_IncNum = Data;
  F_ChangeShowInc();
  R_SaveIncProg[R_ProgramIndex]=R_IncNum;
  F_ChangeGraphInc(R_ProgramIndex,R_IncNum);      
  R_BzCnt=0x04;	             
}
//======================================
void    F_ProgSportSpdQuickKey(unsigned char Data)
{
  if(R_SportMode==SportNormalVal)
  {
    if((Data <= R_SpeedMax) || (Data >= R_SpeedMin)) {
      R_SpeedNum = Data;
    }
    R_BzCnt=0x04;	
    F_ChangeShowSpeed();							
    F_PorgWriteSpeed();
  }
}
//======================================
void	F_ChangeShowSpeed(void)
{
  if((R_CholeIncSpdMode==0)	|| (R_CholeIncSpdMode==1))
    R_Mode=0;	
}
//======================================
void	F_ChangeShowInc(void)
{
  if((R_CholeIncSpdMode==0)	|| (R_CholeIncSpdMode==2))
    R_Mode=1;	
}

//======================================
void	F_PorgWriteSpeed(void)
{
  R_SaveSpeedProg[R_ProgramIndex]=R_SpeedNum;
  F_ChangeGraphSpeed(R_ProgramIndex,R_SpeedNum);
}
//====================================================
//  LCD
//====================================================
void  F_ProgSportMode_Lcd(void)
{
  F_ShowPowerLed();	
  F_ShowPulse();
  F_ShowLaps();
  F_ShowDis();
  F_ShowCal();
  F_ShowTime();		
  F_ShowSpeed(R_SpeedNum);		
  F_ShowInc(R_IncNum);
  switch(R_WarkUpCoolDownMode)
  {
    case	WarkUpVal:
      F_ShowStringMove(midM14);		//	WARM UP – PRESS START TO BYPASS
      break;
      //===========================================
      case	SportVal:
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
        break;
        //===========================================
        case	CoolDownVal:
          F_ShowStringMove(midM15);		//	COOL DOWN
          break;
  }
}



