#include<stdio.h>
#include<malloc.h>
#define MaxSize 100
typedef char ElemType;
typedef struct node {
	ElemType data;
	int ltag, rtag;					//���ӵ��������
	struct node *lchild;			//����ָ��
	struct node *rchild;			//�Һ���ָ��
}TBTNode;
void CreateTBTree(TBTNode * &b, char *str) {
	TBTNode *St[MaxSize], *p;
	int top = -1, k, j = 0;
	char ch = str[j];
	b = NULL;
	while (ch != '\0') {
		switch (ch){
		case '(':top++; St[top] = p; k = 1; break;
		case ')':top--; break;
		case ',':k = 2; break;
		default:
			p = (TBTNode *)malloc(sizeof(TBTNode));
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
		j++;
		ch = str[j];
	}
}
void DispTBTree(TBTNode *b) {				//�������������Ķ�����
	if (b!=NULL) {
		printf(" %c ", b->data);
		if (b->lchild != NULL || b->rchild != NULL) {
			printf("(");
			DispTBTree(b->lchild);
			if (b->lchild != NULL)printf(",");
			DispTBTree(b->rchild);
			printf(")");
		}
	}
}
TBTNode *pre;			//ȫ�ֱ���
void Thread(TBTNode *&p) {			//��������������������CreateThread����(�����˼���������Ȼ�о������ԣ�����)
	if (p != NULL) {
		Thread(p->lchild);			//������������
		if (p->lchild == NULL) {	//��p������ָ��Ϊ��
			p->lchild = pre;		//������ǰ�ڵ��ǰ�����
			p->ltag = 1;
		}
		else p->ltag = 0;
		if (pre->rchild == NULL) {	//��p�ڵ����ָ��Ϊ��
			pre->rchild = p;		//����ǰ�����ĺ��������ע�⣬�˴���pre��ǰ���������жϣ�����������ͬ��
			pre->rtag = 1;
		}
		else pre->rtag = 0;
		pre = p;
		Thread(p->rchild);			//������������
	}
}
TBTNode * CreateThread(TBTNode *b) {						//��������������������
	TBTNode *root;
	root = (TBTNode *)malloc(sizeof(TBTNode));				//���������
	root->ltag = 0; root->rtag = 1;
	root->rchild = b;														//����ͷ��㣬Ϊ����涨������ָ��Ϊ�գ���ָ�����һ�����
	if (b == NULL)											//�ն�����
		root->lchild = root;
	else {
		root->lchild = b;							//pre�����p����ǰ����㣬����������
		pre = root;									//pre��һ��ȫ�ֱ���	����������ʹ��pre��Thread�����ڱ仯�������õ���ͷ����Ҳ���ʲô�ģ���Ϊ���滹Ҫ�ã�����
		Thread(b);									//�����������������
		pre->rchild = root;
		pre->rtag = 1;
		root->rchild = pre;							//�������������
	}
	return root;
}

