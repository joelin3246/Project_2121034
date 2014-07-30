// ===========================================================
//	
// ===========================================================


#ifndef ___connect_H__
#define ___connect_H__

#include "stm32f0xx.h"
#include "ram.h"
#include "Display.h"
//====================
//系統模式參數設定
#define SysStartModeVal         0
#define ProgSetModeVal          1
#define SysCountDownModeVal     2
#define ManualSportModeVal      3
#define ProgSportModeVal        4
#define UserSportModeVal        5
#define HrcSportModeVal         6
#define SysSportPassModeVal     7
#define SysSportModeEndVal      8
#define SysErrModeVal           9
#define EngMode1Val             10
#define EngMode2Val             11
#define EngMode3Val             12
#define EngMode4Val             13
#define SysSleepModeVal         14
//=====================================
//運動模式參數設定
#define	ManualVal               0
#define	Prog1Val                1
#define	Prog2Val                2
#define	Prog3Val                3
#define	Prog4Val                4
#define	Prog5Val                5
#define	User1Val                6
#define	User2Val                7
#define	User3Val                8
#define	Hrc1Val                 9
#define	Hrc2Val                 10
#define	Hrc3Val                 11
#define	TimeModeVal             12
#define	CalModeVal              13
#define	DisModeVal              14
//==========================
//按鍵參數設定
#define start_stop_KeyVal       9
#define Mode_KeyVal             4
#define Set_KeyVal              1
#define Enter_KeyVal            12
#define InclineUp_KeyVal        3
#define InclineDown_KeyVal      2
#define HandInclineUp_KeyVal    18
#define HandInclineDown_KeyVal  17
#define SpeedUp_KeyVal          11
#define SpeedDown_KeyVal        10
#define HandSpeedUp_KeyVal      20
#define HandSpeedDown_KeyVal    19


#define QuickInc_2_KeyVal       23
#define QuickInc_4_KeyVal       24
#define QuickInc_6_KeyVal       15
#define QuickInc_8_KeyVal       16
#define QuickInc_10_KeyVal      7
#define QuickInc_12_KeyVal      8

#define QuickSpd_1_KeyVal       21
#define QuickSpd_4_KeyVal       22
#define QuickSpd_7_KeyVal       13
#define QuickSpd_10_KeyVal      14
#define QuickSpd_13_KeyVal      5
#define QuickSpd_16_KeyVal      6

#define Eng1_KeyVal             25	//	Mode_KeyVal + start_stop_Key
#define Eng2_KeyVal             28	//	start_stop_Key + SpeedUp_KeyVal // 與承認書上的工程模式名稱不同
#define Eng3_KeyVal             27	//	Mode_KeyVal + SpeedDown_KeyVal
#define Eng4_KeyVal             26	//	ModeKey + SpeedUp_KeyVal
#define EepromClear_KeyVal      29      //      Set_KeyVal + start_stop_KeyVal
#define LongSet_KeyVal          30	//      長按
#define LongMode_KeyVal         31	//      長按

//LCD FONT
#define	blankVal	255
//================
//  WarkUpCoolDownMode
#define WarkUpVal         0
#define SportVal          1
#define CoolDownVal       2
//======================================
//  修改機種需要同步修改識別碼
#define O_A2121034      1		//	//	1_212103400  0_212103401
//	212103400	工易、11A990200 eup控制器
//	212103401	寧茂 eup控制器

