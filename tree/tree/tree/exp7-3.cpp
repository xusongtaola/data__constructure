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
BTNode *CreateBT1(char *pre, char *in, int n) {				//由先序遍历和中序遍历构造二叉树
	BTNode *b;
	char *p; int k;
	if (n <= 0)return NULL;
	b = (BTNode *)malloc(sizeof(BTNode));
	b->data = *pre;
	for (p = in; p < in + n; p++)			//在中序遍历中找到等于*pre字符的位置k（根结点）
		if (*p == *pre)						//pre指向根结点
			break;
	k = p - in;								//确定根结点在in中的位置
	b->lchild = CreateBT1(pre + 1, in, k);	//递归构造左子树（递归调用，其左子树所含节点数为k（k是从0开始计数的））
	b->rchild = CreateBT1(pre + k + 1, p + 1, n - k - 1);	//递归构造右子树（右子树在根结点的后面）
	return b;
}
BTNode *CreateBT2(char *post, char *in, int n) {
	BTNode *b; char r, *p; int k;
	if (n <= 0)return NULL;
	r = *(post + n - 1);					//取根结点值
	b = (BTNode *)malloc(sizeof(BTNode));	//创建二叉树结点*b
	b->data = r;
	for (p = in; p < in + n; p++)			//在in中查找根结点
		if (*p == r)break;
	k = p - in;								//k为根结点在in中的下标
	b->lchild = CreateBT2(post, in, k);		//递归构造左子树
	b->rchild = CreateBT2(post + k, p + 1, n - k - 1);	//递归构造右子树
	return b;
}
void DispBTree1(BTNode *b) {
	BTNode *St[MaxSize], *p;
	int level[MaxSize][2], top = -1, n, i, width = 4;
	char type;					//存放左右孩子标记
	if (b != NULL) {
		top++; St[top] = b;		//根结点进栈
		level[top][0] = width;
		level[top][1] = 2;		//0:表示左子树 1：表示右子树 2：表示根结点
		while (top > -1) {		//先序遍历非递归思想，栈不空循环，需要一个二叉树,一个栈，一个计数器（表示状态），一个二维数组，相当于一个结构体的功能
			p = St[top];		//取栈顶结点显示
			n = level[top][0];	//左边的空格空白
			switch (level[top][1]) {	//在相应的字符后附上左右根节点的信息
			case 0:type = 'L'; break;
			case 1:type = 'R'; break;
			case 2:type = 'B'; break;
			}
			for (i = 1; i <= n; i++)
				printf(" ");				//输出空格
			printf(" %c(%c)", p->data, type);//输出数据
			for (i = n + 1; i <= MaxWidth; i += 2)
				printf("--");		//右对齐输出
			printf("\n");
			top--;					//弹栈（还是非递归先序遍历思想）
			if (p->rchild != NULL) {			//非递归先序遍历思想:先右再左，左先出，右后出。
				top++;
				St[top] = p->rchild;
				level[top][0] = n + width;		//不断加大左边空白，形成凹入表示法
				level[top][1] = 1;				//状态表示
			}
			if (p->lchild != NULL) {			//同上
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
	printf("	(5)释放二叉树b\n\n\n");
	DestroyBTree(b);

	printf("\n*******************************************************\n\n");

	//BTNode *b;
	ElemType pre[] = "ABDEHJKLMNCFGI";
	ElemType in[] = "DBJHLKMNEAFCGI";
	ElemType post[] = "DJLNMKHEBFIGCA";
	int n = 14;
	b = CreateBT1(pre, in, n);
	printf("先序遍历：%s\n", pre);
	printf("中序遍历：%s\n", in);
	printf("构造一颗二叉树b：\n");
	printf("	括号表示法："); DispBTree(b); printf("\n");
	printf("	凹入表示法：\n"); DispBTree1(b); printf("\n\n");
	printf("中序遍历：%s\n", in);
	printf("后序遍历：%s\n",post);
	b = CreateBT2(post, in, n);
	printf("构造一颗二叉树b：\n");
	printf("	括号表示法："); DispBTree(b); printf("\n");
	printf("	凹入表示法：\n"); DispBTree1(b); printf("\n");
	DestroyBTree(b);

	system("pause");
	return 1;
}