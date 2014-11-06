
typedef unsigned char byte;
typedef unsigned int word;
typedef unsigned long dword;

typedef union 
 {
   word w;
   struct 
	 {
     byte high,low;
   } b;
 } TWREG;
 
typedef union 
   {
		byte BYTE;
      struct 
      {
        unsigned  B0  :1;   /* Compare Function Value 0 */
        unsigned  B1  :1;   /* Compare Function Value 1 */
        unsigned  B2  :1;   /* Compare Function Value 2 */
        unsigned  B3  :1;   /* Compare Function Value 3 */
        unsigned  B4  :1;   /* Compare Function Value 4 */
        unsigned  B5  :1;   /* Compare Function Value 5 */
        unsigned  B6  :1;   /* Compare Function Value 6 */
        unsigned  B7  :1;   /* Compare Function Value 7 */
      } Bits;
    } BIT_CHAR; 

extern BIT_CHAR Flags0;
extern BIT_CHAR Flags1;
extern BIT_CHAR Flags2;
extern BIT_CHAR Flags3;
extern BIT_CHAR Flags4;
extern BIT_CHAR Flags5;


#define T10msFlg                Flags0.Bits.B0
#define T20msFlg                Flags0.Bits.B1
#define T40msFlg                Flags0.Bits.B2
#define T80msFlg                Flags0.Bits.B3
#define ShowLcdTimeFlg          Flags0.Bits.B4
#define T160msFlg               Flags0.Bits.B5
#define T500msFlg               Flags0.Bits.B6
#define T1sFlg                  Flags0.Bits.B7
	//==============
#define FlashFlg                Flags1.Bits.B0
#define LongBzFlg               Flags1.Bits.B1
#define StringStartFlg          Flags1.Bits.B2
#define StringFirstFlg          Flags1.Bits.B3
#define SetModeFlashFlg         Flags1.Bits.B4
#define ShowHiByeFlg            Flags1.Bits.B5
#define ChangeSpdIncProgFlg     Flags1.Bits.B6
#define ScanKyeEndFlg           Flags1.Bits.B7
	//==============
#define SpeedAutoFlg            Flags2.Bits.B0
#define FriestSpeedFlg          Flags2.Bits.B1
#define SpeedStatusFlg          Flags2.Bits.B2
#define MotoUpDownFlg           Flags2.Bits.B3
#define SpdFbTimeFlg            Flags2.Bits.B4
#define SpeedMoveFlg            Flags2.Bits.B5
#define SportEndBzFlg           Flags2.Bits.B6
	//==============
//      心跳偵測相關旗標
#define Heart_W_PluseFlg        Flags3.Bits.B0
#define W_Pu1intFlg             Flags3.Bits.B1
#define HeartPluseFlg           Flags3.Bits.B3
#define Pu1intFlg               Flags3.Bits.B4
#define HandHeartDetectionFlg   Flags3.Bits.B5
#define wHeartDetectionFlg      Flags3.Bits.B6
#define ShowAcDcMotorFlg        Flags3.Bits.B7

	//================
//      揚升相關旗標
#define IncSetFlag              Flags4.Bits.B0
#define IncUpDownFlg            Flags4.Bits.B1	
#define RelayUpDownFlg          Flags4.Bits.B2	
#define IncErrFlg               Flags4.Bits.B3
#define IncAutoFlg          	Flags4.Bits.B4
#define IncStartDetectFlg   	Flags4.Bits.B5
#define IncStopFlg          	Flags4.Bits.B6
#define AcDcMotorFlg            Flags4.Bits.B7
	//================
#define TimeStatusFlg           Flags5.Bits.B0
#define CalStatusFlg            Flags5.Bits.B1
#define DisStatusFlg            Flags5.Bits.B2
#define HrcSpdIncFlg            Flags5.Bits.B3
#define ChangeUnitFlg           Flags5.Bits.B4
#define SafetyOnFg              Flags5.Bits.B5
#define CoolDownStartFlg        Flags5.Bits.B6
#define FristThrSetFlg          Flags5.Bits.B7

//=========================================================
extern  unsigned char  const    MatrixAsciiCode[59][6];
extern  const unsigned char T_ProgSpeed[5][30];
extern	const unsigned char T_ProgInc[][30];
extern	const unsigned	char T_TrackRam[64][2];

extern	const	unsigned char	T_WarkUpSpeedTabe[];
extern	const	unsigned char	T_CoolDownSpeedTabe[];
//==========================================================
//
//
//==========================================================
#define setbit(val, bitn) (val |=(1<<(bitn))) 
#define clrbit(val, bitn) (val&=~(1<<(bitn))) 

#define BitSet(A, B)    (A |= (B))
#define BitClr(A, B)    (A &= ~(B))

#define BIT0	0x01
#define BIT1	0x02
#define BIT2	0x04
#define BIT3	0x08
#define BIT4	0x10
#define BIT5	0x20
#define BIT6	0x40
#define BIT7	0x80