// Eeprom 識別碼
#define EepromVer_1             0xA5    //  位址 0xFA
#define EepromVer_2             0x10    //  位址 0xFB	212101800 取後面6碼 
#define EepromVer_3             0x34    //  位址 0xFC
#define EepromVer_4             0x00    //  位址 0xFC
// Eeprom 位址 
#define EE_SpeedMaxKm           0x00
#define EE_SpeedMinKm           0x01
#define EE_SpeedMaxMile   	0x02
#define EE_SpeedMinMile   	0x03
#define EE_Unit                 0x04
#define EE_Age                  0x05
#define EE_IncMax               0x06
#define EE_IncUpDown            0x07
#define EE_IncMaxAd             0x08
#define EE_IncMinAd             0x09
#define EE_IncCarryAd           0x0A
#define EE_WheelSize_L          0x0B
#define EE_WheelSize_H          0x0C
#define EE_Wight_L              0x0D
#define EE_Wight_H              0x0E
#define EE_PwmLowSpeed          0x0F
#define EE_TotalTimeBye_1       0x10
#define EE_TotalTimeBye_2       0x11
#define EE_TotalTimeBye_3       0x12
#define EE_TotalTimeBye_4       0x13
#define EE_TotalDisBye_1        0x14
#define EE_TotalDisBye_2        0x15
#define EE_TotalDisBye_3        0x16
#define EE_TotalDisBye_4        0x17
#define EE_TotalLubeBye_L       0x18
#define EE_TotalLubeBye_H       0x19
#define EE_SaveUserInit         0x1A
#define EE_AcDcMotor   			0x1B		

#define UserStartAdr          	0x30
#define User_1_SpeedAdrVal    	UserStartAdr 
#define User_1_IncAdrVal      	UserStartAdr+(30*1) 
#define User_2_SpeedAdrVal    	UserStartAdr+(30*2) 
#define User_2_IncAdrVal      	UserStartAdr+(30*3)
#define User_3_SpeedAdrVal    	UserStartAdr+(30*4) 
#define User_3_IncAdrVal      	UserStartAdr+(30*5)

//==========================
//  預設值
//  年齡
#define AgeDefVal       35
#define AgeMaxVal       99		
#define AgeMinVal       10
//  體重
#define WeightKgDefVal	70
#define WeightKgMaxVal	180				
#define WeightKgMinVal	30

#define WeightLBDefVal	150
#define WeightLBMaxVal	400				
#define WeightLBMinVal	40
//  CountDown
#define CountDownVal    3
//  Time
#define TimeHDefVal       30
#define TimeLDefVal       0
#define	SetTimeMaxVal     99
#define	SetTimeMinVal     10
//  Calorie
#define CalDefVal       1000
#define	SetCalMaxVal  	9999    
#define	SetCalMinVal  	1
//  Dis
#define DistHDefVal     500
#define	SetDisMaxVal    9990
#define	SetDisMinVal    10
//  Speed
#define	SpeedKmMaxVal	  180
#define	SpeedKmMinVal	  10
#define	SpeedMileMaxVal   111
#define	SpeedMileMinVal   6

#define	SportSpeedKmVal   	24
#define	SportSpeedMileVal       14

//      預設 單位
#define	UnitVal     0           //  0 英制  1 公制
//      加油提示時間  2000公里
#define	LubeVal   20000         // 2000*10

//  Incline
#define IncMaxVal     16
#define IncDefVal     1
#define	IncMinVal     0         //	負揚升
//
#define SportNormalVal          0
#define SportTimeEndVal         1
#define SportDisEndVal          2
#define SportCalEndVal          3
//	目標心跳
#define ThrMaxVal		200
#define ThrMinVal		60

#define TargetMileVal		62
#define TargetKmVal             100

//======================================================


//================================
//
//================================
void    F_Sleep_Init(void);
void	F_Safety(void);
void	F_Rest(void);
void	F_Time(void);
void	F_ClearTimeBase(void);
void    F_LedKeyScan(void);
void	F_ShowFlash(void);
void	C_delay(unsigned int count);
void  F_DisplayTime(void);
//=============
void	F_SPI_init1(void);
void	F_UartInt(void);
void  F_TIM2_init(void);
void	F_BackLight(unsigned char data);
void	F_EupControl(unsigned char data);
void  F_GPIO_init(void);
void  F_IdleRam_init(void);
void	CLK_Init(void);
//===================================================
void	F_SysStartMode(void);
void	F_SysStartTime(void);
void	F_SysStartMode_Lcd(void);
void	F_SysStartMode_Key1(void);
void	F_SysStartMode_Key2(void);
void	F_SysStartMode_Key3(void);
		//=============
