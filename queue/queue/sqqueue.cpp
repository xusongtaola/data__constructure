#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define MaxSize 100
typedef char ElemType;
typedef struct {
	ElemType data[MaxSize];
	int front, rear;
}SqQueue;
void InitQueue(SqQueue *&q) {				//��ʼ������q
	q = (SqQueue *)malloc(sizeof(SqQueue));
	q->front = q->rear = 0;					//����Ϊ��������ʼ��
}
void DestroyQueue(SqQueue *&q) {				//���ٶ���
	free(q);
}
bool QueueEmpty(SqQueue *q) {				//�ж϶����Ƿ�Ϊ��
	return(q->front == q->rear);
}
bool enQueue(SqQueue *&q, ElemType e) {			//����
	if ((q->rear + 1) % MaxSize == q->front)
		return false;							//�����������
	q->rear = (q->rear + 1) % MaxSize;			//βָ��ȡ���Խ�һ
	q->data[q->rear] = e;
	return true;
}
bool deQueue(SqQueue *&q, ElemType &e) {				//	����
	if (q->front == q->rear)
		return false;									//�Կգ�����������ж�����������ͬ
	q->front = (q->front + 1) % MaxSize;
	e = q->data[q->front];
	return true;
}
int main(){
	ElemType e;
	SqQueue *q;
	printf("���ζ��л����������£�\n");
	printf("\t(1)��ʼ������q\n");
	InitQueue(q);
	printf("\t(2)���ν�����Ԫ��a,b,c\n");
	if (!enQueue(q, 'a'))printf("\t��ʾ�����������ܽ���\n");
	if (!enQueue(q, 'b'))printf("\t��ʾ�����������ܽ���\n");
	if (!enQueue(q, 'c'))printf("\t��ʾ�����������ܽ���\n");
	printf("\t(3)����Ϊ%s\n", (QueueEmpty(q) ? "��" : "�ǿ�"));
	if (deQueue(q, e) == 0)
		printf("�ӿգ����ܳ���\n");
	else
		printf("\t(4)����һ��Ԫ��%c\n", e);
	printf("\t(5)���ν�����Ԫ��d,e,f\n");
	if (!enQueue(q, 'd'))printf("\t��ʾ�����������ܽ���\n");
	if (!enQueue(q, 'e'))printf("\t��ʾ�����������ܽ���\n");
	if (!enQueue(q, 'f'))printf("\t��ʾ�����������ܽ���\n");
	printf("\t(6)������˳��");
	while (!QueueEmpty(q)) {
		deQueue(q, e);
		printf(" %c ", e);
	}
	printf("\n");
	printf("\t(7)�ͷŶ���\n");
	DestroyQueue(q);
	system("pause");
	return(1);
}