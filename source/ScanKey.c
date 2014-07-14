#include "connect.h"

/* Private define ------------------------------------------------------------*/
//KBSense
#define P_KBSense_PIN1                  GPIO_Pin_0
#define P_KBSense_PIN2                  GPIO_Pin_1 
#define P_KBSense_PIN3                  GPIO_Pin_2 
#define P_KBSense_PIN4                  GPIO_Pin_3  
#define P_KBSense_PIN5                  GPIO_Pin_4 
#define P_KBSense_PIN6                  GPIO_Pin_5 
#define P_KBSense_PIN7                  GPIO_Pin_6 
#define P_KBSense_PIN8                  GPIO_Pin_7 
#define P_KBSense_GPIO_PORT             GPIOA
#define P_KBSense_GPIO_CLK              RCC_AHBPeriph_GPIOA
//KBScan 
#define P_KBScan_PIN1                   GPIO_Pin_2  
#define P_KBScan_PIN2                   GPIO_Pin_10
#define P_KBScan_PIN3                   GPIO_Pin_11
#define P_KBScan_GPIO_PORT              GPIOB
#define P_KBScan_GPIO_CLK               RCC_AHBPeriph_GPIOB
//Led
#define P_LedScan_PIN1                  GPIO_Pin_0  
#define P_LedScan1_GPIO_PORT            GPIOB
#define P_LedScan1_GPIO_CLK             RCC_AHBPeriph_GPIOB

#define P_LedScan_PIN2                  GPIO_Pin_8
#define P_LedScan2_GPIO_PORT            GPIOA
#define P_LedScan2_GPIO_CLK             RCC_AHBPeriph_GPIOA

#define P_LedScan_PIN3                  GPIO_Pin_4
#define P_LedScan3_GPIO_PORT            GPIOB
#define P_LedScan3_GPIO_CLK             RCC_AHBPeriph_GPIOB
/* Private macro -------------------------------------------------------------*/
#define ScanLine1Out(x)     if(x)   P_KBScan_GPIO_PORT->BSRR = P_KBScan_PIN1; else  P_KBScan_GPIO_PORT->BRR = P_KBScan_PIN1;
#define ScanLine2Out(x)     if(x)   P_KBScan_GPIO_PORT->BSRR = P_KBScan_PIN2; else  P_KBScan_GPIO_PORT->BRR = P_KBScan_PIN2;
#define ScanLine3Out(x)     if(x)   P_KBScan_GPIO_PORT->BSRR = P_KBScan_PIN3; else  P_KBScan_GPIO_PORT->BRR = P_KBScan_PIN3;

#define LedScan1Out(x)  if(x)   P_LedScan1_GPIO_PORT->BSRR = P_LedScan_PIN1; else  P_LedScan1_GPIO_PORT->BRR = P_LedScan_PIN1;
#define LedScan2Out(x)  if(x)   P_LedScan2_GPIO_PORT->BSRR = P_LedScan_PIN2; else  P_LedScan2_GPIO_PORT->BRR = P_LedScan_PIN2;
#define LedScan3Out(x)  if(x)   P_LedScan3_GPIO_PORT->BSRR = P_LedScan_PIN3; else  P_LedScan3_GPIO_PORT->BRR = P_LedScan_PIN3;
/* Private functions ---------------------------------------------------------*/

