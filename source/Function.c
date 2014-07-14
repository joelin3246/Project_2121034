#include "connect.h"
//=========================================================
//
//=========================================================
void F_Time(void)
{
    R_Time10msBase++;
    if((R_Time10msBase&0x01)==0x01)	//20ms
    {
      T20msFlg=1;
      if(SportEndBzFlg)
      {
        if(R_BzCnt!=0)
          R_BzCnt--;		
      }
      else
      {		
        if(R_BzWait>7)
        {
          R_BzWait=8;
          if(R_BzCnt!=0)
          {
            R_BzCnt--;
            if(R_BzCnt==0)
              R_BzWait=0;
          }
        }
        //==========================
        if(R_BzCnt==0x08)
        {
          R_BzWait++;
        }
        else
        {
          R_BzWait=0;
          if(R_BzCnt!=0)
          {
            R_BzCnt--;
          }
        }
      }
    }
    if((R_Time10msBase&0x03)==0x02)		//40ms
    {
      T40msFlg=1;
      
    }
    //==================================
    if((R_Time10msBase&0x07)==0x04)	//80ms
    {
      T80msFlg=1;
      
    }
    //==================================		
    if((R_Time10msBase&0x0F)==0x08)	//160ms
    {						
      T160msFlg=1;					
    }
    //==================================
    if(R_Time10msBase==50)		//500ms
    {			
      T500msFlg=1;
      LongBzFlg=0;
    }
    //==================================
    if(R_Time10msBase>99)		//1000ms
    {					
      T1sFlg=1;
      R_Time10msBase=0;	
    }
}
//=================================
void	F_ClearTimeBase(void)
{
    R_Time10msBase=0;
    T20msFlg=0;
    T40msFlg=0;
    T80msFlg=0;
    T160msFlg=0;
    T500msFlg=0;
    T1sFlg=0;		
}

//=========================
void	F_SportBzControl(void)
{
  if(SportEndBzFlg)
  {
    R_BzControlCnt++;
    switch(R_BzControlCnt)
    {
      case 1:
        R_BzCnt=0x14;
        break;
      //===========
      case 100:
        R_BzCnt=0x14;			
        break;
      //===========
      case 200:
        R_BzCnt=0x14;
        break;
    }
      if(R_BzControlCnt>240)
      {
        SportEndBzFlg=0;
      }
  }
    else
      R_BzControlCnt=0;
}
//=========================
void  F_DisplayTime(void)
{
    R_DisplayCnt++;
    if(R_DisplayCnt>7)
    {
      R_DisplayCnt=0; 
      ShowLcdTimeFlg=1;
    }
}
//=====================================================	
void  F_ShowFlash(void)
{
    R_SetModeWait++;
    if(R_SetModeWait>150)
    {
      R_SetModeWait=150;
      R_SetModeFlashCntTemp=0;
      R_SetModeFlashCnt++;
      if(R_SetModeFlashCnt>49)
      {
        R_SetModeFlashCnt=0;
        if(SetModeFlashFlg)
        {
          SetModeFlashFlg=0;
          FlashFlg=0;
        }
        else
        {
          SetModeFlashFlg=1;
          FlashFlg=1;
        }
      }
    }
    else
    {
      R_SetModeFlashCntTemp++;
      if(R_SetModeFlashCntTemp>49)
      {
        R_SetModeFlashCntTemp=0;
        if(FlashFlg)
          FlashFlg=0;
        else
          FlashFlg=1;
      }
    }
}
  //================
