/*����������������������������ͨͼ����������������͹������������������������������������*/
#include "graph.h"
#include <stdlib.h>
#define MaxSize 100
int visited[MAXV] = { 0 };
void DFSTree(AdjGraph *G, int v) {				//��ͼG�Ӷ���v�������������������
	ArcNode *p;
	visited[v] = 1;
	p = G->adjlist[v].firstarc;
	while (p != NULL) {
		if (visited[p->adjvex] == 0) {
			printf("(%d,%d)", v, p->adjvex);			//���˴���ÿһ��ͷ���·���������֮�⣬����ͬDFS
			DFSTree(G, p->adjvex);
		}
		p = p->nextarc;
	}
}
void BFSTree(AdjGraph *G, int v) {
	int w, i;
	int qu[MAXV];
	int front = 0, rear = 0;
	ArcNode *p;
	int visited[MAXV];
	for (i = 0; i < G->n; i++) visited[i] = 0;
	visited[v] = 1;
	rear++;
	qu[rear] = v;
	while (front != rear) {
		front = (front + 1) % MAXV;
		w = qu[front];
		p = G->adjlist[w].firstarc;
		while (p != NULL) {
			if (visited[p->adjvex] == 0) {
				printf("(%d,%d)", w, p->adjvex);			//�˴���������ͬ
				visited[p->adjvex] = 1;
				rear = (rear + 1) % MAXV;
				qu[rear] = p->adjvex;
			}
			p = p->nextarc;
		}
	}
	printf("\n");
}
int main() {
	AdjGraph *G;
	int A[MAXV][MAXV];
	int n = 11, e = 13;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			A[i][j] = 0;
	A[0][1] = 1; A[0][2] = 1; A[0][3] = 1;
	A[1][0] = 1; A[1][4] = 1; A[1][5] = 1;
	A[2][0] = 1; A[2][3] = 1; A[2][5] = 1; A[2][6] = 1;
	A[3][0] = 1; A[3][2] = 1; A[3][7] = 1;
	A[4][1] = 1; A[5][1] = 1; A[5][2] = 1;
	A[6][2] = 1; A[6][7] = 1; A[6][8] = 1; A[6][9] = 1;
	A[7][3] = 1; A[7][6] = 1; A[7][10] = 1;
	A[8][6] = 1; A[9][6] = 1; A[10][7] = 1;
	CreateAdj(G, A, n, e);
	printf("ͼG���ڽӱ�\n");
	DispAdj(G);
	int v = 3;
	printf("���������������\n"); DFSTree(G, v); printf("\n");
	printf("���������������\n"); BFSTree(G, v);
	DestroyAdj(G);
	system("pause");
	return 1;
}