void	F_IdleMode(void);
void	F_IdleModeFlash(void);
void	F_IdleMode_Key(void);
//=======================
void	F_ProgSetMode(void);
void  F_ProgSetMode_key(void);
void	F_LongSetKey(void);
void	F_InclineUpSetKey(void);
void	F_InclineDownSetKey(void);
void	F_SetKey(void);
void  F_EnterSetKey(void);
void  F_ModeSetKey(void);
void  F_StartStopSetKey(void);
void	F_SportInit(void);
unsigned	char	F_FristSportSpeed(void);
void  F_SpeedUpSetKey(void);
void  F_SpeedDownSetKey(void);
void    F_IncQuickKey(unsigned char Data);
void	F_IncSetControlUp(void);
void	F_IncSetControlDown(void);
void  F_TimeStatus(void);
void	F_QuickSetUserInc(unsigned char Data);
void	F_SetUserIncUp(void);
void	F_SetUserIncDown(void);
void	F_QuickSetUserSpeed(unsigned char Data);
void	F_SetUserSpeedUp(void);
void	F_SetUserSpeedDown(void);
void  F_AgeSetUp(void);
void  F_AgeSetDown(void);
void  F_TargetSpdSetUp(void);
void  F_TargetSpdSetDown(void);
void	F_TimeSetUp(void);
void	F_DisSetUp(void);
void	F_CalSetUp(void);
void	F_ThrSetUp(void);
void	F_TimeSetDown(void);
void	F_DisSetDown(void);
void	F_CalSetDown(void);
void	F_ThrSetDown(void);
void  F_ChangeGraphSpeed(unsigned	char	Adr,unsigned	char	SpeedData);
void  F_GraphSpeedInc(void);
void  F_ChangeGraphInc(unsigned	char	Adr,unsigned	char	IncData);
void  F_ProgSetMode_Lcd(void);
void	F_TargetIncSpdShowCount(void);
unsigned	char	F_TargetSpdCount(unsigned	char	SpeedData);
void	F_ProgSetInit(void);
void  F_IdleTime(void);
//========================
void	F_SysSleepMode(void);
void	F_SysSleepMode_Key(void);
void  F_SleepTime(void);
//========================
void	F_SysCountDownMode(void);
void	F_SysCountDownMode_lcd(void);
void	F_CountDown(void);
void	F_CountDownModeInit(void);
//========================
void	F_ManualSportMode(void);
void	F_ManualSportMode_lcd(void);
void	F_ManualSportMode_key(void);
void    F_MenualSpdQuickKey(unsigned char Data);
void	F_SpdSetControlUp(void);
void	F_SpdSetControlDown(void);
void	F_SportStartSet(void);
void	F_SportStartSet(void);
//========================
void  F_ProgSportMode(void);
void	F_ProgTimeCount(void);
void	F_ReadProgData(void);
void  F_WarkUpTime(void);
void  F_ProgWarkUpEnd(void);
void  F_ProgSportEnd(void);
void  F_ProgCoolDownEnd(void);
void  F_ReadWarkUpProg(void);
void  F_ProgSportMode_Key(void);
void    F_ProgSportModeIncUp(void);
void    F_ProgSportModeIncDown(void);
void    F_ProgSportIncQuickKey(unsigned char Data);
void    F_ProgSportSpdQuickKey(unsigned char Data);
void	F_ChangeShowSpeed(void);
void	F_ChangeShowInc(void);
void	F_PorgWriteSpeed(void);
void  F_ProgSportMode_Lcd(void);
//========================
void	F_SysSportPassMode(void);
void	F_SysSportPassMode_Key(void);
void    F_SysSportPassModeIncQuick(unsigned char Data);
void    F_SysSportPassModeIncUp(void);
void    F_SysSportPassModeIncDown(void);
void	F_SysSportPassMode_lcd(void);
void	F_PassModeInit(void);
//========================
void	F_SysSportModeEnd(void);
void	F_SysSportModeEnd_Key(void);
void	F_SysSportModeEnd_Lcd(void);
void	F_SportModeEndInit(void);
//========================
void	F_SysErrMode(void);
void	F_SysErrMode_Lcd(void);
//========================
void  F_UserSportMode(void);
void  F_UserSportMode_Key(void);
void  F_UserSportMode_Lcd(void);
//========================
void  F_HrcSportMode(void);
void  F_HrcSpdIncCount(void);
void  F_HrcSpeedShowUp(unsigned char  Speed);
void  F_HrcSpeedShowDown(unsigned char  Speed);
void  F_IncControlUp(unsigned char  inc);
void  F_IncControlDown(unsigned char  inc);
void  F_HrcSportMode_Key(void);
void    F_HrcSportModeIncUp(void);
void    F_HrcSportModeIncDown(void);
void  F_HrcSportMode_Lcd(void);
//====================================================
//Key
void  F_InitialKB_GPIO(void);
void	F_CheckGetKey(void);
void	F_ReadKey(void);
void  F_LongFast(void);
void F_ERP_KBSet(void);
//============
//Bz
void	F_SportBzControl(void);
void	F_BzOn(void);
//============
//Lcd Set
unsigned char	F_LcdNumberRam(unsigned	char i,unsigned	char j);
unsigned char	F_LcdNumberBit(unsigned	char i,unsigned	char j);
void  F_ShowMatrixLcd(unsigned char adr,unsigned char data);
void  F_Show_8_Lcd(unsigned char adr3,unsigned char adr2,unsigned char adr1,unsigned int data);
void	F_Show_8_FontLcd(unsigned char adr,unsigned char data);
void	F_AllLCDRam(unsigned char data);
void	F_Display(void);
//===========
//	顯示
void	F_ShowIncl(void);
void  F_ShowDis(void);
void  F_ShowCal(void);
void	F_ShowTime(void);
void	F_ShowSpeed(unsigned	char	SpeedData);
void	F_ShowInc(unsigned	char	IncData);
void  F_ShowSpeedIncProg(void);
unsigned  char  F_SpeedIncProg(unsigned char  ProgData);
void  F_ShowProfileFlash(void);
void	F_ShowTrackLed(void);
void	F_ShowPulse(void);
void	F_ShowThrSet(void);
void  F_ShowSportThr(unsigned char  Pluse);
void	F_ShowLaps(void);
void	F_ShowHrc1HeartFlash(void);
void	F_ShowHrc2HeartFlash(void);
void	F_ShowNoHeart(void);
void	F_ShowAge(void);
void	F_ShowVer(void);
void  F_ShowTotalTime(void);
void  F_ShowTotalDis(void);
void	ShowIncSpdPorgLed(void);
void	F_ShowPowerLed(void);
void	F_ShowWheelSize(void);
void	F_ShowLube(void);
//===========
//字串
void  F_ShowStringMove(unsigned  char  String);
void  F_StringMoveTime(void);
void	F_StringInit(void);
unsigned	char	F_MessageP(unsigned	char	StringAdr,unsigned	char	StringData);
void	F_ShowMatrixPicture(unsigned	char	LcdStartAdr,unsigned	char	StringAdr);
//============
//HT1625
void	F_1625CS_1(unsigned char data);
void	F_1625WR(unsigned char data);
void	F_1625DATA(unsigned char data);
void	F_HT1620Initial(void);
void	F_1625ID(unsigned char  a,unsigned char  b,unsigned char  c);
void	F_1625Com(unsigned char ch);
void	F_HT1620Write(unsigned char data);
void	F_HT1620Address(unsigned char adr);
//============
//Pluse
void    F_InitialPulse_GPIO(void);
void	F_Pluse1sub(void);
void	F_Pluse2sub(void);
void	F_PluseFunction1(void);
void	F_PluseFunction2(void);
//============
//I2C
void    F_InitialEEPROM_GPIO(void);
void    F_EUP_EEPROM_GPIO(void);
void	F_SDA(unsigned char data);
void	F_SCL(unsigned char data);
void	I2C_Start(void);
void F_EepromDelayTime(void);
void	I2C_Stop(void);
void	I2C_Clock(void);
void	Write_I2C_Byte(unsigned char byte);
unsigned char Read_I2C_Byte(void);
void	Write_I2C_Control(unsigned char D_Code,unsigned char H_ADD,unsigned char RW);
void	EE_Write(unsigned char WriteAddr8,unsigned char data8);
unsigned char EE_Read(unsigned char ReadAddr8);
unsigned  char  F_ReadFlg(unsigned  char  ReadDataAdr);
unsigned  int F_Read2Byte(unsigned  char  ReadDataAdr);
unsigned  long  F_Read4Byte(unsigned  char  ReadDataAdr);
void  F_Write2Byte(unsigned char  WriteDataAdr,unsigned int Data);
void  F_Write4Byte(unsigned char  WriteDataAdr,unsigned long  Data);
void	F_EE_init(void);
void  F_EepromNoDataInit(void);
void  F_ReadProg_EE(void);
void  F_EepromClear_2(void);
void  F_EepromClear_3(void);
void  F_EepromClear_4(void);
void	F_User_Init(unsigned  char  EE_UserSpeedAdr,unsigned  char  EE_UserIncAdr);
void  F_ReadUserProfile(unsigned  char  EE_UserSpeedAdr,unsigned  char  EE_UserIncAdr);
void	F_UserCholeIncSpd(unsigned	char	EE_UserSpeedAdr,unsigned	char	EE_UserIncAdr);
//==============
//	Function
void  F_ShowFlash(void);
void  F_ShowFlashInt(void);
void	F_TimeCount(void);
void	F_TimeCountEnd(void);
void	F_Calorie(void);
void	F_DisttanceComputing(void);
void	F_Playground(void);
void	F_TotalTimeDisCount(void);
void  F_SaveTotalTimeDis(void);
unsigned	int	F_ChangeKmToMile(unsigned	int	Data);
unsigned	int	F_ChangeMileToKm(unsigned	int	Data);
//======================
//	速度偵測
void    F_InitialSPD_GPIO(void);
void	F_PwmCntSend(void);
unsigned	char	F_SpeedCalculate(void);
void	F_SpeedFeedback(void);
void	F_SpeedAutoInit(void);
void	F_SpeedAuto(unsigned	char	Speed);
void	F_SpeedFirstInit(void);
void	F_SpeedControl(unsigned	char	Speed);
void	F_SpeedSwCotrol(unsigned	char	Data);
//======================
//	揚升
void    F_InitialIncline_Gpio(void);
void    F_InitialADC(void);
void  F_IncTimeCnt(void);
void  F_IncludeProcess(void);
void  F_IncControl(void);
void  F_RelayMoveUp(void);
void  F_RelayMoveDown(void);
void  F_RelayMoveStop(void);
void  F_IncErrDetection(void);
void  F_IncAd(unsigned	char  Data);
void  F_IncAuto(void);
void	F_IncIoUpControl(unsigned	char	Data);
void	F_IncIoDownControl(unsigned	char	Data);
//========================
void	F_EngMode1(void);
void	F_EngFlash(void);
void	F_EngMode1_Key(void);
void	F_EngMode1_Key1(void);
void	F_EngMode1_Key2(void);
void	F_EngMode1_Key3(void);
void	F_EngMode1_Key4(void);
void	F_EngMode1_Key5(void);
void	F_EngMode1_Key6(void);
void	F_EngMode1_Key7(void);
void	F_EngMode1_Lcd(void);
void	F_Eng1EntertSet(void);
void	F_Eng1SpeedUpSet(void);
void	F_Eng1SpeedDownSet(void);
//========================
void	F_EngMode2(void);
void	F_EngMode2_Key(void);
void	F_EngMode2_Lcd(void);
//========================
void	F_EngMode3(void);
void	F_EngMode3_Key1(void);
void	F_EngMode3_Key2(void);
void	F_EngMode3_Lcd(void);
void	F_LcdTest(unsigned	char	Data);
void	F_ProgTest(unsigned	char	Data);
//========================
void	F_EngMode4(void);
void	F_Eng4Test(void);
void	F_EngMode4_Key1(void);
void	F_EngMode4_Key2(void);
void	F_EngMode4_Key3(void);
void	F_EngMode4_Lcd(void);

void IWDG_Config(unsigned char timeout);
#endif	// ___connect_H__