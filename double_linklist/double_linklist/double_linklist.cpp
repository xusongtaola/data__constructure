#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
typedef int ElemType;
typedef struct DNode {
	ElemType data;
	struct DNode *prior;
	struct DNode *next;
}DLinkNode;
void CreateListF(DLinkNode *&L, ElemType a[], int n) {					//头插法建立双链表（结点建立在头结点之后，原开始结点之前）
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
void CreateListR(DLinkNode *&L, ElemType a[], int n) {					//尾插法建立双链表（r始终指向终端结点，开始指向头结点）
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
void InitList(DLinkNode *&L) {			//初始化线性表
	L = (DLinkNode *)malloc(sizeof(DLinkNode));			//创建头结点
	L->prior = L->next = NULL;
}
void DestroyList(DLinkNode *&L) {				//销毁线性表
	DLinkNode *pre = L, *p = pre->next;
	while (p != NULL) {						//pre、p同步后移一个结点
		free(pre);
		pre = p;
		p = pre->next;
	}
	free(p);
}
bool ListEmpty(DLinkNode *L) {			//判断线性表是否为空
	return(L->next == NULL);
}
int ListLength(DLinkNode *L) {			//求线性表长度
	DLinkNode *p = L;
	int i = 0;
	while (p->next != NULL){
		i++;
		p = p->next;
	}
	return(i);
}
void DispList(DLinkNode *L) {				//输出线性表
	DLinkNode *p = L->next;
	while (p != NULL) {
		printf(" %c ", p->data);
		p = p->next;
	}
	printf("\n");
}
bool GetElem(DLinkNode *L, int i, ElemType &e) {			//求线性表中第i个元素值
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
int LocateElem(DLinkNode *L, ElemType e) {			//查找第一个值域为e的元素序号
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
bool ListInsert(DLinkNode *&L, int i, ElemType e) {				//插入第i个元素
	int j = 0;							//p指向头结点
	DLinkNode *p = L, *s;
	if (i <= 0) return false;
	while (j < i - 1 && p != NULL) {								//插入需要第i-1个结点
		j++;
		p = p->next;
	}
	if (p == NULL)
		return false;
	else {												//找到第i-1个结点
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
bool ListDelete(DLinkNode *&L, int i, ElemType &e) {			//删除第i个元素(仍然需要找到第i-1个元素)
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
	printf("双链表的基本运算如下：\n");
	printf("  (1)初始化双链表h\n");
	InitList(h);
	printf("  (2)依次采用尾插法插入a,b,c,d,e元素\n");
	ListInsert(h, 1, 'a');
	ListInsert(h, 2, 'b');
	ListInsert(h, 3, 'c');
	ListInsert(h, 4, 'd');
	ListInsert(h, 5, 'e');
	printf("  (3)输出双链表h："); DispList(h);
	printf("  (4)双链表h长度：%d\n", ListLength(h));
	printf("  (5)双链表h为%s\n", (ListEmpty(h) ? "空" : "非空"));
	GetElem(h, 3, e);
	printf("  (6)双链表h的第三个元素：%c\n", e);
	printf("  (7)元素a的位置：%d\n", LocateElem(h, 'a'));
	printf("  (8)在第4个元素位置上插入f元素：\n");
	ListInsert(h, 4, 'f');
	printf("  (9)输出双链表h："); DispList(h);
	printf("  (10)删除h的第3个元素\n");
	ListDelete(h, 3, e);
	printf("  (11)输出双链表h："); DispList(h);
	printf("  (12)释放双链表h\n");
	DestroyList(h);
	system("pause");
	return 1;
}
