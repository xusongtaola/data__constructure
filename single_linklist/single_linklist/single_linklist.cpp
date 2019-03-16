/**********************************************
单链表创建
**********************************************/

#include<stdio.h>
#include<malloc.h>
typedef char ElemType;
typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LinkNode;
void CreateListF(LinkNode *&L, ElemType a[],int n){	//头插法建立单链表
	LinkNode *s;
	L = (LinkNode * )malloc(sizeof(LinkNode));		//L为头指针，如此将分配的数据类型赋予头指针，头结点便有了存在意义。
	L->next = NULL;
	for (int i=0;i<n;i++){							//头插法(创立结点s并使其落于头结点之后，首结点之前)
		s = (LinkNode * )malloc(sizeof(LinkNode));
		s->next = L->next;
		L->next = s;
	}
}
void CreateListR(LinkNode *&L, ElemType a[],int n){	//尾插法建立单链表
	LinkNode *s,*r;
	L = (LinkNode * )malloc(sizeof(LinkNode));		//L为头指针，如此将分配的数据类型赋予头指针，头结点便有了存在意义。
	L->next = NULL;
	r=L;											//r始终指向尾结点
	for (int i=0;i<n;i++){
		s = (LinkNode * )malloc(sizeof(LinkNode));
		s->data = a[i];
		r->next = s;
		r = s;
	}
	r->next = NULL;									//尾结点next指向空
}
void InitList(LinkNode * &L){
	L = (LinkNode * )malloc(sizeof(LinkNode));	//创立头结点
	L->next = NULL;								//将单链表置为空表
}
void DestroyList(LinkNode *&L){						//销毁线性表
	LinkNode *pre = L, *p = pre->next;
	while (p != NULL){
		free(pre);
		pre = p;
		p = pre->next;								//二者同步后移一个结点，直至最终
	}
	free(pre);										//释放尾结点
}
bool ListEmpty(LinkNode *L){				//	判断线性表是否为空
	return(L->next == NULL);
}
int ListLength(LinkNode *L){					//求线性表长度
	int i=0;									//头结点序号为零
	LinkNode *p = L;
	while(p->next != NULL){
		i++;
		p=p->next;
	}
	return(i);
}
void DispList(LinkNode *L){						//输出线性表
	LinkNode *p = L->next;
	while (p != NULL){
		printf(" %c ",p->data);
		p = p->next;
	}
	printf("\n");
}
bool GetElem(LinkNode *L,int i,ElemType &e){					//求线性表中第i个元素值
	int j=0;													//头结点序号为零
	LinkNode *p = L;
	if (i <= 0)return false;
	while (j<i && p!=NULL){
		j++;
		p=p->next;
	}
	if (p == NULL)
		return false;
	else{
		e = p->data;
		return true;
	}
}
int LocateElem(LinkNode *L,ElemType e){								//查找第一个值域为e的元素序号
	int i=1;
	LinkNode *p = L->next;
	while (p != NULL && p->data != e){
		p = p->next;
		i++;
	}
	if (p == NULL)
		return(0);
	else
		return(i);
}
bool ListInsert(LinkNode *&L,int i,ElemType e){						//插入第i个元素（必须找到第i-1个结点，方可插入，构造其与第i、i-1个结点的关系）
	int j=0;
	LinkNode *p = L, *s;
	if(i<=0)return false;
	while (j<i-1 && p != NULL){
		j++;
		p=p->next;
	}
	if(p == NULL)
		return false;
	else{
		s = (LinkNode * )malloc(sizeof(LinkNode));
		s->data = e;
		s ->next = p->next;
		p->next = s;
		return true;
	}
}
bool ListDelete(LinkNode *&L,int i, ElemType &e){						//删除第i个元素（必须找到第i-1个结点）
	int j=0;
	LinkNode *p=L, *q;
	if(i <= 0)return false;
	while (j<i-1 && p != NULL){
		j++;
		p = p->next;
	}
	if(p == NULL)
		return false;
	else{
		q = p->next;
		if(q == NULL)
			return false;
		e = q->data;
		p->next = q->next;
		free(q);
		return true;
	}
}
int main(){
	LinkNode *h;
	ElemType e;
	printf("单链表的基本运算如下：\n");
	printf("  (1)初始化单链表h\n");
	InitList(h);
	printf("  (2)依次采用尾插法插入a,b,c,d,e元素\n");
	ListInsert(h,1,'a');
	ListInsert(h,2,'b');
	ListInsert(h,3,'c');
	ListInsert(h,4,'d');
	ListInsert(h,5,'e');
	printf("  (3)输出单链表h：");
	DispList(h);
	printf("  (4)单链表h长度：%d\n",ListLength(h));
	printf("  (5)单链表h为%s\n",(ListEmpty(h)?"空":"非空"));
	GetElem(h,3,e);
	printf("  (6)单链表h的第3个元素：%c\n",e);
	printf("  (7)元素a的位置：%d\n",LocateElem(h,'a'));
	printf("  (8)在第4个元素位置上插入f元素\n");
	ListInsert(h,4,'f');
	printf("  (9)输出单链表h：");
	DispList(h);
	printf("  (10)删除h的第3个元素\n");
	ListDelete(h,3,e);
	printf("  (11)输出单链表h：");
	DispList(h);
	printf("  (12)释放单链表h\n");
	DestroyList(h);
	return(1);
}
