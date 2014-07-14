#include "connect.h"

unsigned char const M01[] ={"SELECT PROGRAM"};
unsigned char const M02[] ={"PAUSE. PRESS START TO RESUME"};
unsigned char const M03[] ={"PRESS START TO BEGIN"};
unsigned char const M04[] ={"PRESS START/MODE/ENTER"};
unsigned char const M05[] ={"PRESS START/MODE/SELECT/ENTER"};
unsigned char const M06[] ={"LUBRICATE DECK"};
unsigned char const M07[] ={"PRESS MODE 3 SECONDS TO CANCEL THIS MESSAGE"};
unsigned char const M08[] ={"ENTER WORKOUT DISTANCE"};
unsigned char const M09[] ={"END OF WORKOUT"};
unsigned char const M10[] ={"ENTER WORKOUT CALORIES"};
unsigned char const M11[] ={"ENTER WORKOUT TIME"};
unsigned char const M12[] ={"ENTER AGE"};
unsigned char const M13[] ={"ENTER TARGET HEART RATE"};
unsigned char const M14[] ={"WARM UP-PRESS MODE TO BYPASS"};
unsigned char const M15[] ={"COOL DOWN"};		//COOL DOWN-PRESS STOP TO BYPASS
unsigned char const M16[] ={"PLEASE DECREASE THE SPEED"};
unsigned char const M17[] ={"ENTER WORKOUT MAX SPEED"};

/*
const unsigned	char	*MessageP[]={      // 字串指標
		M01,M02,M03,M04,M05,M06,M07,M08,M09,M10,
		M11,M12,M13,M14,M15,M16,M17
};
*/

const unsigned	char MessageL[]={              // 字串長度
		sizeof(M01),sizeof(M02),sizeof(M03),sizeof(M04),sizeof(M05),
		sizeof(M06),sizeof(M07),sizeof(M08),sizeof(M09),sizeof(M10),
		sizeof(M11),sizeof(M12),sizeof(M13),sizeof(M14),sizeof(M15),
		sizeof(M16),sizeof(M17)
};
//=============================
const unsigned	char P01[]={"ODO"};
const unsigned	char P02[]={"VRS"};
const unsigned	char P03[]={"VER"};
const unsigned	char P04[]={"SAFE"};
const unsigned	char P05[]={"SET"};
const unsigned	char P06[]={"CAL"};
const unsigned	char P07[]={"60%"};
const unsigned	char P08[]={"85%"};

const unsigned	char PictureL[]={
		sizeof(P01),sizeof(P02),sizeof(P03),sizeof(P04),sizeof(P05),
		sizeof(P06),sizeof(P07),sizeof(P08)
};

