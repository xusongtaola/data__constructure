#include<stdio.h>
#include<malloc.h>
#define MaxSize 50
#define ElemType char
typedef struct
{
	ElemType data[MaxSize];
	int length;
}SqList;

void CreateList(SqList * &L,ElemType a[], int n);
void InitList(SqList * &L);
void DestroyList(SqList * &L);
bool ListEmpty(SqList *L);
int ListLength(SqList *L);
void DispList(SqList *L);
bool GetElem(SqList *L, int i, ElemType &e);
int LocateElem(SqList *L, ElemType e);
bool ListInsert(SqList * &L,int i, ElemType e);
bool ListDelete(SqList * &L,int i, ElemType &e);


void CreateList(SqList * &L,ElemType a[], int n)
{
	int i=0,k=0;
	L=(SqList *)malloc(sizeof(SqList));
	while(i<n)
	{
		L ->data[k] = a[i];
		k++;i++;
	}
	L ->length = n;

}
void InitList(SqList * &L)
{
	L=(SqList *)malloc(sizeof(SqList));
	L->length=0;

}
void DestroyList(SqList * &L)
{
	free(L);
}
bool ListEmpty(SqList *L)
{
	return(L->length == 0);
}
int ListLength(SqList *L)
{
	return(L->length);
}
void DispList(SqList *L)
{
	for(int i=0;i<L->length;i++)
		printf(" %c ",L->data[i]);
	printf("\n");
}
bool GetElem(SqList *L, int i, ElemType &e)
{
	if(i<1 || i>L->length)
		return false;
	e = L->data[i-1];
	return true;
}
int LocateElem(SqList *L, ElemType e)
{
	int i = 0;
	while(i<L->length && L->data[i]!=e)
		i++;
	if(i>=L->length)
		return 0;
	else
		return i+1;
}
bool ListInsert(SqList * &L,int i, ElemType e)
{
	int j;
	if (i<1 || i>L->length+1)
		return false;
	i--;
	for(j=L->length;j>i;j--)
		L->data[j]=L->data[j-1];
	L->data[i]=e;
	L->length++;
	return true;
}
bool ListDelete(SqList * &L,int i, ElemType &e)
{
	int j;
	if(i<1||i>L->length)
		return false;
	i--;
	e=L->data[i];
	for(j=i;j<L->length-1;j++)
		L->data[j]=L->data[j+1];
	L->length--;
	return true;
}
void fun_4(SqList *&L){				//ɾ�����Ԫ�� 
	int i,j=0;
	for(i=1;i<L->length;i++){
		if(L->data[i]>L->data[j]){
			j=i;
		}
	}
	for(i=j;i<L->length-1;i++){
		L->data[i]=L->data[i+1];
	}
	L->length--;
} 
void fun_5(SqList *&L,ElemType x){				//��L�����Ԫ����߲���һ����Ԫ��
	int i,j=0;
	for(i=1;i<L->length;i++){
		if(L->data[i]>L->data[j]){
			j=i;
		}
	}
	for(i=L->length;i>j;i--){
		L->data[i]=L->data[i-1];
	}
	L->data[j]=x; 
	L->length++;
} 
int main()
{
	SqList *L;
	ElemType e;
	printf("˳���Ļ�������˳�����£�\n");
	printf("  (1)��ʼ��˳���L\n");
	InitList(L);
	printf("  (2)���β���a��b��c��d��eԪ��\n");
	ListInsert(L,1,'a');
	ListInsert(L,2,'b');
	ListInsert(L,3,'c');
	ListInsert(L,4,'d');
	ListInsert(L,5,'e');
	printf("  (3)���˳���L��");
	DispList(L);
	printf("  (4)˳���L���ȣ�%d\n",ListLength(L));
	printf("  (5)˳���LΪ%s\n",(ListEmpty(L)?"��":"�ǿ�"));
	GetElem(L,3,e);
	printf("  (6)˳���L�ĵ�����Ԫ�أ�%c\n",e);
	printf("  (7)Ԫ��a��λ�ã�%d\n",LocateElem(L,'a'));
	printf("  (8)�ڵ��ĸ�Ԫ�ص�λ���ϲ���fԪ��\n");
	ListInsert(L,4,'f');
	printf("  (9)���˳���L��");
	DispList(L);
	printf("  (10)ɾ��L�ĵ�����Ԫ��\n");
	ListDelete(L,3,e);
	printf("  (11)���˳���L��");
	DispList(L);
	//printf("  (12)ɾ��L�����Ԫ��\n");
	//fun_4(L);
	//printf("  (13)��L�����Ԫ����߲���һ����Ԫ��\n");
	fun_5(L,'a');
	printf("  (14)���˳���L��");
	DispList(L);
	printf("  (15)�ͷ�˳���L\n");
	DestroyList(L);
	return 1;

}