void F_ShowFlashInt(void)
{	
    R_SetModeFlashCnt=0;
    SetModeFlashFlg=1;
    R_SetModeWait=0;
}
//=======================================
//
//=======================================
void F_TimeCount(void)
{
  R_SleepTime=0;	
  if(TimeStatusFlg==1)
  {
    if(R_TimeL==0)
    {
      R_TimeH--;
      R_TimeL=59;
    }
    else
    {
      R_TimeL--;
      if((R_TimeL==0) && (R_TimeH==0))
      {
        if(R_SysMode==ProgSportModeVal)
        {	
          if(CoolDownStartFlg==1)
            F_ProgSportEnd();
          else
            F_TimeCountEnd();
        }
        else
          F_TimeCountEnd();
      }
    }
  }
  else
  {		//時間正數
    R_TimeL++;
    if(R_TimeL>59)
    {
      R_TimeL=0;
      R_TimeH++;
      if(R_TimeH>99)
        R_TimeH=0;
    }
  }
}
//=====================
void F_TimeCountEnd(void)
{
    R_SportMode=SportTimeEndVal;
    SportEndBzFlg=1;
    R_SpeedBuf=R_SpeedNum;
    R_IncBuf=R_IncNum;
    R_IncNum=1;                 //	揚升預設值
    R_SpeedNum=0;
    F_StringInit();
}
//========================== Calories ======================
//程式放在1秒，因速度的值是表示是時速，需在除3600
//英制:
// if speed >= 3.7 mph
//[1+(1.532*speed) + (0.0685*speed*grade)]*weight/2.2
//
// if speed <  3.7 mph 
//[1+(0.768*speed)+ (0.1370*speed*grade)]*weight/2.2, 
//
//公制: Speed =(km)/1.60932	Weight=(kg)*2.20462 以下公式為公制
// if speed >= 5.9 Km
//[1+(1.532*(speed/1.609)/10) + (0.0685*((speed/1.609)/10)*grade)]*weight 
//		因程式放在1s，而speed內的值是表示時速，因此要在除3600
//{[1+(1.532*(speed/1.609)/10) + (0.0685*((speed/1.609)/10)*grade)]*weight}/3600 
// 		if speed <  5.9 Km
//[1+((0.768*(speed/1.609)/10)+ (0.1370*((speed/1.609)/10)*grade)]*weight
//
//============================================================
void F_Calorie(void)
{
  unsigned long i,j;
  unsigned int  Cal;
  unsigned char SpeedTemp;
  if(ChangeUnitFlg==0)          // 公制
    SpeedTemp=R_SpeedNum;
    else
      SpeedTemp=F_ChangeMileToKm(R_SpeedNum);
  if(SpeedTemp>=59)
  {
    i=1532;
    j=68;
  }
  else
  {
    i=768;
    j=137;
  }
  //計算到小數點第三位 如Cal=28  表示0.028卡
  Cal=((16090+(i*SpeedTemp)+(j*SpeedTemp*R_IncNum))*R_Weight)/57924;    //57924=(3600*1609)/100
  while(Cal>0)
  {
    Cal--;	
    R_KcalBye1++;
    if(R_KcalBye1>999)          //      1卡
    {	
      R_KcalBye1=0;
      if(CalStatusFlg==1)
      {
        R_Calorie--;
        if(R_Calorie==0)
        {
          R_SportMode=SportCalEndVal;
          SportEndBzFlg=1;
          R_SpeedBuf=R_SpeedNum;
          R_IncBuf=R_IncNum;
          R_SpeedNum=0;
          F_StringInit();
        }
      }
      else
      {
        R_Calorie++;
        if(R_Calorie>9999)
          R_Calorie=0;
      }
      
    }
  }
}
//=================================================
void F_DisttanceComputing(void)
{
    unsigned char SpeedTemp;
    if(ChangeUnitFlg==0)	//	公制
      SpeedTemp=R_SpeedNum;
    else
      SpeedTemp=F_ChangeMileToKm(R_SpeedNum);
    
    R_Dist0=SpeedTemp+R_Dist0;
    while(R_Dist0>=36)
    {
      R_Dist0=R_Dist0-36;		//	1公尺
      R_Dist1++;	
      F_Playground();
      //=====================
      //        因客戶反應英制下單位計數的時間不平均，所以修改為英制下另外計算	2012/5/8
      if(ChangeUnitFlg==1)      // 2012/3/29 Chandler修改
      {   //  英制
        R_MileDisCount=R_MileDisCount+6213;
        if(R_MileDisCount>=1000000)		//	0.1 英里
        {
          R_MileDisCount=R_MileDisCount-1000000;
          if(DisStatusFlg==1)
          {
            R_Distance--;
            if(R_Distance==0)
            {	
              R_SportMode=SportDisEndVal;
              SportEndBzFlg=1;
              R_SpeedBuf=R_SpeedNum;
              R_IncBuf=R_IncNum;
              R_SpeedNum=0;
              F_StringInit();
            }
          }
          else
          {
            R_Distance++;	
            if(R_Distance>9999)
              R_Distance=0;
          }
        }
      }
      //=====================
      if(R_Dist1>=100)		//	百公尺
      {
        R_Dist1=0;
        //================
        R_TotalDis++; // 總里程 
        if(R_TotalDis>161200)
          R_TotalDis=161200;
        //================
        R_TotalLube++;
        if(R_TotalLube>LubeVal)
          R_TotalLube=LubeVal;
        //================
        if(ChangeUnitFlg==0)	//	2012/3/29 Chandler修改
        {    //  公制	
          if(DisStatusFlg==1)
          {	
            R_Distance--;	
            if(R_Distance==0)
            {	
              R_SportMode=SportDisEndVal;
              SportEndBzFlg=1;
              R_SpeedBuf=R_SpeedNum;
              R_IncBuf=R_IncNum;
              R_SpeedNum=0;
              F_StringInit();
            }
          }
          else
          {
            R_Distance++;	
            if(R_Distance>9999)
              R_Distance=0;
          }
        }
      }
    }
}
//======================================
//
//======================================
void F_Playground(void)
{
    unsigned int Temp;
    R_TrackDis++;
    if(R_TrackDis>=400)	
    {
      R_TrackDis=0;
      R_LapsDis=0;			
      R_TrackCnt=0;	
      R_Laps++;
      if(R_Laps>99)
        R_Laps=0;
    }
    else
    {
      R_LapsDis++;
      //Temp = (float)(400/63)*(R_TrackCnt+1);
      Temp = (400/63)*(R_TrackCnt+1);
      if(R_LapsDis>=Temp)
      {
        R_TrackCnt++;
        if(R_TrackCnt>63)
          R_TrackCnt=63;
      }
    }
}
//====================================================
//  總里程 總時間 儲存
//====================================================
void F_TotalTimeDisCount(void)
{
  R_EeSaveTime++;
  if(R_EeSaveTime>59)
  {
    R_EeSaveTime=0;
    R_TotalTime++;
    if(R_TotalTime>599940)
      R_TotalTime=0;
    F_SaveTotalTimeDis();
  }
}
//======================================
void  F_SaveTotalTimeDis(void)
{   
    F_Write4Byte(EE_TotalTimeBye_1,R_TotalTime);
    F_Write4Byte(EE_TotalDisBye_1,R_TotalDis);
    F_Write2Byte(EE_TotalLubeBye_L,R_TotalLube);
}
//=====================================================
//	公制轉英制
//=====================================================
unsigned int F_ChangeKmToMile(unsigned int Data)
{
    float Num;
    Num = Data*0.6214;
    Data= (unsigned int)Num;
    return Data;
}
//=====================================================
//	英制轉公制
//=====================================================
unsigned int F_ChangeMileToKm(unsigned int Data)
{
  float Num;
    Num = (float) Data*1.6092;
    Data= (unsigned int)Num;
    return	Data;

}
//=======================================
void	F_Rest(void)
{
    IWDG_Config(0); 
    while(1);
}
//=======================================
//
//=======================================
void	C_delay(unsigned int count)
{
    while(count>1)
    {
      count--;
    }
    count=0;
}
//===============================
//IO 轉換
//===============================
/*
  if((PA_ODR & BIT6)==0x00)     //Port PA6
    PA_ODR |= BIT6;             //PA6 Hi	
    else
      PA_ODR &= ~BIT6;          //PA6 Low	
*/
