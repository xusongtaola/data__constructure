#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 50				//叶子结点数
#define M 2*N-1				//树中结点总数
typedef struct {
	char data[5];			//结点值
	int weight;				//权重
	int parent;				//双亲结点
	int lchild;				//左孩子结点
	int rchild;				//右孩子结点
}HTNode;
typedef struct {
	char cd[N];				//存放哈夫曼编码
	int start;				//cd[start..n]存放哈夫曼编码
}HCode;
void CreateHT(HTNode ht[], int n) {				//由ht的叶子结点构造完整的哈夫曼树
	int i, k, lnode, rnode;
	int min1, min2;
	for (i = 0; i < 2 * n - 1; i++)
		ht[i].parent = ht[i].lchild = ht[i].rchild = -1;		//所有节点的相关域置-1，表示其仍为不被纳入哈夫曼树的叶子结点
	for (i = n; i < 2 * n - 1; i++) {						//构造哈夫曼树分支结点（数组中已经构造好了相关的哈夫曼树，现在只是还原）
		min1 = min2 = 32767;
		lnode = rnode = -1;							//lnode、rnode为最小权重的两个结点位置
		for (k = 0; k <= i - 1; k++)
			if (ht[k].parent == -1) {				//不停的查找最小和次小的结点
				if (ht[k].weight < min1) {			//-1负责甄别哪些叶子结点未接入哈夫曼树
					min2 = min1; rnode = lnode;		//把左孩子节点编号赋值给右孩子结点，因为其是次小
					min1 = ht[k].weight; lnode = k;
				}
				else if (ht[k].weight < min2) {
					min2 = ht[k].weight; rnode = k;
				}
			}
		ht[lnode].parent = i; ht[rnode].parent = i;			//合并两个最小和次小的结点
		ht[i].weight = ht[lnode].weight + ht[rnode].weight;
		ht[i].lchild = lnode; ht[i].rchild = rnode;
	}
}
void CreateHCode(HTNode ht[], HCode hcd[], int n) {
	int i, f, c;
	HCode hc;
	for (i = 0; i < n; i++) {					//根据哈弗曼树构造所有叶子节点的哈弗曼编码
		hc.start = n; c = i;
		f = ht[i].parent;
		while (f != -1) {						//循环直到树根结点
			if (ht[f].lchild == c)				//处理左孩子结点
				hc.cd[hc.start--] = '0';
			else								//处理右孩子结点
				hc.cd[hc.start--] = '1';
			c = f; f = ht[f].parent;
		}
		hc.start++;								//这句话不解，不加有影响吗？是为了后面用循环输出编码方便（开始位置不能为-1）
		hcd[i] = hc;							//每一个编码就都保存了下来
	}
}
void DispHCode(HTNode ht[], HCode hcd[], int n) {				//输出哈夫曼编码
	int i, k;
	int sum = 0, m = 0, j;
	printf("输出哈夫曼编码：\n");
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
	printf("\n平均长度=%g\n", 1.0*sum / m);
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