#include "graph.h"
#include<stdlib.h>
int visited[MAXV];
void DFSALL(AdjGraph *G, int v, int path[], int d) {
	ArcNode *p;
	visited[v] = 1;						//���ѷ��ʱ��
	path[d] = v;
	d++;
	if (d == G->n) {					//����ѷ������ж��㣬�������������
		for (int k = 0; k < d; k++)
			printf("%2d", path[k]);
		printf("\n");
	}
	p = G->adjlist[v].firstarc;			//pָ�򶥵�v�ĵ�һ�����ڵ�
	while (p != NULL) {
		if (visited[p->adjvex] == 0)
			DFSALL(G, p->adjvex, path, d);
		p = p->nextarc;
	}
	visited[v] = 0;					//ǰ�����еĶ�������DFS�������ƣ�����������ϴ���Ŀ�Ļ����ڵݹ����ϵĹ����У�ÿһ��ͷ�����ڽӱ���Ŀ���Ĺ����У�ԭ������ǵ���������δ��ǣ�����Է�������������С�
}

int main() {
	AdjGraph *G;
	int A[MAXV][MAXV] = {
		{0,1,0,1,1},{1,0,1,1,0},
		{0,1,0,1,1},{1,1,1,0,1},{1,0,1,1,0}
	};
	int n = 5, e = 8;
	CreateAdj(G, A, n, e);
	printf("ͼG���ڽӱ�\n"); DispAdj(G);
	int path[MAXV], v = 1;
	printf("�Ӷ���%d��������������������У�\n", v);
	DFSALL(G, v, path, 0);
	printf("\n");
	DestroyAdj(G);
	system("pause");
	return 1;
}