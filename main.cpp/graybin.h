#include <stdio.h>
#include <stdlib.h>
unsigned char c[640][480] = {0};
#pragma pack(1)//单字节对齐
typedef struct tagBITMAPFILEHEADER
{
	unsigned char bfType[2];//文件格式
	unsigned int bfSize;//文件大小
	unsigned short bfReserved1;//保留
	unsigned short bfReserved2;//保留
	unsigned int bfOffBits;//数据偏移量
}fileHeader;
#pragma pack()
/*位图信息头*/
#pragma pack(1)
typedef struct tagBITMAPINFOHEADER
{
	unsigned int biSize;//BITMAPINFOHEADER结构所需要的字数
	int biWidth;//图像宽度，像素为单位
	int biHeight;//图像高度，像素为单位，为正数，图像是倒序的，为负数，图像是正序的
	unsigned short biPlanes;//为目标设备说明颜色平面数，总被置为1
	unsigned short biBitCount;//说明比特数/像素
	unsigned int biCompression;//说明数据压缩类型
	unsigned int biSizeImage;//说明图像大小，字节单位
	int biXPixPerMeter;//水平分辨率，像素/米
	int biYPixPerMeter;//垂直分辨率
	unsigned int biClrUsed;//颜色索引数
	unsigned int biClrImportant;//重要颜色索引数，为0表示都重要
}fileInfo;
#pragma pack()
/*调色板结构*/
#pragma pack(1)
typedef struct tagRGBQUAD
{
	unsigned char rgbBlue;//蓝色分亮度
	unsigned char rgbGreen;//绿色分亮度
	unsigned char rgbRed;//红色分亮度
	unsigned char rgbReserved;
}rgbq;
#pragma pack()
void erjihua(unsigned char aa[][480]);
void  printfpic(unsigned char c[][480]);