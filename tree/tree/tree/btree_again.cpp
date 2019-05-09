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
			printf(",");
		}
	}
}
int main() {
	BTNode *b, *p, *lp, *rp;
	printf("二叉树的基本运算如下：\n");
	printf("	(1)创建二叉树\n");
	CreateBTree(b, "A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))");
	printf("	(2)输出二叉树："); DispBTree(b); printf("\n");
	printf("	(3)H结点:");
	p = FindNode(b, 'H');
	if (p != NULL) {
		lp = LchildNode(p);
		if (lp != NULL)printf("左孩子为%c", lp->data);
		else printf("无左孩子");
		rp = RchildNode(p);
		if (rp != NULL)printf("右孩子为%c", rp->data);
		else printf("无右孩子");
	}
	printf("\n");
	printf("	(4)二叉树b的高度：%d\n", BTHeight(b));
	printf("	(5)释放二叉树b\n");
	system("pause");
	DestroyBTree(b);
	return 1;
}