#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
typedef int ElemType;
typedef struct DNode {
	ElemType data;
	struct DNode *prior;
	struct DNode *next;
}DLinkNode;
void CreateListF(DLinkNode *&L, ElemType a[], int n) {			//头插法建立循环双链表
	DLinkNode *s;
	L = (DLinkNode *)malloc(sizeof(DLinkNode));
	L->next = NULL;												//防止其成为野指针，指向垃圾内存！！！
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
void CreateListR(DLinkNode *&L, ElemType a[], int n) {				//尾插法建立循环双链表
	DLinkNode *s, *r;
	L = (DLinkNode *)malloc(sizeof(DLinkNode));
	L->next = NULL;
	r = L;									//实际就是r指向L指针变量所在的内存空间！！！（多看，多查，比如int a=5；a是野指针吗？）
	for (int i = 0; i < n; i++) {
		s = (DLinkNode *)malloc(sizeof(DLinkNode));
		s->data = a[i];
		r->next = s; s->prior = r;
		r = s;
	}
	r->next = L;
	L->prior = r;
}
void InitList(DLinkNode *&L) {		//初始化线性表
	L = (DLinkNode *)malloc(sizeof(DLinkNode));
	L->prior = L->next = L;
}
void DestroyList(DLinkNode *&L) {					//销毁线性表
	DLinkNode *pre = L, *p = pre->next;
	while (p != L) {					//L为野指针！！！指针变量只有在函数结束的时候，其内存空间才会被回收，指针被销毁！
		free(pre);
		pre = p;
		p = pre->next;
	}
	free(pre);
}
bool ListEmpty(DLinkNode *L) {				//判断线性表是否为空表
	return(L->next == L);
}
int ListLength(DLinkNode *L) {				//求线性表的长度
	DLinkNode *p = L;
	int i = 0;
	while (p->next != L) {
		i++;
		p = p->next;
	}
	return(i);
}
void DispList(DLinkNode *L) {						//输出线性表
	DLinkNode *p = L->next;
	while (p != L) {
		printf(" %c ", p->data);
		p = p->next;
	}
	printf("\n");
}
bool GetElem(DLinkNode *L, int i, ElemType &e) {					//求线性表中第i个元素值
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
int LocateElem(DLinkNode *L, ElemType e) {						//查找第一个值域为e的元素序号
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
bool ListInsert(DLinkNode *&L, int i, ElemType e) {			//插入第i个元素
	int j = 1;
	DLinkNode *p = L, *s;
	if (i <= 0) return false;					//把其分为空、i=1、i-1三类时，是因为其前置结点分为前两个，又因为其后置结点分为后两个。
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
bool ListDelete(DLinkNode *&L, int i, ElemType &e) {			//删除第i个元素
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
	printf("循环双链表的基本运算如下：\n");
	printf("  (1)初始化循环双链表h\n");
	InitList(h);
	printf("  (2)依次采用尾插法插入a,b,c,d,e元素\n");
	ListInsert(h, 1, 'a');
	ListInsert(h, 2, 'b');
	ListInsert(h, 3, 'c');
	ListInsert(h, 4, 'd');
	ListInsert(h, 5, 'e');
	printf("  (3)输出循环双链表h："); DispList(h);
	printf("  (4)循环双链表h长度：%d\n", ListLength(h));
	printf("  (5)循环双链表h为%s\n", (ListEmpty(h) ? "空" : "非空"));
	GetElem(h, 3, e);
	printf("  (6)循环双链表h的第三个元素：%c\n", e);
	printf("  (7)元素a的位置：%d\n", LocateElem(h, 'a'));
	printf("  (8)在第4个元素位置上插入f元素：\n");
	ListInsert(h, 4, 'f');
	printf("  (9)输出循环双链表h："); DispList(h);
	printf("  (10)删除h的第3个元素\n");
	ListDelete(h, 3, e);
	printf("  (11)输出循环双链表h："); DispList(h);
	printf("  (12)释放循环双链表h\n");
	DestroyList(h);
	system("pause");
	return 1;
}