void  F_InitialKB_GPIO(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  // Input KBSense  on PA3~A7     
  // Enable the KBSense
  RCC_AHBPeriphClockCmd(P_KBSense_GPIO_CLK, ENABLE);
  // Configure the KBSense pin 
  GPIO_InitStructure.GPIO_Pin = P_KBSense_PIN1 +P_KBSense_PIN2 + P_KBSense_PIN3 +P_KBSense_PIN4 + P_KBSense_PIN5 + P_KBSense_PIN6 + P_KBSense_PIN7 + P_KBSense_PIN8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(P_KBSense_GPIO_PORT, &GPIO_InitStructure);
  
  // Output KBScan
  // Enable the KBScan 
  RCC_AHBPeriphClockCmd(P_KBScan_GPIO_CLK, ENABLE);
  // Configure the KBScan pin 
  GPIO_InitStructure.GPIO_Pin =  P_KBScan_PIN1 + P_KBScan_PIN2 +P_KBScan_PIN3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(P_KBScan_GPIO_PORT, &GPIO_InitStructure);
  
  // Output LedScan
  // Enable the LedScan 
  RCC_AHBPeriphClockCmd(P_LedScan1_GPIO_CLK, ENABLE);
  // Configure the KBScan pin 
  GPIO_InitStructure.GPIO_Pin =  P_LedScan_PIN1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(P_LedScan1_GPIO_PORT, &GPIO_InitStructure);
  
  // Enable the LedScan 
  RCC_AHBPeriphClockCmd(P_LedScan2_GPIO_CLK, ENABLE);
  // Configure the KBScan pin 
  GPIO_InitStructure.GPIO_Pin =  P_LedScan_PIN2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(P_LedScan2_GPIO_PORT, &GPIO_InitStructure);
   
  // Enable the LedScan 
  RCC_AHBPeriphClockCmd(P_LedScan3_GPIO_CLK, ENABLE);
  // Configure the KBScan pin 
  GPIO_InitStructure.GPIO_Pin =  P_LedScan_PIN3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(P_LedScan3_GPIO_PORT, &GPIO_InitStructure);
}
//=====================================================
//	
//=====================================================	
unsigned char F_ReadScanKey(void)
{
  unsigned short ReadkeyData=0;
  ReadkeyData = GPIO_ReadInputData(P_KBSense_GPIO_PORT);
  /*
    if(!GPIO_ReadInputDataBit( P_KBSense_GPIO_PORT, P_KBSense_PIN1 )) {		
      ReadkeyData |= 0x01;
    }
    R_Key.ScanKeyTemp = R_Key.ScanKeyTemp << 1;	
      if(!GPIO_ReadInputDataBit( P_KBSense_GPIO_PORT, P_KBSense_PIN2 )) {		
        ReadkeyData |= 0x01;
      }	
      R_Key.ScanKeyTemp = R_Key.ScanKeyTemp << 1;	
        if( !GPIO_ReadInputDataBit( P_KBSense_GPIO_PORT, P_KBSense_PIN3 )) {		
          ReadkeyData |= 0x01;
        }
        R_Key.ScanKeyTemp = R_Key.ScanKeyTemp << 1;	
          if( !GPIO_ReadInputDataBit( P_KBSense_GPIO_PORT, P_KBSense_PIN4 )) {	
            ReadkeyData |= 0x01;
          }
          R_Key.ScanKeyTemp = R_Key.ScanKeyTemp << 1;
            if( !GPIO_ReadInputDataBit( P_KBSense_GPIO_PORT, P_KBSense_PIN5 )) {
              ReadkeyData |= 0x01;
            }
     */       
     return (unsigned char)ReadkeyData;       
}
//==========================================================
//
//==========================================================
void  F_LedKeyScan(void)
{
  unsigned  char  i;
  
  R_LedScanAdr++;
  if(R_LedScanAdr>2)
    R_LedScanAdr=0;
  switch(R_LedScanAdr)
  {
  case  0:
    R_ScanKeyBuf[2] = ~F_ReadScanKey();
    for(i=0;i<3;i++)
      R_ScanKey[i]=R_ScanKeyBuf[i];
    ScanKyeEndFlg=1;
    //========
    for(i=0;i<3;i++)
      R_ScanKeyBuf[i]=0;
    //================
    ScanLine1Out(0);
    ScanLine2Out(0);
    ScanLine3Out(1);
    C_delay(10);
    LedScan1Out(1);
    LedScan2Out(1);
    LedScan3Out(1);
    if(R_LedSeg & 0x01)
      LedScan1Out(0);
    if(R_LedSeg & 0x02)
      LedScan2Out(0);
    if(R_LedSeg & 0x04)
      LedScan3Out(0);
    ScanLine1Out(1);
    break;
  //===================
  case  1:
    R_ScanKeyBuf[0] = ~F_ReadScanKey();
    //================
    ScanLine1Out(0);
    ScanLine2Out(0);
    ScanLine3Out(1);
    C_delay(10);
    LedScan1Out(1);
    LedScan2Out(1);
    LedScan3Out(1);
    if(R_LedSeg & 0x08)
      LedScan1Out(0);
    if(R_LedSeg & 0x10)
      LedScan2Out(0);
    if(R_LedSeg & 0x20)
      LedScan3Out(0);
    ScanLine2Out(1);
    break;    
  //===================
  case  2:
    R_ScanKeyBuf[1] = ~F_ReadScanKey(); 
    LedScan1Out(1);
    LedScan2Out(1);
    LedScan3Out(1);
    ScanLine1Out(0);
    ScanLine2Out(0);
    ScanLine3Out(0);
    break;
  }
}
//==========================================================
//
//==========================================================
void	F_CheckGetKey(void)
{
  if(KeyRam!=0)
  {
    if(KeyRam==KeyRamBak)
    {	
      R_NoKeyCnt=0;	
      KeyCnt++;	
      if(KeyCnt==1)	//Wait Debums
      {
        R_IdleTime=0;	
        R_SleepTime=0;
        R_LongFastKeyCnt=0;
        switch(KeyRam)		//short key
        {
          case	start_stop_KeyVal:      KeyCode=start_stop_KeyVal;      break;
          case	Mode_KeyVal:            KeyCode=Mode_KeyVal;            break;
          case	Set_KeyVal:             KeyCode=Set_KeyVal;             break;
          case	Enter_KeyVal:           KeyCode=Enter_KeyVal;           break;
          //=========
          case	SpeedUp_KeyVal:   
          case	HandSpeedUp_KeyVal: 
            KeyCode=SpeedUp_KeyVal;         
            break;
          case	SpeedDown_KeyVal:    
          case	HandSpeedDown_KeyVal:     
            KeyCode=SpeedDown_KeyVal;       
            break;
          case	InclineDown_KeyVal:
          case	HandInclineDown_KeyVal:
            KeyCode=InclineDown_KeyVal;     
            break;
          case	InclineUp_KeyVal:  
          case	HandInclineUp_KeyVal:
            KeyCode=InclineUp_KeyVal;       
            break;
            //==========
          case	Eng1_KeyVal:            KeyCode=Eng1_KeyVal;            break;
          case	Eng2_KeyVal:            KeyCode=Eng2_KeyVal;            break;
          case	Eng3_KeyVal:            KeyCode=Eng3_KeyVal;            break;
          case	Eng4_KeyVal:            KeyCode=Eng4_KeyVal;            break;
          case	EepromClear_KeyVal:     KeyCode=EepromClear_KeyVal;     break;
          case	QuickInc_2_KeyVal:      KeyCode=QuickInc_2_KeyVal;      break;
          case	QuickInc_4_KeyVal:      KeyCode=QuickInc_4_KeyVal;      break;
          case	QuickInc_6_KeyVal:      KeyCode=QuickInc_6_KeyVal;      break;
          case	QuickInc_8_KeyVal:      KeyCode=QuickInc_8_KeyVal;      break;
          case	QuickInc_10_KeyVal:     KeyCode=QuickInc_10_KeyVal;     break;
          case	QuickInc_12_KeyVal:     KeyCode=QuickInc_12_KeyVal;     break;
          case	QuickSpd_1_KeyVal:      KeyCode=QuickSpd_1_KeyVal;      break;
          case	QuickSpd_4_KeyVal:      KeyCode=QuickSpd_4_KeyVal;      break;
          case	QuickSpd_7_KeyVal:      KeyCode=QuickSpd_7_KeyVal;      break;
          case	QuickSpd_10_KeyVal:     KeyCode=QuickSpd_10_KeyVal;      break;
          case	QuickSpd_13_KeyVal:     KeyCode=QuickSpd_13_KeyVal;     break;
          case	QuickSpd_16_KeyVal:     KeyCode=QuickSpd_16_KeyVal;     break;
        }
      }
      //=====================
      if(KeyCnt==20)    //20mS*15=0.4s
      {		
        switch(KeyRam)  //long key
        {
          case	InclineDown_KeyVal:
          case	HandInclineDown_KeyVal:
            KeyCode=InclineDown_KeyVal;
            F_LongFast();
            break;
          //===============	
          case	InclineUp_KeyVal:  
          case	HandInclineUp_KeyVal:
            KeyCode=InclineUp_KeyVal;
            F_LongFast();
            break;
          //===============						
          case	SpeedDown_KeyVal:    
          case	HandSpeedDown_KeyVal:   	
            KeyCode=SpeedDown_KeyVal;
            F_LongFast();
            break;
          //===============
          case	SpeedUp_KeyVal:   
          case	HandSpeedUp_KeyVal: 
            KeyCode=SpeedUp_KeyVal;
            F_LongFast();
            break;
        }
      }
      //=====================
      if(KeyCnt==200)           //20mS*200=4s
      {
        switch(KeyRam)          //short key
        {
          case	Set_KeyVal:	
            KeyCode=LongSet_KeyVal;		
            break;			
        }
      }
      if(KeyCnt==250)           //20mS*200=4s
      {
        switch(KeyRam)
        {
          case	Mode_KeyVal:	
            KeyCode=LongMode_KeyVal;		
            break;			
        }
      }
      //=====================
      if(KeyCnt>253)
      {
        KeyCnt=253;             //限制數字超過255
      }
    }	
    else
      KeyRamBak=KeyRam;         //備份key
  }		
  else          //no key
  {
    R_NoKeyCnt++;
    if(R_NoKeyCnt>2)
    {
      R_NoKeyCnt=0;
      R_LongFastKeyCnt=0;
      KeyCnt=0;
      KeyRamBak=0;
      KeyCode=0;
      R_LongKeyStopBz=0;
    }
  }
}

