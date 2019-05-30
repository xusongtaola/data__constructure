#include "graph.h"
#include<stdlib.h>
int visited[MAXV];
void DFSALL(AdjGraph *G, int v, int path[], int d) {
	ArcNode *p;
	visited[v] = 1;						//置已访问标记
	path[d] = v;
	d++;
	if (d == G->n) {					//如果已访问所有顶点，则输出访问序列
		for (int k = 0; k < d; k++)
			printf("%2d", path[k]);
		printf("\n");
	}
	p = G->adjlist[v].firstarc;			//p指向顶点v的第一个相邻点
	while (p != NULL) {
		if (visited[p->adjvex] == 0)
			DFSALL(G, p->adjvex, path, d);
		p = p->nextarc;
	}
	visited[v] = 0;					//前面所有的东西都和DFS遍历相似，但是如果加上此条目的话，在递归向上的过程中，每一个头结点的邻接表条目向后的过程中，原来被标记的数字现在未标记，则可以访问所有深度序列。
}

int main() {
	AdjGraph *G;
	int A[MAXV][MAXV] = {
		{0,1,0,1,1},{1,0,1,1,0},
		{0,1,0,1,1},{1,1,1,0,1},{1,0,1,1,0}
	};
	int n = 5, e = 8;
	CreateAdj(G, A, n, e);
	printf("图G的邻接表：\n"); DispAdj(G);
	int path[MAXV], v = 1;
	printf("从顶点%d出发的所有深度优先序列：\n", v);
	DFSALL(G, v, path, 0);
	printf("\n");
	DestroyAdj(G);
	system("pause");
	return 1;
}