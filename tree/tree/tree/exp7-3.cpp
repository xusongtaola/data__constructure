#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#define MaxSize 100
#define MaxWidth 40
typedef char ElemType;
typedef struct node {
	ElemType data;
	struct node * lchild;
	struct node * rchild;
}BTNode;
void CreateBTree(BTNode * &b, char * str) {
	BTNode *St[MaxSize], *p;
	p = NULL;
	int top = -1, k, j = 0; char ch;
	b = NULL;
	ch = str[j];
	while (ch != '\0') {
		switch (ch) {
		case '(':top++; St[top] = p; k = 1; break;
		case ')':top--; break;
		case ',':k = 2; break;
		default:p = (BTNode *)malloc(sizeof(BTNode));
			p->data = ch; p->lchild = p->rchild = NULL;
			if (b == NULL)
				b = p;
			else {
				switch (k) {
				case 1:St[top]->lchild = p; break;
				case 2:St[top]->rchild = p; break;
				}
			}
		}
		j++; ch = str[j];
	}
}
void DestroyBTree(BTNode *&b) {
	if (b != NULL) {
		DestroyBTree(b->lchild);
		DestroyBTree(b->rchild);
		free(b);
	}
}
BTNode * FindNode(BTNode *b, ElemType x) {
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
BTNode * LchildNode(BTNode *p) {
	return p->lchild;
}
BTNode * RchildNode(BTNode *p) {
	return p->rchild;
}
int BTHeight(BTNode *b) {
	int lchild, rchild;
	if (b == NULL)return(0);
	else {
		lchild = BTHeight(b->lchild);
		rchild = BTHeight(b->rchild);
		return(lchild > rchild) ? (lchild + 1) : (rchild + 1);
	}
}
void DispBTree(BTNode *b) {
	if (b != NULL) {
		printf(" %c ", b->data);
		if (b->lchild != NULL || b->rchild != NULL) {
			printf("(");
			DispBTree(b->lchild);
			if (b->rchild != NULL)printf(",");
			DispBTree(b->rchild);
			printf(")");
		}
	}
}
BTNode *CreateBT1(char *pre, char *in, int n) {				//���������������������������
	BTNode *b;
	char *p; int k;
	if (n <= 0)return NULL;
	b = (BTNode *)malloc(sizeof(BTNode));
	b->data = *pre;
	for (p = in; p < in + n; p++)			//������������ҵ�����*pre�ַ���λ��k������㣩
		if (*p == *pre)						//preָ������
			break;
	k = p - in;								//ȷ���������in�е�λ��
	b->lchild = CreateBT1(pre + 1, in, k);	//�ݹ鹹�����������ݹ���ã��������������ڵ���Ϊk��k�Ǵ�0��ʼ�����ģ���
	b->rchild = CreateBT1(pre + k + 1, p + 1, n - k - 1);	//�ݹ鹹�����������������ڸ����ĺ��棩
	return b;
}
BTNode *CreateBT2(char *post, char *in, int n) {
	BTNode *b; char r, *p; int k;
	if (n <= 0)return NULL;
	r = *(post + n - 1);					//ȡ�����ֵ
	b = (BTNode *)malloc(sizeof(BTNode));	//�������������*b
	b->data = r;
	for (p = in; p < in + n; p++)			//��in�в��Ҹ����
		if (*p == r)break;
	k = p - in;								//kΪ�������in�е��±�
	b->lchild = CreateBT2(post, in, k);		//�ݹ鹹��������
	b->rchild = CreateBT2(post + k, p + 1, n - k - 1);	//�ݹ鹹��������
	return b;
}
void DispBTree1(BTNode *b) {
	BTNode *St[MaxSize], *p;
	int level[MaxSize][2], top = -1, n, i, width = 4;
	char type;					//������Һ��ӱ��
	if (b != NULL) {
		top++; St[top] = b;		//������ջ
		level[top][0] = width;
		level[top][1] = 2;		//0:��ʾ������ 1����ʾ������ 2����ʾ�����
		while (top > -1) {		//��������ǵݹ�˼�룬ջ����ѭ������Ҫһ��������,һ��ջ��һ������������ʾ״̬����һ����ά���飬�൱��һ���ṹ��Ĺ���
			p = St[top];		//ȡջ�������ʾ
			n = level[top][0];	//��ߵĿո�հ�
			switch (level[top][1]) {	//����Ӧ���ַ��������Ҹ��ڵ����Ϣ
			case 0:type = 'L'; break;
			case 1:type = 'R'; break;
			case 2:type = 'B'; break;
			}
			for (i = 1; i <= n; i++)
				printf(" ");				//����ո�
			printf(" %c(%c)", p->data, type);//�������
			for (i = n + 1; i <= MaxWidth; i += 2)
				printf("--");		//�Ҷ������
			printf("\n");
			top--;					//��ջ�����Ƿǵݹ��������˼�룩
			if (p->rchild != NULL) {			//�ǵݹ��������˼��:�����������ȳ����Һ����
				top++;
				St[top] = p->rchild;
				level[top][0] = n + width;		//���ϼӴ���߿հף��γɰ����ʾ��
				level[top][1] = 1;				//״̬��ʾ
			}
			if (p->lchild != NULL) {			//ͬ��
				top++;
				St[top] = p->lchild;
				level[top][0] = n + width;
				level[top][1] = 0;
			}
		}
	}
}
int main() {
	BTNode *b, *p, *lp, *rp;
	printf("�������Ļ����������£�\n");
	printf("	(1)����������\n");
	CreateBTree(b, "A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))");
	printf("	(2)�����������"); DispBTree(b); printf("\n");
	printf("	(3)H���:");
	p = FindNode(b, 'H');
	if (p != NULL) {
		lp = LchildNode(p);
		if (lp != NULL)printf("����Ϊ%c", lp->data);
		else printf("������");
		rp = RchildNode(p);
		if (rp != NULL)printf("�Һ���Ϊ%c", rp->data);
		else printf("���Һ���");
	}
	printf("\n");
	printf("	(4)������b�ĸ߶ȣ�%d\n", BTHeight(b));
	printf("	(5)�ͷŶ�����b\n\n\n");
	DestroyBTree(b);

	printf("\n*******************************************************\n\n");

	//BTNode *b;
	ElemType pre[] = "ABDEHJKLMNCFGI";
	ElemType in[] = "DBJHLKMNEAFCGI";
	ElemType post[] = "DJLNMKHEBFIGCA";
	int n = 14;
	b = CreateBT1(pre, in, n);
	printf("���������%s\n", pre);
	printf("���������%s\n", in);
	printf("����һ�Ŷ�����b��\n");
	printf("	���ű�ʾ����"); DispBTree(b); printf("\n");
	printf("	�����ʾ����\n"); DispBTree1(b); printf("\n\n");
	printf("���������%s\n", in);
	printf("���������%s\n",post);
	b = CreateBT2(post, in, n);
	printf("����һ�Ŷ�����b��\n");
	printf("	���ű�ʾ����"); DispBTree(b); printf("\n");
	printf("	�����ʾ����\n"); DispBTree1(b); printf("\n");
	DestroyBTree(b);

	system("pause");
	return 1;
}