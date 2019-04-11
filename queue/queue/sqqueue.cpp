#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define MaxSize 100
typedef char ElemType;
typedef struct {
	ElemType data[MaxSize];
	int front, rear;
}SqQueue;
void InitQueue(SqQueue *&q) {				//初始化队列q
	q = (SqQueue *)malloc(sizeof(SqQueue));
	q->front = q->rear = 0;					//队列为空条件初始化
}
void DestroyQueue(SqQueue *&q) {				//销毁队列
	free(q);
}
bool QueueEmpty(SqQueue *q) {				//判断队列是否为空
	return(q->front == q->rear);
}
bool enQueue(SqQueue *&q, ElemType e) {			//进队
	if ((q->rear + 1) % MaxSize == q->front)
		return false;							//队满，上溢出
	q->rear = (q->rear + 1) % MaxSize;			//尾指针取整以进一
	q->data[q->rear] = e;
	return true;
}
bool deQueue(SqQueue *&q, ElemType &e) {				//	出队
	if (q->front == q->rear)
		return false;									//对空，下溢出，与判断条件队满不同
	q->front = (q->front + 1) % MaxSize;
	e = q->data[q->front];
	return true;
}
int main(){
	ElemType e;
	SqQueue *q;
	printf("环形队列基本运算如下：\n");
	printf("\t(1)初始化队列q\n");
	InitQueue(q);
	printf("\t(2)依次进队列元素a,b,c\n");
	if (!enQueue(q, 'a'))printf("\t提示：队满，不能进队\n");
	if (!enQueue(q, 'b'))printf("\t提示：队满，不能进队\n");
	if (!enQueue(q, 'c'))printf("\t提示：队满，不能进队\n");
	printf("\t(3)队列为%s\n", (QueueEmpty(q) ? "空" : "非空"));
	if (deQueue(q, e) == 0)
		printf("队空，不能出队\n");
	else
		printf("\t(4)出队一个元素%c\n", e);
	printf("\t(5)依次进队列元素d,e,f\n");
	if (!enQueue(q, 'd'))printf("\t提示：队满，不能进队\n");
	if (!enQueue(q, 'e'))printf("\t提示：队满，不能进队\n");
	if (!enQueue(q, 'f'))printf("\t提示：队满，不能进队\n");
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