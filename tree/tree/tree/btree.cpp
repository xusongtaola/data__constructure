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
void CreateBTree(BTNode * &b, const char * str) {			//创建二叉树（需要一个链栈（保存父节点）、一个空的二叉树，以遍历括号内容）
	BTNode * St[MaxSize], *p;
	p = NULL;
	int top = -1, k, j = 0; char ch;
	b = NULL;				//创建二叉树初始时为空
	ch = str[j];			//遍历字符串，以建立二叉树
	while (ch != '\0') {						//str未扫描完时循环
		switch (ch) {
		case '(':
			top++; St[top] = p; k = 1; break;		//开始处理左子树（前一个结点进栈，且k置1，以开始左结点）
		case ')':
			top--; break;							//前一个结点弹栈，子树结束
		case ',':
			k = 2; break;							//开始处理右子树(k置2)
		default:									//最后一种情况，此字符为结点
			p = (BTNode *)malloc(sizeof(BTNode));
			p->data = ch; p->lchild = p->rchild = NULL;
			if (b == NULL)							//若b为空，p置为二叉树的根结点
				b = p;
			else {									//已建立二叉树根结点，可依据栈的内容来指向并建立二叉树
				switch (k) {
				case 1:St[top]->lchild = p; break;
				case 2:St[top]->rchild = p; break;
				}
			}
		}
		j++; ch = str[j];
	}
}
void DestroyBTree(BTNode *&b) {					//销毁二叉树
	if (b != NULL) {
		DestroyBTree(b->lchild);
		DestroyBTree(b->rchild);
		free(b);
	}
}
BTNode * FindNode(BTNode *b, ElemType x) {			//查找值为x的结点
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
BTNode * LchildNode(BTNode * p) {			//返回p结点的左孩子结点指针
	return p->lchild;
}
BTNode * RchildNode(BTNode * p) {					//返回p结点的右孩子结点指针
	return p->rchild;
}
int BTHeight(BTNode *b) {				//求二叉树b的高度
	int lchildh, rchildh;
	if (b == NULL) return(0);				//空树的高度为0
	else {
		lchildh = BTHeight(b->lchild);			//求左子树的高度为lchild
		rchildh = BTHeight(b->rchild);			//求右子树的高度为rchild
		return(lchildh > rchildh) ? (lchildh + 1) : (rchildh + 1);
	}
}
void DispBTree(BTNode * b) {				//以括号表示法输出二叉树
	if (b != NULL) {
		printf("%c", b->data);
		if (b->lchild != NULL || b->rchild != NULL) {
			printf("(");			//有孩子结点时才输出（
			DispBTree(b->lchild);	//递归处理左子树
			if (b->rchild != NULL)	//有右孩子结点时才输出
				printf(",");
			DispBTree(b->rchild);	//递归处理右子树
			printf(")");			//有孩子结点时才输出）
		}
	}
}

int main() {
	BTNode *p, *b, *lp, *rp;
	//char *s;
	//char * s = strdup("A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))");
	//s = "A(B(D,E(H(J,K(L,M(,N)))),C(F,G(,I)))";
	printf("二叉树的基本运算如下：\n");
	printf("	(1)创建二叉树\n");
	CreateBTree(b, "A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))");
	printf("	(2)输出二叉树：");
	DispBTree(b);
	printf("\n");
	printf("	(3)H结点：");
	p = FindNode(b, 'H');
	if (p != NULL) {
		lp = LchildNode(p);
		if (lp != NULL)
			printf("左孩子为%c   ", lp->data);
		else
			printf("无左孩子");
		rp = RchildNode(p);
		if (rp != NULL)
			printf("右孩子为%c", rp->data);
		else
			printf("无右孩子");
	}
	printf("\n");
	printf("	(4)二叉树b的高度：%d\n", BTHeight(b));
	printf("	(5)释放二叉树b\n");
	DestroyBTree(b);
	system("pause");
	return 1;
}