extern	unsigned char R_TimeBase,R_Time10msBase;
extern	unsigned char R_SetModeWait,R_SetModeFlashCnt,R_SetModeFlashCntTemp;
extern	unsigned char R_DisplayCnt;
extern	unsigned int	R_IdleTime,R_SleepTime;
//================
//LED RAM
extern	unsigned char   R_Seg[56],R_LedSeg,R_LedSegBuf,R_LedScanAdr;
extern	unsigned char   R_TimeH,R_TimeL,R_TimeHBuf;
extern	unsigned char   R_Dist0,R_Dist1,R_TrackCnt,R_LapsDis1,R_Laps;
extern	unsigned int    R_Calorie,R_Distance,R_MileDisCount;
extern	unsigned int    R_KcalBye1,R_TrackDis,R_LapsDis;
//================
//	Prog圖形
extern	unsigned char   R_ShowSpeedProg[30],R_ShowIncProg[30],R_User_SetSpeed,R_User_SetInc;
extern	unsigned char   R_ProgramIndex,R_ProgAdr;
extern	unsigned int    R_ProgTimeBase,R_ProgTime;
extern	unsigned int    R_Weight;
extern	unsigned char   R_Age;
//================
//	字串
extern	unsigned char   R_StringMoveTime,R_StringChangeTime;
extern	unsigned int    R_StringMax,R_StringStartAdr;
//================
//	SaveProg
extern	unsigned char   R_SaveSpeedProg[30],R_SaveIncProg[30];
//================
//SysMode	Ram											
extern	unsigned char   R_SysMode,R_Mode,R_SportMode,R_PorgMode,R_WarkUpCoolDownMode,R_ErrData;
extern	unsigned char   R_SysStartTime,R_CholeIncSpdMode;
extern	unsigned char   R_CountDownCnt;
//================
//Key Ram	
extern	unsigned char   KeyRam,KeyRamBak,KeyCode,KeyCnt,R_NoKeyCnt,R_LongFastKeyCnt;
extern	unsigned char	R_LongKeyStopBz;
extern	unsigned long	R_ScanKeyTemp;
extern	unsigned char	R_ScanKey[3],R_ScanKeyBuf[3];
//================
//BZ Ram
extern	unsigned char	R_BzCnt,R_BzWait;
extern	unsigned char	R_BzControlCnt;
//===================
//揚升
extern	unsigned char   R_IncNumAd,R_IncNumAdBuf,R_IncNumDetect;
extern	unsigned char   R_IncMaxAd,R_IncMinAd,R_IncCarryAd;
extern	unsigned char   R_RelayWaitTime;
extern	unsigned char   R_IncStartCnt;
extern	unsigned char   R_IncAutoTemp1,R_IncAutoTemp2;
extern	unsigned char   R_IncAutoAd;
extern	unsigned char   R_IncErrAd;
extern	unsigned int    R_IncErrTime;
extern	unsigned char   R_IncAutoTime,R_IncAutoCnt;
//==================
//CheckSpeedIncline
extern	unsigned char   R_SpeedNum,R_SpeedBuf,R_SpeedErrTime;
extern	unsigned char   R_SpeedMax,R_SpeedMin,R_TargetSpd;
extern	unsigned char   R_IncNum,R_IncBuf;
extern	unsigned char   R_IncMax,R_IncNumAd;
extern	unsigned int    R_WheelSize;
//==================
//Pluse
extern	unsigned int	R_Plusecount;
extern	unsigned char	R_PluseTemp,R_Pluse,R_PluOld;
extern	unsigned char	R_pluseIndex;
extern	unsigned char	R_pubf[4];
extern	unsigned char	R_HeartPluseWidth;
//WPluse
extern	unsigned int	R_W_Plusecount;
extern	unsigned char   R_W_PluseTemp,R_W_Pluse,R_W_PluOld;
extern	unsigned char	R_W_pluseIndex;
extern	unsigned char	R_W_pubf[4];
extern	unsigned char	R_Heart_W_PluseWidth;
extern	unsigned char	R_W_DelayTime;
//SafeKey
extern	unsigned char   R_Safety;
//===================
//	SpeedDet
extern	unsigned char   R_SpeedDetectTime,R_PwmLowSpeed,R_SpeedAutoCnt,R_LowSpeedCntDelay;
extern	unsigned int    R_SpeedCnt,R_SpeedCntBuf,R_SpdFbTime;
extern	unsigned int    R_SpeedPwmCnt,R_SpeedPwmCntSave;
//===================
//	工程模式
extern	unsigned char   R_EngFlashAdr,R_KeyTest;
extern	unsigned int    R_EngFlashCnt;
//===================
//	Hrc
extern	unsigned char   R_HrcSpdIncTime,R_HrcNoPulse,R_Thr,R_ThrBuf,R_ThrDelayTime;

//===================
// 總里程 總時間
extern	unsigned char   R_EeSaveTime,R_ClearTotal_TimeDis;
extern	unsigned long   R_TotalTime,R_TotalDis;
extern	unsigned int    R_TotalLube;

extern	unsigned int    R_SpdFbTimeEnd;

extern	volatile unsigned short EepromDelayTimeCnt;