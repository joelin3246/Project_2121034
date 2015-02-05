#include "connect.h"
//=================================================
//	工程模式3
//=================================================
void	F_EngMode3(void)
{
  if(T20msFlg==1)
  {			
    T20msFlg=0;
    F_ReadKey();
    F_CheckGetKey();
    switch(R_Mode)
    {
      case	0:
        F_EngMode3_Key1();
        break;
        case	1:
          F_EngMode3_Key2();
          break;
    }
  }
  //=================	
  if(ShowLcdTimeFlg==1)
  {
    ShowLcdTimeFlg=0;
    F_AllLCDRam(0x00);
    F_EngMode3_Lcd();
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
void	F_EngMode3_Key1(void)
{
  switch(KeyCode)
  {
    case	Mode_KeyVal:
      KeyCode=0;
      R_Mode=1;
      R_BzCnt=0x04;
      break;
  }
}
//======================
void	F_EngMode3_Key2(void)
{
  switch(KeyCode)
  {
      case      0:
      
      break;
      //==========	
      case	Set_KeyVal:
	KeyCode=0;
	R_KeyTest=1;
	R_BzCnt=0x04;
        break;
      //==========
      case	InclineDown_KeyVal:
        KeyCode=0;
        R_KeyTest=2;
          if(R_LongKeyStopBz==0)	
            R_BzCnt=0x04;
          break;
      //==========
      case	InclineUp_KeyVal:
        KeyCode=0;
        R_KeyTest=3;
        if(R_LongKeyStopBz==0)	
          R_BzCnt=0x04;
            break;
      //==========
      case	Mode_KeyVal:
        KeyCode=0;
        R_KeyTest=4;
        R_BzCnt=0x04;
        break;
      //==========	
      case	start_stop_KeyVal:
        KeyCode=0;
        R_KeyTest=5;
        R_BzCnt=0x04;
        break;
      //==========	
      case	SpeedDown_KeyVal:
        KeyCode=0;
        R_KeyTest=6;
        if(R_LongKeyStopBz==0)	
          R_BzCnt=0x04;
        break;
      //==========	
      case	SpeedUp_KeyVal:
        KeyCode=0;
        R_KeyTest=7;
        if(R_LongKeyStopBz==0)	
          R_BzCnt=0x04;
        break;
      //==========	
      case	Enter_KeyVal:
        KeyCode=0;
        R_KeyTest=8;
        R_BzCnt=0x04;
        break;
      //==========	
      case	QuickInc_2_KeyVal:
        KeyCode=0;
        R_KeyTest=13;
          R_BzCnt=0x04;
        break;
      //==========	
      case	QuickInc_4_KeyVal:
        KeyCode=0;
        R_KeyTest=14;
        R_BzCnt=0x04;
        break;
      //==========	
      case	QuickInc_6_KeyVal:
        KeyCode=0;
        R_KeyTest=15;
          R_BzCnt=0x04;
        break;
      //==========	
      case	QuickInc_8_KeyVal:
        KeyCode=0;
        R_KeyTest=16;
        R_BzCnt=0x04;
        break;
      //==========	
      case	QuickInc_10_KeyVal:
        KeyCode=0;
        R_KeyTest=17;
          R_BzCnt=0x04;
        break;
      //==========	
      case	QuickInc_12_KeyVal:
        KeyCode=0;
        R_KeyTest=18;
        R_BzCnt=0x04;
        break;
      //==========	
      case	QuickSpd_1_KeyVal:
        KeyCode=0;
        R_KeyTest=19;
          R_BzCnt=0x04;
        break;
      //==========	
      case	QuickSpd_4_KeyVal:
        KeyCode=0;
        R_KeyTest=20;
        R_BzCnt=0x04;
        break;
      //==========	
      case	QuickSpd_7_KeyVal:
        KeyCode=0;
        R_KeyTest=21;
          R_BzCnt=0x04;
        break;
      //==========	
      case	QuickSpd_10_KeyVal:
        KeyCode=0;
        R_KeyTest=22;
        R_BzCnt=0x04;
        break;
      //==========	
      case	QuickSpd_13_KeyVal:
        KeyCode=0;
        R_KeyTest=23;
          R_BzCnt=0x04;
        break;
      //==========	
      case	QuickSpd_16_KeyVal:
        KeyCode=0;
        R_KeyTest=24;
        R_BzCnt=0x04;
        break;
      //==========
      case      Eng1_KeyVal:
        KeyCode=0;
        F_Rest();	
        break;
      //==========	
  }
}
#define Eng3TestDisplayTime	3

//===========================================
//
//===========================================
void	F_EngMode3_Lcd(void)
{
  switch(R_Mode)
  {
    case	0:
      R_KeyTest=0;
      R_EngFlashCnt++;
      if(R_EngFlashCnt<Eng3TestDisplayTime*1)
      {
        F_LcdTest(1);			
      }
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*2)
      {
        F_LcdTest(2);
      }
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*3)
      {
        F_LcdTest(3);
        //F_ProgTest(0x20);
      }
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*4)
      {
        F_LcdTest(4);
        //F_ProgTest(0x10);
      }
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*5)
      {
        F_LcdTest(5);
        //F_ProgTest(0x08);
      }
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*6)
      {
        F_LcdTest(6);
        //F_ProgTest(0x04);
      }
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*7)
      {
        F_LcdTest(7);
        //F_ProgTest(0x02);
      }
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*8)
      {
        F_LcdTest(8);
        //F_ProgTest(0x01);
      }
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*9)
      {
        F_LcdTest(9);
      }
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*11)
      {
        F_LcdTest(0);
      }		
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*12)
      {
        F_ProgTest(0x80);
      }		
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*13)
      {
        F_ProgTest(0x40);
      }	
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*14)
      {
        F_ProgTest(0x20);
      }
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*15)
      {
        F_ProgTest(0x10);
      }			
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*16)
      {
        F_ProgTest(0x08);
      }		
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*17)
      {
        F_ProgTest(0x04);
      }	
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*18)
      {
        F_ProgTest(0x02);
      }
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*19)
      {
        F_ProgTest(0x01);
      }			
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*20)
      {
        R_Seg[43]=0x01;			// 1 <
      }					
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*21)
      {
        R_Seg[43]=0x02;			// 2 <
      }			
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*22)
      {
        R_Seg[44] = 0x80;			//	T1
      }	
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*23)
      {
        R_Seg[45] = 0x80;			//	T1
      }				
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*24)
      {
        R_Seg[46] = 0x80;			//	T1
      }				
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*25)
      {
        R_Seg[47] = 0x80;			//	T1
      }	
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*26)
      {
        R_Seg[50] |= 0x80;			//	COL
      }				
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*27)
      {
        R_Seg[52] |= 0x80;			//	T
      }	
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*28)
      {
        R_Seg[53] |= 0x80;			//	T
      }	
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*29)
      {
        R_Seg[54] |= 0x80;			//	T
      }				
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*30)
      {
        R_Seg[55] |= 0x80;			//	T
      }				
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*31)
      {
        R_Seg[15]=0x10;		// 5 >
      }	
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*32)
      {
        R_Seg[15]=0x20;		// 6 >
      }				
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*33)
      {
        R_Seg[43]=0x04;			// 3 <
      }			
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*34)
      {
        R_Seg[43]=0x08;			// 4 <
      }			
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*35)
      {
        R_Seg[27] = 0x80;
      }	
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*36)
      {
        R_Seg[26] = 0x80;
      }			
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*37)
      {
        R_Seg[25] = 0x80;
      }	
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*38)
      {
        R_Seg[24]=0x80;	
      }			
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*39)
      {
        R_Seg[23]=0x80;	
      }				
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*40)
      {
        R_Seg[22]=0x80;
      }			
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*41)
      {
        R_Seg[21]=0x80;
      }				
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*42)
      {
        R_Seg[20]=0x80;
      }			
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*43)
      {
        R_Seg[19]=0x80;
      }				
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*44)
      {
        R_Seg[18]=0x80;
      }			
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*45)
      {
        R_Seg[17]=0x80;
      }	
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*46)
      {
        R_Seg[16]=0x80;
      }			
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*47)
      {
        R_Seg[15]=0x40;		// Km
      }				
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*48)
      {
        R_Seg[15]=0x80;		//	M
      }	
      else	if(R_EngFlashCnt<Eng3TestDisplayTime*50)
      {
        R_Mode=1;	
      }	
      break;
      //===============================
      case	1:
        F_Show_8_Lcd(21,20,19,R_KeyTest);
        break;
  }
}
//=================================================
void	F_LcdTest(unsigned	char	Data)
{
  F_Show_8_FontLcd(44,Data);
  F_Show_8_FontLcd(45,Data);
  F_Show_8_FontLcd(46,Data);
  F_Show_8_FontLcd(47,Data);
  
  F_Show_8_FontLcd(48,Data);
  F_Show_8_FontLcd(49,Data);
  F_Show_8_FontLcd(50,Data);
  F_Show_8_FontLcd(51,Data);
  
  F_Show_8_FontLcd(52,Data);
  F_Show_8_FontLcd(53,Data);
  F_Show_8_FontLcd(54,Data);
  F_Show_8_FontLcd(55,Data);
  
  F_Show_8_FontLcd(25,Data);
  F_Show_8_FontLcd(26,Data);
  F_Show_8_FontLcd(27,Data);
  
  F_Show_8_FontLcd(24,Data);
  F_Show_8_FontLcd(23,Data);
  F_Show_8_FontLcd(22,Data);
  
  F_Show_8_FontLcd(21,Data);
  F_Show_8_FontLcd(20,Data);
  F_Show_8_FontLcd(19,Data);
  
  F_Show_8_FontLcd(18,Data);
  F_Show_8_FontLcd(17,Data);
  F_Show_8_FontLcd(16,Data);
}
//=================================================
void	F_ProgTest(unsigned	char	Data)
{
  R_Seg[42]=Data;
  R_Seg[41]=Data;
  R_Seg[40]=Data;
  R_Seg[39]=Data;
  R_Seg[38]=Data;
  R_Seg[37]=Data;
  R_Seg[36]=Data;
  R_Seg[35]=Data;
  R_Seg[34]=Data;
  R_Seg[33]=Data;
  R_Seg[32]=Data;
  R_Seg[31]=Data;
  R_Seg[30]=Data;
  R_Seg[29]=Data;
  R_Seg[28]=Data;
  R_Seg[0]=Data;
  R_Seg[1]=Data;
  R_Seg[2]=Data;
  R_Seg[3]=Data;
  R_Seg[4]=Data;
  R_Seg[5]=Data;
  R_Seg[6]=Data;
  R_Seg[7]=Data;
  R_Seg[8]=Data;
  R_Seg[9]=Data;
  R_Seg[10]=Data;
  R_Seg[11]=Data;
  R_Seg[12]=Data;
  R_Seg[13]=Data;
  R_Seg[14]=Data;
}
//=================================================
//	工程模式4
//=================================================
void	F_EngMode4(void)
{
  if(T20msFlg==1)
  {			
    T20msFlg=0;
    F_ReadKey();
    F_CheckGetKey();
    switch(R_Mode)
    {
      case	0:
        F_EngMode4_Key1();
        break;
        case	1:
          //F_EngMode4_Key2();
          break;		
          case	2:
            F_EngMode4_Key3();
            break;
    }
  }
  //=================	
  if(ShowLcdTimeFlg==1)
  {
    ShowLcdTimeFlg=0;
    F_AllLCDRam(0x00);
    F_EngMode4_Lcd();
    F_Display();
  }
  //=================		
  if(T1sFlg==1)
  {
    T1sFlg=0;
    F_Eng4Test();
  }
}
//==========================================
void    F_IncFinsh(void)
{
      if(IncUpDownFlg==1) 
      {
        R_IncCarryAd=R_IncMaxAd;
        EE_Write(EE_IncCarryAd,R_IncCarryAd);
        EE_Write(EE_IncMaxAd,R_IncMaxAd - R_IncZeroAdr);
      }
      else
      {
        R_IncCarryAd=R_IncMinAd;
        EE_Write(EE_IncCarryAd,R_IncCarryAd);
        EE_Write(EE_IncMinAd,R_IncMinAd + R_IncZeroAdr);
      }
}
//==========================================
void	F_Eng4Test(void)
{
  if(R_Mode==1)	//	校正模式
  {
    if((IncAutoFlg==0) && (SpeedAutoFlg==0))
    {
      //R_Mode=2;       //  打開可以執行揚升的微調
      //===================
      F_IncFinsh();
      F_Rest();
      //===================
    }
  }
}
//============================================
//
//============================================
void	F_EngMode4_Key1(void)
{
  switch(KeyCode)
  {
    //=============
    case	start_stop_KeyVal:
      KeyCode=0;
      R_Mode=1;		//進入校正
      IncAutoFlg=1;
      F_SpeedAutoInit();
      R_BzCnt=0x04;		
      break;
  }
}
//=================================
void	F_EngMode4_Key3(void)
{
  switch(KeyCode)
  {
    //=============
    case	start_stop_KeyVal:
      KeyCode=0;
      F_IncFinsh();
      F_Rest();
      break;
      //=============
      case	InclineUp_KeyVal:
	KeyCode=0;
        if(IncUpDownFlg==1) 
        {
          if(R_IncNumAdBuf<R_IncMaxAd)
          {
            R_IncNumAdBuf=R_IncNumAdBuf+3;
            IncSetFlag=1;
            IncStopFlg=0;
            if(R_LongKeyStopBz==0)	
              R_BzCnt=0x04;	
          }
          else
            R_IncNumAdBuf=R_IncMaxAd;
        }
        else
        {
          if(R_IncNumAdBuf<80)
          {
            R_IncNumAdBuf=R_IncNumAdBuf+3;
            IncSetFlag=1;
            IncStopFlg=0;
            if(R_LongKeyStopBz==0)	
              R_BzCnt=0x04;	
          }
          else
            R_IncNumAdBuf=80;
        }
        break;	
	//=============
	case	InclineDown_KeyVal:
          KeyCode=0;
          if(IncUpDownFlg==1) 
          {
            if(R_IncNumAdBuf>180)
            {
              R_IncNumAdBuf=R_IncNumAdBuf-3;
              IncSetFlag=1;
              IncStopFlg=0;
              if(R_LongKeyStopBz==0)	
                R_BzCnt=0x04;	
            }
            else
              R_IncNumAdBuf=180;
          }
          else
          {
            if(R_IncNumAdBuf>R_IncMinAd)
            {
              R_IncNumAdBuf=R_IncNumAdBuf-3;
              IncSetFlag=1;
              IncStopFlg=0;
              if(R_LongKeyStopBz==0)	
                R_BzCnt=0x04;	
            }
            else
              R_IncNumAdBuf=R_IncMinAd;
          }	
          break;
  }
}
//===========================================
//
//
//===========================================
void	F_EngMode4_Lcd(void)
{
  switch(R_Mode)
  {
    case	0:
      F_ShowMatrixPicture(6,PidCal);
      break;
      //=================
      case	1:	
        F_ShowMatrixPicture(6,PidCal);
        F_Show_8_Lcd(24,23,22,R_IncNumAd);
        F_Show_8_Lcd(21,20,19,R_SpeedPwmCntSave);
        F_ShowSpeed(R_SpeedBuf);
        break;
        //=================
        case	2:	
          F_Show_8_Lcd(27,26,25,R_IncZeroAdr);
          F_Show_8_Lcd(24,23,22,R_IncNumAd);
          if(IncErrFlg==1)
          {
            R_Seg[27]=0x5B;		//	E
            R_Seg[26]=0x18;		//	r
            R_Seg[25]=0x18;		//	r
          }
          else
            F_Show_8_Lcd(27,26,25,R_IncNumAdBuf);
          break;
          //=================
  }
}
