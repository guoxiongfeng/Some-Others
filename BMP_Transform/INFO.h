#ifndef INFO_H
#define INFO_H
#include <stdio.h>
#define WIDTHBYTES(bits) (((bits)+31)/32*4) //？ 理解： 保证其为整数个word长。 试试用width*bitInfoHead.biBitCount/8 代替之。
int l_width;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef long LONG;


//位图文件头信息结构定义
//其中不包含文件类型信息（由于结构体的内存结构决定，要是加了的话将不能正确读取文件信息）

typedef struct tagBITMAPFILEHEADER {

DWORD bfSize; //文件大小
WORD bfReserved1; //保留字，不考虑
WORD bfReserved2; //保留字，同上
DWORD bfOffBits; //实际位图数据的偏移字节数，即前三个部分长度之和
} BITMAPFILEHEADER;


//信息头BITMAPINFOHEADER，也是一个结构，其定义如下：

typedef struct tagBITMAPINFOHEADER{
//public:
DWORD biSize; //指定此结构体的长度，为40
LONG biWidth; //位图宽
LONG biHeight; //位图高
WORD biPlanes; //平面数，为1
WORD biBitCount; //采用颜色位数，可以是1，2，4，8，16，24，新的可以是32
DWORD biCompression; //压缩方式，可以是0，1，2，其中0表示不压缩
DWORD biSizeImage; //实际位图数据占用的字节数
LONG biXPelsPerMeter; //X方向分辨率
LONG biYPelsPerMeter; //Y方向分辨率
DWORD biClrUsed; //使用的颜色数，如果为0，则表示默认值(2^颜色位数)
DWORD biClrImportant; //重要颜色数，如果为0，则表示所有颜色都是重要的
} BITMAPINFOHEADER;


//调色板Palette，当然，这里是对那些需要调色板的位图文件而言的。24位和32位是不需要调色板的。
//（似乎是调色板结构体个数等于使用的颜色数。）

typedef struct tagRGBQUAD {
//public:
BYTE rgbBlue; //该颜色的蓝色分量
BYTE rgbGreen; //该颜色的绿色分量
BYTE rgbRed; //该颜色的红色分量
BYTE rgbReserved; //保留值
} RGBQUAD;



void showBmpHead(BITMAPFILEHEADER* pBmpHead)
{
printf("位图文件头:\n");
printf("文件大小:%d\n",pBmpHead->bfSize);
printf("保留字:%d\n",pBmpHead->bfReserved1);
printf("保留字:%d\n",pBmpHead->bfReserved2);
printf("实际位图数据的偏移字节数:%d\n",pBmpHead->bfOffBits);

}


void showBmpInforHead(struct tagBITMAPINFOHEADER* pBmpInforHead)
{
printf("位图信息头:\n");
printf("结构体的长度:%d\n",pBmpInforHead->biSize);
printf("位图宽:%d\n",pBmpInforHead->biWidth);
printf("位图高:%d\n",pBmpInforHead->biHeight);
printf("biPlanes平面数:%d\n",pBmpInforHead->biPlanes);
printf("biBitCount采用颜色位数:%d\n",pBmpInforHead->biBitCount);
printf("压缩方式:%d\n",pBmpInforHead->biCompression);
printf("biSizeImage实际位图数据占用的字节数:%d\n",pBmpInforHead->biSizeImage);
printf("X方向分辨率:%d\n",pBmpInforHead->biXPelsPerMeter);
printf("Y方向分辨率:%d\n",pBmpInforHead->biYPelsPerMeter);
printf("使用的颜色数:%d\n",pBmpInforHead->biClrUsed);
printf("重要颜色数:%d\n",pBmpInforHead->biClrImportant);
}

void showRgbQuan(struct tagRGBQUAD* pRGB)
{
printf("(%-3d,%-3d,%-3d) ",pRGB->rgbRed,pRGB->rgbGreen,pRGB->rgbBlue);

}
int bigger(int a, int b) {
    if (a > b) return a;
    else return b;
}

#endif
