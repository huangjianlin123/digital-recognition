#include <stdio.h>
#include <stdlib.h>
unsigned char c[640][480] = {0};
#pragma pack(1)//���ֽڶ���
typedef struct tagBITMAPFILEHEADER
{
	unsigned char bfType[2];//�ļ���ʽ
	unsigned int bfSize;//�ļ���С
	unsigned short bfReserved1;//����
	unsigned short bfReserved2;//����
	unsigned int bfOffBits;//����ƫ����
}fileHeader;
#pragma pack()
/*λͼ��Ϣͷ*/
#pragma pack(1)
typedef struct tagBITMAPINFOHEADER
{
	unsigned int biSize;//BITMAPINFOHEADER�ṹ����Ҫ������
	int biWidth;//ͼ���ȣ�����Ϊ��λ
	int biHeight;//ͼ��߶ȣ�����Ϊ��λ��Ϊ������ͼ���ǵ���ģ�Ϊ������ͼ���������
	unsigned short biPlanes;//ΪĿ���豸˵����ɫƽ�������ܱ���Ϊ1
	unsigned short biBitCount;//˵��������/����
	unsigned int biCompression;//˵������ѹ������
	unsigned int biSizeImage;//˵��ͼ���С���ֽڵ�λ
	int biXPixPerMeter;//ˮƽ�ֱ��ʣ�����/��
	int biYPixPerMeter;//��ֱ�ֱ���
	unsigned int biClrUsed;//��ɫ������
	unsigned int biClrImportant;//��Ҫ��ɫ��������Ϊ0��ʾ����Ҫ
}fileInfo;
#pragma pack()
/*��ɫ��ṹ*/
#pragma pack(1)
typedef struct tagRGBQUAD
{
	unsigned char rgbBlue;//��ɫ������
	unsigned char rgbGreen;//��ɫ������
	unsigned char rgbRed;//��ɫ������
	unsigned char rgbReserved;
}rgbq;
#pragma pack()
void erjihua(unsigned char aa[][480]);
void  printfpic(unsigned char c[][480]);