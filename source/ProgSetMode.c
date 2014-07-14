#include "connect.h"

void  F_ProgSetMode(void)
{
    if(T20msFlg==1)
    {
    T20msFlg=0;	
    F_ReadKey();
    F_CheckGetKey();
    F_ProgSetMode_key();
    }
    //=================
      if(ShowLcdTimeFlg==1)
      {
      ShowLcdTimeFlg=0;
      F_AllLCDRam(0x00);     
      F_ProgSetMode_Lcd();
      F_Display();
      }
      //=================
        if(T1sFlg==1)
        {
        T1sFlg=0;
        F_SleepTime();
        }
}
//===================================================
//  Key
//===================================================
void  F_ProgSetMode_key(void)
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
      F_QuickSetUserSpeed(10);
      break;		
    //======================
    case	QuickSpd_4_KeyVal:
      KeyCode=0;
      F_QuickSetUserSpeed(40);
      break;
    //======================
    case	QuickSpd_7_KeyVal:
      KeyCode=0;
      F_QuickSetUserSpeed(70);
      break;
    //======================
    case	QuickSpd_10_KeyVal:
      KeyCode=0;
      F_QuickSetUserSpeed(100);
      break; 
    //======================
    case	QuickSpd_13_KeyVal:
      KeyCode=0;
      F_QuickSetUserSpeed(130);
      break;
    //======================
    case	QuickSpd_16_KeyVal:
      KeyCode=0;
      F_QuickSetUserSpeed(160);
      break;
    //======================
    case	QuickInc_2_KeyVal:
      KeyCode=0;
      switch(R_PorgMode)
      {
        case	User1Val:
        case	User2Val:
        case	User3Val:
          if(R_Mode==5)
            F_QuickSetUserInc(3);
            else
              F_IncQuickKey(3);
          break;
        //============
        default :
          F_IncQuickKey(3);
          break;
      }
      break;		
    //======================
    case	QuickInc_4_KeyVal:
      KeyCode=0;
      switch(R_PorgMode)
      {
        case	User1Val:
        case	User2Val:
        case	User3Val:
          if(R_Mode==5)
            F_QuickSetUserInc(5);
            else
              F_IncQuickKey(5);
          break;
        //============
        default :
          F_IncQuickKey(5);
          break;
      }
      break;
    //======================
    case	QuickInc_6_KeyVal:
      KeyCode=0;
      switch(R_PorgMode)
      {
        case	User1Val:
        case	User2Val:
        case	User3Val:
          if(R_Mode==5)
            F_QuickSetUserInc(7);
            else
              F_IncQuickKey(7);
          break;
        //============
        default :
          F_IncQuickKey(7);
          break;
      }
      break; 
    //======================
    case	QuickInc_8_KeyVal:
      KeyCode=0;
      switch(R_PorgMode)
      {
        case	User1Val:
        case	User2Val:
        case	User3Val:
          if(R_Mode==5)
            F_QuickSetUserInc(9);
            else
              F_IncQuickKey(9);
          break;
        //============
        default :
          F_IncQuickKey(9);
          break;
      }
      break;
    //======================
    case	QuickInc_10_KeyVal:
      KeyCode=0;
      switch(R_PorgMode)
      {
        case	User1Val:
        case	User2Val:
        case	User3Val:
          if(R_Mode==5)
            F_QuickSetUserInc(11);
            else
              F_IncQuickKey(11);
          break;
        //============
        default :
          F_IncQuickKey(11);
          break;
      }
      break;
    //======================
    case	QuickInc_12_KeyVal:
      KeyCode=0;
      switch(R_PorgMode)
      {
        case	User1Val:
        case	User2Val:
        case	User3Val:
          if(R_Mode==5)
            F_QuickSetUserInc(13);
            else
              F_IncQuickKey(13);
          break;
        //============
        default :
          F_IncQuickKey(13);
          break;
      }
      break;
    //======================	
    case        LongMode_KeyVal:
      KeyCode=0;
      F_EepromClear_4();
      R_BzCnt=0x04;
      break;
    //===============================
    case        LongSet_KeyVal:
      KeyCode=0;
      F_LongSetKey();
      break;
    //===============================	
    case	Set_KeyVal:
      KeyCode=0;
      F_SetKey();
      break;
    //===============================
    case	Mode_KeyVal:
      KeyCode=0;
      R_PorgMode++;
      if(R_PorgMode>Hrc2Val)
        R_PorgMode=0;
      F_ProgSetInit();
      R_BzCnt=0x04;	
      break;
    //===============================
    case        Enter_KeyVal:
      KeyCode=0;
      F_EnterSetKey();
      F_StringInit();
      R_BzCnt=0x04;
      break;
    //===============================
    case	InclineUp_KeyVal:
      KeyCode=0;
      F_InclineUpSetKey();
      break;	
    //===============================
    case	InclineDown_KeyVal:
      KeyCode=0;
      F_InclineDownSetKey();
      break;			
    //===============================
    case	SpeedUp_KeyVal:
      KeyCode=0;
      F_SpeedUpSetKey();
      break;
    //===============================
    case	SpeedDown_KeyVal:
      KeyCode=0;
      F_SpeedDownSetKey();
      break;
    //===============================
    case	start_stop_KeyVal:
      KeyCode=0;
      if(SpeedMoveFlg==0)
        F_StartStopSetKey();
      break;	
  }
}
//===================================================
//
//===================================================
void F_LongSetKey(void)
{
    switch(R_PorgMode)
    {
      case      User1Val:
        if(R_Mode==0)
        {
          F_User_Init(User_1_SpeedAdrVal,User_1_IncAdrVal);
          R_BzCnt=0x14;
        }	
        break;
      //============
      case	User2Val:
        if(R_Mode==0)
        {
          F_User_Init(User_2_SpeedAdrVal,User_2_IncAdrVal);
          R_BzCnt=0x14;
        }		
        break;
      //============
      case      User3Val:
        if(R_Mode==0)
        {
          F_User_Init(User_3_SpeedAdrVal,User_3_IncAdrVal);
          R_BzCnt=0x14;
        }
        break;
    }	
}
//====================================
void F_InclineUpSetKey(void)
{
    switch(R_PorgMode)
    {
      case	User1Val:
      case	User2Val:
      case	User3Val:
        if(R_Mode==5)
          F_SetUserIncUp();
          else
            F_IncSetControlUp();
        break;
      //============
      default :
        F_IncSetControlUp();
        break;
    }
}
//====================================
void F_InclineDownSetKey(void)
{
  switch(R_PorgMode)
  {
    case	User1Val:
    case	User2Val:
    case	User3Val:
      if(R_Mode==5)
        F_SetUserIncDown();
        else
          F_IncSetControlDown();
      break;
    //============
    default :
      F_IncSetControlDown();
      break;
  }
}
//====================================
void F_SetKey(void)
{
    switch(R_PorgMode)
    {
      //============				
      case	Prog1Val:
      case	Prog2Val:
      case	Prog3Val:		
      case	Prog4Val:		
      case	Prog5Val:
        if(R_Mode==0) {
          if(R_CholeIncSpdMode==2) {
            if(ChangeUnitFlg==1)
              R_TargetSpd=TargetMileVal;        //  英制
              else
                R_TargetSpd=TargetKmVal;
          }
          R_CholeIncSpdMode++;
          if(R_CholeIncSpdMode>2)
            R_CholeIncSpdMode=0;
            else if(R_CholeIncSpdMode==2)
                    R_TargetSpd=R_SpeedMin;
          R_BzCnt=0x04;	
        }
          break;
        //============
        case	User1Val:
        case	User2Val:
        case	User3Val:				
          if(R_Mode==5) {
            if(ChangeSpdIncProgFlg==1)
              ChangeSpdIncProgFlg=0;
              else
                ChangeSpdIncProgFlg=1;
            R_BzCnt=0x04;	
          }
            else {
              if(R_Mode==0) {
                R_CholeIncSpdMode++;
                if(R_CholeIncSpdMode>2)
                  R_CholeIncSpdMode=0;
                  R_BzCnt=0x04;	
              }
            }
          break;
    }
}
//==============================
void  F_EnterSetKey(void)
{
    switch(R_PorgMode)
    {
      case	ManualVal:
        switch(R_Mode)
        {
          case	0:
            R_Mode=1;           //	時間設定
            break;
          //========	
          case	1:
            R_Mode=2;		//	距離設定
            break;
          //========	
          case	2:	
            R_Mode=3;		//	卡路里設定
            break;
          //========	
          case  3:	
            R_Mode=4;           //	Thr設定
            break;	
          //========	
          case	4:	
            R_Mode=0;		//	Manual
            break;
          //========
          default :
            R_Mode=0;	
            break;
        }
        break;
        //============		
      case	Prog1Val:
      case	Prog2Val:
      case	Prog3Val:		
      case	Prog4Val:		
      case	Prog5Val:
        switch(R_Mode)
        {
          case	0:
            if(R_CholeIncSpdMode==2)
              ChangeSpdIncProgFlg=1;    //	選擇incline Porg跳過Target Speed設定
              else
                ChangeSpdIncProgFlg=0;  //	Target Speed設定
            R_Mode=1;	
            F_TargetIncSpdShowCount();
            break;
          //========	
          case	1:	
            R_Mode=2;           //	時間設定
            break;
          //========	
          case	2:	
            R_Mode=3;           //	距離設定
            break;
          //========	
          case	3:	
            R_Mode=4;		//	卡路里設定
            break;	
          //========	
          case	4:	
            R_Mode=5;		//	Thr設定
            break;
          //========
          case	5:	
            R_Mode=0;		//	Manual
            break;
          //========
          default :
            R_Mode=0;
            break;
          }
        break;
      //============		
      case	User1Val:
      case	User2Val:
      case	User3Val:
        switch(R_Mode)
        {
          case	0:
            R_Mode=1;		//	時間設定
            break;
          //========
          case	1:
            R_Mode=2;		//	距離設定
            break;
          //========
          case	2:
            R_Mode=3;		//	卡路里設定
            break;
          //========
          case	3:	
            R_Mode=4;		//	Thr設定
            break;
          //========
          case	4:
            R_Mode=5;
            R_ProgramIndex=0;
            if(R_PorgMode==User1Val)	
              F_ReadUserProfile(User_1_SpeedAdrVal,User_1_IncAdrVal);
              else if(R_PorgMode==User2Val)
                    F_ReadUserProfile(User_2_SpeedAdrVal,User_2_IncAdrVal);
              else if(R_PorgMode==User3Val)				
                    F_ReadUserProfile(User_3_SpeedAdrVal,User_3_IncAdrVal);
              break;
          //========
          case	5:
            F_GraphSpeedInc();
            break;
        }
          break;
        //============
        case	Hrc1Val:
        case	Hrc2Val:
          switch(R_Mode)
          {
            case 0:
              R_Mode=1;         //	年齡設定		
              break;
            //========
            case 1:
              R_Mode=2;         //	Thr設定
              if(R_PorgMode==Hrc1Val)	
                R_Thr=((220-R_Age)*60)/100;
                else	
                  R_Thr=((220-R_Age)*85)/100;	
              break;
            //========
            case 2:
              R_Mode=3;		//	時間設定
              break;
            //========
            case 3:
              R_Mode=4;		//	距離設定
              break;
            //========
            case 4:
              R_Mode=5;		//	卡路里設定
              break;
            //========
            case 5:
              R_Mode=0;	
              break;
          }
          break;
        //============
    }
}
//===================================================
//
//===================================================
void  F_StartStopSetKey(void)
{
    switch(R_PorgMode)
    {
      case ManualVal:
        F_SportInit();
        break;
      //============		
      case Prog1Val:
      case Prog2Val:
      case Prog3Val:		
      case Prog4Val:		
      case Prog5Val:
        F_SportInit();
        break;
      //============		
      case User1Val:
      case User2Val:
      case User3Val:
        F_SportInit();
        break;
      //============
      case Hrc1Val:
      case Hrc2Val:
        F_SportInit();
        break;
      //============
    }
}
//==============================
void F_SportInit(void)
{
    F_TimeStatus();
    //==================
    if(R_Calorie==0)
      CalStatusFlg=0;           //卡路里正數
      else
        CalStatusFlg=1;           //卡路里倒數
    //==================	
    if(R_Distance==0)		
      DisStatusFlg=0;				//距離正數
      else
        DisStatusFlg=1;			//距離倒數
    //==================	
    switch(R_PorgMode)
    {
      case	ManualVal:
        R_SpeedBuf=F_FristSportSpeed();
        //R_IncBuf=IncDefVal;
        R_IncBuf=R_IncNum;      // 2014/5/28 Chandler 修改 開機後 在MANUAL待機模式下，將揚昇按至L15  再按START揚昇會自己回到L0    應該要停在L15的地方啟動
        break;
      //================================
      case	Prog1Val:
      case	Prog2Val:
      case	Prog3Val:		
      case	Prog4Val:
      case	Prog5Val:
        R_SpeedBuf=F_TargetSpdCount(T_WarkUpSpeedTabe[0]);
        if((R_Calorie==0) && (R_Distance==0) && (R_TimeH==30))
          CoolDownStartFlg=1;           //	CoolDown 啟動
          else	
            CoolDownStartFlg=0;		//	CoolDown 關閉
        R_IncBuf=IncDefVal;
        R_TimeHBuf=R_TimeH;
        R_TimeH=3;		//	WarkUpTime
        R_ProgAdr=1;
        break;
      //================================
      case	User1Val:
      case	User2Val:
      case	User3Val:
        if(R_PorgMode==User1Val)	
          F_UserCholeIncSpd(User_1_SpeedAdrVal,User_1_IncAdrVal);
          else	if(R_PorgMode==User2Val)
                  F_UserCholeIncSpd(User_2_SpeedAdrVal,User_2_IncAdrVal);
          else  if(R_PorgMode==User3Val)				
                  F_UserCholeIncSpd(User_3_SpeedAdrVal,User_3_IncAdrVal);
        switch(R_CholeIncSpdMode)
        {
          case	0:      //	Speed Inc混合
            R_SpeedBuf=R_SaveSpeedProg[0];
            R_IncBuf=R_SaveIncProg[0];
            break;
          //==============
          case	1:	//	Speed
            R_SpeedBuf=R_SaveSpeedProg[0];
            R_IncBuf=R_IncNum;
            break;
          //==============	
          case	2:      //	Inc
            R_SpeedBuf=F_FristSportSpeed();
            R_IncBuf=R_SaveIncProg[0];
            break;
          }			
          break;
      //================================
      case      Hrc1Val:
      case	Hrc2Val:
        if(R_Thr==0)	//	未設定
        {	
          if(R_PorgMode==Hrc1Val)	
            R_Thr=((220-R_Age)*60)/100;
            else	
              R_Thr=((220-R_Age)*85)/100;	
        }				
        R_ThrBuf=R_Thr;
        R_SpeedBuf=R_SpeedMin;
        R_IncBuf=IncDefVal;
        break;
      //================================
    }
    R_Laps=0;
    R_ProgTime=0;
    R_TrackDis=0;
    R_LapsDis=0;			
    R_TrackCnt=0;
    R_KcalBye1=0;
    R_ProgramIndex=0;
    R_Mode=0;
    R_BzCnt=0x04;
    F_CountDownModeInit();
}
//===================================================
unsigned char F_FristSportSpeed(void)
{
    unsigned    char	Data;
      Data=R_SpeedMin;
    return	Data;
}
//===================================================
//
//===================================================
void  F_SpeedUpSetKey(void)
{
  switch(R_PorgMode)
  {
    case	ManualVal:
      switch(R_Mode)
      {
        case	1:
          F_TimeSetUp();
          break;
          //========
          case	2:
            F_DisSetUp();
            break;
            //========				
            case	3:
              F_CalSetUp();
              break;
              //========				
              case	4:
                F_ThrSetUp();
                break;
      }
      break;
      //============		
      case	Prog1Val:
        case	Prog2Val:
          case	Prog3Val:		
            case	Prog4Val:		
              case	Prog5Val:
                switch(R_Mode)
                {
                  //========
                  case	1:
                    if(R_CholeIncSpdMode!=2)
                      F_TargetSpdSetUp();
                    break;
                    //========
                    case	2:
                      F_TimeSetUp();
                      break;
                      //========
                      case	3:
                        F_DisSetUp();
                        break;
                        //========
                        case	4:
                          F_CalSetUp();
                          break;
                          //========
                          case	5:
                            F_ThrSetUp();
                            break;
                            //========
                }
                break;
                //============		
                case	User1Val:
                  case	User2Val:
                    case	User3Val:
                      switch(R_Mode)
                      {
                        //========
                        case	1:
                          F_TimeSetUp();
                          break;
                          //========
                          case	2:
                            F_DisSetUp();
                            break;
                            //========
                            case	3:
                              F_CalSetUp();
                              break;
                              //========
                              case	4:
                                F_ThrSetUp();
                                break;
                                //========
                                case	5:
                                  F_SetUserSpeedUp();
                                  break;
                                  //========
                      }
                      break;
                      //============
                      case	Hrc1Val:
			case	Hrc2Val:
                          switch(R_Mode)
                          {
                            //========
                            case	1:
                              F_AgeSetUp();
                              break;
                              //========
                              case	2:
                                F_ThrSetUp();
                                break;
                                //========
                                case	3:
                                  F_TimeSetUp();
                                  break;
                                  //========
                                  case	4:
                                    F_DisSetUp();
                                    break;
                                    //========
                                    case	5:
                                      F_CalSetUp();
                                      break;
                                      //========
                          }
                          break;
                          //============
  }
}
//===================================================
//
//===================================================
void  F_SpeedDownSetKey(void)
{
  switch(R_PorgMode)
  {
    case	ManualVal:
      switch(R_Mode)
      {
        case	1:
          F_TimeSetDown();
          break;
          //========
          case	2:
            F_DisSetDown();
            break;
            //========
            case	3:
              F_CalSetDown();
              break;
              //========
              case	4:
                F_ThrSetDown();
                break;
                //========
      }
      break;
      //============		
      case	Prog1Val:
        case	Prog2Val:
          case	Prog3Val:		
            case	Prog4Val:		
              case	Prog5Val:
                switch(R_Mode)
                {
                  //========
                  case	1:
                    if(R_CholeIncSpdMode!=2)
                      F_TargetSpdSetDown();
                    break;
                    //========
                    case	2:
                      F_TimeSetDown();
                      break;
                      //========
                      case	3:
                        F_DisSetDown();
                        break;
                        //========
                        case	4:
                          F_CalSetDown();
                          break;
                          //========
                          case	5:
                            F_ThrSetDown();
                            break;
                            //========
                }
                break;
                //============		
                case	User1Val:
                  case	User2Val:
                    case	User3Val:
                      switch(R_Mode)
                      {
                        case	1:
                          F_TimeSetDown();
                          break;
                          //========
                          case	2:
                            F_DisSetDown();
                            break;
                            //========
                            case	3:
                              F_CalSetDown();
                              break;
                              //========
                              case	4:
                                F_ThrSetDown();
                                break;
                                //========
                                case	5:
                                  F_SetUserSpeedDown();	
                                  break;
                                  //========
                      }
                      break;
                      //============
                      case	Hrc1Val:
			case	Hrc2Val:
                          switch(R_Mode)
                          {
                            //========
                            case	1:
                              F_AgeSetDown();
                              break;
                              //========
                              case	2:
                                F_ThrSetDown();
                                break;
                                //========
                                case	3:
                                  F_TimeSetDown();
                                  break;
                                  //========
                                  case	4:
                                    F_DisSetDown();
                                    break;
                                    //========
                                    case	5:
                                      F_CalSetDown();
                                      break;
                                      //========
                          }
                          break;
                          //============
  }
}
//===================================================
//
//===================================================
void    F_IncQuickKey(unsigned char Data)
{
  if(IncErrFlg==1)
    IncErrFlg=0;		//發生揚升錯誤，在按下揚升動作需要能解除錯誤
  IncStopFlg=0;
  R_IncNum = Data;
  R_BzCnt=0x04;	
}

