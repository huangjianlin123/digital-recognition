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
// 卷积层
typedef struct convolutional_layer{
	int inputWidth;   //输入图像的宽
	int inputHeight;  //输入图像的长
	int mapSize;      //特征模板的大小，模板一般都是正方形
	int inChannels;   //输入图像的数目
	int outChannels;  //输出图像的数目
	int Covtype;
	float**** mapData;     //存放特征模块的数据
	float* basicData;   //偏置，偏置的大小，为outChannels
	bool isFullConnect; //是否为全连接
	bool* connectModel; //连接模式（默认为全连接）
	float*** v; // 进入激活函数的输入值
	float*** y; // 激活函数后神经元的输出
}CovLayer;
// 采样层 pooling
typedef struct pooling_layer{
	int inputWidth;   //输入图像的宽
	int inputHeight;  //输入图像的长
	int mapSize;      //特征模板的大小
	int inChannels;   //输入图像的数目
	int outChannels;  //输出图像的数目
	int poolType;     //Pooling的方法
	float*** y; // 采样函数后神经元的输出,无激活函数
}PoolLayer;
// 输出层 全连接的神经网络
typedef struct nn_layer{
	int inputNum;   //输入数据的数目
	int outputNum;  //输出数据的数目
    float** wData; // 权重数据，为一个inputNum*outputNum大小
	float* basicData;   //偏置，大小为outputNum大小
	float* v; // 进入激活函数的输入值
	float* y; // 激活函数后神经元的输出
	bool isFullConnect; //是否为全连接
}OutLayer;
//包含所有操作的全局图
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
// 测试cnn函数
int cnntest(CNN* cnn, float ** inputData);
// 保存cnn
void savecnn(CNN* cnn, const char* filename);
// 导入cnn的数据
void importcnn(CNN* cnn);

// 初始化卷积层
CovLayer* initCovLayer(int inputWidth,int inputHeight,int mapSize,int inChannels,int outChannels,int covtype);
void CovLayerConnect(CovLayer* covL,bool* connectModel);
// 初始化采样层
PoolLayer* initPoolLayer(int inputWidth,int inputHeigh,int mapSize,int inChannels,int outChannels,int poolType);
void PoolLayerConnect(PoolLayer* poolL,bool* connectModel);
// 初始化输出层
OutLayer* initOutLayer(int inputNum,int outputNum);

// 激活函数 input是数据，inputNum说明数据数目，bas表明偏置
float activation_Sigma(float input,float bas); // sigma激活函数
float activation_relu(float input, float bas);
void cnnff(CNN* cnn,float** inputData); // 网络的前向传播
void cnnbp(CNN* cnn,float* outputData); // 网络的后向传播
void cnnclear(CNN* cnn); // 将数据vyd清零

/*
	Pooling Function
	input 输入数据
	inputNum 输入数据数目
	mapSize 求平均的模块区域
*/
void avgPooling(float** output,nSize outputSize,float** input,nSize inputSize,int mapSize); // 求平均值
void maxPooling(float** output, nSize outputSize, float** input, nSize inputSize, int mapSize);
/* 
	单层全连接神经网络的处理
	nnSize是网络的大小
*/
void nnff(float* output,float* input,float** wdata,float* bas,nSize nnSize); // 单层全连接神经网络的前向传播

void savecnndata(CNN* cnn,const char* filename,float** inputdata); // 保存CNN网络中的相关数据

#endif
