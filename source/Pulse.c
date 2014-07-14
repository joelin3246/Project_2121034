#include "connect.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
//PULSE2
#define P_PULSE2_PIN                    GPIO_Pin_12
#define P_PULSE2_GPIO_PORT              GPIOA
#define P_PULSE2_GPIO_CLK               RCC_AHBPeriph_GPIOA
//PULSE1
#define P_PULSE1_PIN                    GPIO_Pin_11
#define P_PULSE1_GPIO_PORT              GPIOA
#define P_PULSE1_GPIO_CLK               RCC_AHBPeriph_GPIOA
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
//==============================================================================
//This routine will setup the PULSE Port
//==============================================================================
void F_InitialPulse_GPIO(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  // Input PULSE2   on PA11  
  // Enable the PULSE2 
  RCC_AHBPeriphClockCmd(P_PULSE2_GPIO_CLK, ENABLE);
  // Configure the PULSE2  pin 
  GPIO_InitStructure.GPIO_Pin = P_PULSE2_PIN ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(P_PULSE2_GPIO_PORT, &GPIO_InitStructure);
  
  // Input PULSE1   on PA12       
  // Enable the PULSE1 
  RCC_AHBPeriphClockCmd(P_PULSE1_GPIO_CLK, ENABLE);
  // Configure the PULSE1  pin 
  GPIO_InitStructure.GPIO_Pin = P_PULSE1_PIN ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(P_PULSE1_GPIO_PORT, &GPIO_InitStructure);
}
//===========================================================================		
//手握心線訊號偵測
//===========================================================================	
void	F_Pluse1sub(void)		
{
  unsigned char i;
  R_Plusecount++;
  if(GPIO_ReadInputDataBit(P_PULSE1_GPIO_PORT,P_PULSE1_PIN))	//pluse_P=1
  {
    //=================		
    if(HeartPluseFlg==0)	//low-->Hi
    {
      R_HeartPluseWidth++;
      if(R_HeartPluseWidth>10)	//Hi寬度需大於10mS才承認心跳訊號
      {	
        R_HeartPluseWidth=0;
        HeartPluseFlg=1;
        if((R_Plusecount<1500)&&(R_Plusecount>272))	//	(60000/40)<R_Plusecount<(60000/220)
        {											//	40<R_Pluse1<220
          R_PluseTemp=60000/R_Plusecount;
          R_Plusecount=0;
          HandHeartDetectionFlg=1;
          //==============================
          if(R_Pluse==0)
          {
            if(R_PluOld==0)
            {
              R_PluOld=R_PluseTemp;
            }
            else
            {
              if(R_PluseTemp>R_PluOld)
                i=R_PluseTemp-R_PluOld;
              else
                i=R_PluOld-R_PluseTemp;
              //===================
              if(i<10)
                Pu1intFlg=1;
              //===================
              R_PluOld=R_PluseTemp;
            }		
          }
          else
          {
            Pu1intFlg=1;
          }
          //==============================
        }
        else
        {
          R_Plusecount=0;
          Pu1intFlg=0;
        }
      }							
    }
    //=================	
  }
  else
  {
    HeartPluseFlg=0;
    R_HeartPluseWidth=0;	
  }
  //==================	
  if(R_Plusecount>3000)
  {
    R_Plusecount=0;
    R_Pluse=0;
    R_PluseTemp=0;
    R_PluOld=0;
    HandHeartDetectionFlg=0;
    R_pubf[0]=0;
    R_pubf[1]=0;
    R_pubf[2]=0;
    R_pubf[3]=0;
  }
}
//==========================================
//手握心線訊號計算
//==========================================
void	F_PluseFunction1(void)
{
  unsigned int i; 
  unsigned char k,l,m;
  if(Pu1intFlg==1)
  {
    Pu1intFlg=0;
    if(R_Pluse==0)
    {
      R_pluseIndex=0;
      if(R_PluseTemp>99)
      {
        R_Pluse=99;
        R_pubf[0]=R_Pluse;
        R_pubf[1]=R_Pluse;
        R_pubf[2]=R_Pluse;
        R_pubf[3]=R_Pluse;	
      }
      else if(R_PluseTemp<70)
      {
        R_Pluse=70;			
        R_pubf[0]=R_Pluse;
        R_pubf[1]=R_Pluse;
        R_pubf[2]=R_Pluse;
        R_pubf[3]=R_Pluse;
      }
      else
      {
        R_Pluse=R_PluseTemp;			
        R_pubf[0]=R_Pluse;
        R_pubf[1]=R_Pluse;
        R_pubf[2]=R_Pluse;
        R_pubf[3]=R_Pluse;
      }		
    }
    else
    {
      k=0;
      m=0;
      //===============				
      if(R_PluseTemp>R_Pluse)
      {
        k=R_PluseTemp-R_Pluse;
      }
      else
      {
        m=R_Pluse-R_PluseTemp;
      }
      //===============						
      //				l=R_PluseTemp;
      if(k>8)
      {
        l=R_Pluse+8;
      }
      else	if(m>8)
      {
        l=R_Pluse-8;
      }
      else
        l=R_PluseTemp;
      R_PluseTemp=l;
      R_pubf[R_pluseIndex]=R_PluseTemp;
      
      R_pluseIndex++;
      if(R_pluseIndex>3)
        R_pluseIndex=0;
      if(R_pluseIndex==0)
      {
        i=R_pubf[0];
        i=i+R_pubf[1];
        i=i+R_pubf[2];
        i=i+R_pubf[3];			
        i=i>>2;			//i/4			
        R_Pluse=i;	
      }
    }
  }
}
//========================================================
//無線心跳訊號偵側
//========================================================
void	F_Pluse2sub(void)	
{
  unsigned char i;
  R_W_Plusecount++;
  if(GPIO_ReadInputDataBit(P_PULSE2_GPIO_PORT,P_PULSE2_PIN))	//Wpluse_P=1	PG1_P
  {	
    //===========================================================		
    if(Heart_W_PluseFlg==0)	//low-->Hi
    {
      R_Heart_W_PluseWidth++;
      if(R_Heart_W_PluseWidth>10)	//Hi寬度需大於10mS才承認心跳訊號
      {	
        R_Heart_W_PluseWidth=0;
        Heart_W_PluseFlg=1;
        if((R_W_Plusecount<1500)&&(R_W_Plusecount>272))	//	(60000/40)<R_Plusecount<(60000/220)
        {											//	40<R_Pluse1<220
          R_W_PluseTemp=60000/R_W_Plusecount;
          R_W_Plusecount=0;
          wHeartDetectionFlg=1;
          //==============================		
          if(R_W_Pluse==0)
          {
            if(R_W_PluOld==0)
            {
              R_W_PluOld=R_W_PluseTemp;
            }
            else
            {
              if(R_W_PluseTemp>R_W_PluOld)
                i=R_W_PluseTemp-R_W_PluOld;
              else
                i=R_W_PluOld-R_W_PluseTemp;
              //===================
              if(i<4)
              {
                R_W_DelayTime++;
                if(R_W_DelayTime>3)
                {
                  R_W_DelayTime=0;
                  W_Pu1intFlg=1;
                }
              }
              //===================
              R_W_PluOld=R_W_PluseTemp;
            }
          }
          else
          {
            W_Pu1intFlg=1;
          }
          //==============================		
        }
        else
        {
          R_W_Plusecount=0;
          W_Pu1intFlg=0;
        }
      }					
    }
    //==========================================================
  }
  else
  {
    Heart_W_PluseFlg=0;
    R_Heart_W_PluseWidth=0;	
  }
  //==================
  if(R_W_Plusecount>3000)
  {
    R_W_Plusecount=0;
    R_W_DelayTime=0;
    R_W_Pluse=0;
    wHeartDetectionFlg=0;
    R_W_PluseTemp=0;			
    R_W_PluOld=0;
    R_W_pubf[0]=0;
    R_W_pubf[1]=0;
    R_W_pubf[2]=0;
    R_W_pubf[3]=0;
  }
}
//=======================================
//無線心跳訊號計算
//=======================================	
void	F_PluseFunction2(void)
{
  unsigned int i; 
  unsigned char k,l,m;
  if(W_Pu1intFlg==1)
  {
    W_Pu1intFlg=0;
    if(R_W_Pluse==0)	
    {
      R_W_pluseIndex=0;
      if(R_W_PluseTemp>99)
      {
        R_W_Pluse=99;
        R_W_pubf[0]=R_W_Pluse;
        R_W_pubf[1]=R_W_Pluse;
        R_W_pubf[2]=R_W_Pluse;
        R_W_pubf[3]=R_W_Pluse;	
      }
      else if(R_W_PluseTemp<70)
      {
        R_W_Pluse=70;			
        R_W_pubf[0]=R_W_Pluse;
        R_W_pubf[1]=R_W_Pluse;
        R_W_pubf[2]=R_W_Pluse;
        R_W_pubf[3]=R_W_Pluse;
      }
      else
      {
        R_W_Pluse=R_W_PluseTemp;			
        R_W_pubf[0]=R_W_Pluse;
        R_W_pubf[1]=R_W_Pluse;
        R_W_pubf[2]=R_W_Pluse;
        R_W_pubf[3]=R_W_Pluse;
      }		
    }
    else
    {
      k=0;
      m=0;
      //===============
      if(R_W_PluseTemp>R_W_Pluse)
      {
        k=R_W_PluseTemp-R_W_Pluse;
      }
      else
      {
        m=R_W_Pluse-R_W_PluseTemp;
      }
      //=================
      if(k>8)
      {
        l=R_W_Pluse+8;
      }
      else	if(m>8)
      {
        l=R_W_Pluse-8;
      }
      else
        l=R_W_PluseTemp;
      R_W_PluseTemp=l;
      R_W_pubf[R_W_pluseIndex]=R_W_PluseTemp;
      R_W_pluseIndex++;
      if(R_W_pluseIndex>3)
        R_W_pluseIndex=0;
      if(R_W_pluseIndex==0)
      {
        i=R_W_pubf[0];
        i=i+R_W_pubf[1];
        i=i+R_W_pubf[2];
        i=i+R_W_pubf[3];			
        i=i>>2;			//i/4			
        R_W_Pluse=i;	
      }
    }
  }
}