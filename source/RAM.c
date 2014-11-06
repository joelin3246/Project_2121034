
/*
BIT_CHAR Flags0;
BIT_CHAR Flags1;
BIT_CHAR Flags2;
BIT_CHAR Flags3;
BIT_CHAR Flags4;
BIT_CHAR Flags5;
*/
union{
  unsigned char byte;
  struct{
    unsigned b0:1;
    unsigned b1:1;
    unsigned b2:1;
    unsigned b3:1;
    unsigned b4:1;
    unsigned b5:1;
    unsigned b6:1;
    unsigned b7:1;
  };
}Flags0;

union{
  unsigned char byte;
  struct{
    unsigned b0:1;
    unsigned b1:1;
    unsigned b2:1;
    unsigned b3:1;
    unsigned b4:1;
    unsigned b5:1;
    unsigned b6:1;
    unsigned b7:1;
  };
}Flags1;

union{
  unsigned char byte;
  struct{
    unsigned b0:1;
    unsigned b1:1;
    unsigned b2:1;
    unsigned b3:1;
    unsigned b4:1;
    unsigned b5:1;
    unsigned b6:1;
    unsigned b7:1;
  };
}Flags2;

union{
  unsigned char byte;
  struct{
    unsigned b0:1;
    unsigned b1:1;
    unsigned b2:1;
    unsigned b3:1;
    unsigned b4:1;
    unsigned b5:1;
    unsigned b6:1;
    unsigned b7:1;
  };
}Flags3;

union{
  unsigned char byte;
  struct{
    unsigned b0:1;
    unsigned b1:1;
    unsigned b2:1;
    unsigned b3:1;
    unsigned b4:1;
    unsigned b5:1;
    unsigned b6:1;
    unsigned b7:1;
  };
}Flags4;

union{
  unsigned char byte;
  struct{
    unsigned b0:1;
    unsigned b1:1;
    unsigned b2:1;
    unsigned b3:1;
    unsigned b4:1;
    unsigned b5:1;
    unsigned b6:1;
    unsigned b7:1;
  };
}Flags5;


unsigned char   R_TimeBase,R_Time10msBase;
unsigned char   R_SetModeWait,R_SetModeFlashCnt,R_SetModeFlashCntTemp;
unsigned char   R_DisplayCnt;
unsigned int    R_IdleTime,R_SleepTime;
//================
//      LED RAM
unsigned char   R_Seg[56],R_LedSeg,R_LedSegBuf,R_LedScanAdr;
unsigned char   R_TimeH,R_TimeL,R_TimeHBuf;
unsigned char   R_Dist0,R_Dist1,R_TrackCnt,R_LapsDis1,R_Laps;
unsigned int    R_Calorie,R_Distance,R_MileDisCount;
unsigned int    R_KcalBye1,R_TrackDis,R_LapsDis;
//================
//      Prog圖形
unsigned char   R_ShowSpeedProg[30],R_ShowIncProg[30],R_User_SetSpeed,R_User_SetInc;
unsigned char   R_ProgramIndex,R_ProgAdr;
unsigned int    R_ProgTimeBase,R_ProgTime;
unsigned int    R_Weight;
unsigned char   R_Age;
//================
//	字串
unsigned char   R_StringMoveTime,R_StringChangeTime;
unsigned int    R_StringMax,R_StringStartAdr;
//================
//      SaveProg
unsigned char   R_SaveSpeedProg[30],R_SaveIncProg[30];
//================
//SysMode	Ram											
unsigned char   R_SysMode,R_Mode,R_SportMode,R_PorgMode,R_WarkUpCoolDownMode,R_ErrData;
unsigned char	R_SysStartTime,R_CholeIncSpdMode;
unsigned char	R_CountDownCnt;
//================
//Key Ram	
unsigned char	KeyRam,KeyRamBak,KeyCode,KeyCnt,R_NoKeyCnt,R_LongFastKeyCnt;
unsigned char	R_LongKeyStopBz;
unsigned long	R_ScanKeyTemp;
unsigned char	R_ScanKey[3],R_ScanKeyBuf[3];
//================
//BZ Ram
unsigned char	R_BzCnt,R_BzWait;
unsigned char	R_BzControlCnt;
//===================
//揚升
unsigned char   R_IncNumAd,R_IncNumAdBuf,R_IncNumDetect;
unsigned char   R_IncMaxAd,R_IncMinAd,R_IncCarryAd;
unsigned char   R_RelayWaitTime;
unsigned char   R_IncStartCnt;
unsigned char   R_IncAutoTemp1,R_IncAutoTemp2;
unsigned char   R_IncAutoAd;
unsigned char   R_IncErrAd;
unsigned int    R_IncErrTime;
unsigned char   R_IncAutoTime,R_IncAutoCnt;
//==================
//CheckSpeedIncline
unsigned char   R_SpeedNum,R_SpeedBuf,R_SpeedErrTime;
unsigned char   R_SpeedMax,R_SpeedMin,R_TargetSpd;
unsigned char   R_IncNum,R_IncBuf;
unsigned char   R_IncMax,R_IncNumAd;
unsigned int    R_WheelSize;
//==================
//Pluse
unsigned int    R_Plusecount;
unsigned char	R_PluseTemp,R_Pluse,R_PluOld;
unsigned char	R_pluseIndex;
unsigned char	R_pubf[4];
unsigned char	R_HeartPluseWidth;
//WPluse
unsigned int	R_W_Plusecount;
unsigned char	R_W_PluseTemp,R_W_Pluse,R_W_PluOld;
unsigned char	R_W_pluseIndex;
unsigned char	R_W_pubf[4];
unsigned char	R_Heart_W_PluseWidth;
unsigned char   R_W_DelayTime;
//SafeKey
unsigned char   R_Safety;
//===================
//	SpeedDet
unsigned char   R_SpeedDetectTime,R_PwmLowSpeed,R_SpeedAutoCnt,R_LowSpeedCntDelay;
unsigned int    R_SpeedCnt,R_SpeedCntBuf,R_SpdFbTime;
unsigned int    R_SpeedPwmCnt,R_SpeedPwmCntSave;
//===================
//	工程模式
unsigned char   R_EngFlashAdr,R_KeyTest;
unsigned int    R_EngFlashCnt;
//===================
//	Hrc
unsigned char   R_HrcSpdIncTime,R_HrcNoPulse,R_Thr,R_ThrBuf,R_ThrDelayTime;

//===================
// 總里程 總時間
unsigned char   R_EeSaveTime,R_ClearTotal_TimeDis;
unsigned long   R_TotalTime,R_TotalDis;
unsigned int    R_TotalLube;

unsigned int    R_SpdFbTimeEnd;

volatile unsigned short EepromDelayTimeCnt;