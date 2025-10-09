#include "EPD_Init.h"
#include "EPD.h"



/*******************************************************************
    函数说明:判忙函数
    入口参数:无
    说明:忙状态为1
*******************************************************************/
void EPD_READBUSY(void)
{
  while (1)
  {
    if (EPD_ReadBUSY == 0)
    {
      break;
    }
  }
}
/*******************************************************************
    函数说明:硬件复位函数
    入口参数:无
    说明:在E-Paper进入Deepsleep状态后需要硬件复位
*******************************************************************/
void EPD_HW_RESET(void)
{
  delay(10);
  EPD_RES_Clr();
  delay(10);
  EPD_RES_Set();
  delay(10);
  EPD_READBUSY();
}

/*******************************************************************
    函数说明:更新函数
    入口参数:无
    说明:更新显示内容到E-Paper
*******************************************************************/
void EPD_Update(void)
{
  EPD_WR_REG(0x22);
  EPD_WR_DATA8(0xF7);
  EPD_WR_REG(0x20);
  EPD_READBUSY();
}
/*******************************************************************
    函数说明:局刷更新函数
    入口参数:无
    说明:E-Paper工作在局刷模式
*******************************************************************/
void EPD_PartUpdate(void)
{
  EPD_WR_REG(0x22);
  EPD_WR_DATA8(0xDC);
  EPD_WR_REG(0x20);
  EPD_READBUSY();
}
/*******************************************************************
    函数说明:快刷更新函数
    入口参数:无
    说明:E-Paper工作在快刷模式
*******************************************************************/
void EPD_FastUpdate(void)
{
  EPD_WR_REG(0x22);
  EPD_WR_DATA8(0xC7);
  EPD_WR_REG(0x20);
  EPD_READBUSY();
}

/*******************************************************************
    函数说明:休眠函数
    入口参数:无
    说明:屏幕进入低功耗模式
*******************************************************************/
void EPD_DeepSleep(void)
{
//    EPD_WR_REG(0x3C);
//    EPD_WR_DATA8(0x01);
//    EPD_READBUSY();

  EPD_WR_REG(0x10);
  EPD_WR_DATA8(0x01);
  delay(5);
}

void EPD_Init(void)
{
  EPD_HW_RESET();
  EPD_READBUSY();
  EPD_WR_REG(0x12);
  EPD_READBUSY();
}

void EPD_FastMode1Init(void)
{
  EPD_HW_RESET();
  EPD_READBUSY();
  EPD_WR_REG(0x12);  //SWRESET
  EPD_READBUSY();

  EPD_WR_REG(0x18); //Read built-in temperature sensor
  EPD_WR_DATA8(0x80);

  EPD_WR_REG(0x22); // Load temperature value
  EPD_WR_DATA8(0xB1);
  EPD_WR_REG(0x20);
  EPD_READBUSY();

  EPD_WR_REG(0x1A); // Write to temperature register
  EPD_WR_DATA8(0x64);
  EPD_WR_DATA8(0x00);

  EPD_WR_REG(0x22); // Load temperature value
  EPD_WR_DATA8(0x91);
  EPD_WR_REG(0x20);
  EPD_READBUSY();

  EPD_WR_REG(0x3C);
  EPD_WR_DATA8(0x3);
  EPD_READBUSY();
}

void EPD_SetRAMMP(void)
{
  EPD_WR_REG(0x11);	 // Data Entry mode setting
  EPD_WR_DATA8(0x05);     // 1 –Y decrement, X increment
  EPD_WR_REG(0x44);	 						 // Set Ram X- address Start / End position
  EPD_WR_DATA8(0x00);     						 // XStart, POR = 00h
  EPD_WR_DATA8(0x31); //400/8-1
  EPD_WR_REG(0x45);	 									// Set Ram Y- address  Start / End position
  EPD_WR_DATA8(0x0f);
  EPD_WR_DATA8(0x01);  //300-1
  EPD_WR_DATA8(0x00);     									// YEnd L
  EPD_WR_DATA8(0x00);
}

void EPD_SetRAMMA(void)
{
  EPD_WR_REG(0x4e);
  EPD_WR_DATA8(0x00);
  EPD_WR_REG(0x4f);
  EPD_WR_DATA8(0x0f);
  EPD_WR_DATA8(0x01);
}

void EPD_SetRAMSP(void)
{
  EPD_WR_REG(0x91);
  EPD_WR_DATA8(0x04);
  EPD_WR_REG(0xc4);	 // Set Ram X- address Start / End position
  EPD_WR_DATA8(0x31);// XStart, POR = 00h
  EPD_WR_DATA8(0x00);
  EPD_WR_REG(0xc5);	 // Set Ram Y- address  Start / End position
  EPD_WR_DATA8(0x0f);
  EPD_WR_DATA8(0x01);
  EPD_WR_DATA8(0x00);// YEnd L
  EPD_WR_DATA8(0x00);
}

void EPD_SetRAMSA(void)
{
  EPD_WR_REG(0xce);
  EPD_WR_DATA8(0x31);
  EPD_WR_REG(0xcf);
  EPD_WR_DATA8(0x0f);
  EPD_WR_DATA8(0x01);
}

void EPD_Clear_R26A6H(void)
{
  uint16_t i, j;
  EPD_SetRAMMA();
  EPD_WR_REG(0x26);
  for (i = 0; i < Gate_BITS; i++)
  {
    for (j = 0; j < Source_BYTES; j++)
    {
      EPD_WR_DATA8(0xFF);
    }
  }
  EPD_SetRAMSA();
  EPD_WR_REG(0xA6);
  for (i = 0; i < Gate_BITS; i++)
  {
    for (j = 0; j < Source_BYTES; j++)
    {
      EPD_WR_DATA8(0xFF);
    }
  }
}

