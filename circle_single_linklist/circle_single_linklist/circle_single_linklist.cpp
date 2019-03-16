#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
typedef int ElemType;
typedef struct LNode {
	ElemType data;
	struct LNode *next;
}LinkNode;
void CreateListF(LinkNode *&L, ElemType a[], int n) {				//头插法创立循环单链表
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
void CreateListR(LinkNode *&L, ElemType a[], int n) {					//	尾插法创立循环单链表
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
void InitList(LinkNode *&L) {		//初始化线性表
	L = (LinkNode *)malloc(sizeof(LinkNode));
	L->next = L;
}
void DestroyList(LinkNode *&L) {			//销毁线性表
	LinkNode *pre = L, *p = pre->next;
	while (p != NULL) {						//这里可以找到L（头结点）吗?不是已经销毁了吗？
		free(pre);
		pre = NULL; 
		pre = p;
		p = pre->next;
	}
	free(pre);
}
bool ListEmpty(LinkNode *L) {				//判断线性表是否为空表（直接循环回到自身）
	return(L->next == L);
}
int ListLength(LinkNode *L) {				//求线性表的长度
	LinkNode *p = L; int i = 0;
	while (p->next != L) {
		i++;
		p = p->next;
	}
	return(i);
}
void DispList(LinkNode *L) {						//输出线性表（所有的终止判断都与L（开头）有关）
	LinkNode *p = L->next;
	while (p != L) {
		printf(" %c ", p->data);
		p = p->next;
	}
	printf("\n");
}
bool GetElem(LinkNode *L, int i, ElemType &e) {					//求线性表中第i个元素值
	int j = 1;						//必须从1开始，因为要判断 “p ！= L”，不是NULL！
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
int LocateElem(LinkNode *L, ElemType e) {					//查找第一个值域为e的元素序号
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
bool ListInsert(LinkNode *&L, int i, ElemType e) {				//插入第i个元素（不是很明白）
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
bool ListDelete(LinkNode *&L, int i, ElemType &e) {					//删除第i个元素(不太懂)
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
	printf("循环单链表的基本运算如下：\n");
	printf("  (1)初始化循环单链表h\n");
	InitList(h);
	printf("  (2)依次采用尾插法插入a,b,c,d,e元素\n");
	ListInsert(h, 1, 'a');
	ListInsert(h, 2, 'b');
	ListInsert(h, 3, 'c');
	ListInsert(h, 4, 'd');
	ListInsert(h, 5, 'e');
	printf("  (3)输出循环单链表h："); DispList(h);
	printf("  (4)循环单链表h长度：%d\n", ListLength(h));
	printf("  (5)循环单链表h为%s\n", (ListEmpty(h) ? "空" : "非空"));
	GetElem(h, 3, e);
	printf("  (6)循环单链表h的第三个元素：%c\n", e);
	printf("  (7)元素a的位置：%d\n", LocateElem(h, 'a'));
	printf("  (8)在第4个元素位置上插入f元素：\n");
	ListInsert(h, 4, 'f');
	printf("  (9)输出循环单链表h："); DispList(h);
	printf("  (10)删除h的第3个元素\n");
	ListDelete(h, 3, e);
	printf("  (11)输出循环单链表h："); DispList(h);
	printf("  (12)释放循环单链表h\n");
	DestroyList(h);
	system("pause");
	return 1;
}

