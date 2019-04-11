#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
typedef char ElemType;
typedef struct DataNode {
	ElemType data;
	struct DataNode *next;
}DataNode;							//�����������ݽ������
typedef struct {
	DataNode *front;
	DataNode *rear;
}LinkQuNode;						//������������
void InitQueue(LinkQuNode *&q) {				//��ʼ������q
	q = (LinkQuNode*)malloc(sizeof(LinkQuNode));
	q->front = q->rear = NULL;
}
void DestroyQueue(LinkQuNode *&q) {				//��������
	DataNode *p = q->front, *r;
	if (p != NULL) {
		r = p->next;
		while (r != NULL) {				//�ͷ����ݽ��
			free(p);
			p = r; r = p->next;
		}
	}
	free(q);					//�ͷ����ӽ��q
}
bool QueueEmpty(LinkQuNode *q) {				//�ж϶���q�Ƿ�Ϊ��
	return(q->rear == NULL);
}
void enQueue(LinkQuNode *&q, ElemType e) {			//����
	DataNode *p;
	p = (DataNode *)malloc(sizeof(DataNode));				//�������ݽ��
	p->data = e;
	p->next = NULL;
	if (q->rear == NULL)					//���Ϊ�գ���ͷβֱ������
		q->front = q->rear = p;
	else {									//����β�巨����β��
		q->rear->next = p;
		q->rear = p;
	}
}
bool deQueue(LinkQuNode *&q, ElemType &e) {				//����
	DataNode *t;
	if (q->rear == NULL)
		return false;
	t = q->front;
	if (q->front == q->rear)				//ֻ��һ�����ݽ��
		q->front = q->rear = NULL;
	else									//�������ж�����
		q->front = q->front->next;
	e = t->data;
	free(t);
	return true;
}
int main() {
	ElemType e;
	LinkQuNode *q;
	printf("���ζ��л����������£�\n");
	printf("\t(1)��ʼ������q\n");
	InitQueue(q);
	printf("\t(2)���ν�����Ԫ��a,b,c\n");
	enQueue(q, 'a');
	enQueue(q, 'b');
	enQueue(q, 'c');
	printf("\t(3)����Ϊ%s\n", (QueueEmpty(q) ? "��" : "�ǿ�"));
	if (deQueue(q, e) == 0)
		printf("�ӿգ����ܳ���\n");
	else
		printf("\t(4)����һ��Ԫ��%c\n", e);
	printf("\t(5)���ν�����Ԫ��d,e,f\n");
	enQueue(q, 'd');
	enQueue(q, 'e');
	enQueue(q, 'f');
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