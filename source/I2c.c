#include "connect.h"
/* Private typedef -----------------------------------------------------------*/
GPIO_InitTypeDef SDAOutput_InitStructure;
GPIO_InitTypeDef SDAInput_InitStructure;
/* Private define ------------------------------------------------------------*/
//EEPROM SCL
#define P_SCL_PIN                       GPIO_Pin_8                              
#define P_SCL_GPIO_PORT                 GPIOB
#define P_SCL_GPIO_CLK                  RCC_AHBPeriph_GPIOB
//EEPROM SDA
#define P_SDA_PIN                       GPIO_Pin_9                            
#define P_SDA_GPIO_PORT                 GPIOB
#define P_SDA_GPIO_CLK                  RCC_AHBPeriph_GPIOB


/* Private macro -------------------------------------------------------------*/
#define M_SCL_SetHigh                   P_SCL_GPIO_PORT->BSRR = P_SCL_PIN 
#define M_SCL_SetLow                    P_SCL_GPIO_PORT->BRR = P_SCL_PIN 
#define M_SDA_SetHigh                   P_SDA_GPIO_PORT->BSRR = P_SDA_PIN
#define M_SDA_SetLow                    P_SDA_GPIO_PORT->BRR = P_SDA_PIN 
#define M_SDA_Read                      GPIO_ReadInputDataBit(P_SDA_GPIO_PORT,P_SDA_PIN)
/* Private variables ---------------------------------------------------------*/

//==============================================================================
//SDA 輸出設定
//==============================================================================
void F_SDA_SetOutput(void)
{
  GPIO_Init(P_SDA_GPIO_PORT, &SDAOutput_InitStructure);
}
//==============================================================================
//SDA 輸入設定
//==============================================================================
void F_SDA_SetInput(void)
{
  GPIO_Init(P_SDA_GPIO_PORT, &SDAInput_InitStructure);
}
//==============================================================================
//This routine will setup the I2C Port
//==============================================================================
void  F_InitialEEPROM_GPIO(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  // Output EEPROM    
  // Enable the EEPROM SCL
  RCC_AHBPeriphClockCmd(P_SCL_GPIO_CLK, ENABLE);
  // Configure the EEPROM SCL  pin
  GPIO_InitStructure.GPIO_Pin = P_SCL_PIN ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(P_SCL_GPIO_PORT, &GPIO_InitStructure);
  //set high
  P_SCL_GPIO_PORT->BSRR = P_SCL_PIN;  
  
  // Enable EEPROM SDA
  RCC_AHBPeriphClockCmd(P_SDA_GPIO_CLK, ENABLE);
  // Configure the EEPROM SDA  pin 
  GPIO_InitStructure.GPIO_Pin = P_SDA_PIN ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(P_SDA_GPIO_PORT, &GPIO_InitStructure);
  //set high
  P_SDA_GPIO_PORT->BSRR = P_SDA_PIN;
  
  // Configure the EEPROM SDA  pin
  SDAOutput_InitStructure.GPIO_Pin = P_SDA_PIN ;
  SDAOutput_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  SDAOutput_InitStructure.GPIO_OType = GPIO_OType_PP;
  SDAOutput_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  SDAOutput_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  // Configure the EEPROM SDA  pin 
  SDAInput_InitStructure.GPIO_Pin = P_SDA_PIN ;
  SDAInput_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  SDAInput_InitStructure.GPIO_OType = GPIO_OType_PP;
  SDAInput_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  SDAInput_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
}
//==============================================================================
//This routine will EUP the I2C Port
//==============================================================================
void  F_EUP_EEPROM_GPIO(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  // Output EEPROM    
  // Enable the EEPROM SCL
  RCC_AHBPeriphClockCmd(P_SCL_GPIO_CLK, ENABLE);
  // Configure the EEPROM SCL  pin
  GPIO_InitStructure.GPIO_Pin = P_SCL_PIN ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(P_SCL_GPIO_PORT, &GPIO_InitStructure);
  //set low
  P_SCL_GPIO_PORT->BRR = P_SCL_PIN;  
  //M_SCL_SetHigh;
  // Enable EEPROM SDA
  RCC_AHBPeriphClockCmd(P_SDA_GPIO_CLK, ENABLE);
  // Configure the EEPROM SDA  pin 
  GPIO_InitStructure.GPIO_Pin = P_SDA_PIN ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(P_SDA_GPIO_PORT, &GPIO_InitStructure);
  //set low
  P_SDA_GPIO_PORT->BRR = P_SDA_PIN;
  //M_SDA_SetHigh;
}
//==============================================================================
//EEPROM 延遲
//==============================================================================
void F_EEDelay(volatile unsigned short cnt)
{
  /*
  volatile unsigned short c;
  // Delay for EEPROM Write
  c=0;
  while(c<cnt)
  {
    c++;
    __asm("nop");
    __asm("nop");
    __asm("nop");
    __asm("nop");
    __asm("nop");      
  }
  */
    while(cnt>1)
    {
      cnt--;
      __asm("nop");
      __asm("nop");
      __asm("nop");
      __asm("nop");
      __asm("nop");  
    }
    cnt=0;
}
//==============================================================================
//This routine returns a 0 if the I2C device sends an acknowledge
//==============================================================================
unsigned char F_I2C_Ackn(void)
{
  unsigned char Ackn = 0,PortData;      // Temp RAM for Ackn flag
  
  F_SDA_SetInput();                     // Set SDA to input
  M_SCL_SetHigh;                        // Clock the ACK bit
  F_EEDelay(5); 
  PortData = M_SDA_Read;  
  if(PortData)
    Ackn = 1;                           // Check the ACK bit on SDA	
  M_SCL_SetLow;                         // Clear the clock
  return Ackn;                          // Return our ACK bit
}	
//==============================================================================
//This routine will send the I2C Start Bit
//==============================================================================
void F_I2C_Start (void)
{  
  F_SDA_SetOutput();                    // Set SDA to output
  M_SCL_SetHigh;                        // Set SCL High
  F_EEDelay(7);
  M_SDA_SetHigh;                        // Set SDA High
  F_EEDelay(7);                         // Delay for EEPROM Write
  M_SDA_SetLow;                         // Clear SDA
  F_EEDelay(7);                         // Delay for EEPROM Write
}
//==============================================================================
//This routine will send the I2C Stop Bit
//==============================================================================
void F_EepromDelayTime(void)
{
    EepromDelayTimeCnt++;
}

