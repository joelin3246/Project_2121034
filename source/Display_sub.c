/* Includes ------------------------------------------------------------------*/
#include "connect.h"
/* Private define ------------------------------------------------------------*/
// 1625
#define P_HT1625CS_PIN                  GPIO_Pin_5                              
#define P_HT1625CS_GPIO_PORT            GPIOB
#define P_HT1625CS_GPIO_CLK             RCC_AHBPeriph_GPIOB

#define P_HT1625WR_PIN                  GPIO_Pin_6                             
#define P_HT1625WR_GPIO_PORT            GPIOB
#define P_HT1625WR_GPIO_CLK             RCC_AHBPeriph_GPIOB

#define P_HT1625DA_PIN                  GPIO_Pin_7                              
#define P_HT1625DA_GPIO_PORT            GPIOB
#define P_HT1625DA_GPIO_CLK             RCC_AHBPeriph_GPIOB

//==========================
#define D_NORMAL	0xe3
#define D_SysEN		0x01
#define D_SysDis	0x00
#define D_TIMEREN	0x06
#define D_IRQEN		0x88
#define D_IRQDIS	0x80
#define D_BIAS		0x29	//0x29
#define D_TONE2K	0x60
#define D_TONEON	0x09
#define D_TONEOFF	0x08
#define D_LCD_ON	0x03
#define D_LCD_OFF	0x02
#define D_IRQ1		0xa0	

//================================================
void F_InitialHT1625_GPIO(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
    
  // Output 1625
  // Enable the P_HT1625CS_PIN
  RCC_AHBPeriphClockCmd(P_HT1625CS_GPIO_CLK, ENABLE);
  // Configure the P_HT1625CS_PIN  pin 
  GPIO_InitStructure.GPIO_Pin = P_HT1625CS_PIN ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(P_HT1625CS_GPIO_PORT, &GPIO_InitStructure);
  
  // Enable the P_HT1625WR_PIN
  RCC_AHBPeriphClockCmd(P_HT1625WR_GPIO_CLK, ENABLE);
  // Configure the P_HT1625WR_PIN  pin 
  GPIO_InitStructure.GPIO_Pin = P_HT1625WR_PIN ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(P_HT1625WR_GPIO_PORT, &GPIO_InitStructure);
  
  // Enable the P_HT1625DA_PIN
  RCC_AHBPeriphClockCmd(P_HT1625DA_GPIO_CLK, ENABLE);
  // Configure the P_HT1625WR_PIN  pin
  GPIO_InitStructure.GPIO_Pin = P_HT1625DA_PIN ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(P_HT1625DA_GPIO_PORT, &GPIO_InitStructure);
}
//================================================
void F_1625CS_1(unsigned char data)
{																
  if(data)
    P_HT1625CS_GPIO_PORT -> BSRR = P_HT1625CS_PIN;  
    else
      P_HT1625CS_GPIO_PORT -> BRR =P_HT1625CS_PIN;  
}

void F_1625WR(unsigned char data)
{																
  if(data)
    P_HT1625WR_GPIO_PORT -> BSRR = P_HT1625WR_PIN;  
    else
      P_HT1625WR_GPIO_PORT -> BRR = P_HT1625WR_PIN;  
}

