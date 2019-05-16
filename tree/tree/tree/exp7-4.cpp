#include<stdio.h>
#include<malloc.h>
#define MaxSize 100
typedef char ElemType;
typedef struct node {
	ElemType data;
	int ltag, rtag;					//增加的线索标记
	struct node *lchild;			//左孩子指针
	struct node *rchild;			//右孩子指针
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
void DispTBTree(TBTNode *b) {				//输出含空线索域的二叉树
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
TBTNode *pre;			//全局变量
void Thread(TBTNode *&p) {			//中序线索化二叉树，被CreateThread调用(中序的思想在哪里？仍然感觉不明显！！！)
	if (p != NULL) {
		Thread(p->lchild);			//左子树线索化
		if (p->lchild == NULL) {	//若p结点的左指针为空
			p->lchild = pre;		//建立当前节点的前驱结点
			p->ltag = 1;
		}
		else p->ltag = 0;
		if (pre->rchild == NULL) {	//若p节点的右指针为空
			pre->rchild = p;		//建立前驱结点的后继线索（注意，此处对pre即前驱结点进行判断，与左子树不同）
			pre->rtag = 1;
		}
		else pre->rtag = 0;
		pre = p;
		Thread(p->rchild);			//右子树线索化
	}
}
TBTNode * CreateThread(TBTNode *b) {						//创建中序线索化二叉树
	TBTNode *root;
	root = (TBTNode *)malloc(sizeof(TBTNode));				//创建根结点
	root->ltag = 0; root->rtag = 1;
	root->rchild = b;														//这是头结点，为特殊规定，有右指针为空，且指向最后一个结点
	if (b == NULL)											//空二叉树
		root->lchild = root;
	else {
		root->lchild = b;							//pre结点是p结点的前驱结点，供加线索用
		pre = root;									//pre是一个全局变量	，这样可以使得pre在Thread函数内变化，而不用担心头结点找不到什么的，因为后面还要用！！！
		Thread(b);									//中序遍历线索二叉树
		pre->rchild = root;
		pre->rtag = 1;
		root->rchild = pre;							//根结点右线索化
	}
	return root;
}

