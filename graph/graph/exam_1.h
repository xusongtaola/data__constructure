#pragma once
#include "graph.h"

//--------------���ͼG��ÿ����������------------------//
void CalcVexInDegree(AdjGraph *G) {			//˼�룺�������ö��㣬�ͰѸö����Ӧ�ı�������һ��֮��ѭ��������ɡ�
	int InDegree[100] = { 0 }, n, i;		//Ϊ�������в����Զ���һ��G->n�������ⲻ�ǳ�����?
	ArcNode *p = NULL;
	for (i = 0; i < G->n; i++) {
		n = 0;
		p = G->adjlist[i].firstarc;
		while (p != NULL) {
			InDegree[p->adjvex]++;
			p = p->nextarc;
		}
	}
	printf("a.���������Ϊ��\n");
	for (i = 0; i < G->n; i++) {
		printf("����%d:%d\n", i, InDegree[i]);
	}
}

//--------------���ͼG��ÿ������ĳ���------------------//
void CalcVexOutDegree(AdjGraph *G) {
	int i, n;
	ArcNode *p = NULL;
	printf("b.���������Ϊ��\n");
	for (i = 0; i < G->n; i++) {
		n = 0;
		p = G->adjlist[i].firstarc;
		while (p != NULL) {
			n++;
			p = p->nextarc;
		}
		printf("����%d:%d\n", i, n);
	}
}

//----------------���ͼG�г�������һ�����㣬����ö�����---------------//
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
	printf("c.�����ȶ���Ϊ��\n");
	printf("����%d:%d\n", MaxPoint, Max);
}

//-------------------����ͼ�г���Ϊ0�Ķ�����Ŀ------------------------//
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
	printf("d.����Ϊ0�Ķ�����ĿΪ��%d\n",ZeroDegreeNum);
}

//-----------------�ж�ͼG�Ƿ���ڱ�<i,j>------------------------------//
bool IsExistArc(AdjGraph *G, int i, int j) {
	ArcNode *p = NULL;
	p = G->adjlist[i].firstarc;
	while (p != NULL && p->adjvex != j)
		p = p->nextarc;
	if (p == NULL) {
		printf("e.������%d��%d�ı�\n", i, j);
		return false;
	}
	else {
		printf("e.%d��%d�ıߴ��ڡ�\n", i, j);
		return true;
	}
}