//=====================================================
//模組函式功能: 流動字串
//=====================================================
void  F_ShowStringMove(unsigned  char  String)
{
    unsigned char TempAdr,StringRam[30];  
    unsigned char	LcdAdr,StringData;
    unsigned char	MessageAdr,MatrixAsciiAdr;
    unsigned int	StringRamAdr,StringIndex;
    if(StringStartFlg)
    {  
      StringStartFlg=0;
      R_StringStartAdr=0;
      /*
      for(TempAdr=0;TempAdr<30;TempAdr++)  
      R_StringRam[TempAdr]=0;
      */
    }
    for(TempAdr=0;TempAdr<30;TempAdr++)  
      StringRam[TempAdr]=0;
    
    R_StringMax=(MessageL[String]-1)*6;	
    //================================= 
    if(R_StringStartAdr<30)
      StringIndex=0;
    else
      StringIndex=R_StringStartAdr-29;
    StringRamAdr=R_StringStartAdr;
    LcdAdr=29;
    for(TempAdr=StringIndex;TempAdr<=R_StringStartAdr;TempAdr++)
    {
      if(StringRamAdr<R_StringMax)
      {
        MessageAdr=StringRamAdr/6;
        MatrixAsciiAdr=StringRamAdr%6;
        StringData=F_MessageP(String,MessageAdr);
        StringData=MatrixAsciiCode[StringData-' '][MatrixAsciiAdr];
      }
      else
        StringData=0;
      StringRam[LcdAdr]=StringData;			
      if(StringRamAdr!=0)
        StringRamAdr--;
      if(LcdAdr!=0)
        LcdAdr--;
    }
    for(TempAdr=0;TempAdr<30;TempAdr++)
      F_ShowMatrixLcd(TempAdr,StringRam[TempAdr]);
}
//====================================
void F_ShowMatrixPicture(unsigned char LcdStartAdr,unsigned char StringAdr)
{
    unsigned char	LcdAdr,StringData,StringRamAdr;
    unsigned char	MessageAdr,MatrixAsciiAdr;
    unsigned char	StringMax;
    StringRamAdr=0;
    StringMax=(PictureL[StringAdr]-1)*6;
    for(LcdAdr=LcdStartAdr;LcdAdr<30;LcdAdr++)
    {
      MessageAdr=StringRamAdr/6;
      MatrixAsciiAdr=StringRamAdr%6;
      if(StringRamAdr<StringMax)
      {
        StringRamAdr++;
        switch(StringAdr)
        {
          case  PidOdo:
            StringData=P01[MessageAdr];
            break;
          //===========
          case  PidHer:
            StringData=P02[MessageAdr];
            break;
          //===========
          case	PidVer:
            StringData=P03[MessageAdr];
            break;
          //===========
          case  PidSafe:
            StringData=P04[MessageAdr];
            break;
          //===========
          case  PidSet:
            StringData=P05[MessageAdr];
            break;	
          //===========
          case  PidCal:
            StringData=P06[MessageAdr];
            break;	
          //===========
          case  Pid60:
            StringData=P07[MessageAdr];
            break;	
          //===========
          case  Pid80:
            StringData=P08[MessageAdr];
            break;	
        }
      }
      else
        StringData=' ';
      StringData=MatrixAsciiCode[StringData-' '][MatrixAsciiAdr];
      F_ShowMatrixLcd(LcdAdr,StringData);
    }
}
//===========================
void  F_StringMoveTime(void)
{ //  10ms
    R_StringMoveTime++;
    if(R_StringMoveTime>15)
    {
      R_StringMoveTime=0;
      R_StringStartAdr++;
      if(R_StringStartAdr>=R_StringMax+29)
      {
        R_StringStartAdr=0;
        StringStartFlg=1;
        StringFirstFlg=0;
      }
    }
}
//===========================
void F_StringInit(void)
{
     R_StringMoveTime=0;
     StringStartFlg=1;
     StringFirstFlg=1;
}
//============================
unsigned char F_MessageP(unsigned char StringAdr,unsigned char StringData)
{
    unsigned	char	Data;
    switch(StringAdr)
    {
      case      midM01:
        Data=M01[StringData];
        break;
      //============
      case      midM02:
        Data=M02[StringData];
        break;
      //============
      case      midM03:
        Data=M03[StringData];
        break;
      //============
      case      midM04:
        Data=M04[StringData];
        break;
      //============
      case	midM05:
        Data=M05[StringData];
        break;
      //============
      case	midM06:
        Data=M06[StringData];
        break;
      //============
      case	midM07:
        Data=M07[StringData];
        break;
      //============
      case      midM08:
        Data=M08[StringData];
        break;
      //============
      case      midM09:
        Data=M09[StringData];
        break;
      //============
      case	midM10:
        Data=M10[StringData];
        break;
      //============
      case	midM11:
        Data=M11[StringData];
        break;
      //============
      case	midM12:
        Data=M12[StringData];
        break;
      //============
      case      midM13:
        Data=M13[StringData];
        break;
      //============
      case      midM14:
        Data=M14[StringData];
        break;
      //============
      case      midM15:
        Data=M15[StringData];
        break;
      //============
      case      midM16:
        Data=M16[StringData];
        break;
      //============
      case      midM17:
        Data=M17[StringData];
        break;
    }
    return      Data;
}
