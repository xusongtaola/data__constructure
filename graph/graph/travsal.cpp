#include "graph.h"
#include <stdlib.h>
int visited[MAXV];
void DFS(AdjGraph *G, int v) {				//递归深度优先遍历算法
	ArcNode *p;
	printf(" %3d", v); visited[v] = 1;		//访问顶点v，并置已访问标记
	p = G->adjlist[v].firstarc;				//p指向顶点v的第一条弧的弧头结点
	while (p != NULL) {
		if (visited[p->adjvex] == 0)		//若p->adjvex顶点未访问，递归访问它
			DFS(G, p->adjvex);				//利用函数递归来不停地退出最终一层，并不断往相邻结点做遍历检查
		p = p->nextarc;						//p指向下一条弧的弧头结点（p指向本结点的下一结点）
	}
}
void DFS1(AdjGraph *G, int v) {					//非递归深度优先遍历算法
	ArcNode *p;
	int St[MAXV];
	int top = -1, w, x, i;
	for (i = 0; i < G->n; i++) visited[i] = 0;		//顶点访问标志均置位0
	printf(" %3d", v);								//访问顶点v
	visited[v] = 1;									//置顶点v已访问
	top++; St[top] = v;								//将顶点v进栈，通过栈来实现递归退栈的本质思想
	while (top > -1) {								//栈不空循环
		x = St[top];								//取栈顶顶点x作为当前顶点
		p = G->adjlist[x].firstarc;					//找顶点x的第一个相邻点
		while (p != NULL) {
			w = p->adjvex;
			if (visited[w] == 0) {					//检查其是否被访问
				printf(" %3d", w);
				visited[w] = 1;						//将其置位已访问
				top++;								//将其进栈（栈为先进后出，即进入下一层深度递归）
				St[top] = w;
				break;								//退出循环，即再处理栈顶的顶点（相当于此时结束前一层次递归，进入深一层次递归）
			}
			p = p->nextarc;							//找顶点x的下一个相邻点
		}
		if (p == NULL) top--;						//若顶点x再没有相邻点，将其退栈（递归层次递减）
	}
	printf("\n");
}
void BFS(AdjGraph *G, int v) {						//广度优先遍历算法
	ArcNode *p;
	int queue[MAXV], front = 0, rear = 0;			//定义环形队列并初始化
	int visited[MAXV];								//定义存放顶点的访问标志的数组
	int w, i;
	for (i = 0; i < G->n; i++) visited[i] = 0;		//输出被访问顶点的标号
	printf(" %3d",v);									//置已访问标记
	visited[v] = 1;
	rear = (rear + 1) % MAXV;						//尾指针进1，表示有数字要进队
	queue[rear] = v;								//v进队
	while (front != rear) {							//队列不空时循环
		front = (front + 1) % MAXV;
		w = queue[front];							//出队并赋给w
		p = G->adjlist[w].firstarc;					//找顶点w的第一个相邻点
		while (p != NULL) {
			if (visited[p->adjvex] == 0) {			//相邻点未被访问
				printf(" %3d", p->adjvex);
				visited[p->adjvex] = 1;				//置已访问
				rear = (rear + 1) % MAXV;			//顶点进队
				queue[rear] = p->adjvex;
			}
			p=p->nextarc;								//找下一个相邻点
		}
	}
	printf("\n");
}

int main() {
	AdjGraph *G;
	int A[MAXV][MAXV] = {
		{0,5,INF,7,INF,INF},{INF,0,4,INF,INF,INF},
		{8,INF,0,INF,INF,9},{INF,INF,5,0,INF,6},
		{INF,INF,INF,5,0,INF},{3,INF,INF,INF,1,0}
	};
	int n = 6, e = 10;
	CreateAdj(G, A, n, e);
	printf("图G的邻接表：\n"); DispAdj(G);
	printf("从顶点0开始的DFS（递归算法）:\n");
	DFS(G, 0); printf("\n");
	printf("从顶点0开始的DFS（非递归算法）:\n");
	DFS1(G, 0);
	printf("从顶点0开始的BFS（递归算法）:\n");
	BFS(G, 0);
	DestroyAdj(G);
	system("pause");
	return 1;
}