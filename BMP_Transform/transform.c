#include"INFO.h"
#include<string.h>
/*struct tagRGBQUAD average(struct tagRGBQUAD* RGBdata, int i, int j, int w) {
    struct tagRGBQUAD tmp;
    tmp.rgbBlue = (RGBdata[w * (i - 1) + j - 1].rgbBlue + RGBdata[w * (i - 1) + j].rgbBlue + RGBdata[w * (i - 1) + j + 1].rgbBlue + RGBdata[w * i + j - 1].rgbBlue + RGBdata[w * i + j].rgbBlue + RGBdata[w * i + j + 1].rgbBlue + RGBdata[w * (i + 1) + j - 1].rgbBlue + RGBdata[w * (i + 1) + j].rgbBlue + RGBdata[w * (i + 1) + j + 1].rgbBlue) / 9;
    tmp.rgbGreen =(RGBdata[w * (i - 1) + j - 1].rgbGreen + RGBdata[w * (i - 1) + j].rgbGreen + RGBdata[w * (i - 1) + j + 1].rgbGreen + RGBdata[w * i + j - 1].rgbGreen + RGBdata[w * i + j].rgbGreen + RGBdata[w * i + j + 1].rgbGreen + RGBdata[w * (i + 1) + j - 1].rgbGreen + RGBdata[w * (i + 1) + j].rgbGreen + RGBdata[w * (i + 1) + j + 1].rgbGreen) / 9;
    tmp.rgbRed = (RGBdata[w * (i - 1) + j - 1].rgbRed + RGBdata[w * (i - 1) + j].rgbRed + RGBdata[w * (i - 1) + j + 1].rgbRed + RGBdata[w * i + j - 1].rgbRed + RGBdata[w * i + j].rgbRed + RGBdata[w * i + j + 1].rgbRed + RGBdata[w * (i + 1) + j - 1].rgbRed + RGBdata[w * (i + 1) + j].rgbRed + RGBdata[w * (i + 1) + j + 1].rgbRed) / 9;
    return tmp;
}*/
/*struct tagRGBQUAD average(struct tagRGBQUAD* RGBdata, int row, int col, int w) {
    struct tagRGBQUAD tmp;
    memset(&tmp, 0, sizeof(tmp));
    int i, j;
    for (i = row - 1; i <= row + 1; ++i)
        for (j = col - 1; j <= col + 1; ++j) {
            tmp.rgbBlue += RGBdata[i * w + j].rgbBlue % 256;
            tmp.rgbGreen += RGBdata[i * w + j].rgbGreen  % 256;
            tmp.rgbRed += RGBdata[i * w + j].rgbRed % 256;
        }
    tmp.rgbBlue/= 9;
    tmp.rgbGreen/= 9;
    tmp.rgbRed/= 9;//同时缩小或可调亮度
    return tmp;
}*/

struct tagRGBQUAD average(struct tagRGBQUAD* RGBdata, int row, int col, int w) {
    int red = 0, green = 0, blue = 0, i, j;
    struct tagRGBQUAD tmp;
    for (i = row - 6; i <= row + 6; ++i)
        for (j = col - 6; j <= col + 6; ++j) {
            blue += RGBdata[i * w + j].rgbBlue ;
            green += RGBdata[i * w + j].rgbGreen;
            red += RGBdata[i * w + j].rgbRed;
        }
    tmp.rgbBlue = blue / 169;
    tmp.rgbGreen = green / 169;
    tmp.rgbRed = red / 169;
    return tmp;
}
void set(struct tagRGBQUAD* RGBdata, int row, int col, int w) {
    int i, j;
    for (i = row - 2; i <= row + 2; ++i)
        for (j = col - 2; j <= col + 2; ++j) {
            RGBdata[w * i + j] = RGBdata[w * row + col];
        }
    return;
}
void swap(struct tagRGBQUAD *a, struct tagRGBQUAD *b) {
    struct tagRGBQUAD tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}
void transform_inverse(struct tagRGBQUAD* RGBdata, int h, int w) {
    int k;
    for (k = 0; k < h * w; ++k) {
        RGBdata[k].rgbBlue = 255 - RGBdata[k].rgbBlue;
        RGBdata[k].rgbGreen = 255 - RGBdata[k].rgbGreen;
        RGBdata[k].rgbRed = 255 - RGBdata[k].rgbRed;
    }
    return ;
}


void transform_gray(struct tagRGBQUAD* RGBdata, int h, int w) {
    int  k, gray;
    for (k = 0; k < h * w; ++k) {
        gray = (RGBdata[k].rgbRed * 30 + RGBdata[k].rgbGreen * 59 + RGBdata[k].rgbBlue * 11 + 50) / 100;
        RGBdata[k].rgbBlue = gray;
        RGBdata[k].rgbGreen = gray;
        RGBdata[k].rgbRed = gray;
    }
    return ;
}


void transform_upsidedown(struct tagRGBQUAD *RGBdata, int h, int w) {
    int i, j, k;
    for (k = 0; k < h * w; ++k) {
        i = k / w;
        j = k % w;
        if (i > h / 2) return ;
        swap(&RGBdata[k], &RGBdata[(h - i -1) * w + j]);
    }
}


void transform_flip(struct tagRGBQUAD *RGBdata, int h, int w) {
    int i, j, k;
    for (k = 0; k < h * w; ++k) {
        i = k / w;
        j = k % w;
        if (j > w / 2) continue;
        swap(&RGBdata[k], &RGBdata[i * w + w - j - 1]);
    }
    return;
}


void transform_halfheight(struct tagRGBQUAD *RGBdata, int h, int w) {
    int i, j, k;
    for (k = 0; k < h * w; ++k) {
        i = k / w;
        j = k % w;
        RGBdata[i / 2 * w + j] = RGBdata[i * w + j];
        if (i >= h / 2) memset(&RGBdata[k], 255, sizeof(struct tagRGBQUAD));
    }
    return ;
}


void transform_halfwidth(struct tagRGBQUAD *RGBdata, int h, int w) {
    int i, j, k;
    for (k = 0; k < h * w; ++k) {
        i = k / w;
        j = k % w;
        RGBdata[i * w+ j / 2] = RGBdata[k];
        if (j >= w / 2) memset(&RGBdata[k], 255, sizeof(struct tagRGBQUAD));
    }
    return;
}
void transform_blur(struct tagRGBQUAD *RGBdata, int h, int w) {
    int i, j, k;
    for (i = 6; i < h - 6; ++i)
        for (j = 6; j < w - 6; ++j) {
            RGBdata[w * i + j] = average(RGBdata, i, j, w);
        }
}
void transform_mosaic(struct tagRGBQUAD *RGBdata, int h, int w) {
    int i, j;
    for (i = 2; i < h - 3; i+= 5)
        for (j = 2; j < w - 3; j+= 5) {
            set(RGBdata, i, j, w);
        }
}
void transform_brightness(struct tagRGBQUAD *RGBdata, int h, int w, float l) {
    int k;
    for (k = 0; k < h * w; ++k) {
        RGBdata[k].rgbBlue = l * RGBdata[k].rgbBlue;
        RGBdata[k].rgbGreen = l * RGBdata[k].rgbGreen;
        RGBdata[k].rgbRed = l * RGBdata[k].rgbRed;
    }
    return ;
}/*亮度 饱和度*/
