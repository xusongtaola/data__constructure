#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#define MaxSize 100
typedef char ElemType;
typedef struct node {
	ElemType data;
	struct node * lchild;
	struct node * rchild;
}BTNode;
void CreateBTree(BTNode * &b, const char * str) {			//��������������Ҫһ����ջ�����游�ڵ㣩��һ���յĶ��������Ա����������ݣ�
	BTNode * St[MaxSize], *p;
	p = NULL;
	int top = -1, k, j = 0; char ch;
	b = NULL;				//������������ʼʱΪ��
	ch = str[j];			//�����ַ������Խ���������
	while (ch != '\0') {						//strδɨ����ʱѭ��
		switch (ch) {
		case '(':
			top++; St[top] = p; k = 1; break;		//��ʼ������������ǰһ������ջ����k��1���Կ�ʼ���㣩
		case ')':
			top--; break;							//ǰһ����㵯ջ����������
		case ',':
			k = 2; break;							//��ʼ����������(k��2)
		default:									//���һ����������ַ�Ϊ���
			p = (BTNode *)malloc(sizeof(BTNode));
			p->data = ch; p->lchild = p->rchild = NULL;
			if (b == NULL)							//��bΪ�գ�p��Ϊ�������ĸ����
				b = p;
			else {									//�ѽ�������������㣬������ջ��������ָ�򲢽���������
				switch (k) {
				case 1:St[top]->lchild = p; break;
				case 2:St[top]->rchild = p; break;
				}
			}
		}
		j++; ch = str[j];
	}
}
void DestroyBTree(BTNode *&b) {					//���ٶ�����
	if (b != NULL) {
		DestroyBTree(b->lchild);
		DestroyBTree(b->rchild);
		free(b);
	}
}
BTNode * FindNode(BTNode *b, ElemType x) {			//����ֵΪx�Ľ��
	BTNode *p;
	if (b == NULL)
		return NULL;
	else if (b->data == x)
		return b;
	else {
		p = FindNode(b->lchild, x);
		if (p != NULL)
			return p;
		else
			return FindNode(b->rchild, x);
	}
}
BTNode * LchildNode(BTNode * p) {			//����p�������ӽ��ָ��
	return p->lchild;
}
BTNode * RchildNode(BTNode * p) {					//����p�����Һ��ӽ��ָ��
	return p->rchild;
}
int BTHeight(BTNode *b) {				//�������b�ĸ߶�
	int lchildh, rchildh;
	if (b == NULL) return(0);				//�����ĸ߶�Ϊ0
	else {
		lchildh = BTHeight(b->lchild);			//���������ĸ߶�Ϊlchild
		rchildh = BTHeight(b->rchild);			//���������ĸ߶�Ϊrchild
		return(lchildh > rchildh) ? (lchildh + 1) : (rchildh + 1);
	}
}
void DispBTree(BTNode * b) {				//�����ű�ʾ�����������
	if (b != NULL) {
		printf("%c", b->data);
		if (b->lchild != NULL || b->rchild != NULL) {
			printf("(");			//�к��ӽ��ʱ�������
			DispBTree(b->lchild);	//�ݹ鴦��������
			if (b->rchild != NULL)	//���Һ��ӽ��ʱ�����
				printf(",");
			DispBTree(b->rchild);	//�ݹ鴦��������
			printf(")");			//�к��ӽ��ʱ�������
		}
	}
}
int Nodes(BTNode *b){					//�������������
	int num1,num2;
	if(b==NULL)
		return 0;
	else if(b->lchild==NULL&&b->rchild==NULL)
		return 1;
	else{
		num1=Nodes(b->lchild);
		num2=Nodes(b->rchild);
		return (num1+num2+1);			//��������b�������ҽ��ĸ��������Ҫ��1
	}
}
int LeafNodes(BTNode *b){				//�������b��Ҷ�ӽڵ����
	int num1,num2;
	if(b==NULL)
		return 0;
	else if (b->data==x)
		return(h);
	else{
		num1=Nodes(b->lchild);
		num2=Nodes(b->rchild);
		return (num1+num2);				//���ﲻ��1������Ϊֻ����Ҷ�ӽڵ��������������ڵ㣨���ģ�ͣ����������ϵ���
	}
}
int Level(BTNode *b,ElemType x,int h){			//�������b�н��ֵΪx�Ľ��Ĳ�Σ���FindNode�������Աȣ�ֻ�ǰѷ��ؽ���ַ�ĳ��˷��ز�Σ�����һ��int�;Ϳ����ˣ�
	int l;
	if(b==NULL)
		return(0);
	else if(b->data==x)
		return(h);
	else{
		l=Level(b->lchild,x,h+1);				//���������в���(����h���ϵ�ջ���ݹ飩���ϣ�h��������)
		if(l!=0)return(1);
		else return(Level(b->rchild,x,h+1));	//����������δ�ҵ����ٵ���������ȥѰ��
	}
}
int BTWidth(BTNode *b){					//�������b�Ŀ�ȣ����÷ǻ��ζ��н��в�α�����
	struct{
		int lno;			//�����
		BTNode *p;			//���ָ��
	}Qu[MaxSize];			//����ǻ��ζ���
	int front,rear;			//������׶�βָ��
	int lnum,max,i,n;
	front=rear=0;			//�ö���Ϊ��
	if(b!=NULL){
		rear++;Qu[rear].p=b;		//���ڵ����
		Qu[rear].lno=1;				//���ڵ���Ϊ1
		while(rear!=front){			//�ӿ�����
			front++;b=Qu[front].p;	//��βָ��ָ����ڵ㣬��ʾ����(������ÿһ��ĸ��ڵ����)
			lnum=Qu[front].lno;
			if(b->lchild!=NULL){
				rear++;Qu[rear].p=b->lchild;		//���ӽ���
				Qu[rear].lno=lnum+1;
			}
			if(b->rchild!=NULL){
				rear++;Qu[rear].p=b->rchild;		//�Һ��ӽ���
				Qu[rear].lno=lnum+1;
			}
		}
		max=0;lnum=1;i=1;					//max��ſ��
		while(i<rear){
			n=0;
			while(i<=rear&&Qu[i].lno==lnum){		//����ÿһ����ͬ�Ĳ�Σ�lno������ͳ��
				n++;								//n����һ�����ܵĽ�������ͳ�Ƴ���Ӧ��һ����
				i++;								//iɨ����������нڵ㣬����֮�����ͳ����һ��ı��
			}
			lnum=Qu[i].lno;							//�������ĵ�iͳ�ƴ���һ��Ĳ�α��
			if(n>max) max=n;
		}
		return max;
	}
	else return 0;
}
int FindLevelNode(BTNode *b,int h,int level,int &n){
	if(b==NULL)
		return 0;
	else if(h==h)
		n++;
	else{
		FindLevelNode(b->lchild,h,)
	}
}
int main() {
	BTNode *p, *b, *lp, *rp;
	//char *s;
	//char * s = strdup("A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))");
	//s = "A(B(D,E(H(J,K(L,M(,N)))),C(F,G(,I)))";
	printf("�������Ļ����������£�\n");
	printf("	(1)����������\n");
	CreateBTree(b, "A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))");
	printf("	(2)�����������");
	DispBTree(b);
	printf("\n");
	printf("	(3)H��㣺");
	p = FindNode(b, 'H');
	if (p != NULL) {
		lp = LchildNode(p);
		if (lp != NULL)
			printf("����Ϊ%c   ", lp->data);
		else
			printf("������");
		rp = RchildNode(p);
		if (rp != NULL)
			printf("�Һ���Ϊ%c", rp->data);
		else
			printf("���Һ���");
	}
	printf("\n");
	printf("	(4)������b�ĸ߶ȣ�%d\n", BTHeight(b));
	printf("	(5)�ͷŶ�����b\n");
	DestroyBTree(b);
	system("pause");
	return 1;
}