//===================================================
void	F_ReadKey(void)
{
  KeyRam=0;
  if(ScanKyeEndFlg==1)
  {  
    switch(R_ScanKey[0])
    {
      case 0:                   break;	
      case 1:   KeyRam=1;       break;	
      case 2:   KeyRam=2;       break;
      case 4:   KeyRam=3;       break;			
      case 8:   KeyRam=4;       break;
      case 16:  KeyRam=5;       break;
      case 32:  KeyRam=6;       break;
      case 64:  KeyRam=7;       break; 
      case 128: KeyRam=8;       break; 
    default :   KeyRam=0;       break;			
    }
    switch(R_ScanKey[1])
    {
      case 0:                   break;		
      case 1:	KeyRam=9;       break;			
      case 2:	KeyRam=10;      break;
      case 4:	KeyRam=11;      break;			
      case 8:	KeyRam=12;      break;	
      case 16:	KeyRam=13;      break;
      case 32:	KeyRam=14;      break;	
      case 64:	KeyRam=15;      break; 
      case 128: KeyRam=16;      break; 
      default : KeyRam=0;       break;	
    }
    switch(R_ScanKey[2])
    {
    case  0:                    break;
    case  1:	KeyRam=17;      R_KeyTest=12;    break;
    case  2:	KeyRam=18;      R_KeyTest=11;    break;
    case  4:	KeyRam=19;      R_KeyTest=10;    break;
    case  8:	KeyRam=20;      R_KeyTest=9;    break;
    case  16:	KeyRam=21;      break;	
    case  32:	KeyRam=22;      break;
    case  64:	KeyRam=23;      break;  
    case 128:   KeyRam=24;      break; 
    default :   KeyRam=0;       break;
    }
    if((R_ScanKey[0]==8) && (R_ScanKey[1]==1))
    {	
      KeyRam=25;
      KeyCnt=0;
    }
      if(R_ScanKey[1]==5)
      {
        KeyRam=26;
        KeyCnt=0;
      }
        if((R_ScanKey[0]==8) && (R_ScanKey[1]==2))
        {	
          KeyRam=27;
          KeyCnt=0;
        }
          if((R_ScanKey[0]==8) && (R_ScanKey[1]==4))
          {		
            KeyRam=28;
            KeyCnt=0;
          }
            if((R_ScanKey[0]==1) && (R_ScanKey[1]==1))
            {
              KeyRam=29;
              KeyCnt=0;
            }
    ScanKyeEndFlg=0;
  }
}
//=====================================================
void  F_LongFast(void)
{
  if(R_LongFastKeyCnt<200)
    R_LongFastKeyCnt++;
    switch(R_LongFastKeyCnt)
    {  
      case 0:
                  
        break;
      //========= 
      case 1:
      KeyCnt=10;	            
        break;
      //=========  
      case 2:
      KeyCnt=10;	     
        break;
      //=========  
      case 3:
      KeyCnt=10;	          
        break;
      //=========  
      case 4:
      KeyCnt=10;	      
        break;
      //========= 
      case 5:
      KeyCnt=10;	         
        break;
      //========= 
      case 6:
      KeyCnt=10;	   
        break;
      //========= 
      case 7:
      KeyCnt=10;	    
        break;
      //========= 
      case 8:
      KeyCnt=10;	 
        break;
      //=========       
      case 9:
      KeyCnt=10;	     
        break;
      //========= 
      case 10:
      KeyCnt=15;	            
        break;
      //=========  
      case 11:
      KeyCnt=15;	     
        break;
      //=========  
      case 12:
      KeyCnt=15;	          
        break;
      //=========  
      case 13:
      KeyCnt=15;	      
        break;
      //========= 
      case 14:
      KeyCnt=15;	         
        break;
      //========= 
      case 15:
      KeyCnt=15;	   
        break;
      //========= 
      case 16:
      KeyCnt=15;	    
        break;
      //========= 
      case 17:
      KeyCnt=15;	 
        break;
      //=========       
      case 18:
      KeyCnt=15;	     
        break;
      //=========  		
      default :
      KeyCnt=19;
        break;
      }
    R_LongKeyStopBz=1;
}
//==============================================================================
// ERP IO 設定
//==============================================================================
void F_ERP_KBSet(void)
{
    LedScan1Out(1);
    LedScan2Out(1);
    LedScan3Out(1);
    ScanLine1Out(1);
    ScanLine2Out(1);
    ScanLine3Out(0);
}
