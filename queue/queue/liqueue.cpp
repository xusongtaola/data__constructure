#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
typedef char ElemType;
typedef struct DataNode {
	ElemType data;
	struct DataNode *next;
}DataNode;							//声明链队数据结点类型
typedef struct {
	DataNode *front;
	DataNode *rear;
}LinkQuNode;						//声明链队类型
void InitQueue(LinkQuNode *&q) {				//初始化队列q
	q = (LinkQuNode*)malloc(sizeof(LinkQuNode));
	q->front = q->rear = NULL;
}
void DestroyQueue(LinkQuNode *&q) {				//销毁链队
	DataNode *p = q->front, *r;
	if (p != NULL) {
		r = p->next;
		while (r != NULL) {				//释放数据结点
			free(p);
			p = r; r = p->next;
		}
	}
	free(q);					//释放链队结点q
}
bool QueueEmpty(LinkQuNode *q) {				//判断队列q是否为空
	return(q->rear == NULL);
}
void enQueue(LinkQuNode *&q, ElemType e) {			//进队
	DataNode *p;
	p = (DataNode *)malloc(sizeof(DataNode));				//创建数据结点
	p->data = e;
	p->next = NULL;
	if (q->rear == NULL)					//如果为空，则头尾直接连接
		q->front = q->rear = p;
	else {									//否则尾插法插入尾部
		q->rear->next = p;
		q->rear = p;
	}
}
bool deQueue(LinkQuNode *&q, ElemType &e) {				//出队
	DataNode *t;
	if (q->rear == NULL)
		return false;
	t = q->front;
	if (q->front == q->rear)				//只有一个数据结点
		q->front = q->rear = NULL;
	else									//队列中有多个结点
		q->front = q->front->next;
	e = t->data;
	free(t);
	return true;
}
int main() {
	ElemType e;
	LinkQuNode *q;
	printf("环形队列基本运算如下：\n");
	printf("\t(1)初始化队列q\n");
	InitQueue(q);
	printf("\t(2)依次进队列元素a,b,c\n");
	enQueue(q, 'a');
	enQueue(q, 'b');
	enQueue(q, 'c');
	printf("\t(3)队列为%s\n", (QueueEmpty(q) ? "空" : "非空"));
	if (deQueue(q, e) == 0)
		printf("队空，不能出队\n");
	else
		printf("\t(4)出队一个元素%c\n", e);
	printf("\t(5)依次进队列元素d,e,f\n");
	enQueue(q, 'd');
	enQueue(q, 'e');
	enQueue(q, 'f');
	printf("\t(6)出队列顺序");
	while (!QueueEmpty(q)) {
		deQueue(q, e);
		printf(" %c ", e);
	}
	printf("\n");
	printf("\t(7)释放队列\n");
	DestroyQueue(q);
	system("pause");
	return(1);
}