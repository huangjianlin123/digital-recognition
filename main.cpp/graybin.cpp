#include"graybin.h"
void erjihua(unsigned char aa[][480])
{
	FILE *fpBMP, *fpTwoValue;//源文件fpBMP,目标文件fpTwoValue
	fileHeader *fh;//位图文件头
	fileInfo *fi;//位图信息头
	rgbq *rg;//调色板
	int i, j, k = 0;
	unsigned char *a;//存储源图每行像素值
	unsigned char b;//存储每个像素的灰度值或二值
	unsigned char *c;//存储每行像素的二值
	/*打开源文件，创建输出文件*/
	if ((fpBMP = fopen("C:\\Users\\dell\\Desktop\\11.bmp", "rb")) == NULL){
		printf("file open failed");
		exit(0);
	}
	if ((fpTwoValue = fopen("C:\\Users\\dell\\Desktop\\111.bmp", "wb")) == NULL){
		printf("file creat failed");
		exit(0);
	}
	fh = (fileHeader *)malloc(sizeof(fileHeader));
	fi = (fileInfo *)malloc(sizeof(fileInfo));
	rg = (rgbq *)malloc(2 * sizeof(rgbq));
	/*读入源位图文件头和信息头*/
	fread(fh, sizeof(fileHeader), 1, fpBMP);
	fread(fi, sizeof(fileInfo), 1, fpBMP);
	/*修改文件头，信息头信息*/
	fi->biBitCount = 8;//转换成二值图后，颜色深度由24位变为8位
	fi->biSizeImage = ((fi->biWidth + 3) / 4) * 4 * fi->biHeight;//每个像素由三字节变为单字节，同时每行像素要四字节对齐
	fi->biClrUsed = 2;//颜色索引表数量，二值图为2
	fi->biClrImportant = 0;//重要颜色索引为0，表示都重要
	fh->bfOffBits = sizeof(fileHeader)+sizeof(fileInfo)+2 * sizeof(rgbq);//数据区偏移量，等于文件头，信息头，索引表的大小之和
	fh->bfSize = fh->bfOffBits + fi->biSizeImage;//文件大小，等于偏移量加上数据区大小
	rg[0].rgbBlue = rg[0].rgbGreen = rg[0].rgbRed = rg[0].rgbReserved = 0;//调色板颜色为黑色对应的索引为0
	rg[1].rgbBlue = rg[1].rgbGreen = rg[1].rgbRed = 255;//白色对应的索引为1
	rg[1].rgbReserved = 0;
	/*将位图文件头，信息头和调色板写入文件*/
	fwrite(fh, sizeof(fileHeader), 1, fpTwoValue);
	fwrite(fi, sizeof(fileInfo), 1, fpTwoValue);
	fwrite(rg, 2 * sizeof(rgbq), 1, fpTwoValue);
	/*将彩色图转为二值图*/
	a = (unsigned char *)malloc((fi->biWidth * 3 + 3) / 4 * 4);//给变量a申请源图每行像素所占大小的空间,考虑四字节对齐问题
	c = (unsigned char *)malloc((fi->biWidth + 3) / 4 * 4);//给变量c申请目标图每行像素所占大小的空间,同样四字节对齐
	for (i = 0; i<fi->biHeight; i++){//遍历图像每行的循环
		for (j = 0; j<((fi->biWidth * 3 + 3) / 4 * 4); j++){//遍历每行中每个字节的循环
			fread(a + j, 1, 1, fpBMP);//将源图每行的每一个字节读入变量a所指向的内存空间
			//printf("%d ",a[j]);
		}
		for (j = 0; j<fi->biWidth; j++){//循环像素宽度次,就不会计算读入四字节填充位
			b = (int)(0.114*(float)a[k] + 0.587*(float)a[k + 1] + 0.299*(float)a[k + 2]);//a中每三个字节分别代表BGR分量，乘上不同权值转化为灰度值
			//printf("%d",b);
			if (190 <= (int)b) b = 1;//将灰度值转化为二值，这里选取的阈值为190
			else b = 0;
			c[j] = b;//存储每行的二值
			aa[i][j] =1- b;
			k += 3;
		}
		fwrite(c, (fi->biWidth + 3) / 4 * 4, 1, fpTwoValue);//将二值像素四字节填充写入文件,填充位没有初始化,为随机值
		k = 0;
	}
	/********************************************************************/
	/*释放内存空间，关闭文件*/
	free(fh);
	free(fi);
	free(rg);
	free(a);
	free(c);
	fclose(fpBMP);
	fclose(fpTwoValue);
	printf("success!\n");
}
void printfpic(unsigned char c[][480]){
	int i,j;
	FILE *fpTwoValue = fopen("C:\\Users\\dell\\Desktop\\1.txt", "w");
	for (i = 0; i < 640; i++){
		for (j = 0; j < 480; j++){
			fprintf(fpTwoValue,"%c ", 1);
		}
		printf("\n");
	}
	fclose(fpTwoValue);
}
void main(){
	//erjihua(c);
	printfpic(c);
}

	
