#ifndef __CNN_
#define __CNN_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <random>
#include <time.h>
#include "mat.h"


#define AvePool 0
#define MaxPool 1
#define MinPool 2
// �����
typedef struct convolutional_layer{
	int inputWidth;   //����ͼ��Ŀ�
	int inputHeight;  //����ͼ��ĳ�
	int mapSize;      //����ģ��Ĵ�С��ģ��һ�㶼��������
	int inChannels;   //����ͼ�����Ŀ
	int outChannels;  //���ͼ�����Ŀ
	int Covtype;
	float**** mapData;     //�������ģ�������
	float* basicData;   //ƫ�ã�ƫ�õĴ�С��ΪoutChannels
	bool isFullConnect; //�Ƿ�Ϊȫ����
	bool* connectModel; //����ģʽ��Ĭ��Ϊȫ���ӣ�
	float*** v; // ���뼤���������ֵ
	float*** y; // ���������Ԫ�����
}CovLayer;
// ������ pooling
typedef struct pooling_layer{
	int inputWidth;   //����ͼ��Ŀ�
	int inputHeight;  //����ͼ��ĳ�
	int mapSize;      //����ģ��Ĵ�С
	int inChannels;   //����ͼ�����Ŀ
	int outChannels;  //���ͼ�����Ŀ
	int poolType;     //Pooling�ķ���
	float*** y; // ������������Ԫ�����,�޼����
}PoolLayer;
// ����� ȫ���ӵ�������
typedef struct nn_layer{
	int inputNum;   //�������ݵ���Ŀ
	int outputNum;  //������ݵ���Ŀ
    float** wData; // Ȩ�����ݣ�Ϊһ��inputNum*outputNum��С
	float* basicData;   //ƫ�ã���СΪoutputNum��С
	float* v; // ���뼤���������ֵ
	float* y; // ���������Ԫ�����
	bool isFullConnect; //�Ƿ�Ϊȫ����
}OutLayer;
//�������в�����ȫ��ͼ
typedef struct cnn_network{
	int layerNum;
	CovLayer* C1;
	PoolLayer* S2;
	CovLayer* C3;
	PoolLayer* S4;
	OutLayer* O5;
	OutLayer* O6;
	OutLayer* O7;
}CNN;

void cnnsetup(CNN* cnn,nSize inputSize,int outputSize);
// ����cnn����
int cnntest(CNN* cnn, float ** inputData);
// ����cnn
void savecnn(CNN* cnn, const char* filename);
// ����cnn������
void importcnn(CNN* cnn);

// ��ʼ�������
CovLayer* initCovLayer(int inputWidth,int inputHeight,int mapSize,int inChannels,int outChannels,int covtype);
void CovLayerConnect(CovLayer* covL,bool* connectModel);
// ��ʼ��������
PoolLayer* initPoolLayer(int inputWidth,int inputHeigh,int mapSize,int inChannels,int outChannels,int poolType);
void PoolLayerConnect(PoolLayer* poolL,bool* connectModel);
// ��ʼ�������
OutLayer* initOutLayer(int inputNum,int outputNum);

// ����� input�����ݣ�inputNum˵��������Ŀ��bas����ƫ��
float activation_Sigma(float input,float bas); // sigma�����
float activation_relu(float input, float bas);
void cnnff(CNN* cnn,float** inputData); // �����ǰ�򴫲�
void cnnbp(CNN* cnn,float* outputData); // ����ĺ��򴫲�
void cnnclear(CNN* cnn); // ������vyd����

/*
	Pooling Function
	input ��������
	inputNum ����������Ŀ
	mapSize ��ƽ����ģ������
*/
void avgPooling(float** output,nSize outputSize,float** input,nSize inputSize,int mapSize); // ��ƽ��ֵ
void maxPooling(float** output, nSize outputSize, float** input, nSize inputSize, int mapSize);
/* 
	����ȫ����������Ĵ���
	nnSize������Ĵ�С
*/
void nnff(float* output,float* input,float** wdata,float* bas,nSize nnSize); // ����ȫ�����������ǰ�򴫲�

void savecnndata(CNN* cnn,const char* filename,float** inputdata); // ����CNN�����е��������

#endif
