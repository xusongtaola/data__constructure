/**********************************************
��������
**********************************************/

#include<stdio.h>
#include<malloc.h>
typedef char ElemType;
typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LinkNode;
void CreateListF(LinkNode *&L, ElemType a[],int n){	//ͷ�巨����������
	LinkNode *s;
	L = (LinkNode * )malloc(sizeof(LinkNode));		//LΪͷָ�룬��˽�������������͸���ͷָ�룬ͷ�������˴������塣
	L->next = NULL;
	for (int i=0;i<n;i++){							//ͷ�巨(�������s��ʹ������ͷ���֮���׽��֮ǰ)
		s = (LinkNode * )malloc(sizeof(LinkNode));
		s->next = L->next;
		L->next = s;
	}
}
void CreateListR(LinkNode *&L, ElemType a[],int n){	//β�巨����������
	LinkNode *s,*r;
	L = (LinkNode * )malloc(sizeof(LinkNode));		//LΪͷָ�룬��˽�������������͸���ͷָ�룬ͷ�������˴������塣
	L->next = NULL;
	r=L;											//rʼ��ָ��β���
	for (int i=0;i<n;i++){
		s = (LinkNode * )malloc(sizeof(LinkNode));
		s->data = a[i];
		r->next = s;
		r = s;
	}
	r->next = NULL;									//β���nextָ���
}
void InitList(LinkNode * &L){
	L = (LinkNode * )malloc(sizeof(LinkNode));	//����ͷ���
	L->next = NULL;								//����������Ϊ�ձ�
}
void DestroyList(LinkNode *&L){						//�������Ա�
	LinkNode *pre = L, *p = pre->next;
	while (p != NULL){
		free(pre);
		pre = p;
		p = pre->next;								//����ͬ������һ����㣬ֱ������
	}
	free(pre);										//�ͷ�β���
}
bool ListEmpty(LinkNode *L){				//	�ж����Ա��Ƿ�Ϊ��
	return(L->next == NULL);
}
int ListLength(LinkNode *L){					//�����Ա���
	int i=0;									//ͷ������Ϊ��
	LinkNode *p = L;
	while(p->next != NULL){
		i++;
		p=p->next;
	}
	return(i);
}
void DispList(LinkNode *L){						//������Ա�
	LinkNode *p = L->next;
	while (p != NULL){
		printf(" %c ",p->data);
		p = p->next;
	}
	printf("\n");
}
bool GetElem(LinkNode *L,int i,ElemType &e){					//�����Ա��е�i��Ԫ��ֵ
	int j=0;													//ͷ������Ϊ��
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
int LocateElem(LinkNode *L,ElemType e){								//���ҵ�һ��ֵ��Ϊe��Ԫ�����
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
bool ListInsert(LinkNode *&L,int i,ElemType e){						//�����i��Ԫ�أ������ҵ���i-1����㣬���ɲ��룬���������i��i-1�����Ĺ�ϵ��
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
bool ListDelete(LinkNode *&L,int i, ElemType &e){						//ɾ����i��Ԫ�أ������ҵ���i-1����㣩
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
	printf("������Ļ����������£�\n");
	printf("  (1)��ʼ��������h\n");
	InitList(h);
	printf("  (2)���β���β�巨����a,b,c,d,eԪ��\n");
	ListInsert(h,1,'a');
	ListInsert(h,2,'b');
	ListInsert(h,3,'c');
	ListInsert(h,4,'d');
	ListInsert(h,5,'e');
	printf("  (3)���������h��");
	DispList(h);
	printf("  (4)������h���ȣ�%d\n",ListLength(h));
	printf("  (5)������hΪ%s\n",(ListEmpty(h)?"��":"�ǿ�"));
	GetElem(h,3,e);
	printf("  (6)������h�ĵ�3��Ԫ�أ�%c\n",e);
	printf("  (7)Ԫ��a��λ�ã�%d\n",LocateElem(h,'a'));
	printf("  (8)�ڵ�4��Ԫ��λ���ϲ���fԪ��\n");
	ListInsert(h,4,'f');
	printf("  (9)���������h��");
	DispList(h);
	printf("  (10)ɾ��h�ĵ�3��Ԫ��\n");
	ListDelete(h,3,e);
	printf("  (11)���������h��");
	DispList(h);
	printf("  (12)�ͷŵ�����h\n");
	DestroyList(h);
	return(1);
}
