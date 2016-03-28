#ifndef INFO_H
#define INFO_H
#include <stdio.h>
#define WIDTHBYTES(bits) (((bits)+31)/32*4) //�� ��⣺ ��֤��Ϊ������word���� ������width*bitInfoHead.biBitCount/8 ����֮��
int l_width;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef long LONG;


//λͼ�ļ�ͷ��Ϣ�ṹ����
//���в������ļ�������Ϣ�����ڽṹ����ڴ�ṹ������Ҫ�Ǽ��˵Ļ���������ȷ��ȡ�ļ���Ϣ��

typedef struct tagBITMAPFILEHEADER {

DWORD bfSize; //�ļ���С
WORD bfReserved1; //�����֣�������
WORD bfReserved2; //�����֣�ͬ��
DWORD bfOffBits; //ʵ��λͼ���ݵ�ƫ���ֽ�������ǰ�������ֳ���֮��
} BITMAPFILEHEADER;


//��ϢͷBITMAPINFOHEADER��Ҳ��һ���ṹ���䶨�����£�

typedef struct tagBITMAPINFOHEADER{
//public:
DWORD biSize; //ָ���˽ṹ��ĳ��ȣ�Ϊ40
LONG biWidth; //λͼ��
LONG biHeight; //λͼ��
WORD biPlanes; //ƽ������Ϊ1
WORD biBitCount; //������ɫλ����������1��2��4��8��16��24���µĿ�����32
DWORD biCompression; //ѹ����ʽ��������0��1��2������0��ʾ��ѹ��
DWORD biSizeImage; //ʵ��λͼ����ռ�õ��ֽ���
LONG biXPelsPerMeter; //X����ֱ���
LONG biYPelsPerMeter; //Y����ֱ���
DWORD biClrUsed; //ʹ�õ���ɫ�������Ϊ0�����ʾĬ��ֵ(2^��ɫλ��)
DWORD biClrImportant; //��Ҫ��ɫ�������Ϊ0�����ʾ������ɫ������Ҫ��
} BITMAPINFOHEADER;


//��ɫ��Palette����Ȼ�������Ƕ���Щ��Ҫ��ɫ���λͼ�ļ����Եġ�24λ��32λ�ǲ���Ҫ��ɫ��ġ�
//���ƺ��ǵ�ɫ��ṹ���������ʹ�õ���ɫ������

typedef struct tagRGBQUAD {
//public:
BYTE rgbBlue; //����ɫ����ɫ����
BYTE rgbGreen; //����ɫ����ɫ����
BYTE rgbRed; //����ɫ�ĺ�ɫ����
BYTE rgbReserved; //����ֵ
} RGBQUAD;



void showBmpHead(BITMAPFILEHEADER* pBmpHead)
{
printf("λͼ�ļ�ͷ:\n");
printf("�ļ���С:%d\n",pBmpHead->bfSize);
printf("������:%d\n",pBmpHead->bfReserved1);
printf("������:%d\n",pBmpHead->bfReserved2);
printf("ʵ��λͼ���ݵ�ƫ���ֽ���:%d\n",pBmpHead->bfOffBits);

}


void showBmpInforHead(struct tagBITMAPINFOHEADER* pBmpInforHead)
{
printf("λͼ��Ϣͷ:\n");
printf("�ṹ��ĳ���:%d\n",pBmpInforHead->biSize);
printf("λͼ��:%d\n",pBmpInforHead->biWidth);
printf("λͼ��:%d\n",pBmpInforHead->biHeight);
printf("biPlanesƽ����:%d\n",pBmpInforHead->biPlanes);
printf("biBitCount������ɫλ��:%d\n",pBmpInforHead->biBitCount);
printf("ѹ����ʽ:%d\n",pBmpInforHead->biCompression);
printf("biSizeImageʵ��λͼ����ռ�õ��ֽ���:%d\n",pBmpInforHead->biSizeImage);
printf("X����ֱ���:%d\n",pBmpInforHead->biXPelsPerMeter);
printf("Y����ֱ���:%d\n",pBmpInforHead->biYPelsPerMeter);
printf("ʹ�õ���ɫ��:%d\n",pBmpInforHead->biClrUsed);
printf("��Ҫ��ɫ��:%d\n",pBmpInforHead->biClrImportant);
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
