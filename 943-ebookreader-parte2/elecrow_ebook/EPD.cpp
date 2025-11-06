#include "EPD.h"
#include "EPDfont.h"
#include "string.h"

PAINT Paint;


/*******************************************************************
    函数说明：创建图片缓存数组
    接口说明：*image  要传入的图片数组
               Width  图片宽度
               Heighe 图片长度
               Rotate 屏幕显示方向
               Color  显示颜色
    返回值：  无
*******************************************************************/
void Paint_NewImage(uint8_t *image,uint16_t Width,uint16_t Height,uint16_t Rotate,uint16_t Color)
{
	Paint.Image = 0x00;
	Paint.Image = image;
	Paint.color = Color;  
	Paint.widthMemory = Width;
	Paint.heightMemory = Height;  
	Paint.widthByte = (Width % 8 == 0)? (Width / 8 ): (Width / 8 + 1);
	Paint.heightByte = Height;     
	Paint.rotate = Rotate;
	if(Rotate==0||Rotate==180) 
	{
		Paint.width=Height;
		Paint.height=Width;
	} 
	else 
	{
		Paint.width = Width;
		Paint.height = Height;
	}
}				 

/*******************************************************************
    函数说明：清空缓冲区 
    接口说明：Color  像素点颜色参数
    返回值：  无
*******************************************************************/
void Paint_Clear(uint8_t Color)
{
	uint16_t X,Y;
	uint32_t Addr;
  for(Y=0;Y<Paint.heightByte;Y++) 
	{
    for(X=0;X<Paint.widthByte;X++) 
		{   
      Addr=X+Y*Paint.widthByte;//8 pixel =  1 byte
      Paint.Image[Addr]=Color;
    }
  }
}


/*******************************************************************
    函数说明：点亮一个像素点
    接口说明：Xpoint 像素点x坐标参数
              Ypoint 像素点Y坐标参数
              Color  像素点颜色参数
    返回值：  无
*******************************************************************/
void Paint_SetPixel(uint16_t Xpoint,uint16_t Ypoint,uint16_t Color)
{
	uint16_t X, Y;
	uint32_t Addr;
	uint8_t Rdata;		
    switch(Paint.rotate) 
		{
				case 0:
					if(Xpoint>=396)
					{
						Xpoint+=8;
					}
					X=Xpoint;
					Y=Ypoint;
					break;
			case 90:
					if(Ypoint>=396)
					{
						Ypoint+=8;
					}
					X=Paint.widthMemory-Ypoint-1;
					Y=Xpoint;
					break;
			case 180:
				  if(Xpoint>=396)
					{
						Xpoint+=8;
					}
					X=Paint.widthMemory-Xpoint-1;
					Y=Paint.heightMemory-Ypoint-1;
					break;

			case 270:
					if(Ypoint>=396)
					{
						Ypoint+=8;
					}
					X=Ypoint;
					Y=Paint.heightMemory-Xpoint-1;
					break;
				default:
						return;
    }
		Addr=X/8+Y*Paint.widthByte;
    Rdata=Paint.Image[Addr];
    if(Color==BLACK)
    {    
			Paint.Image[Addr]=Rdata&~(0x80>>(X % 8)); //将对应数据位置0
		}
    else
		{
      Paint.Image[Addr]=Rdata|(0x80>>(X % 8));   //将对应数据位置1  
		}
}


