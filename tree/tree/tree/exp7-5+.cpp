#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 50				//Ҷ�ӽ����
#define M 2*N-1				//���н������
typedef struct {
	char data[5];			//���ֵ
	int weight;				//Ȩ��
	int parent;				//˫�׽��
	int lchild;				//���ӽ��
	int rchild;				//�Һ��ӽ��
}HTNode;
typedef struct {
	char cd[N];				//��Ź���������
	int start;				//cd[start..n]��Ź���������
}HCode;
void CreateHT(HTNode ht[], int n) {				//��ht��Ҷ�ӽ�㹹�������Ĺ�������
	int i, k, lnode, rnode;
	int min1, min2;
	for (i = 0; i < 2 * n - 1; i++)
		ht[i].parent = ht[i].lchild = ht[i].rchild = -1;		//���нڵ���������-1����ʾ����Ϊ�����������������Ҷ�ӽ��
	for (i = n; i < 2 * n - 1; i++) {						//�������������֧��㣨�������Ѿ����������صĹ�������������ֻ�ǻ�ԭ��
		min1 = min2 = 32767;
		lnode = rnode = -1;							//lnode��rnodeΪ��СȨ�ص��������λ��
		for (k = 0; k <= i - 1; k++)
			if (ht[k].parent == -1) {				//��ͣ�Ĳ�����С�ʹ�С�Ľ��
				if (ht[k].weight < min1) {			//-1���������ЩҶ�ӽ��δ�����������
					min2 = min1; rnode = lnode;		//�����ӽڵ��Ÿ�ֵ���Һ��ӽ�㣬��Ϊ���Ǵ�С
					min1 = ht[k].weight; lnode = k;
				}
				else if (ht[k].weight < min2) {
					min2 = ht[k].weight; rnode = k;
				}
			}
		ht[lnode].parent = i; ht[rnode].parent = i;			//�ϲ�������С�ʹ�С�Ľ��
		ht[i].weight = ht[lnode].weight + ht[rnode].weight;
		ht[i].lchild = lnode; ht[i].rchild = rnode;
	}
}
void CreateHCode(HTNode ht[], HCode hcd[], int n) {
	int i, f, c;
	HCode hc;
	for (i = 0; i < n; i++) {					//���ݹ���������������Ҷ�ӽڵ�Ĺ���������
		hc.start = n; c = i;
		f = ht[i].parent;
		while (f != -1) {						//ѭ��ֱ���������
			if (ht[f].lchild == c)				//�������ӽ��
				hc.cd[hc.start--] = '0';
			else								//�����Һ��ӽ��
				hc.cd[hc.start--] = '1';
			c = f; f = ht[f].parent;
		}
		hc.start++;								//��仰���⣬������Ӱ������Ϊ�˺�����ѭ��������뷽�㣨��ʼλ�ò���Ϊ-1��
		hcd[i] = hc;							//ÿһ������Ͷ�����������
	}
}
void DispHCode(HTNode ht[], HCode hcd[], int n) {				//�������������
	int i, k;
	int sum = 0, m = 0, j;
	printf("������������룺\n");
	for (i = 0; i < n; i++) {
		j = 0;
		printf("\n	%s: \t", ht[i].data);
		for (k = hcd[i].start; k <= n; k++) {
			printf(" %c ", hcd[i].cd[k]);
			j++;
		}
		m += ht[i].weight;
		sum += ht[i].weight * j;
	}
	printf("\nƽ������=%g\n", 1.0*sum / m);
}
int main() {
	int n = 23, i;
	char *str[] = { "1","2","3","4","5","6","7","8","9","10","11","12","13","14","15" ,"16" ,"17" ,"18" ,"19" ,"20" ,"21" ,"22" ,"23" };
	int fnum[] = { 186,64,13,22 ,32 ,103 ,21, 15, 47 ,57, 1, 5, 32, 20, 57, 63 ,15 ,1 ,48, 51, 80 ,23 ,8 };
	HTNode ht[M];
	HCode hcd[N];
	for (i = 0; i < n; i++) {
		strcpy_s(ht[i].data, str[i]);
		//ht[i].data = i+1;
		ht[i].weight = fnum[i];
	}
	CreateHT(ht, n);
	CreateHCode(ht, hcd, n);
	DispHCode(ht, hcd, n);
	system("pause");
	return 1;
}