void F_1625DATA(unsigned char data)
{																
  if(data)
    P_HT1625DA_GPIO_PORT -> BSRR = P_HT1625DA_PIN;  
    else
      P_HT1625DA_GPIO_PORT -> BRR = P_HT1625DA_PIN;  
}
//==============================================================================
// ht1625 選擇
//==============================================================================
void F_1625ID(unsigned char  a,unsigned char  b,unsigned char  c)
{	
    F_1625DATA(a);
    F_1625WR(0);
    C_delay(2);
    F_1625WR(1);
    C_delay(2);
    F_1625DATA(b);
    F_1625WR(0);
    C_delay(2);
    F_1625WR(1);
    C_delay(2);
    F_1625DATA(c);
    F_1625WR(0);
    C_delay(2);
    F_1625WR(1);
}
//==============================================================================
// ht1625 指令訊號 function
//==============================================================================
void F_1625Com(unsigned char ch)
{
  unsigned char i,j;
  for(i=0;i<9;i++)
  {
    j=ch&0x80;
    if(j==0)
    {
      F_1625DATA(0);
      F_1625WR(0);
      C_delay(2);		
      F_1625WR(1);
    }	
    else
    { 	
      F_1625DATA(1);
      F_1625WR(0);	
      C_delay(2);
      F_1625WR(1);
    }	
    ch=ch << 1;
  }
}
//================================================
void F_1625Start(void)
{
    F_1625CS_1(0);
    C_delay(2);
    F_1625ID(1,0,0);
}
//===========
void F_HT1620Initial(void)
{
    F_1625Start();
    F_1625Com(D_SysEN);
    F_1625Com(D_LCD_ON);
    F_1625Com(D_BIAS);
    F_1625Com(D_NORMAL);
    F_1625CS_1(1);
}
//==============================================
void F_HT1620Write(unsigned char data)
{
    unsigned char i,j;
    
    for(i=0;i<8;i++)
    {
      j=data&0x80;
      if(j==0)
      {
        F_1625DATA(0);
        F_1625WR(0);
        C_delay(2);
        F_1625WR(1);
      }	
      else
      { 	
        F_1625DATA(1);
        F_1625WR(0);	
        C_delay(2);		
        F_1625WR(1);
      }
      data=data << 1;
    }	
}
//=================================================================	
void F_HT1620Address(unsigned char adr)
{
  unsigned char k,m;
  
  for(m=0;m<7;m++)
  {
    k=adr&0x40;
    if(k==0)
    {
      F_1625DATA(0);
      F_1625WR(0);
      C_delay(2);		
      F_1625WR(1);
    }	
    else
    {
      F_1625DATA(1);
      F_1625WR(0);	
      C_delay(2);		
      F_1625WR(1);
    }
    adr=adr << 1;
  }	
}
//================================================
void F_AllLCDRam(unsigned char data)
{
    unsigned char i;
    for(i=0;i<56;i++)
    {
      R_Seg[i]=data;
    }
    R_LedSegBuf=data;
}
//================================
void F_Display(void)
{
    unsigned char i;
    F_HT1620Initial();	
    F_1625CS_1(0);
    F_1625ID(1,0,1);	
    F_HT1620Address(0);
    for (i=0;i<56;i++)
    {
      F_HT1620Write(R_Seg[i]);
    }
    F_1625CS_1(1);
    F_1625WR(1);
    F_1625DATA(1);
    R_LedSeg=R_LedSegBuf;
}

