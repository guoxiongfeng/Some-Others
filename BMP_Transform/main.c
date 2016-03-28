#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include"INFO.h"
#include"transform.c"
/*--------------------------------------------------------------------------------------------*/


void input(struct tagRGBQUAD * RGBdata, BYTE * data, int h, int w) {
    int i, j, index = 0, k;
    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++) {
            k = i * l_width + j * 3;
            RGBdata[index].rgbRed = data[k+2];
            RGBdata[index].rgbGreen = data[k+1];
            RGBdata[index].rgbBlue = data[k];
            index++;
        }
}
void output(BYTE * data, struct tagRGBQUAD * RGBdata, int h, int w) {
    int i, j, index = 0, k;
    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++) {
            k = i * l_width + j * 3;
            data[k] = RGBdata[index].rgbBlue;
            data[k + 1] = RGBdata[index].rgbGreen;
            data[k + 2] = RGBdata[index].rgbRed;
            index++;
        }
}

void deal(BYTE * data, struct tagRGBQUAD * RGBdata, int h, int w) {
    input(RGBdata, data, h, w);
    memset(data, 0, h * l_width);
    transform_gray(RGBdata, h, w);
    output(data, RGBdata, h, w);
}
/*-----------------------------------------------------------------------------------------------*/

int main() {

    BITMAPFILEHEADER bitHead;
    BITMAPINFOHEADER bitInfoHead;
    FILE* pfile, *p;
    WORD fileType;
    char strFile[50];
    printf("please input the .bmp file name:\n");
    scanf("%s",strFile);
    pfile = fopen(strFile,"rb");//打开文件
    p = fopen("copy.bmp", "wb");
    if(pfile!=NULL) {
    printf("file bkwood.bmp open success.\n");
    //读取位图文件头信息
    fread(&fileType,1,sizeof(WORD),pfile);
    fwrite(&fileType, 1, sizeof (WORD), p);
    if(fileType != 0x4d42) { //到底是BM还是MB。。。
        printf("file is not .bmp file!");
        return;
    }
//fseek(pfile,2,SEEK_CUR); // "BM"
    fread(&bitHead, 1,sizeof(struct tagBITMAPFILEHEADER),pfile);
    fwrite(&bitHead, 1, sizeof(struct tagBITMAPFILEHEADER), p);
    showBmpHead(&bitHead);
    printf("\n\n");

    //读取位图信息头信息
    fread(&bitInfoHead,1,sizeof(BITMAPINFOHEADER),pfile);
    fwrite(&bitInfoHead, 1, sizeof(BITMAPINFOHEADER), p);
    showBmpInforHead(&bitInfoHead);
    printf("\n");
    }
    else {
        printf("file open fail!\n");
        return;
    }

    int width = bitInfoHead.biWidth;
    int height = bitInfoHead.biHeight;
    //分配内存空间把源图存入内存
    int max = bigger(width, height);


    l_width = width*bitInfoHead.biBitCount / 8;/*WIDTHBYTES(width* bitInfoHead.biBitCount);*///计算位图的实际宽度并确保它为32的倍数


    BYTE *pColorData=(BYTE *)malloc(height * l_width);
    memset(pColorData,0,height*l_width);
    long nData = height*l_width;

    //把位图数据信息读到数组里（主要信息！！！！！！！！）
    fread(pColorData,1,nData,pfile);

    struct tagRGBQUAD *dataOfBmp = (struct tagRGBQUAD *)malloc(width * height * sizeof(struct tagRGBQUAD));//用于保存各像素对应的RGB数据
    memset(dataOfBmp, 0, sizeof(dataOfBmp));
    /*处理数据*/
    deal(pColorData, dataOfBmp, height, width);
    
    fwrite(pColorData, 1, nData, p);

    fclose(pfile);
    fclose(p);
    free(dataOfBmp);
    free(pColorData);
    printf("\n");
    return 0;
}
