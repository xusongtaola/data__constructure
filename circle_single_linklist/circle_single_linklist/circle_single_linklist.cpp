#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
typedef int ElemType;
typedef struct LNode {
	ElemType data;
	struct LNode *next;
}LinkNode;
void CreateListF(LinkNode *&L, ElemType a[], int n) {				//ͷ�巨����ѭ��������
	LinkNode *s; int i;
	L = (LinkNode *)malloc(sizeof(LinkNode));
	L->next = NULL;
	for (i = 0; i < n; i++) {
		s = (LinkNode *)malloc(sizeof(LinkNode));
		s->next = L->next;
		L->next = s;
	}
	s = L->next;
	while (s->next != NULL)
		s = s->next;
	s->next = L;
}
void CreateListR(LinkNode *&L, ElemType a[], int n) {					//	β�巨����ѭ��������
	LinkNode *s, *r; int i;
	L = (LinkNode *)malloc(sizeof(LinkNode));
	L->next = NULL;
	r = L;
	for (i = 0; i < n; i++) {
		s = (LinkNode *)malloc(sizeof(LinkNode));
		s->data = a[i];
		r->next = s;
		r = s;
	}
}
void InitList(LinkNode *&L) {		//��ʼ�����Ա�
	L = (LinkNode *)malloc(sizeof(LinkNode));
	L->next = L;
}
void DestroyList(LinkNode *&L) {			//�������Ա�
	LinkNode *pre = L, *p = pre->next;
	while (p != NULL) {						//��������ҵ�L��ͷ��㣩��?�����Ѿ���������
		free(pre);
		pre = NULL; 
		pre = p;
		p = pre->next;
	}
	free(pre);
}
bool ListEmpty(LinkNode *L) {				//�ж����Ա��Ƿ�Ϊ�ձ�ֱ��ѭ���ص�����
	return(L->next == L);
}
int ListLength(LinkNode *L) {				//�����Ա�ĳ���
	LinkNode *p = L; int i = 0;
	while (p->next != L) {
		i++;
		p = p->next;
	}
	return(i);
}
void DispList(LinkNode *L) {						//������Ա����е���ֹ�ж϶���L����ͷ���йأ�
	LinkNode *p = L->next;
	while (p != L) {
		printf(" %c ", p->data);
		p = p->next;
	}
	printf("\n");
}
bool GetElem(LinkNode *L, int i, ElemType &e) {					//�����Ա��е�i��Ԫ��ֵ
	int j = 1;						//�����1��ʼ����ΪҪ�ж� ��p ��= L��������NULL��
	LinkNode *p = L->next;
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
int LocateElem(LinkNode *L, ElemType e) {					//���ҵ�һ��ֵ��Ϊe��Ԫ�����
	LinkNode *p = L->next;
	int i = 1;
	while (p != L && p->data != e) {
		p = p->next;
		i++;
	}
	if (p == L)
		return(0);
	else
		return(i);
}
bool ListInsert(LinkNode *&L, int i, ElemType e) {				//�����i��Ԫ�أ����Ǻ����ף�
	int j = 1;
	LinkNode *p = L, *s;
	if (i <= 0)return false;
	if (p->next == L || i == 1) {
		s = (LinkNode *)malloc(sizeof(LinkNode));
		s->data = e;
		s->next = p->next;
		p->next = s;
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
			s = (LinkNode *)malloc(sizeof(LinkNode));
			s->data = e;
			s->next = p->next;
			p->next = s;
			return true;
		}
	}
}
bool ListDelete(LinkNode *&L, int i, ElemType &e) {					//ɾ����i��Ԫ��(��̫��)
	int j = 1;
	LinkNode *p = L, *q;
	if (i <= 0 || L->next == L)
		return false;
	if (i == 1) {
		q = L->next;
		e = q->data;
		L->next = q->next;
		free(q);
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
			q = p->next;
			e = q->data;
			L->next = q->next;
			free(q);
			return true;
		}
	}
}
int main() {
	LinkNode *h;
	ElemType e;
	printf("ѭ��������Ļ����������£�\n");
	printf("  (1)��ʼ��ѭ��������h\n");
	InitList(h);
	printf("  (2)���β���β�巨����a,b,c,d,eԪ��\n");
	ListInsert(h, 1, 'a');
	ListInsert(h, 2, 'b');
	ListInsert(h, 3, 'c');
	ListInsert(h, 4, 'd');
	ListInsert(h, 5, 'e');
	printf("  (3)���ѭ��������h��"); DispList(h);
	printf("  (4)ѭ��������h���ȣ�%d\n", ListLength(h));
	printf("  (5)ѭ��������hΪ%s\n", (ListEmpty(h) ? "��" : "�ǿ�"));
	GetElem(h, 3, e);
	printf("  (6)ѭ��������h�ĵ�����Ԫ�أ�%c\n", e);
	printf("  (7)Ԫ��a��λ�ã�%d\n", LocateElem(h, 'a'));
	printf("  (8)�ڵ�4��Ԫ��λ���ϲ���fԪ�أ�\n");
	ListInsert(h, 4, 'f');
	printf("  (9)���ѭ��������h��"); DispList(h);
	printf("  (10)ɾ��h�ĵ�3��Ԫ��\n");
	ListDelete(h, 3, e);
	printf("  (11)���ѭ��������h��"); DispList(h);
	printf("  (12)�ͷ�ѭ��������h\n");
	DestroyList(h);
	system("pause");
	return 1;
}

