#include"graybin.h"
void erjihua(unsigned char aa[][480])
{
	FILE *fpBMP, *fpTwoValue;//Դ�ļ�fpBMP,Ŀ���ļ�fpTwoValue
	fileHeader *fh;//λͼ�ļ�ͷ
	fileInfo *fi;//λͼ��Ϣͷ
	rgbq *rg;//��ɫ��
	int i, j, k = 0;
	unsigned char *a;//�洢Դͼÿ������ֵ
	unsigned char b;//�洢ÿ�����صĻҶ�ֵ���ֵ
	unsigned char *c;//�洢ÿ�����صĶ�ֵ
	/*��Դ�ļ�����������ļ�*/
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
	/*����Դλͼ�ļ�ͷ����Ϣͷ*/
	fread(fh, sizeof(fileHeader), 1, fpBMP);
	fread(fi, sizeof(fileInfo), 1, fpBMP);
	/*�޸��ļ�ͷ����Ϣͷ��Ϣ*/
	fi->biBitCount = 8;//ת���ɶ�ֵͼ����ɫ�����24λ��Ϊ8λ
	fi->biSizeImage = ((fi->biWidth + 3) / 4) * 4 * fi->biHeight;//ÿ�����������ֽڱ�Ϊ���ֽڣ�ͬʱÿ������Ҫ���ֽڶ���
	fi->biClrUsed = 2;//��ɫ��������������ֵͼΪ2
	fi->biClrImportant = 0;//��Ҫ��ɫ����Ϊ0����ʾ����Ҫ
	fh->bfOffBits = sizeof(fileHeader)+sizeof(fileInfo)+2 * sizeof(rgbq);//������ƫ�����������ļ�ͷ����Ϣͷ��������Ĵ�С֮��
	fh->bfSize = fh->bfOffBits + fi->biSizeImage;//�ļ���С������ƫ����������������С
	rg[0].rgbBlue = rg[0].rgbGreen = rg[0].rgbRed = rg[0].rgbReserved = 0;//��ɫ����ɫΪ��ɫ��Ӧ������Ϊ0
	rg[1].rgbBlue = rg[1].rgbGreen = rg[1].rgbRed = 255;//��ɫ��Ӧ������Ϊ1
	rg[1].rgbReserved = 0;
	/*��λͼ�ļ�ͷ����Ϣͷ�͵�ɫ��д���ļ�*/
	fwrite(fh, sizeof(fileHeader), 1, fpTwoValue);
	fwrite(fi, sizeof(fileInfo), 1, fpTwoValue);
	fwrite(rg, 2 * sizeof(rgbq), 1, fpTwoValue);
	/*����ɫͼתΪ��ֵͼ*/
	a = (unsigned char *)malloc((fi->biWidth * 3 + 3) / 4 * 4);//������a����Դͼÿ��������ռ��С�Ŀռ�,�������ֽڶ�������
	c = (unsigned char *)malloc((fi->biWidth + 3) / 4 * 4);//������c����Ŀ��ͼÿ��������ռ��С�Ŀռ�,ͬ�����ֽڶ���
	for (i = 0; i<fi->biHeight; i++){//����ͼ��ÿ�е�ѭ��
		for (j = 0; j<((fi->biWidth * 3 + 3) / 4 * 4); j++){//����ÿ����ÿ���ֽڵ�ѭ��
			fread(a + j, 1, 1, fpBMP);//��Դͼÿ�е�ÿһ���ֽڶ������a��ָ����ڴ�ռ�
			//printf("%d ",a[j]);
		}
		for (j = 0; j<fi->biWidth; j++){//ѭ�����ؿ�ȴ�,�Ͳ������������ֽ����λ
			b = (int)(0.114*(float)a[k] + 0.587*(float)a[k + 1] + 0.299*(float)a[k + 2]);//a��ÿ�����ֽڷֱ����BGR���������ϲ�ͬȨֵת��Ϊ�Ҷ�ֵ
			//printf("%d",b);
			if (190 <= (int)b) b = 1;//���Ҷ�ֵת��Ϊ��ֵ������ѡȡ����ֵΪ190
			else b = 0;
			c[j] = b;//�洢ÿ�еĶ�ֵ
			aa[i][j] =1- b;
			k += 3;
		}
		fwrite(c, (fi->biWidth + 3) / 4 * 4, 1, fpTwoValue);//����ֵ�������ֽ����д���ļ�,���λû�г�ʼ��,Ϊ���ֵ
		k = 0;
	}
	/********************************************************************/
	/*�ͷ��ڴ�ռ䣬�ر��ļ�*/
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

	