/*******************************************************************
    函数说明：划线函数
    接口说明：Xstart 像素x起始坐标参数
              Ystart 像素Y起始坐标参数
              Xend   像素x结束坐标参数
              Yend   像素Y结束坐标参数
              Color  像素点颜色参数
    返回值：  无
*******************************************************************/
void EPD_DrawLine(uint16_t Xstart,uint16_t Ystart,uint16_t Xend,uint16_t Yend,uint16_t Color)
{   
	uint16_t Xpoint, Ypoint;
	int dx, dy;
	int XAddway,YAddway;
	int Esp;
	char Dotted_Len;
  Xpoint = Xstart;
  Ypoint = Ystart;
  dx = (int)Xend - (int)Xstart >= 0 ? Xend - Xstart : Xstart - Xend;
  dy = (int)Yend - (int)Ystart <= 0 ? Yend - Ystart : Ystart - Yend;
  XAddway = Xstart < Xend ? 1 : -1;
  YAddway = Ystart < Yend ? 1 : -1;
  Esp = dx + dy;
  Dotted_Len = 0;
  for (;;) {
        Dotted_Len++;
            Paint_SetPixel(Xpoint, Ypoint, Color);
        if (2 * Esp >= dy) {
            if (Xpoint == Xend)
                break;
            Esp += dy;
            Xpoint += XAddway;
        }
        if (2 * Esp <= dx) {
            if (Ypoint == Yend)
                break;
            Esp += dx;
            Ypoint += YAddway;
        }
    }
}
/*******************************************************************
    函数说明：画矩形函数
    接口说明：Xstart 矩形x起始坐标参数
              Ystart 矩形Y起始坐标参数
              Xend   矩形x结束坐标参数
              Yend   矩形Y结束坐标参数
              Color  像素点颜色参数
              mode   矩形是否进行填充
    返回值：  无
*******************************************************************/
void EPD_DrawRectangle(uint16_t Xstart,uint16_t Ystart,uint16_t Xend,uint16_t Yend,uint16_t Color,uint8_t mode)
{
	uint16_t i;
    if (mode)
			{
        for(i = Ystart; i < Yend; i++) 
				{
          EPD_DrawLine(Xstart,i,Xend,i,Color);
        }
      }
		else 
		 {
        EPD_DrawLine(Xstart, Ystart, Xend, Ystart, Color);
        EPD_DrawLine(Xstart, Ystart, Xstart, Yend, Color);
        EPD_DrawLine(Xend, Yend, Xend, Ystart, Color);
        EPD_DrawLine(Xend, Yend, Xstart, Yend, Color);
		 }
}
/*******************************************************************
    函数说明：画圆函数
    接口说明：X_Center 圆心x起始坐标参数
              Y_Center 圆心Y坐标参数
              Radius   圆形半径参数
              Color  像素点颜色参数
              mode   圆形是否填充显示
    返回值：  无
*******************************************************************/
void EPD_DrawCircle(uint16_t X_Center,uint16_t Y_Center,uint16_t Radius,uint16_t Color,uint8_t mode)
{
	int Esp, sCountY;
	uint16_t XCurrent, YCurrent;
  XCurrent = 0;
  YCurrent = Radius;
  Esp = 3 - (Radius << 1 );
    if (mode) {
        while (XCurrent <= YCurrent ) { //Realistic circles
            for (sCountY = XCurrent; sCountY <= YCurrent; sCountY ++ ) {
                Paint_SetPixel(X_Center + XCurrent, Y_Center + sCountY, Color);//1
                Paint_SetPixel(X_Center - XCurrent, Y_Center + sCountY, Color);//2
                Paint_SetPixel(X_Center - sCountY, Y_Center + XCurrent, Color);//3
                Paint_SetPixel(X_Center - sCountY, Y_Center - XCurrent, Color);//4
                Paint_SetPixel(X_Center - XCurrent, Y_Center - sCountY, Color);//5
                Paint_SetPixel(X_Center + XCurrent, Y_Center - sCountY, Color);//6
                Paint_SetPixel(X_Center + sCountY, Y_Center - XCurrent, Color);//7
                Paint_SetPixel(X_Center + sCountY, Y_Center + XCurrent, Color);
            }
            if ((int)Esp < 0 )
                Esp += 4 * XCurrent + 6;
            else {
                Esp += 10 + 4 * (XCurrent - YCurrent );
                YCurrent --;
            }
            XCurrent ++;
        }
    } else { //Draw a hollow circle
        while (XCurrent <= YCurrent ) {
            Paint_SetPixel(X_Center + XCurrent, Y_Center + YCurrent, Color);//1
            Paint_SetPixel(X_Center - XCurrent, Y_Center + YCurrent, Color);//2
            Paint_SetPixel(X_Center - YCurrent, Y_Center + XCurrent, Color);//3
            Paint_SetPixel(X_Center - YCurrent, Y_Center - XCurrent, Color);//4
            Paint_SetPixel(X_Center - XCurrent, Y_Center - YCurrent, Color);//5
            Paint_SetPixel(X_Center + XCurrent, Y_Center - YCurrent, Color);//6
            Paint_SetPixel(X_Center + YCurrent, Y_Center - XCurrent, Color);//7
            Paint_SetPixel(X_Center + YCurrent, Y_Center + XCurrent, Color);//0
            if ((int)Esp < 0 )
                Esp += 4 * XCurrent + 6;
            else {
                Esp += 10 + 4 * (XCurrent - YCurrent );
                YCurrent --;
            }
            XCurrent ++;
        }
    }
}

/*******************************************************************
    函数说明：显示单个字符
    接口说明：x     字符x坐标参数
              y      字符Y坐标参数
              chr    要显示的字符
              size1  显示字符字号大小
              Color  像素点颜色参数
    返回值：  无
*******************************************************************/
void EPD_ShowChar(uint16_t x,uint16_t y,uint16_t chr,uint16_t size1,uint16_t color)
{
	uint16_t i,m,temp,size2,chr1;
	uint16_t x0,y0;
	x0=x,y0=y;
	if(size1==8)size2=6;
	else size2=(size1/8+((size1%8)?1:0))*(size1/2);  //得到字体一个字符对应点阵集所占的字节数
	chr1=chr-' ';  //计算偏移后的值
	for(i=0;i<size2;i++)
	{
		if(size1==12)
        {temp=ascii_1206[chr1][i];} //调用1206字体
		else if(size1==16)
        {temp=ascii_1608[chr1][i];} //调用1608字体
		else if(size1==24)
        {temp=ascii_2412[chr1][i];} //调用2412字体
		else if(size1==48)
        {temp=ascii_4824[chr1][i];} //调用2412字体
		else return;
		for(m=0;m<8;m++)
		{
			if(temp&0x01)Paint_SetPixel(x,y,color);
			else Paint_SetPixel(x,y,!color);
			temp>>=1;
			y++;
		}
		x++;
		if((size1!=8)&&((x-x0)==size1/2))
		{x=x0;y0=y0+8;}
		y=y0;
  }
}