//==========================================================
//
//
//==========================================================
void	F_ShowIncl(void)
{
    R_Seg[48] |= 0x24;	//	I
    R_Seg[49] |= 0x38;	//	n
    R_Seg[50] |= 0x58;	//	c
    R_Seg[51] |= 0x52;	//	L
}
//=================
void  F_ShowDis(void)
{
    unsigned  char  DistanceTemp1,DistanceTemp2;
    unsigned  int Distance;
    Distance=R_Distance;
    DistanceTemp2=Distance/100;
    DistanceTemp1=Distance%100;		
    if(DistanceTemp2>0)
    {
      F_Show_8_Lcd(blankVal,44,45,DistanceTemp2);
    }
    ShowHiByeFlg=1;		
    F_Show_8_Lcd(blankVal,46,47,DistanceTemp1);
    ShowHiByeFlg=0;		
    R_Seg[46] |= 0x80;          //	T2
}
//=================
void  F_ShowCal(void)
{
    unsigned  char  CalorieTemp1,CalorieTemp2;
    CalorieTemp2=R_Calorie/100;
    CalorieTemp1=R_Calorie%100;	
    if(CalorieTemp2>0)
    {
      F_Show_8_Lcd(blankVal,52,53,CalorieTemp2);
      ShowHiByeFlg=1;
    }
    F_Show_8_Lcd(blankVal,54,55,CalorieTemp1);
    ShowHiByeFlg=0;
    //R_Seg[54] |= 0x80;			//	T7
}
//===================
void F_ShowTime(void)
{
    F_Show_8_Lcd(blankVal,48,49,R_TimeH);
    ShowHiByeFlg=1;
    F_Show_8_Lcd(blankVal,50,51,R_TimeL);
    ShowHiByeFlg=0;
    R_Seg[50] |= 0x80;			//	COL
}
//====================
void F_ShowSpeed(unsigned	char	SpeedData)
{
    ShowHiByeFlg=1;
    F_Show_8_Lcd(18,17,16,SpeedData);
    ShowHiByeFlg=0;
    R_Seg[17] |= 0x80;            //	T19
    
    if(ChangeUnitFlg==0)
      R_Seg[15]=0x40;		// Km
    else
      R_Seg[15]=0x80;		// M
}
//====================
void F_ShowInc(unsigned	char	IncData)
{
  if(IncErrFlg==0)
  {
    if(IncData==0)
    {
      IncData=1;
      R_Seg[23]=0x08;		//	-
    }
    else
      IncData=IncData-1;
    F_Show_8_Lcd(blankVal,23,22,IncData);
  }
  else
  {
    R_Seg[24]=0x5B;		//	E
    R_Seg[23]=0x18;		//	r
    R_Seg[22]=0x18;		//	r
  }
}
//=====================================================
//
//
//=====================================================
const unsigned char T_SpeedProg[8] = {
    0x01,       //  1
    0x03,       //  2
    0x07,       //  3
    0x0F,       //  4
    0x1F,       //  5
    0x3F,       //  6
    0x7F,       //  7
    0xFF        //  8   
};
//==========
const unsigned char T_IncProg[9] = {
    0x00,         //  0
    0x01,         //  1
    0x03,         //  2
    0x07,         //  3
    0x0F,         //  4
    0x1F,         //  5
    0x3F,         //  6
    0x7F,         //  7
    0xFF          //  8
};
//===========
void  F_ShowSpeedIncProg(void)
{
    unsigned char TempProg[30],i;
    for(i=0;i<30;i++)
    {
      if(ChangeSpdIncProgFlg)
        TempProg[i]=R_ShowIncProg[i];
        else
          TempProg[i]=R_ShowSpeedProg[i];
    }
    R_Seg[42]=F_SpeedIncProg(TempProg[0]);
    R_Seg[41]=F_SpeedIncProg(TempProg[1]);
    R_Seg[40]=F_SpeedIncProg(TempProg[2]);
    R_Seg[39]=F_SpeedIncProg(TempProg[3]);
    R_Seg[38]=F_SpeedIncProg(TempProg[4]);
    R_Seg[37]=F_SpeedIncProg(TempProg[5]);
    R_Seg[36]=F_SpeedIncProg(TempProg[6]);
    R_Seg[35]=F_SpeedIncProg(TempProg[7]);
    R_Seg[34]=F_SpeedIncProg(TempProg[8]);
    R_Seg[33]=F_SpeedIncProg(TempProg[9]);
    R_Seg[32]=F_SpeedIncProg(TempProg[10]);
    R_Seg[31]=F_SpeedIncProg(TempProg[11]);
    R_Seg[30]=F_SpeedIncProg(TempProg[12]);
    R_Seg[29]=F_SpeedIncProg(TempProg[13]);
    R_Seg[28]=F_SpeedIncProg(TempProg[14]);
    R_Seg[0]=F_SpeedIncProg(TempProg[15]);
    R_Seg[1]=F_SpeedIncProg(TempProg[16]);
    R_Seg[2]=F_SpeedIncProg(TempProg[17]);
    R_Seg[3]=F_SpeedIncProg(TempProg[18]);
    R_Seg[4]=F_SpeedIncProg(TempProg[19]);
    R_Seg[5]=F_SpeedIncProg(TempProg[20]);
    R_Seg[6]=F_SpeedIncProg(TempProg[21]);
    R_Seg[7]=F_SpeedIncProg(TempProg[22]);
    R_Seg[8]=F_SpeedIncProg(TempProg[23]);
    R_Seg[9]=F_SpeedIncProg(TempProg[24]);
    R_Seg[10]=F_SpeedIncProg(TempProg[25]);
    R_Seg[11]=F_SpeedIncProg(TempProg[26]);
    R_Seg[12]=F_SpeedIncProg(TempProg[27]);
    R_Seg[13]=F_SpeedIncProg(TempProg[28]);
    R_Seg[14]=F_SpeedIncProg(TempProg[29]);
}
//=====================================
unsigned  char  F_SpeedIncProg(unsigned char  ProgData)
{
    unsigned  int i;
    if(ChangeSpdIncProgFlg)
    {
      if(ProgData==0)
        i=T_IncProg[0];
      else  if(ProgData<=2)
        i=T_IncProg[1];			
      else  if(ProgData<=4)
        i=T_IncProg[2];		
      else  if(ProgData<=6)
        i=T_IncProg[3];		
      else  if(ProgData<=8)
        i=T_IncProg[4];		
      else  if(ProgData<=10)
        i=T_IncProg[5];     
      else  if(ProgData<=12)
        i=T_IncProg[6];
      else  if(ProgData<=14)
        i=T_IncProg[7];
      else
        i=T_IncProg[8];
    }
    else
    {
      if(ProgData<=12)
        i=T_SpeedProg[0];
      else  if(ProgData<=25)
        i=T_SpeedProg[1];			
      else  if(ProgData<=37)
        i=T_SpeedProg[2];		
      else  if(ProgData<=50)
        i=T_SpeedProg[3];		
      else  if(ProgData<=62)
        i=T_SpeedProg[4];		
      else  if(ProgData<=75)
        i=T_SpeedProg[5];     
      else  if(ProgData<=85)
        i=T_SpeedProg[6];
      else
        i=T_SpeedProg[7];
    }
    return(i);
}
//========================
void  F_ChangeGraphSpeed(unsigned	char	Adr,unsigned	char	SpeedData)
{
    //R_ShowSpeedProg[Adr]=((unsigned  int)(SpeedData-R_SpeedMin)*80)/(R_SpeedMax-R_SpeedMin);
    R_ShowSpeedProg[Adr]=(unsigned  int)(SpeedData*100)/(R_SpeedMax);
}
//=====================================
void  F_ChangeGraphInc(unsigned	char	Adr,unsigned	char	IncData)
{
    //R_ShowIncProg[Adr]=((unsigned  int)(IncData*80)/R_IncMax);
    R_ShowIncProg[Adr]=IncData;
}
//=====================================
void  F_ShowProfileFlash(void)
{
    switch(R_ProgramIndex)
    {
    case  0:
      R_Seg[42] = 0;
      break;
      //=======
    case  1:
      R_Seg[41] = 0;
      break;
      //=======
    case  2:
      R_Seg[40] = 0;
      break;
      //=======
    case  3:
      R_Seg[39] = 0;
      break;
      //=======
    case  4:
      R_Seg[38] = 0;
      break;
      //=======
    case  5:
      R_Seg[37] = 0;
      break;
      //=======
    case  6:
      R_Seg[36] = 0;
      break;
      //=======
    case  7:
      R_Seg[35] = 0;
      break;
      //=======
    case  8: 
      R_Seg[34] = 0;
      break;
      //=======
    case  9:   
      R_Seg[33] = 0;
      break;
      //=======
    case  10:  
      R_Seg[32] = 0;
      break;
      //=======
    case  11:
      R_Seg[31] = 0;
      break;
      //=======
    case  12:
      R_Seg[30] = 0;
      break;
      //=======
    case  13:
      R_Seg[29] = 0;
      break;
      //=======
    case  14:
      R_Seg[28] = 0;
      break;
      //=======
    case  15:
      R_Seg[0] = 0;
      break;
      //=======
    case  16:
      R_Seg[1] = 0;
      break;
      //=======
    case  17:
      R_Seg[2] = 0;
      break;
      //=======
    case  18:
      R_Seg[3] = 0;
      break;
      //=======
    case  19:
      R_Seg[4] = 0;
      break;
      //=======
    case  20:
      R_Seg[5] = 0;
      break;
      //=======
    case  21:
      R_Seg[6] = 0;
      break;
      //=======
    case  22:
      R_Seg[7] = 0;
      break;
      //=======
    case  23:
      R_Seg[8] = 0;
      break;
      //=======
    case  24:
      R_Seg[9] = 0;
      break;
      //=======
    case  25:
      R_Seg[10] = 0;
      break;
      //=======
    case  26:
      R_Seg[11] = 0;
      break;
      //=======
    case  27:
      R_Seg[12] = 0;
      break;
      //=======
    case  28:
      R_Seg[13] = 0;
      break;
      //=======
    case  29:
      R_Seg[14] = 0;	
      break;
    }
}
//===============================================
void	F_ShowTrackLed(void)
{
    unsigned char K;
    R_Seg[42]=0x7E;	
    R_Seg[41]=0x81;
    R_Seg[40]=0xBD;	
    R_Seg[39]=0xA5;
    R_Seg[38]=0xA5;
    R_Seg[37]=0xA5;
    R_Seg[36]=0xA5;
    R_Seg[35]=0xA5;
    R_Seg[34]=0xA5;
    R_Seg[33]=0xA5;
    R_Seg[32]=0xA5;
    R_Seg[31]=0xA5;
    R_Seg[30]=0xA5;
    R_Seg[29]=0xA5;
    R_Seg[28]=0xA5;
    R_Seg[0]=0xA5;
    R_Seg[1]=0xA5;
    R_Seg[2]=0xA5;
    R_Seg[3]=0xA5;
    R_Seg[4]=0xA5;
    R_Seg[5]=0xA5;
    R_Seg[6]=0xA5;
    R_Seg[7]=0xA5;
    R_Seg[8]=0xA5;
    R_Seg[9]=0xA5;
    R_Seg[10]=0xA5;
    R_Seg[11]=0xA5;
    R_Seg[12]=0xBD;
    R_Seg[13]=0x81;
    R_Seg[14]=0x7E;
    if(R_TrackCnt>=64)
      R_TrackCnt=63;
    if(FlashFlg)
    {
      K=T_TrackRam[R_TrackCnt][0];
      R_Seg[K] |= T_TrackRam[R_TrackCnt][1];	
    }
}
//=====================
void	F_ShowPulse(void)
{
    if((R_W_Pluse==0) && (R_Pluse==0))
    {
      R_Seg[19] |= 0x1F;
    }
    else
    {
      if(R_W_Pluse==0)      //無線與手握同時存在，顯示無線心跳數值
      {	
        if(R_Thr==0)
          F_Show_8_Lcd(21,20,19,R_Pluse);
        else
        {
          if(R_Pluse>R_Thr)
          {
            if(FlashFlg==1)
              F_Show_8_Lcd(21,20,19,R_Pluse);
          }
          else
            F_Show_8_Lcd(21,20,19,R_Pluse);
        }
      }	
      else
      {
        if(R_Thr==0)
          F_Show_8_Lcd(21,20,19,R_W_Pluse);
        else
        {
          if(R_W_Pluse>R_Thr)
          {
            if(FlashFlg==1)
              F_Show_8_Lcd(21,20,19,R_W_Pluse);
          }
          else
            F_Show_8_Lcd(21,20,19,R_W_Pluse);
        }
      }
    }
    //=================================
    if(HandHeartDetectionFlg==1 || wHeartDetectionFlg==1)
    {
      if(FlashFlg==1)
        R_Seg[19] |= 0x80;      //  HT	
    }
}
//==================================
void	F_ShowThrSet(void)
{
    F_Show_8_Lcd(21,20,19,R_Thr);
}
//==================================
void  F_ShowSportThr(unsigned char  Pluse)
{
    if(R_Thr!=R_ThrBuf)
    {
      if(R_ThrDelayTime<200)  //限制加超過
        R_ThrDelayTime++;
      if(R_ThrDelayTime<7)   //延遲 20秒
      { 
        F_Show_8_Lcd(21,20,19,R_Thr);
      }
      else  if(R_ThrDelayTime<14)
      {
        
      }
      else  if(R_ThrDelayTime<21)
      {
        F_Show_8_Lcd(21,20,19,R_Thr);           
      }
      else  if(R_ThrDelayTime>28)
      {  
        R_ThrDelayTime=0;
        R_ThrBuf=R_Thr;
      }
    }
    else
    {  
      F_Show_8_Lcd(21,20,19,Pluse);
      R_ThrDelayTime=0;
    }
}
//====================
void	F_ShowLaps(void)
{
    R_Seg[27] |= 0x52;      //      L
    R_Seg[43] |= 0x08;      //      4 <	
    F_Show_8_Lcd(blankVal,26,25,R_Laps);
}
//====================
void	F_ShowHrc1HeartFlash(void)
{
    if(FlashFlg)
    {
      R_Seg[32]=0x70;
      R_Seg[31]=0xF8;
      R_Seg[30]=0xFC;
      R_Seg[29]=0xFE;
      R_Seg[28]=0x7F;
      R_Seg[0]=0x7F;
      R_Seg[1]=0xFE;
      R_Seg[2]=0xFC;
      R_Seg[3]=0xF8;
      R_Seg[4]=0x70;
    }
    else
    {
      R_Seg[31]=0x30;
      R_Seg[30]=0x78;
      R_Seg[29]=0x7C;
      R_Seg[28]=0x3E;
      R_Seg[0]=0x3E;
      R_Seg[1]=0x7C;
      R_Seg[2]=0x78;
      R_Seg[3]=0x30;	
    }
}
//====================
void	F_ShowHrc2HeartFlash(void)
{
    if(FlashFlg)
    {
      R_Seg[38]=0x70;
      R_Seg[37]=0x88;
      R_Seg[36]=0x84;
      R_Seg[35]=0x82;
      R_Seg[34]=0x41;
      R_Seg[33]=0x41;
      R_Seg[32]=0x82;
      R_Seg[31]=0x84;
      R_Seg[30]=0x88;
      R_Seg[29]=0x70;
      
      R_Seg[1]=0x70;
      R_Seg[2]=0xF8;
      R_Seg[3]=0xFC;
      R_Seg[4]=0xFE;
      R_Seg[5]=0x7F;
      R_Seg[6]=0x7F;
      R_Seg[7]=0xFE;
      R_Seg[8]=0xFC;
      R_Seg[9]=0xF8;
      R_Seg[10]=0x70;
    }
    else
    {
      R_Seg[38]=0x70;
      R_Seg[37]=0xF8;
      R_Seg[36]=0xFC;
      R_Seg[35]=0xFE;
      R_Seg[34]=0x7F;
      R_Seg[33]=0x7F;
      R_Seg[32]=0xFE;
      R_Seg[31]=0xFC;
      R_Seg[30]=0xF8;
      R_Seg[29]=0x70;
      
      R_Seg[1]=0x70;
      R_Seg[2]=0x88;
      R_Seg[3]=0x84;
      R_Seg[4]=0x82;
      R_Seg[5]=0x41;
      R_Seg[6]=0x41;
      R_Seg[7]=0x82;
      R_Seg[8]=0x84;
      R_Seg[9]=0x88;
      R_Seg[10]=0x70;
    }
}
//====================
void	F_ShowNoHeart(void)
{
    R_Seg[1]=0x30;
    R_Seg[2]=0x78;
    R_Seg[3]=0x7C;
    R_Seg[4]=0x3E;
    R_Seg[5]=0x3E;
    R_Seg[6]=0x7C;
    R_Seg[7]=0x78;
    R_Seg[8]=0x30;
    if(FlashFlg)
    {
      R_Seg[33]=0x60;
      R_Seg[32]=0x80;
      R_Seg[31]=0x8D;
      R_Seg[30]=0x90;
      R_Seg[29]=0x60;	
    }
}
//====================
void	F_ShowAge(void)
{
    F_Show_8_Lcd(21,20,19,R_Age);
}
//====================
void	F_ShowVer(void)
{
    ShowHiByeFlg=1;
    F_Show_8_Lcd(blankVal,26,25,12);
    ShowHiByeFlg=0;
    ShowHiByeFlg=0;
    R_Seg[26] |= 0x80;
}
//=============================================
void  F_ShowTotalTime(void)
{
    unsigned  int TimeHour;
    unsigned  char  Temp1,Temp2;
    TimeHour=R_TotalTime/60;
    if(R_TotalTime>5999)
    {
      Temp2=TimeHour/100;
      Temp1=TimeHour%100;		
    }
    else
    {
      Temp2=TimeHour;
      Temp1=R_TotalTime%60;
      R_Seg[50] |= 0x80;			//	COL
    }
    F_Show_8_Lcd(blankVal,48,49,Temp2);
    ShowHiByeFlg=1;
    F_Show_8_Lcd(blankVal,50,51,Temp1);
    ShowHiByeFlg=0;
}
//=============================================
void  F_ShowTotalDis(void)
{
    unsigned  int DisTemp;
    unsigned  char  Temp1,Temp2;
    unsigned  long  TotalDis;
    if(ChangeUnitFlg==1)
    { //  英制
      TotalDis=(R_TotalDis*621)/1000;
    }
    else
    { //  公制
      TotalDis=R_TotalDis;
    }
    if(TotalDis>9999)
    {
      DisTemp=TotalDis/10;	//	百公尺取消
      Temp2=DisTemp/100;
      Temp1=DisTemp%100;
      if(Temp2>99)
      {
        Temp2=99;
        Temp1=99;
      }
      F_Show_8_Lcd(blankVal,44,45,Temp2);
      ShowHiByeFlg=1; 
      F_Show_8_Lcd(blankVal,46,47,Temp1);
      ShowHiByeFlg=0;
    }
    else
    {
      Temp2=TotalDis/100;
      Temp1=TotalDis%100;
      if(Temp2>0)
        F_Show_8_Lcd(blankVal,44,45,Temp2);
      ShowHiByeFlg=1;
      F_Show_8_Lcd(blankVal,46,47,Temp1);
      ShowHiByeFlg=0;
      R_Seg[46] |= 0x80;
    }
}
//======================================
void	ShowIncSpdPorgLed(void)
{
  switch(R_CholeIncSpdMode)
  {
    case 0:
      R_LedSegBuf |= 0x02;      // Speed Led
      R_LedSegBuf |= 0x01;      // Inc	Led		
      break;
      //=============	
    case 1:
      R_LedSegBuf |= 0x02;      // Speed Led
      break;
        //=============	
    case 2:
      R_LedSegBuf |= 0x01;      // Inc Led
      break;		
  }
}
//========================================
void    F_ShowPowerLed(void)
{
  if(R_SysMode==SysErrModeVal)
    R_LedSegBuf |= 0x08;        // 紅色
    else
      R_LedSegBuf |= 0x10;      // 綠色
}
//============================
void	F_ShowWheelSize(void)
{
    F_Show_8_Lcd(21,20,19,R_WheelSize);
    R_Seg[21] |= 0x80;
}
//============================
void	F_ShowLube(void)
{
    if(R_TotalLube>=LubeVal)
    {
      R_Seg[43] |= 0x01;        // 1 <
    }
}