void    F_IncSetControlUp(void)
{
  if(IncErrFlg==1)
    IncErrFlg=0;		//發生揚升錯誤，在按下揚升動作需要能解除錯誤
  
  IncStopFlg=0;
  if(R_IncNum<R_IncMax)
  {
    R_IncNum++;
    if(R_LongKeyStopBz==0)	
      R_BzCnt=0x04;	
  }
  else
    R_IncNum=R_IncMax;
}
//================================
void F_IncSetControlDown(void)
{
  if(IncErrFlg==1)
    IncErrFlg=0;		//發生揚升錯誤，在按下揚升動作需要能解除錯誤
  
  IncStopFlg=0;
  if(R_IncNum>IncMinVal)
  {
    R_IncNum--;
    if(R_LongKeyStopBz==0)	
      R_BzCnt=0x04;	
  }
  else
    R_IncNum=IncMinVal;
}
//================================
void  F_TimeStatus(void)
{
    if(R_TimeH==0)
    {
      TimeStatusFlg=0;      //時間正數		
      R_ProgTimeBase=60;		
    }
    else
    {
      TimeStatusFlg=1;								//時間倒數
      R_ProgTimeBase=R_TimeH*2;       //時間倒數取每段時間
    }
}
//================================
void	F_QuickSetUserInc(unsigned char Data)
{
    F_ShowFlashInt();
    R_User_SetInc = Data;
    R_BzCnt=0x04; 
    F_ChangeGraphInc(R_ProgramIndex,R_User_SetInc);
    ChangeSpdIncProgFlg=1;
}
//================================
void	F_SetUserIncUp(void)
{
    F_ShowFlashInt();
    if(R_User_SetInc<R_IncMax)
    {
      R_User_SetInc++;
      if(R_LongKeyStopBz==0)	//長按時蜂鳴器不叫
        R_BzCnt=0x04;      
    }
    else
    {
      R_User_SetInc=R_IncMax;       
    }
    F_ChangeGraphInc(R_ProgramIndex,R_User_SetInc);
    ChangeSpdIncProgFlg=1;
}
//================================				
void	F_SetUserIncDown(void)
{
    F_ShowFlashInt();
    if(R_User_SetInc>IncMinVal)
    {
      R_User_SetInc--;
      if(R_LongKeyStopBz==0)	//長按時蜂鳴器不叫
        R_BzCnt=0x04; 
    }
    else
    {	
      R_User_SetInc=IncMinVal;     
    }
    F_ChangeGraphInc(R_ProgramIndex,R_User_SetInc);	
    ChangeSpdIncProgFlg=1;
}
//================================
void	F_QuickSetUserSpeed(unsigned char Data)
{
      switch(R_PorgMode)
      {
        case	User1Val:
        case	User2Val:
        case	User3Val:
          if(R_Mode==5) {
            F_ShowFlashInt();
            R_User_SetSpeed=Data;   
            R_BzCnt=0x04; 
            F_ChangeGraphSpeed(R_ProgramIndex,R_User_SetSpeed);
            ChangeSpdIncProgFlg=0;
            
          }
          break;
      }
}
//================================
void    F_SetUserSpeedUp(void)
{
    F_ShowFlashInt();
    if(R_User_SetSpeed<R_SpeedMax)
    {
      R_User_SetSpeed++;
      if(R_LongKeyStopBz==0)	//長按時蜂鳴器不叫
        R_BzCnt=0x04;   
    }
    else
    {	
      R_User_SetSpeed=R_SpeedMax;
    }
    F_ChangeGraphSpeed(R_ProgramIndex,R_User_SetSpeed);
    ChangeSpdIncProgFlg=0;
}
//================================	
void	F_SetUserSpeedDown(void)
{
    F_ShowFlashInt();
    if(R_User_SetSpeed>R_SpeedMin)
    {
      R_User_SetSpeed--;
      if(R_LongKeyStopBz==0)	//長按時蜂鳴器不叫
        R_BzCnt=0x04; 
    }
    else
    {
      R_User_SetSpeed=R_SpeedMin;      
    }
    F_ChangeGraphSpeed(R_ProgramIndex,R_User_SetSpeed);
    ChangeSpdIncProgFlg=0;
}
//================================
void  F_AgeSetUp(void)
{
    F_ShowFlashInt();
    if(R_Age<AgeMaxVal)
      R_Age++;
    else
      R_Age=AgeMinVal;
    if(R_LongKeyStopBz==0)	//長按時蜂鳴器不叫
      R_BzCnt=0x04;       
}
//================================
void  F_AgeSetDown(void)
{
    F_ShowFlashInt();
    if(R_Age>AgeMinVal)
      R_Age--;
    else  
      R_Age=AgeMaxVal;
    if(R_LongKeyStopBz==0)	//長按時蜂鳴器不叫
      R_BzCnt=0x04;       
}
//================================
void  F_TargetSpdSetUp(void)
{
    F_ShowFlashInt();
    if(R_TargetSpd<R_SpeedMax) 
    {
      R_TargetSpd++;
      if(R_LongKeyStopBz==0)	//長按時蜂鳴器不叫
        R_BzCnt=0x04;
    }
    else  
    {
      R_TargetSpd=R_SpeedMax;       
    }
    F_TargetIncSpdShowCount(); 
}
//================================
void  F_TargetSpdSetDown(void)
{
    F_ShowFlashInt();
    if(R_TargetSpd>R_SpeedMin)
    {
      R_TargetSpd--;
      if(R_LongKeyStopBz==0)	//長按時蜂鳴器不叫
        R_BzCnt=0x04;
    }
    else
    {	
      R_TargetSpd=R_SpeedMin;       
    }    
    F_TargetIncSpdShowCount();    
}
//================================
void	F_TimeSetUp(void)
{
    F_ShowFlashInt();
    if(R_TimeH!=0)
    {  
      if(R_TimeH<SetTimeMaxVal)
        R_TimeH++;
      else
        R_TimeH=0; 
    }
    else
      R_TimeH=SetTimeMinVal;
    
    if(R_LongKeyStopBz==0)	//長按時蜂鳴器不叫
      R_BzCnt=0x04;  
}
//================================
void	F_DisSetUp(void)
{
    F_ShowFlashInt();
    if(R_Distance<100)
    {
      R_Distance++;
    }
    else
    {
      R_Distance=R_Distance+10;
      if(R_Distance>SetDisMaxVal)
        R_Distance=0;
    }
    if(R_LongKeyStopBz==0)	//長按時蜂鳴器不叫
      R_BzCnt=0x04;  
}
//================================
void	F_CalSetUp(void)
{
    F_ShowFlashInt();
    R_Calorie++;
    if(R_Calorie>SetCalMaxVal)
    {
      R_Calorie=0; 
    }
    /*	
    if(R_Calorie!=0)
    {
    if(R_Calorie<SetCalMaxVal)
    R_Calorie=R_Calorie+10;
    else
    R_Calorie=0; 
  }
    else
    R_Calorie=SetCalMinVal;
    */				
    if(R_LongKeyStopBz==0)	//長按時蜂鳴器不叫
      R_BzCnt=0x04;  
}
//================================
void	F_ThrSetUp(void)
{
    F_ShowFlashInt(); 
    if((R_PorgMode==Hrc1Val) || (R_PorgMode==Hrc2Val))
    {
      if(R_Thr<ThrMaxVal)
        R_Thr++;
      else
        R_Thr=ThrMinVal;
    }	
    else
    {	
      if(FristThrSetFlg)
      {
        if(R_Thr==0)
          R_Thr=ThrMinVal;
        else
        {
          if(R_Thr<ThrMaxVal)
            R_Thr++;
          else
            R_Thr=0;
        }	
      }
      else
      {
        FristThrSetFlg=1;
        R_Thr=120;
      }
    }
    if(R_LongKeyStopBz==0)	//長按時蜂鳴器不叫
      R_BzCnt=0x04;
}
//================================
void	F_TimeSetDown(void)
{
    F_ShowFlashInt();
    if(R_TimeH!=0)
    {  
      if(R_TimeH>SetTimeMinVal)
        R_TimeH--;
      else
        R_TimeH=0;
    }
    else
      R_TimeH=99;
    if(R_LongKeyStopBz==0)	//長按時蜂鳴器不叫
      R_BzCnt=0x04;
}
//================================
void	F_DisSetDown(void)
{
    F_ShowFlashInt();
    if(R_Distance<=100)
    {
      if(R_Distance>0)
        R_Distance--;
      else
        R_Distance=SetDisMaxVal;		
    }
    else
    {
      R_Distance=R_Distance-10;
      
    }	
    if(R_LongKeyStopBz==0)	//長按時蜂鳴器不叫
      R_BzCnt=0x04;
}
//================================
void	F_CalSetDown(void)
{
    F_ShowFlashInt();
    if(R_Calorie>0)
    {
      R_Calorie--;	
    }
    else
      R_Calorie=SetCalMaxVal;	
    if(R_LongKeyStopBz==0)	//長按時蜂鳴器不叫
      R_BzCnt=0x04;
}
//================================
void	F_ThrSetDown(void)
{
    F_ShowFlashInt(); 
    if((R_PorgMode==Hrc1Val) || (R_PorgMode==Hrc2Val))
    {
      if(R_Thr>ThrMinVal)
        R_Thr--;
      else
        R_Thr=ThrMaxVal;
    }
    else
    {
      if(FristThrSetFlg)
      {
        if(R_Thr==0)
          R_Thr=ThrMaxVal;
        else
        {
          if(R_Thr>ThrMinVal)
            R_Thr--;
          else
            R_Thr=0;
        }	
        
      }
      else
      {
        FristThrSetFlg=1;
        R_Thr=120;
      }
    }
    if(R_LongKeyStopBz==0)	//長按時蜂鳴器不叫
      R_BzCnt=0x04;
}
//========================
void  F_GraphSpeedInc(void)
{
    unsigned	char	SpeedAdrTemp,IncAdrTemp;
    switch(R_PorgMode)
    {
      case	User1Val:
        SpeedAdrTemp=User_1_SpeedAdrVal;
        IncAdrTemp=User_1_IncAdrVal;
        break;
        //============
        case	User2Val:
          SpeedAdrTemp=User_2_SpeedAdrVal;
          IncAdrTemp=User_2_IncAdrVal;	
          break;
          //============
          case	User3Val:
            SpeedAdrTemp=User_3_SpeedAdrVal;
            IncAdrTemp=User_3_IncAdrVal;
            break;
            //============
    }
    EE_Write(SpeedAdrTemp+R_ProgramIndex,R_User_SetSpeed);
    EE_Write(IncAdrTemp+R_ProgramIndex,R_User_SetInc);
    //===========
    R_ProgramIndex++;
    if(R_ProgramIndex>=30)
    {
      R_ProgramIndex=0;
      R_Mode=0;
    }
    else
    {
      R_User_SetSpeed=EE_Read(SpeedAdrTemp+R_ProgramIndex);
      R_User_SetInc=EE_Read(IncAdrTemp+R_ProgramIndex);
      //F_ChangeGraphInc(R_ProgramIndex,R_User_SetInc);
      //F_ChangeGraphSpeed(R_ProgramIndex,R_User_SetSpeed);
    }
}
//===================================================
//  LCD
//===================================================
void  F_ProgSetMode_Lcd(void)
{
  F_ShowPowerLed();
  R_Seg[26] |= 0x08;		//	-
  switch(R_PorgMode)
  {
    case	ManualVal:
      R_Seg[27] |= 0x1F;		//	P
      F_Show_8_FontLcd(25,0);
      F_ShowInc(R_IncNum);
      F_ShowSpeed(0);
      switch(R_Mode)
      {
        case	0:
          F_ShowStringMove(midM04);
          F_ShowTime();
          F_ShowDis();
          F_ShowCal();
          F_ShowPulse();
          break;
          //========
          case	1:
            F_ShowStringMove(midM11);		//	ENTER WORKOUT TIME
            F_ShowDis();
            F_ShowCal();
            F_ShowPulse();
            if(SetModeFlashFlg)
              F_ShowTime();	
            break;	
            //========
            case	2:
              F_ShowStringMove(midM08);		//	ENTER WORKOUT DISTANCE
              F_ShowTime();
              F_ShowCal();
              F_ShowPulse();
              if(SetModeFlashFlg)
                F_ShowDis();
              break;	
              //========
              case	3:
                F_ShowStringMove(midM10);		//	ENTER WORKOUT CALORIES
                F_ShowTime();
                F_ShowDis();
                F_ShowPulse();
                if(SetModeFlashFlg)
                  F_ShowCal();	
                break;	
                //========
                case	4:
                  F_ShowStringMove(midM13);		//	ENTER TARGET HEART RATE
                  F_ShowTime();
                  F_ShowDis();
                  F_ShowCal();
                  if(SetModeFlashFlg)
                    F_ShowThrSet();
                  break;
      }
      break;
      //===================================
      case	Prog1Val:
        case	Prog2Val:
          case	Prog3Val:
            case	Prog4Val:
              case	Prog5Val:
		R_Seg[27] |= 0x1F;		//	P
                if(R_PorgMode==Prog1Val)
                  F_Show_8_FontLcd(25,1);
                else	if(R_PorgMode==Prog2Val)
                  F_Show_8_FontLcd(25,2);
                else	if(R_PorgMode==Prog3Val)
                  F_Show_8_FontLcd(25,3);
                else	if(R_PorgMode==Prog4Val)
                  F_Show_8_FontLcd(25,4);
                else	if(R_PorgMode==Prog5Val)
                  F_Show_8_FontLcd(25,5);						
		F_ShowInc(R_IncNum);
		ShowIncSpdPorgLed();
                switch(R_Mode)
                {
                  case	0:
                    F_ShowStringMove(midM05);
                    F_ShowSpeed(R_TargetSpd);
                    F_ShowTime();
                    F_ShowDis();
                    F_ShowCal();
                    F_ShowPulse();
                    break;
                    //========
                    case	1:
                      F_ShowSpeedIncProg();
                      F_ShowTime();
                      F_ShowDis();
                      F_ShowCal();
                      F_ShowPulse();
                      if(R_CholeIncSpdMode!=2)	//	選擇incline Porg跳過Target Speed設定
                      {
                        if(SetModeFlashFlg)
                          F_ShowSpeed(R_TargetSpd);
                      }
                      else
                        F_ShowSpeed(R_TargetSpd);
                      break;	
                      //========
                      case	2:
                        F_ShowStringMove(midM11);		//	ENTER WORKOUT TIME	
                        F_ShowSpeed(R_TargetSpd);
                        F_ShowDis();
                        F_ShowCal();
                        F_ShowPulse();
                        if(SetModeFlashFlg)
                          F_ShowTime();
                        break;	
                        //========
                        case	3:
                          F_ShowStringMove(midM08);		//	ENTER WORKOUT DISTANCE
                          F_ShowSpeed(R_TargetSpd);
                          F_ShowTime();
                          F_ShowCal();
                          F_ShowPulse();	
                          if(SetModeFlashFlg)
                            F_ShowDis();
                          break;	
                          //========
                          case	4:
                            F_ShowStringMove(midM10);		//	ENTER WORKOUT CALORIES
                            F_ShowSpeed(R_TargetSpd);
                            F_ShowTime();
                            F_ShowDis();
                            F_ShowPulse();	
                            if(SetModeFlashFlg)
                              F_ShowCal();
                            break;	
                            //========
                            case	5:
                              F_ShowStringMove(midM13);		//	ENTER TARGET HEART RATE
                              F_ShowSpeed(R_TargetSpd);
                              F_ShowTime();
                              F_ShowDis();
                              F_ShowCal();
                              if(SetModeFlashFlg)
                                F_ShowThrSet();
                              break;	
                              //========
                }
                break;
		//===================================
		case	User1Val:
                  case	User2Val:	
                    case	User3Val:
                      R_Seg[27] |= 0x76;		//	U
                      if(R_PorgMode==User1Val)
                        F_Show_8_FontLcd(25,1);
                      else	if(R_PorgMode==User2Val)
                        F_Show_8_FontLcd(25,2);
                      else	if(R_PorgMode==User3Val)
                        F_Show_8_FontLcd(25,3);
                      switch(R_Mode)
                      {
                        case	0:
                          F_ShowStringMove(midM04);	
                          ShowIncSpdPorgLed();
                          F_ShowTime();
                          F_ShowDis();
                          F_ShowCal();
                          F_ShowPulse();
                          F_ShowSpeed(0);		
                          F_ShowInc(R_IncNum);
                          break;
                          //========	
                          case	1:
                            F_ShowStringMove(midM11);		//	ENTER WORKOUT TIME
                            ShowIncSpdPorgLed();
                            F_ShowDis();
                            F_ShowCal();
                            F_ShowPulse();
                            F_ShowSpeed(0);		
                            F_ShowInc(R_IncNum);
                            if(SetModeFlashFlg)		
                              F_ShowTime();
                            break;
                            //========	
                            case	2:
                              F_ShowStringMove(midM08);		//	ENTER WORKOUT DISTANCE
                              ShowIncSpdPorgLed();
                              F_ShowTime();
                              F_ShowCal();
                              F_ShowPulse();
                              F_ShowSpeed(0);		
                              F_ShowInc(R_IncNum);
                              if(SetModeFlashFlg)		
                                F_ShowDis();			
                              break;	
                              //========	
                              case	3:	
				F_ShowStringMove(midM10);		//	ENTER WORKOUT CALORIES
				ShowIncSpdPorgLed();
				F_ShowTime();
				F_ShowDis();
				F_ShowPulse();
				F_ShowSpeed(0);		
				F_ShowInc(R_IncNum);
                                if(SetModeFlashFlg)		
                                  F_ShowCal();
                                break;	
				//========	
				case	4:
                                  F_ShowStringMove(midM13);		//	ENTER TARGET HEART RATE
                                  ShowIncSpdPorgLed();	
                                  F_ShowTime();
                                  F_ShowDis();
                                  F_ShowCal();
                                  F_ShowSpeed(0);		
                                  F_ShowInc(R_IncNum);
                                  if(SetModeFlashFlg)		
                                    F_ShowThrSet();		
                                  break;	
                                  //========
                                  case	5:
                                    if(ChangeSpdIncProgFlg)
                                      R_LedSegBuf |= 0x01;	//	Inc	Led	
                                    else
                                      R_LedSegBuf |= 0x02;		//	Speed Led
                                    F_ShowTime();
                                    F_ShowDis();
                                    F_ShowCal();
                                    F_ShowPulse();
                                    F_ShowSpeedIncProg();
                                    if(ChangeSpdIncProgFlg)
                                    {
                                      F_ShowSpeed(R_User_SetSpeed);
                                      if(SetModeFlashFlg)		
                                        F_ShowInc(R_User_SetInc);
                                      if(SetModeFlashFlg==0)		
                                        F_ShowProfileFlash();
                                    }
                                    else
                                    {
                                      F_ShowInc(R_User_SetInc);
                                      if(SetModeFlashFlg)
                                        F_ShowSpeed(R_User_SetSpeed);
                                      if(SetModeFlashFlg==0)
                                        F_ShowProfileFlash();
                                    }
                                    break;	
                                    //========	
                      }
                      break;
                      //===================================
                      case	Hrc1Val:
                        case	Hrc2Val:
                          R_Seg[27] |= 0x3E;		//	H
                          if(R_PorgMode==Hrc1Val)
                            F_Show_8_FontLcd(25,1);
                          else	if(R_PorgMode==Hrc2Val)
                            F_Show_8_FontLcd(25,2);
                          F_ShowInc(R_IncNum);
                          F_ShowSpeed(0);
                          switch(R_Mode)
                          {
                            case	0:
                              R_StringChangeTime++;
                              if(R_StringChangeTime>20)
                              {
                                R_StringChangeTime=20;
                                F_ShowStringMove(midM04);
                              }
                              else
                              {
                                if(R_PorgMode==Hrc1Val)
                                  F_ShowMatrixPicture(7,Pid60);
                                else	if(R_PorgMode==Hrc2Val)
                                  F_ShowMatrixPicture(7,Pid80);
                              }	
                              F_ShowTime();
                              F_ShowDis();
                              F_ShowCal();
                              F_ShowPulse();
                              break;
                              //========
                              case	1:
				F_ShowStringMove(midM12);		//	ENTER AGE
				F_ShowTime();
				F_ShowDis();
				F_ShowCal();
				if(SetModeFlashFlg)
                                  F_ShowAge();
                                break;
				//========
				case	2:
                                  F_ShowStringMove(midM13);		//	ENTER TARGET HEART RATE	
                                  F_ShowTime();
                                  F_ShowDis();
                                  F_ShowCal();
                                  if(SetModeFlashFlg)
                                    F_ShowThrSet();		
                                  break;	
                                  //========
                                  case	3:
                                    F_ShowStringMove(midM11);		//	ENTER WORKOUT TIME
                                    F_ShowDis();
                                    F_ShowCal();
                                    F_ShowPulse();
                                    if(SetModeFlashFlg)
                                      F_ShowTime();
                                    break;		
                                    //========
                                    case	4:
                                      F_ShowStringMove(midM08);		//	ENTER WORKOUT DISTANCE
                                      F_ShowTime();
                                      F_ShowCal();
                                      F_ShowPulse();
                                      if(SetModeFlashFlg)
					F_ShowDis();
                                      break;	
                                      //========
                                      case	5:
                                        F_ShowStringMove(midM10);		//	ENTER WORKOUT CALORIES
                                        F_ShowTime();
                                        F_ShowDis();
                                        F_ShowPulse();
                                        if(SetModeFlashFlg)
                                          F_ShowCal();
					break;	
                          }
                          break;
                          //============
  }
  R_Seg[43] |= 0x04;			// 3 <
  F_ShowLube();	
}
//===================================================
void	F_TargetIncSpdShowCount(void)
{
    unsigned	char	i,SpeedTemp,Porg=0;
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
      if(R_CholeIncSpdMode==2)
        F_ChangeGraphInc(i,T_ProgInc[Porg][i]+1);
      else
      {		
        SpeedTemp=F_TargetSpdCount(T_ProgSpeed[Porg][i]);
        F_ChangeGraphSpeed(i,SpeedTemp);
      }
    }
}
//=========================
unsigned char F_TargetSpdCount(unsigned	char SpeedData)
{
    unsigned	char	SpeedTemp;
    SpeedTemp=(SpeedData*R_TargetSpd)/100;
    if(SpeedTemp<R_SpeedMin)
      SpeedTemp=R_SpeedMin;	
    return	SpeedTemp;
}
//===================================================
//
//===================================================
void    F_ProgSetInit(void)
{
  R_SysMode=ProgSetModeVal;
  //===============
  switch(R_PorgMode)
  {
    case	ManualVal:
      case	Hrc1Val:
        case	Hrc2Val:				
          R_TimeH=0;
          break;
          //============
  default :
    R_TimeH=TimeHDefVal;
    break;
  }
  if(ChangeUnitFlg==1)
    R_TargetSpd=TargetMileVal;		//  英制
  else
    R_TargetSpd=TargetKmVal;
  R_Calorie=0;
  R_Distance=0;	
  R_Dist0=0;
  R_Dist1=0;
  R_MileDisCount=0;
  R_Thr=0;
  FristThrSetFlg=0;
  R_TimeL=0;
  R_StringChangeTime=0;
  //===============
  R_CholeIncSpdMode=0;
  R_WarkUpCoolDownMode=WarkUpVal;
  R_SportMode=SportNormalVal;
  R_Mode=0;
  R_Age=AgeDefVal;                //  預設年齡
  ChangeSpdIncProgFlg=0;
  F_StringInit();
}
//=======================================
// 暫停及設定模式下未按鍵，5分鐘進入Idle
//=======================================
void  F_IdleTime(void)
{
    R_IdleTime++;
    if(R_IdleTime>300)
    {
      R_IdleTime=0;	
      F_IdleRam_init();	
    }
}