#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
typedef int ElemType;
typedef struct DNode {
	ElemType data;
	struct DNode *prior;
	struct DNode *next;
}DLinkNode;
void CreateListF(DLinkNode *&L, ElemType a[], int n) {			//ͷ�巨����ѭ��˫����
	DLinkNode *s;
	L = (DLinkNode *)malloc(sizeof(DLinkNode));
	L->next = NULL;												//��ֹ���ΪҰָ�룬ָ�������ڴ棡����
	for (int i = 0; i < n; i++) {
		s = (DLinkNode *)malloc(sizeof(DLinkNode));
		s->data = a[i];
		s->next = L->next;
		if (L->next != NULL)L->next->prior = s;
		L->next = s; s->prior = L;
	}
	s = L->next;
	while (s->next != NULL)
		s = s->next;
	s->next = L;
	L->prior = s;
}
void CreateListR(DLinkNode *&L, ElemType a[], int n) {				//β�巨����ѭ��˫����
	DLinkNode *s, *r;
	L = (DLinkNode *)malloc(sizeof(DLinkNode));
	L->next = NULL;
	r = L;									//ʵ�ʾ���rָ��Lָ��������ڵ��ڴ�ռ䣡�������࿴����飬����int a=5��a��Ұָ���𣿣�
	for (int i = 0; i < n; i++) {
		s = (DLinkNode *)malloc(sizeof(DLinkNode));
		s->data = a[i];
		r->next = s; s->prior = r;
		r = s;
	}
	r->next = L;
	L->prior = r;
}
void InitList(DLinkNode *&L) {		//��ʼ�����Ա�
	L = (DLinkNode *)malloc(sizeof(DLinkNode));
	L->prior = L->next = L;
}
void DestroyList(DLinkNode *&L) {					//�������Ա�
	DLinkNode *pre = L, *p = pre->next;
	while (p != L) {					//LΪҰָ�룡����ָ�����ֻ���ں���������ʱ�����ڴ�ռ�Żᱻ���գ�ָ�뱻���٣�
		free(pre);
		pre = p;
		p = pre->next;
	}
	free(pre);
}
bool ListEmpty(DLinkNode *L) {				//�ж����Ա��Ƿ�Ϊ�ձ�
	return(L->next == L);
}
int ListLength(DLinkNode *L) {				//�����Ա�ĳ���
	DLinkNode *p = L;
	int i = 0;
	while (p->next != L) {
		i++;
		p = p->next;
	}
	return(i);
}
void DispList(DLinkNode *L) {						//������Ա�
	DLinkNode *p = L->next;
	while (p != L) {
		printf(" %c ", p->data);
		p = p->next;
	}
	printf("\n");
}
bool GetElem(DLinkNode *L, int i, ElemType &e) {					//�����Ա��е�i��Ԫ��ֵ
	int j = 1;
	DLinkNode *p = L->next;
	if (i <= 0 || L->next == L)
		return false;
	if (i == 1) {
		e = L->next->data;
		return true;
	}
	else {
		while (j <= i - 1 && p != L) {
			j++;
			p = p->next;
		}
		if (p == L)
			return false;
		else {
			e = p->data;
			return true;
		}
	}
}
int LocateElem(DLinkNode *L, ElemType e) {						//���ҵ�һ��ֵ��Ϊe��Ԫ�����
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
bool ListInsert(DLinkNode *&L, int i, ElemType e) {			//�����i��Ԫ��
	int j = 1;
	DLinkNode *p = L, *s;
	if (i <= 0) return false;					//�����Ϊ�ա�i=1��i-1����ʱ������Ϊ��ǰ�ý���Ϊǰ����������Ϊ����ý���Ϊ��������
	if (p->next == L) {
		s = (DLinkNode *)malloc(sizeof(DLinkNode));
		s->data = e;
		p->next = s; s->next = p;
		p->prior = s; s->prior = p;
		return true;
	}
	else if (i == 1) {
		s = (DLinkNode *)malloc(sizeof(DLinkNode));
		s->data = e;
		s->next = p->next; p->next = s;
		s->next->prior = s; s->prior = p;
		return true;
	}
	else {
		p = L->next;
		while (j <= i - 2 && p != L) {
			j++;
			p = p->next;
		}
		if (p == L)
			return false;
		else {
			s = (DLinkNode *)malloc(sizeof(DLinkNode));
			s->data = e;
			s->next = p->next;
			if (p->next != NULL)p->next->prior = s;
			s->prior = p;
			p->next = s;
			return true;
		}
	}
}
bool ListDelete(DLinkNode *&L, int i, ElemType &e) {			//ɾ����i��Ԫ��
	int j = 1;
	DLinkNode *p = L, *q;
	if (i < 0 || L->next == L)
		return false;
	if (i == 1) {
		q = L->next;
		e = q->data;
		L->next = q->next;
		q->next->prior = L;
		free(q);
		return true;
	}
	else {
		p = L->next;
		while (j <= i - 2 && p != NULL) {
			j++;
			p = p->next;
		}
		if (p == NULL)
			return false;
		else {
			q = p->next;
			if (q == NULL) return 0;
			e = q->data;
			p->next = q->next;
			if (p->next != NULL) p->next->prior = p;
			free(q);
			return true;
		}
	}
}
int main() {
	DLinkNode *h;
	ElemType e;
	printf("ѭ��˫����Ļ����������£�\n");
	printf("  (1)��ʼ��ѭ��˫����h\n");
	InitList(h);
	printf("  (2)���β���β�巨����a,b,c,d,eԪ��\n");
	ListInsert(h, 1, 'a');
	ListInsert(h, 2, 'b');
	ListInsert(h, 3, 'c');
	ListInsert(h, 4, 'd');
	ListInsert(h, 5, 'e');
	printf("  (3)���ѭ��˫����h��"); DispList(h);
	printf("  (4)ѭ��˫����h���ȣ�%d\n", ListLength(h));
	printf("  (5)ѭ��˫����hΪ%s\n", (ListEmpty(h) ? "��" : "�ǿ�"));
	GetElem(h, 3, e);
	printf("  (6)ѭ��˫����h�ĵ�����Ԫ�أ�%c\n", e);
	printf("  (7)Ԫ��a��λ�ã�%d\n", LocateElem(h, 'a'));
	printf("  (8)�ڵ�4��Ԫ��λ���ϲ���fԪ�أ�\n");
	ListInsert(h, 4, 'f');
	printf("  (9)���ѭ��˫����h��"); DispList(h);
	printf("  (10)ɾ��h�ĵ�3��Ԫ��\n");
	ListDelete(h, 3, e);
	printf("  (11)���ѭ��˫����h��"); DispList(h);
	printf("  (12)�ͷ�ѭ��˫����h\n");
	DestroyList(h);
	system("pause");
	return 1;
}