/*******************************************************************
    函数说明：显示字符串
    接口说明：x     字符串x坐标参数
              y      字符串Y坐标参数
              *chr    要显示的字符串
              size1  显示字符串字号大小
              Color  像素点颜色参数
    返回值：  无
*******************************************************************/
void EPD_ShowString(uint16_t x,uint16_t y,const char *chr,uint16_t size1,uint16_t color)
{
	while(*chr!='\0')//判断是不是非法字符!
	{
		EPD_ShowChar(x,y,*chr,size1,color);
		chr++;
		x+=size1/2;
  }
}
/*******************************************************************
    函数说明：指数运算
    接口说明：m 底数
              n 指数
    返回值：  m的n次方
*******************************************************************/
uint32_t EPD_Pow(uint16_t m,uint16_t n)
{
	uint32_t result=1;
	while(n--)
	{
	  result*=m;
	}
	return result;
}
/*******************************************************************
    函数说明：显示整型数字
    接口说明：x     数字x坐标参数
              y      数字Y坐标参数
              num    要显示的数字
              len    数字的位数
              size1  显示字符串字号大小
              Color  像素点颜色参数
    返回值：  无
*******************************************************************/
void EPD_ShowNum(uint16_t x,uint16_t y,uint32_t num,uint16_t len,uint16_t size1,uint16_t color)
{
	uint8_t t,temp,m=0;
	if(size1==8)m=2;
	for(t=0;t<len;t++)
	{
		temp=(num/EPD_Pow(10,len-t-1))%10;
			if(temp==0)
			{
				EPD_ShowChar(x+(size1/2+m)*t,y,'0',size1,color);
      }
			else 
			{
			  EPD_ShowChar(x+(size1/2+m)*t,y,temp+'0',size1,color);
			}
  }
}
/*******************************************************************
    函数说明：显示浮点型数字
    接口说明：x     数字x坐标参数
              y      数字Y坐标参数
              num    要显示的浮点数
              len    数字的位数
              pre    浮点数的精度
              size1  显示字符串字号大小
              Color  像素点颜色参数
    返回值：  无
*******************************************************************/

void EPD_ShowFloatNum1(uint16_t x,uint16_t y,float num,uint8_t len,uint8_t pre,uint8_t sizey,uint8_t color)
{         	
	uint8_t t,temp,sizex;
	uint16_t num1;
	sizex=sizey/2;
	num1=num*EPD_Pow(10,pre);
	for(t=0;t<len;t++)
	{
		temp=(num1/EPD_Pow(10,len-t-1))%10;
		if(t==(len-pre))
		{
			EPD_ShowChar(x+(len-pre)*sizex,y,'.',sizey,color);
			t++;
			len+=1;
		}
	 	EPD_ShowChar(x+t*sizex,y,temp+48,sizey,color);
	}
}





//GUI显示秒表
void EPD_ShowWatch(uint16_t x,uint16_t y,float num,uint8_t len,uint8_t pre,uint8_t sizey,uint8_t color)
{         	
	uint8_t t,temp,sizex;
	uint16_t num1;
	sizex=sizey/2;
	num1=num*EPD_Pow(10,pre);
	for(t=0;t<len;t++)
	{
		temp=(num1/EPD_Pow(10,len-t-1))%10;
		if(t==(len-pre))
		{
			EPD_ShowChar(x+(len-pre)*sizex+(sizex/2-2),y-6,':',sizey,color);
			t++;
			len+=1;
		}
	 	EPD_ShowChar(x+t*sizex,y,temp+48,sizey,color);
	}
}



void EPD_ShowPicture(uint16_t x,uint16_t y,uint16_t sizex,uint16_t sizey,const uint8_t BMP[],uint16_t Color)
{
	uint16_t j=0,t;
	uint16_t i,temp,x0,TypefaceNum=sizey*(sizex/8+((sizex%8)?1:0));
	x0=x;
  for(i=0;i<TypefaceNum;i++)
	{
		temp=BMP[j];
		for(t=0;t<8;t++)
		{
		 if(temp&0x80)
		 {
			 Paint_SetPixel(x,y,!Color);
		 }
		 else
		 {
			 Paint_SetPixel(x,y,Color);
		 }
		 x++;
		 temp<<=1;
		}
		if((x-x0)==sizex)
		{
			x=x0;
			y++;
		}
		j++;
//    delayMicroseconds(10); // 延时微秒
	}
}
