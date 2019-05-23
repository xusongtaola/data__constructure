#pragma once
#include<stdio.h>
#include<malloc.h>
#define MAXV 100
#define INF 32767
typedef char InfoType;

//以下定义邻接矩阵类型
typedef struct {		//顶点类型
	int no;			//顶点编号
	InfoType info;	//其他顶点信息
}VertexType;
typedef struct {		//完整的图邻接矩阵类型
	int edges[MAXV][MAXV];	//邻接矩阵数组
	int n, e;				//顶点数、边数
	VertexType vexs[MAXV];	//存放顶点信息
}MatGraph;

//以下定义邻接表类型
typedef struct ANode {		//边结点类型
	int adjvex;				//该边的邻接点编号
	struct ANode * nextarc;	//指向下一条边的指针
	int weight;				//该边的相关信息，如权值（用整型表示）
}ArcNode;
typedef struct Vnode {		//邻接表头结点类型
	InfoType info;			//顶点其他信息
	int count;				//存放顶点入度，仅用于拓扑排序
	ArcNode * firstarc;		//指向第一条边
}VNode;
typedef struct {				//完整的图邻接表类型
	VNode adjlist[MAXV];	//邻接点头结点数组
	int n, e;				//图中顶点数n和边数e
}AdjGraph;

//----邻接矩阵的基本运算-----------------------------------------
void CreateMat(MatGraph &g, int A[MAXV][MAXV], int n, int e) {		//创建图的邻接矩阵
	int i, j;
	g.n = n; g.e = e;
	for (i = 0; i < g.n; i++)
		for (j = 0; j < g.n; j++)
			g.edges[i][j] = A[i][j];
}
void DispMat(MatGraph g) {								//输出邻接矩阵g
	int i, j;
	for (i = 0; i < g.n; i++) {
		for (j = 0; j < g.n; j++)
			if (g.edges[i][j] != INF)
				printf(" %4d", g.edges[i][j]);
			else
				printf(" %4s", "∞");
		printf("\n");
	}
}

//----邻接表的基本运算-----------------------------------------
void CreateAdj(AdjGraph *&G, int A[MAXV][MAXV], int n, int e) {		//创建图的邻接表
	int i, j;
	ArcNode *p;
	G = (AdjGraph *)malloc(sizeof(AdjGraph));
	for (i = 0; i < n; i++)											//给邻接表中所有头结点的指针域置初值
		G->adjlist[i].firstarc = NULL;
	for (i = 0; i < n; i++)											//检查邻接矩阵中的所有元素
		for (j = n - 1; j >= 0; j--)
			if (A[i][j] != 0 && A[i][j] != INF) {						//如果存在一条边，则创建一个结点p
				p = (ArcNode *)malloc(sizeof(ArcNode));
				p->adjvex = j;
				p->weight = A[i][j];
				p->nextarc = G->adjlist[i].firstarc;				//采用头插法插入结点p
				G->adjlist[i].firstarc = p;
			}
	G->n = n; G->e = e;
}
void DispAdj(AdjGraph *G) {			//输出邻接表
	ArcNode *p;
	for (int i = 0; i < G->n; i++) {
		p = G->adjlist[i].firstarc;
		printf("%3d:", i);
		while (p != NULL) {
			printf(" %3d[ %d ]→", p->adjvex, p->weight);
			p = p->nextarc;
		}
		printf("∧\n");
	}
}
void DestroyAdj(AdjGraph *&G) {				//销毁图的邻接表
	ArcNode *pre, *p;
	for (int i = 0; i < G->n; i++) {				//扫描所有的单链表
		pre = G->adjlist[i].firstarc;			//p指向第i个单链表的结点
		if (pre != NULL) {
			p = pre->nextarc;
			while (p != NULL) {					//释放第i个单链表的所有边结点	
				free(pre);
				pre = p; p = p->nextarc;
			}
			free(pre);
		}
	}
	free(G);								//释放头结点数组
}
