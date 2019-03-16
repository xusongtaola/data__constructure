#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
typedef int ElemType;
typedef struct DNode {
	ElemType data;
	struct DNode *prior;
	struct DNode *next;
}DLinkNode;
void CreateListF(DLinkNode *&L, ElemType a[], int n) {					//ͷ�巨����˫������㽨����ͷ���֮��ԭ��ʼ���֮ǰ��
	DLinkNode *s;
	L = (DLinkNode *)malloc(sizeof(DLinkNode));
	L->prior = L->next = NULL;
	for (int i = 0; i < n; i++) {
		s = (DLinkNode *)malloc(sizeof(DLinkNode));
		s->data = a[i];
		s->next = L->next;
		if (L->next != NULL) L->next->prior = s;
		L->next = s; s->prior = L;
	}
}
void CreateListR(DLinkNode *&L, ElemType a[], int n) {					//β�巨����˫����rʼ��ָ���ն˽�㣬��ʼָ��ͷ��㣩
	DLinkNode *s, *r;
	L = (DLinkNode *)malloc(sizeof(DLinkNode));
	L->prior = L->next = NULL;
	r = L;
	for (int i = 0; i < n; i++) {
		s = (DLinkNode *)malloc(sizeof(DLinkNode));
		s->data = a[i];
		r->next = s; s->prior = r;
		r = s;
	}
	r->next = NULL;
}
void InitList(DLinkNode *&L) {			//��ʼ�����Ա�
	L = (DLinkNode *)malloc(sizeof(DLinkNode));			//����ͷ���
	L->prior = L->next = NULL;
}
void DestroyList(DLinkNode *&L) {				//�������Ա�
	DLinkNode *pre = L, *p = pre->next;
	while (p != NULL) {						//pre��pͬ������һ�����
		free(pre);
		pre = p;
		p = pre->next;
	}
	free(p);
}
bool ListEmpty(DLinkNode *L) {			//�ж����Ա��Ƿ�Ϊ��
	return(L->next == NULL);
}
int ListLength(DLinkNode *L) {			//�����Ա���
	DLinkNode *p = L;
	int i = 0;
	while (p->next != NULL){
		i++;
		p = p->next;
	}
	return(i);
}
void DispList(DLinkNode *L) {				//������Ա�
	DLinkNode *p = L->next;
	while (p != NULL) {
		printf(" %c ", p->data);
		p = p->next;
	}
	printf("\n");
}
bool GetElem(DLinkNode *L, int i, ElemType &e) {			//�����Ա��е�i��Ԫ��ֵ
	int j = 0;
	DLinkNode *p = L;
	if (i <= 0) return false;
	while (j<i && p != NULL){
		j++;

		p = p->next;
	}
	if (p == NULL)
		return false;
	else {
		e = p->data;
		return true;
	}
}
int LocateElem(DLinkNode *L, ElemType e) {			//���ҵ�һ��ֵ��Ϊe��Ԫ�����
	int i = 1;
	DLinkNode *p = L->next;
	while (p != NULL && p->data != e) {
		i++;
		p = p->next;
	}
	if (p == NULL)
		return(0);
	else
		return(i);
}
bool ListInsert(DLinkNode *&L, int i, ElemType e) {				//�����i��Ԫ��
	int j = 0;							//pָ��ͷ���
	DLinkNode *p = L, *s;
	if (i <= 0) return false;
	while (j < i - 1 && p != NULL) {								//������Ҫ��i-1�����
		j++;
		p = p->next;
	}
	if (p == NULL)
		return false;
	else {												//�ҵ���i-1�����
		s = (DLinkNode *)malloc(sizeof(DLinkNode));
		s->data = e;
		s->next = p->next;
		if (p->next != NULL)
			p->next->prior = s;
		s->prior = p;
		p->next = s;
		return true;
	}
}
bool ListDelete(DLinkNode *&L, int i, ElemType &e) {			//ɾ����i��Ԫ��(��Ȼ��Ҫ�ҵ���i-1��Ԫ��)
	int j = 0;
	DLinkNode *p = L, *q;
	if (i <= 0)return false;
	while (j < i - 1 && p != NULL) {
		j++;
		p = p->next;
	}
	if (p == NULL)
		return false;
	else {
		q = p->next;
		if (q == NULL)
			return false;
		e = q->data;
		p->next = q->next;
		if (p->next != NULL)
			p->next->prior = p;
		free(q);
		return true;
	}
}
int main() {
	DLinkNode *h;
	ElemType e;
	printf("˫����Ļ����������£�\n");
	printf("  (1)��ʼ��˫����h\n");
	InitList(h);
	printf("  (2)���β���β�巨����a,b,c,d,eԪ��\n");
	ListInsert(h, 1, 'a');
	ListInsert(h, 2, 'b');
	ListInsert(h, 3, 'c');
	ListInsert(h, 4, 'd');
	ListInsert(h, 5, 'e');
	printf("  (3)���˫����h��"); DispList(h);
	printf("  (4)˫����h���ȣ�%d\n", ListLength(h));
	printf("  (5)˫����hΪ%s\n", (ListEmpty(h) ? "��" : "�ǿ�"));
	GetElem(h, 3, e);
	printf("  (6)˫����h�ĵ�����Ԫ�أ�%c\n", e);
	printf("  (7)Ԫ��a��λ�ã�%d\n", LocateElem(h, 'a'));
	printf("  (8)�ڵ�4��Ԫ��λ���ϲ���fԪ�أ�\n");
	ListInsert(h, 4, 'f');
	printf("  (9)���˫����h��"); DispList(h);
	printf("  (10)ɾ��h�ĵ�3��Ԫ��\n");
	ListDelete(h, 3, e);
	printf("  (11)���˫����h��"); DispList(h);
	printf("  (12)�ͷ�˫����h\n");
	DestroyList(h);
	system("pause");
	return 1;
}