void EPD_Display_Clear(void)
{
  uint16_t i, j;
  EPD_SetRAMMP();
  EPD_SetRAMMA();
  EPD_WR_REG(0x24);
  for (i = 0; i < Gate_BITS; i++)
  {
    for (j = 0; j < Source_BYTES; j++)
    {
      EPD_WR_DATA8(0xFF);
    }
  }
  EPD_SetRAMMA();
  EPD_WR_REG(0x26);
  for (i = 0; i < Gate_BITS; i++)
  {
    for (j = 0; j < Source_BYTES; j++)
    {
      EPD_WR_DATA8(0x00);
    }
  }
  EPD_SetRAMSP();
  EPD_SetRAMSA();
  EPD_WR_REG(0xA4);
  for (i = 0; i < Gate_BITS; i++)
  {
    for (j = 0; j < Source_BYTES; j++)
    {
      EPD_WR_DATA8(0xFF);
    }
  }
  EPD_SetRAMSA();
  EPD_WR_REG(0xA6);
  for (i = 0; i < Gate_BITS; i++)
  {
    for (j = 0; j < Source_BYTES; j++)
    {
      EPD_WR_DATA8(0x00);
    }
  }
}


void EPD_Display(const uint8_t *ImageBW)
{
  uint32_t i;
  uint8_t tempOriginal;
  uint32_t tempcol = 0;
  uint32_t templine = 0;
  EPD_SetRAMMP();
  EPD_SetRAMMA();
  EPD_WR_REG(0x24);
  for (i = 0; i < ALLSCREEN_BYTES; i++)
  {
    tempOriginal = *(ImageBW + templine * Source_BYTES * 2 + tempcol);
    templine++;
    if (templine >= Gate_BITS)
    {
      tempcol++;
      templine = 0;
    }
    EPD_WR_DATA8(tempOriginal);
  }
  EPD_SetRAMSP();
  EPD_SetRAMSA();
  EPD_WR_REG(0xa4);   //write RAM for black(0)/white (1)
  for (i = 0; i < ALLSCREEN_BYTES; i++)
  {
    tempOriginal = *(ImageBW + templine * Source_BYTES * 2 + tempcol);
    templine++;
    if (templine >= Gate_BITS)
    {
      tempcol++;
      templine = 0;
    }
    EPD_WR_DATA8(tempOriginal);
  }
}

//Horizontal scanning, from right to left, from bottom to top
void EPD_WhiteScreen_ALL_Fast(const unsigned char *datas)
{
  unsigned int i;
  unsigned char tempOriginal;
  unsigned int tempcol = 0;
  unsigned int templine = 0;

  EPD_WR_REG(0x11);
  EPD_WR_DATA8(0x05);

  EPD_WR_REG(0x44); //set Ram-X address start/end position
  EPD_WR_DATA8(0x00);
  EPD_WR_DATA8(0x31);    //0x12-->(18+1)*8=152

  EPD_WR_REG(0x45); //set Ram-Y address start/end position
  EPD_WR_DATA8(0x0F);   //0x97-->(151+1)=152
  EPD_WR_DATA8(0x01);
  EPD_WR_DATA8(0x00);
  EPD_WR_DATA8(0x00);

  EPD_WR_REG(0x4E);
  EPD_WR_DATA8(0x00);
  EPD_WR_REG(0x4F);
  EPD_WR_DATA8(0x0F);
  EPD_WR_DATA8(0x01);

  EPD_READBUSY();
  EPD_WR_REG(0x24);   //write RAM for black(0)/white (1)
  for (i = 0; i < Source_BYTES * Gate_BITS; i++)
  {
    tempOriginal = *(datas + templine * Source_BYTES * 2 + tempcol);
    templine++;
    if (templine >= Gate_BITS)
    {
      tempcol++;
      templine = 0;
    }
    EPD_WR_DATA8(~tempOriginal);
  }

  EPD_WR_REG(0x26);   //write RAM for black(0)/white (1)
  for (i = 0; i < Source_BYTES * Gate_BITS; i++)
  {
    EPD_WR_DATA8(0X00);
  }


  EPD_WR_REG(0x91);
  EPD_WR_DATA8(0x04);

  EPD_WR_REG(0xC4); //set Ram-X address start/end position
  EPD_WR_DATA8(0x31);
  EPD_WR_DATA8(0x00);    //0x12-->(18+1)*8=152

  EPD_WR_REG(0xC5); //set Ram-Y address start/end position
  EPD_WR_DATA8(0x0F);   //0x97-->(151+1)=152  ÐÞ¸ÄµÄ
  EPD_WR_DATA8(0x01);
  EPD_WR_DATA8(0x00);
  EPD_WR_DATA8(0x00);

  EPD_WR_REG(0xCE);
  EPD_WR_DATA8(0x31);
  EPD_WR_REG(0xCF);
  EPD_WR_DATA8(0x0F);
  EPD_WR_DATA8(0x01);

  EPD_READBUSY();

  tempcol = tempcol - 1; //Byte dislocation processing
  templine = 0;
  EPD_WR_REG(0xa4);   //write RAM for black(0)/white (1)
  for (i = 0; i < Source_BYTES * Gate_BITS; i++)
  {
    tempOriginal = *(datas + templine * Source_BYTES * 2 + tempcol);
    templine++;
    if (templine >= Gate_BITS)
    {
      tempcol++;
      templine = 0;
    }
    EPD_WR_DATA8(~tempOriginal);
  }

  EPD_WR_REG(0xa6);   //write RAM for black(0)/white (1)
  for (i = 0; i < Source_BYTES * Gate_BITS; i++)
  {
    EPD_WR_DATA8(0X00);
  }

  EPD_FastUpdate();
}
