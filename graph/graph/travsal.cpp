#include "graph.h"
#include <stdlib.h>
int visited[MAXV];
void DFS(AdjGraph *G, int v) {				//�ݹ�������ȱ����㷨
	ArcNode *p;
	printf(" %3d", v); visited[v] = 1;		//���ʶ���v�������ѷ��ʱ��
	p = G->adjlist[v].firstarc;				//pָ�򶥵�v�ĵ�һ�����Ļ�ͷ���
	while (p != NULL) {
		if (visited[p->adjvex] == 0)		//��p->adjvex����δ���ʣ��ݹ������
			DFS(G, p->adjvex);				//���ú����ݹ�����ͣ���˳�����һ�㣬�����������ڽ�����������
		p = p->nextarc;						//pָ����һ�����Ļ�ͷ��㣨pָ�򱾽�����һ��㣩
	}
}
void DFS1(AdjGraph *G, int v) {					//�ǵݹ�������ȱ����㷨
	ArcNode *p;
	int St[MAXV];
	int top = -1, w, x, i;
	for (i = 0; i < G->n; i++) visited[i] = 0;		//������ʱ�־����λ0
	printf(" %3d", v);								//���ʶ���v
	visited[v] = 1;									//�ö���v�ѷ���
	top++; St[top] = v;								//������v��ջ��ͨ��ջ��ʵ�ֵݹ���ջ�ı���˼��
	while (top > -1) {								//ջ����ѭ��
		x = St[top];								//ȡջ������x��Ϊ��ǰ����
		p = G->adjlist[x].firstarc;					//�Ҷ���x�ĵ�һ�����ڵ�
		while (p != NULL) {
			w = p->adjvex;
			if (visited[w] == 0) {					//������Ƿ񱻷���
				printf(" %3d", w);
				visited[w] = 1;						//������λ�ѷ���
				top++;								//�����ջ��ջΪ�Ƚ��������������һ����ȵݹ飩
				St[top] = w;
				break;								//�˳�ѭ�������ٴ���ջ���Ķ��㣨�൱�ڴ�ʱ����ǰһ��εݹ飬������һ��εݹ飩
			}
			p = p->nextarc;							//�Ҷ���x����һ�����ڵ�
		}
		if (p == NULL) top--;						//������x��û�����ڵ㣬������ջ���ݹ��εݼ���
	}
	printf("\n");
}
void BFS(AdjGraph *G, int v) {						//������ȱ����㷨
	ArcNode *p;
	int queue[MAXV], front = 0, rear = 0;			//���廷�ζ��в���ʼ��
	int visited[MAXV];								//�����Ŷ���ķ��ʱ�־������
	int w, i;
	for (i = 0; i < G->n; i++) visited[i] = 0;		//��������ʶ���ı��
	printf(" %3d",v);									//���ѷ��ʱ��
	visited[v] = 1;
	rear = (rear + 1) % MAXV;						//βָ���1����ʾ������Ҫ����
	queue[rear] = v;								//v����
	while (front != rear) {							//���в���ʱѭ��
		front = (front + 1) % MAXV;
		w = queue[front];							//���Ӳ�����w
		p = G->adjlist[w].firstarc;					//�Ҷ���w�ĵ�һ�����ڵ�
		while (p != NULL) {
			if (visited[p->adjvex] == 0) {			//���ڵ�δ������
				printf(" %3d", p->adjvex);
				visited[p->adjvex] = 1;				//���ѷ���
				rear = (rear + 1) % MAXV;			//�������
				queue[rear] = p->adjvex;
			}
			p=p->nextarc;								//����һ�����ڵ�
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
	printf("ͼG���ڽӱ�\n"); DispAdj(G);
	printf("�Ӷ���0��ʼ��DFS���ݹ��㷨��:\n");
	DFS(G, 0); printf("\n");
	printf("�Ӷ���0��ʼ��DFS���ǵݹ��㷨��:\n");
	DFS1(G, 0);
	printf("�Ӷ���0��ʼ��BFS���ݹ��㷨��:\n");
	BFS(G, 0);
	DestroyAdj(G);
	system("pause");
	return 1;
}