void F_I2C_Stop (void)
{
  F_SDA_SetOutput();                    // Set SDA to output
  M_SDA_SetLow;                         // Clear SDA
  __asm("nop");
  M_SCL_SetLow;                         // Clear SCL
  F_EEDelay(7);
  M_SCL_SetHigh;                        // Set SCL High
  F_EEDelay(7);
  M_SDA_SetHigh;                        // Set SDA High
  EepromDelayTimeCnt = 0;
  while(EepromDelayTimeCnt <=6) {

  }
  //F_EEDelay(60000);
}
//==============================================================================
void F_Read_I2C_Stop (void)
{
  F_SDA_SetOutput();                    // Set SDA to output
  M_SDA_SetLow;                         // Clear SDA
  __asm("nop");
  M_SCL_SetLow;                         // Clear SCL
  F_EEDelay(7);
  M_SCL_SetHigh;                        // Set SCL High
  F_EEDelay(7);
  M_SDA_SetHigh;                        // Set SDA High
}
//==============================================================================
//This routine will send the I2C clock pulse
//==============================================================================
void F_I2C_Clock (void)
{
  M_SCL_SetHigh;                        // Set SCL high
  F_EEDelay(5);                         // Delay for EEPROM Write
  M_SCL_SetLow;                         // Set SCL low
  F_EEDelay(5);                         // Delay for EEPROM Write
}
//==============================================================================
//This routine will write a byte to the I2C device
//==============================================================================
void F_Write_I2C_Byte(unsigned char byte)
{
  unsigned char i;
  
  F_SDA_SetOutput();                    // Set SDA to output
  M_SCL_SetLow;                         // Clear I2C SCL PIN
  F_EEDelay(300); 
  
  for (i = 0; i < 8; i++)               // Loop for our 8 bits
  {  				
    // Set or Clear SDA pin
    if((byte & 0x80) == 0x80)
      M_SDA_SetHigh;                    // Set I2C SDA PIN
    else 
      M_SDA_SetLow;                     // Clear I2C SDA PIN
    
    M_SCL_SetHigh;                      // Set SCL High, Clock data
    F_EEDelay(300); 
    byte = byte << 1;                   // Shift data in buffer right one
    M_SCL_SetLow;                       // Clear SCL
    F_EEDelay(300); 
  }
  while(F_I2C_Ackn());                  // Check for acknowledge from I2C device	
}
//==============================================================================
//This routine will read a byte from the I2C device
//==============================================================================
unsigned char F_Read_I2C_Byte(void)
{	
  unsigned char i,buff = 0,PortData;
  F_SDA_SetInput();  
  
  for(i = 0; i < 8; i++)
  {
    buff = buff << 1;           // Set SDA to input
    M_SCL_SetHigh;              // Set SCL High,Clock bit out
    F_EEDelay(5);
    PortData = M_SDA_Read;      // Read data on P_SDA_Pin pin
    if(PortData) 
      buff = buff | 0x01;	
    M_SCL_SetLow;               // Clear SCL
    F_EEDelay(5);
  }
  // No ACK
  F_I2C_Clock();                // Clock I2C bit
  return buff;                  // Return our I2C byte
}
//==============================================================================
//This routine will write the I2C device code,set the device chip select bits, 
//and set or clear the I2C R/W bit	
//==============================================================================
void F_Write_I2C_Control(unsigned char D_Code,unsigned char H_ADD,unsigned char RW)
{
  // Send the I2C device Control code
  M_SCL_SetLow;                                 // Clear SCL clock
  F_EEDelay(5);
  
  if((D_Code & 0x08) == 0x08) 
    M_SDA_SetHigh;                              // Set I2C SDA PIN
  else 
    M_SDA_SetLow;                               // Clear I2C SDA PIN
  F_I2C_Clock();                                // Clock I2C bit
  
  if((D_Code & 0x04) == 0x04) 
    M_SDA_SetHigh;                              // Set I2C SDA PIN
  else 
    M_SDA_SetLow;                               // Clear I2C SDA PIN
  F_I2C_Clock();                                // Clock I2C bit
  
  if((D_Code & 0x02) == 0x02) 
    M_SDA_SetHigh;                              // Set I2C SDA PIN
  else 
    M_SDA_SetLow;                               // Clear I2C SDA PIN
  F_I2C_Clock();                                // Clock I2C bit
  
  if((D_Code & 0x01) == 0x01) 
    M_SDA_SetHigh;                              // Set I2C SDA PIN
  else 
    M_SDA_SetLow;                               // Clear I2C SDA PIN
  F_I2C_Clock();                                // Clock I2C bit
  
  // Send the I2C Control byte chip selects bits 
  
  if((H_ADD & 0x04) == 0x04) 
    M_SDA_SetHigh;                              // Set I2C SDA PIN
  else 
    M_SDA_SetLow;                               // Clear I2C SDA PIN
  F_I2C_Clock();                                // Clock I2C bit
  
  if((H_ADD & 0x02) == 0x02) 
    M_SDA_SetHigh;                              // Set I2C SDA PIN
  else 
    M_SDA_SetLow;                               // Clear I2C SDA PIN
  F_I2C_Clock();                                // Clock I2C bit
  
  if((H_ADD & 0x01) == 0x01) 
    M_SDA_SetHigh;                              // Set I2C SDA PIN
  else 
    M_SDA_SetLow;                               // Clear I2C SDA PIN
  F_I2C_Clock();                                // Clock I2C bit
  
  // Set or Clear the read / write bit for I2C control 
  if(RW) 
    M_SDA_SetHigh;                              // Set I2C SDA PIN
  else 
    M_SDA_SetLow;                               // Clear I2C SDA PIN
  F_I2C_Clock();                                // Clock I2C bit
  while(F_I2C_Ackn());                          // Check for acknowledge from I2C device
}
//==============================================================================
// Example of using Imagecraft I2C driver                         
// to write to an external 8 bit address EEPROM                  
// H_ADD is the hardware address set on the device A0,A1 & A2 pins 
// M_ADD is the devices internal memory address                   
// Data is user data to be writen                                
//==============================================================================
void EE_Write(unsigned char M_ADD,unsigned char Data)
{
  volatile unsigned char H_ADD = 0;
  F_I2C_Start();                                // Set I2C start condition
  F_Write_I2C_Control(0x0A,H_ADD,0);            // Send the EEPROM control Byte
  F_Write_I2C_Byte(M_ADD);                      // Send the EEPROM internal Address
  F_Write_I2C_Byte(Data);                       // Send the EEPROM Data
  F_I2C_Stop();                                 // Set I2C Stop condition
}
//==============================================================================
// Example of using Imagecraft I2C driver                          
// to Read an external 8 bit address EEPROM                        
// H_ADD is the hardware address set on the device A0,A1 & A2 pins  
// M_ADD is the devices internal memory address                     
// Data is user data to be writen                                        
//==============================================================================
unsigned char EE_Read(unsigned char M_ADD)
{
  unsigned char Temp;                           // Temp RAM for EEPROM Read
  volatile unsigned char H_ADD = 0;
    
  F_I2C_Start();                                // Set I2C start condition
  F_Write_I2C_Control(0x0A,H_ADD,0);            // Send the EEPROM control Byte   // Dummy write to set address
  F_Write_I2C_Byte(M_ADD);                      // Send the EEPROM internal Address
  F_I2C_Start();                                // Set I2C start condition
  F_Write_I2C_Control(0x0A,H_ADD,1);            // Send the EEPROM control Byte
  Temp = F_Read_I2C_Byte();                     // Read data from EEPROM
  F_Read_I2C_Stop();                                 // Set I2C Stop condition
  return  Temp;                                 // Return data from EEPROM
}
//============================================================
//
//============================================================
unsigned  char  F_ReadFlg(unsigned  char  ReadDataAdr)
{
    unsigned  char Data;
    if(EE_Read(ReadDataAdr)==0)
      Data=0;
      else
        Data=1;
    return  Data;     
}
//==============
unsigned  int F_Read2Byte(unsigned  char  ReadDataAdr)
{
    unsigned  char  TempByte_H,TempByte_L;
    unsigned  int Data;
    TempByte_L  = EE_Read(ReadDataAdr);
    TempByte_H  = EE_Read(ReadDataAdr+1);
    Data  = (unsigned  int)(TempByte_H << 8);
    Data  |= TempByte_L;
    return  Data;
}
//==============
unsigned  long  F_Read4Byte(unsigned  char  ReadDataAdr)
{
    unsigned  char  TempByte_1,TempByte_2,TempByte_3,TempByte_4;
    unsigned  long  Data;
    
    TempByte_1  = EE_Read(ReadDataAdr);
    TempByte_2  = EE_Read(ReadDataAdr+1);
    TempByte_3  = EE_Read(ReadDataAdr+2);
    TempByte_4  = EE_Read(ReadDataAdr+3);

    Data = (unsigned long)TempByte_4 << 24;
    Data |= (unsigned long)TempByte_3 << 16;
    Data |= (unsigned int)TempByte_2 << 8;
    Data |= TempByte_1;
    return  Data;
}
//==============
void  F_Write2Byte(unsigned char  WriteDataAdr,unsigned int Data)
{
    unsigned  char  TempByte_H,TempByte_L;
    TempByte_L = Data;
    TempByte_H = Data >>  8;
    EE_Write(WriteDataAdr,TempByte_L);
    EE_Write(WriteDataAdr+1,TempByte_H);
}
//==============
void  F_Write4Byte(unsigned char  WriteDataAdr,unsigned long  Data)
{
    unsigned  char  TempByte_1,TempByte_2,TempByte_3,TempByte_4;
    TempByte_1  = Data;
    TempByte_2  = Data >> 8;
    TempByte_3  = Data >> 16;
    TempByte_4  = Data >> 24;
    
    EE_Write(WriteDataAdr,TempByte_1);
    EE_Write(WriteDataAdr+1,TempByte_2);
    EE_Write(WriteDataAdr+2,TempByte_3);
    EE_Write(WriteDataAdr+3,TempByte_4);
}
//==============
void	F_EE_init(void)
{
    static unsigned  char  TempByte1,TempByte2,TempByte3,TempByte4;
    EE_Write(0xFF,0xA5);
    EE_Write(0xFE,0x5A);
    TempByte1=EE_Read(0xFF);
    TempByte2=EE_Read(0xFE);
    //============================
    if((TempByte1==0xA5)&&(TempByte2==0x5A))
    { //  Eeprom 正確
      TempByte1=EE_Read(0xFA);
      TempByte2=EE_Read(0xFB);
      TempByte3=EE_Read(0xFC);
      TempByte4=EE_Read(0xFD);
      if((TempByte1==EepromVer_1) && (TempByte2==EepromVer_2) && (TempByte3==EepromVer_3) && (TempByte4==EepromVer_4))
      {
        F_ReadProg_EE();
      }
      else
      { //  Eeprom  初始化
        F_EepromNoDataInit();
      }
    }
    else
    { //  Eeprom  錯誤 進入EER模式	
      R_SysMode=SysErrModeVal;
      R_ErrData=1;
    }
}
//===========================================================
void  F_EepromNoDataInit(void)
{
      EE_Write(0xFA,EepromVer_1);
      EE_Write(0xFB,EepromVer_2);
      
      ChangeUnitFlg=UnitVal;          //  預設  公制 英制單位    
      F_EepromClear_2();              //  公英制切換需清除的資料
      
      //R_Age=AgeDefVal;                //  預設年齡
      //EE_Write(EE_Age,R_Age);
      //=========
      R_IncMax=IncMaxVal;             //  預設Incline 最大段數
      EE_Write(EE_IncMax,R_IncMax);
      //=========
      R_IncMaxAd=0xF0;
      R_IncMinAd=0x1A;
      R_IncCarryAd=0x0A;
      IncUpDownFlg=1;     //正向
      EE_Write(EE_IncUpDown,1);						
      EE_Write(EE_IncMaxAd,R_IncMaxAd);
      EE_Write(EE_IncMinAd,R_IncMinAd);
      EE_Write(EE_IncCarryAd,R_IncCarryAd);
      //=========
      R_WheelSize=242;    //  預設輪徑
      F_Write2Byte(EE_WheelSize_L,R_WheelSize);
      //=========
      R_PwmLowSpeed=10;
      EE_Write(EE_PwmLowSpeed,R_PwmLowSpeed);	
      //=========
      F_User_Init(User_1_SpeedAdrVal,User_1_IncAdrVal);
      F_User_Init(User_2_SpeedAdrVal,User_2_IncAdrVal);
      F_User_Init(User_3_SpeedAdrVal,User_3_IncAdrVal);
      F_EepromClear_3();
      F_EepromClear_4();
      //=========
      EE_Write(EE_SaveUserInit,0); 
    #if	O_A2121034	//	1_DC 0_AC
      EE_Write(EE_AcDcMotor,1); 
      AcDcMotorFlg=1;
    #else
      EE_Write(EE_AcDcMotor,0); 
      AcDcMotorFlg=0;
    #endif
      ShowAcDcMotorFlg=AcDcMotorFlg;
      //=========
      EE_Write(0xFC,EepromVer_3);
      EE_Write(0xFD,EepromVer_4);
}
//===================================
void  F_ReadProg_EE(void)
{
    //==================
    ChangeUnitFlg=F_ReadFlg(EE_Unit);
    if(ChangeUnitFlg==0)
    {   //公制
    R_SpeedMax=EE_Read(EE_SpeedMaxKm);
    R_SpeedMin=EE_Read(EE_SpeedMinKm); 
    }
      else
      { //英制
      R_SpeedMax=EE_Read(EE_SpeedMaxMile);
      R_SpeedMin=EE_Read(EE_SpeedMinMile); 
      }
    //==================  
    //R_Age=EE_Read(EE_Age);
    R_Weight=F_Read2Byte(EE_Wight_L);
    R_IncMax=EE_Read(EE_IncMax);
    R_IncMaxAd=EE_Read(EE_IncMaxAd);
    R_IncMinAd=EE_Read(EE_IncMinAd);
    R_IncCarryAd=EE_Read(EE_IncCarryAd);
    IncUpDownFlg=F_ReadFlg(EE_IncUpDown);
    R_WheelSize=F_Read2Byte(EE_WheelSize_L);
    R_PwmLowSpeed=EE_Read(EE_PwmLowSpeed);
    //==================
    R_TotalDis=F_Read4Byte(EE_TotalDisBye_1);  	 
    R_TotalTime=F_Read4Byte(EE_TotalTimeBye_1);
    R_TotalLube=F_Read2Byte(EE_TotalLubeBye_L); 
    //==================
    AcDcMotorFlg=F_ReadFlg(EE_AcDcMotor);
    ShowAcDcMotorFlg=AcDcMotorFlg;
    if(EE_Read(EE_SaveUserInit)==1)
    {	// 工程模式下有修改公英制 需清除USER
      EE_Write(EE_SaveUserInit,0);
      F_User_Init(User_1_SpeedAdrVal,User_1_IncAdrVal);
      F_User_Init(User_2_SpeedAdrVal,User_2_IncAdrVal);
      F_User_Init(User_3_SpeedAdrVal,User_3_IncAdrVal);
    }
}
//====================================================
//  公英制切換需清除的資料
//====================================================
void  F_EepromClear_2(void)
{
    if(ChangeUnitFlg==0)
    {  // 公制 預設值
      R_Weight=WeightKgDefVal;
      R_SpeedMax=SpeedKmMaxVal;       //  預設  公制速度最大
      R_SpeedMin=SpeedKmMinVal;       //  預設  公制速度最小
      EE_Write(EE_SpeedMaxKm,R_SpeedMax);  
      EE_Write(EE_SpeedMinKm,R_SpeedMin);  
      EE_Write(EE_Unit,0); 
    }
      else
      {  // 英制 預設值
        R_Weight=WeightLBDefVal;
        R_SpeedMax=SpeedMileMaxVal;
        R_SpeedMin=SpeedMileMinVal;
        EE_Write(EE_SpeedMaxMile,R_SpeedMax);  
        EE_Write(EE_SpeedMinMile,R_SpeedMin); 
        EE_Write(EE_Unit,1);
      }
      F_Write2Byte(EE_Wight_L,R_Weight);
}
//===========================================================
//  總里程 總時間 清除
//===========================================================
void  F_EepromClear_3(void)
{
    R_TotalTime=0;
    R_TotalDis=0;
    F_Write4Byte(EE_TotalTimeBye_1,0);
    F_Write4Byte(EE_TotalDisBye_1,0);
}
//===========================================================
//  加油提示時間 清除
//===========================================================
void  F_EepromClear_4(void)
{
    R_TotalLube=0;
    F_Write2Byte(EE_TotalLubeBye_L,0);
}
//====================================================
//  
//====================================================
void	F_User_Init(unsigned  char  EE_UserSpeedAdr,unsigned  char  EE_UserIncAdr)
{
    unsigned	char	i;
    for(i=EE_UserSpeedAdr;i<(EE_UserSpeedAdr+30);i++)
    {
      EE_Write(i,R_SpeedMin);
    }
      for(i=EE_UserIncAdr;i<(EE_UserIncAdr+30);i++)
      {
        EE_Write(i,1);
      }
}
//====================
void  F_ReadUserProfile(unsigned  char  EE_UserSpeedAdr,unsigned  char  EE_UserIncAdr)
{
    unsigned   char i,SpeedTemp,IncTemp;
    for(i=0;i<30;i++)
    {  
      SpeedTemp=EE_Read(EE_UserSpeedAdr+i);
      R_SaveSpeedProg[i]=SpeedTemp;
      F_ChangeGraphSpeed(i,SpeedTemp);
      IncTemp=EE_Read(EE_UserIncAdr+i);
      R_SaveIncProg[i]=IncTemp;
      F_ChangeGraphInc(i,IncTemp);
    }
    R_User_SetSpeed=EE_Read(EE_UserSpeedAdr);
    R_User_SetInc=EE_Read(EE_UserIncAdr);
}
//========================
void F_UserCholeIncSpd(unsigned	char EE_UserSpeedAdr,unsigned char EE_UserIncAdr)
{
  unsigned	char	i,SpeedTemp,IncTemp;
  
  for(i=0;i<30;i++)
  {
    switch(R_CholeIncSpdMode)
    {
      case 0:		//      Speed Inc混合
        SpeedTemp=EE_Read(EE_UserSpeedAdr+i);
        IncTemp=EE_Read(EE_UserIncAdr+i);
        break;
      //==============
      case 1:           //      Speed
        SpeedTemp=EE_Read(EE_UserSpeedAdr+i);
        IncTemp=IncDefVal;				
        break;
      //==============	
      case 2:		//	Inc
        IncTemp=EE_Read(EE_UserIncAdr+i);
        SpeedTemp=R_SpeedMin;
        break;
    }
    R_SaveSpeedProg[i]=SpeedTemp;	
    F_ChangeGraphSpeed(i,SpeedTemp);
    R_SaveIncProg[i]=IncTemp;
    F_ChangeGraphInc(i,IncTemp);
  }
}