#pragma once
#include "graph.h"

//--------------求出图G中每个顶点的入度------------------//
void CalcVexInDegree(AdjGraph *G) {			//思想：遍历到该顶点，就把该顶点对应的编号数组加一，之后循环输出即可。
	int InDegree[100] = { 0 }, n, i;		//为何数组中不可以定义一个G->n的数，这不是常量吗?
	ArcNode *p = NULL;
	for (i = 0; i < G->n; i++) {
		n = 0;
		p = G->adjlist[i].firstarc;
		while (p != NULL) {
			InDegree[p->adjvex]++;
			p = p->nextarc;
		}
	}
	printf("a.各顶点入度为：\n");
	for (i = 0; i < G->n; i++) {
		printf("顶点%d:%d\n", i, InDegree[i]);
	}
}

//--------------求出图G中每个顶点的出度------------------//
void CalcVexOutDegree(AdjGraph *G) {
	int i, n;
	ArcNode *p = NULL;
	printf("b.各顶点出度为：\n");
	for (i = 0; i < G->n; i++) {
		n = 0;
		p = G->adjlist[i].firstarc;
		while (p != NULL) {
			n++;
			p = p->nextarc;
		}
		printf("顶点%d:%d\n", i, n);
	}
}

//----------------求出图G中出度最大的一个顶点，输出该顶点编号---------------//
void CalcVexOutMaxDegree(AdjGraph *G) {
	int OutDegree[100] = { 0 }, n, i,Max=0,MaxPoint;		
	ArcNode *p = NULL;
	for (i = 0; i < G->n; i++) {
		n = 0;
		p = G->adjlist[i].firstarc;
		while (p != NULL) {
			OutDegree[i]++;
			p = p->nextarc;
		}
	}
	for (i = 0; i < G->n; i++) {
		if (Max < OutDegree[i]) {
			Max = OutDegree[i];
			MaxPoint = i;
		}
	}
	printf("c.最大出度顶点为：\n");
	printf("顶点%d:%d\n", MaxPoint, Max);
}

//-------------------计算图中出度为0的顶点数目------------------------//
void CalcVexOutZeroDegree(AdjGraph *G) {
	int OutDegree[100] = { 0 }, n, i, ZeroDegreeNum=0;
	ArcNode *p = NULL;
	for (i = 0; i < G->n; i++) {
		n = 0;
		p = G->adjlist[i].firstarc;
		while (p != NULL) {
			OutDegree[i]++;
			p = p->nextarc;
		}
	}
	for (i = 0; i < G->n; i++) {
		if(OutDegree[i]==0){
			ZeroDegreeNum++;
		}
	}
	printf("d.出度为0的顶点数目为：%d\n",ZeroDegreeNum);
}

//-----------------判断图G是否存在边<i,j>------------------------------//
bool IsExistArc(AdjGraph *G, int i, int j) {
	ArcNode *p = NULL;
	p = G->adjlist[i].firstarc;
	while (p != NULL && p->adjvex != j)
		p = p->nextarc;
	if (p == NULL) {
		printf("e.不存在%d到%d的边\n", i, j);
		return false;
	}
	else {
		printf("e.%d到%d的边存在。\n", i, j);
		return true;
	}
}