/*
  ===============================================================================
  Name        : SoundBoard.c
  Author      : $(author)
  Version     :
  Copyright   : $(copyright)
  Description : main definition
  ===============================================================================
*/
#ifdef __USE_CMSIS
#include "LPC11xx.h"
#endif
#include <stdlib.h>
#include "xprintf.h"
#include "main.h"
#include "wav/wav.h"
#include "fatfs/diskio.h"
#include "fatfs/ff.h"
#include <cr_section_macros.h>

#define BUFFERSIZE (512*2)
#define HALFSIZE (BUFFERSIZE>>1)
uint8_t Buff[BUFFERSIZE];
#define PLAYCTRL(x) ((x==true)? NVIC_EnableIRQ(TIMER_16_0_IRQn):NVIC_DisableIRQ(TIMER_16_0_IRQn))
uint32_t Bri=0,Bwi=0,Bct=0;

extern void disk_timerproc (void);

void GPIO_Init(void);
void BlinkLED(uint8_t num);
void BlankProc(uint32_t count);
inline void BufferClear(void);
void ErrorHandle(uint8_t blinknum,const char *message);

volatile uint32_t Timer;

int main(void)
{
  DIR dir;
  FILINFO info;

  FATFS fs;
  FIL fil;

  FormatChunk_t FmCk;
  SizeWav_t WvSz;
  uint32_t decoy,musicnum,nowtrack = 0,skipcount = 0;
  bool wav_ok=false,play = false,playctrl = true;

  GPIO_Init();//ADC_Init(0x00,HARD);

  UART_Init(9600);// I2C_Init(SLAVE,STANDARD,0x20);
  xdev_out(Putc);
  xdev_in(Getc);

  LPC_IOCON->R_PIO1_1 = 0x83;//PWM output left channel [MAT0 output mode]
  LPC_IOCON->R_PIO1_2 = 0x83;//PWM output right channel [MAT1 output mode]

  ENABLETMR16B0CLK();
  MRxRaiseHandle(TMR16B0,0);
  MRxClearCT(TMR16B0,0);
  SetPrescal(TMR16B0,0);
  SetMRxValue(TMR16B0,0,1093);
  TMRxStart(TMR16B0);
  EnableTMR16B0IRQ();

  PWM32B1Init(0,0x03);

  SysTick_Config(SystemCoreClock/(1001-1));

  NVIC_SetPriority(TIMER_16_0_IRQn,0);


  if(disk_initialize(0))
    ErrorHandle(1,"FatFs mount error\n");

  if(f_mount(&fs,"",0)!=FR_OK)
    ErrorHandle(2,"FatFs initialize error\n");

  musicnum = GetMusicNum(&dir,&info);
  if(musicnum<0)
    ErrorHandle(3,"Read wav header error\n");

  while(1)
    {
      if(f_opendir(&dir,"")==FR_OK)wav_ok=true;
      else wav_ok = false;

      while(wav_ok)
	{
	  do{
	    if(skipcount>0)skipcount--;
	    if(f_readdir(&dir,&info)!=FR_OK)skipcount++;
	    if(strstr(info.fname,".WAV")==NULL)
	      skipcount++;
	  }while(skipcount);

	  if(f_open(&fil,info.fname,FA_READ)!=FR_OK)break;

	  CheckWavFile(&fil,&FmCk,&WvSz);
	  DispWavInfo(&FmCk,&WvSz);

	  if(f_read(&fil,&Buff[0],BUFFERSIZE,&decoy)!=FR_OK)break;
	  Bct = decoy;

	  nowtrack++;
	  play = true;

	  PLAYCTRL(true);
	  while(play)
	    {
	      if(GPIO0STAT(3))
		{
		  if(!GPIO0STAT(1))
		    {
		      play = false;
		      if(nowtrack==musicnum)
			{
			  f_closedir(&dir);
			  wav_ok = false;
			  nowtrack = 0;
			}
		    }
		  else if(!GPIO1STAT(8))
		    {
		      if(nowtrack==1)
			{
			  nowtrack = musicnum-1;
			  skipcount = musicnum;
			}
		      else
			{
			  nowtrack -=2;
			  skipcount = nowtrack+1;
			}
		      f_closedir(&dir);
		      play = false;
		      wav_ok = false;
		    }

		  if(!GPIO1STAT(9)&&(Timer>250))
		    {
		      Timer = 0;
		      if(playctrl)
			{
			  playctrl =false;
			  PLAYCTRL(false);
			}
		      else
			{
			  playctrl = true;
			  PLAYCTRL(true);
			}
		    }
		}

	      if(Bct<HALFSIZE)
		{
		  f_read(&fil,&Buff[Bwi],HALFSIZE,&decoy);
		  GPIO1HIGH(4);
		  if(decoy!=HALFSIZE)play=false;
		  Bwi = (Bwi+decoy) & (BUFFERSIZE-1);
		  __disable_irq();
		  Bct+=decoy;
		  __enable_irq();
		}
	      else
		GPIO1LOW(4);
	    }
	  if(nowtrack==musicnum)
	    {
	      wav_ok = false;
	      nowtrack = 1;
	    }
	  PLAYCTRL(false);

	  BufferClear();
	  Bwi = 0;
	  Bri  = 0;
	}
    }
}

void GPIO_Init(void)
{
  LPC_IOCON->PIO0_1 = 0x10;//control playing music(Play)[pull up mode]
  LPC_IOCON->PIO0_3 = 0x10;//control lock[pull up mode]
  //****WARNING don't change this register LPC_IOCON->SWCLK_PIO0_10
  //****WARNING don't change this register LPC_IOCON->SWDIO_PIO1_3
  LPC_IOCON->PIO1_4 = 0x00;//indicator LED
  LPC_IOCON->PIO1_8 = 0x10;//control playing music(stop/start)[pull up mode]
  LPC_IOCON->PIO1_9 = 0x10;//control playing music(Back)[pull up mode]

  LPC_GPIO0->DIR = 0x000000000;//
  LPC_GPIO1->DIR = (1<<4);

  LPC_GPIO0->DATA = 0x00;//GPIO0 IS CLEARED
  LPC_GPIO1->DATA = 0x00;//GPIO1 IS CLEARED
}

void BlinkLED(uint8_t num)
{
  uint8_t i;
  for(i=0;i<num;i++)
    {
      BlankProc(2000);
      GPIO1TG(4);
    }
}

void TIMER16_0_IRQHandler (void)
{
  LPC_TMR32B1->MR0 = (*(int16_t*)(Buff+(Bri))+0x7FFF)>>7;
  LPC_TMR32B1->MR1 = (*(int16_t*)(Buff+(Bri+2))+0x7FFF)>>7;
  Bri = (Bri+4)&(BUFFERSIZE-1);
  Bct-=4;
  LPC_TMR32B1->TC=0;//clear timer counte
  TMR16B0IRCLEAR(0);
}

inline void BufferClear(void)
{
  uint32_t decoy;
  for(decoy=0;decoy<BUFFERSIZE;decoy++)
    Buff[decoy] = 0x10;
}

void SysTick_Handler(void)
{
  if((Timer<60000)&&GPIO1STAT(9))Timer++;
  disk_timerproc();	/* Disk timer process */
}

void ErrorHandle(uint8_t blinknum,const char *message)
{
  BlinkLED(blinknum*2);
  xprintf(message);
  while(1);
}

void BlankProc(uint32_t count)
{
  uint32_t i,i2;
  for(i=0;i<count;i++)
    for(i2=0;i2<480;i2++){
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");//5
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");//10
    }
}

