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
BTNode *CRTree(char s[], int i, int j) {		//建立简单算数表达式s[i...j]对应的二叉树
	BTNode *p;
	int k, plus = 0, posi;						//plus记录运算符的个数
	if (i == j) {								//处理i=j的情况，说明只有一个字符
		p = (BTNode*)malloc(sizeof(BTNode));
		p->data = s[i];
		p->lchild = p->rchild = NULL;
		return p;
	}
	for (k = i; k <= j; k++)					//以下为i不等于j的情况
		if (s[k] == '+' || s[k] == '-') {		//先查找+和-的运算符
			plus++;								//plus记录+-的个数
			posi = k;							//记录最后一个+-的个数
		}
	if(plus==0)									//如果没有+-
		for(k=i;k<=j;k++)
			if (s[k] == ' * ' || s[k] == ' / ') {
				plus++;							//plus记录*和/的个数
				posi = k;						//posi记录最后一个*和/的位置
			}
	if (plus != 0) {							//如果有运算符（每次递归先统计+-,然后统计*/，最后判断有无符号（plus），有的话就创立结点），创建一个保存它的结点
		p = (BTNode*)malloc(sizeof(BTNode));
		p->data = s[posi];
		p->lchild = CRTree(s, i, posi - 1);			//以最后的运算符为中间分界（根），划分为左右两个子树
		p->rchild = CRTree(s, posi + 1, j);
		return p;
	}
	else
		return NULL;							//没有运算符，就返回NULL
}
double Comp(BTNode  *b) {
	double v1, v2;
	if (b == NULL)return 0;
	if (b->lchild == NULL && b->rchild == NULL)
		return b->data - '0';				//叶子节点直接返回结点值
	v1 = Comp(b->lchild);					//递归求出左子树的值v1
	v2 = Comp(b->rchild);					//递归求出右子树的值v2
	switch (b->data) {						//根据b结点做相应运算（为何b结点有时是数字有时是运算符号？）
	case '+':
		return v1 + v2;
	case '-':
		return v1 - v2;
	case '*':
		return v1 * v2;
	case '/':
		if (v2 != 0)return v1 / v2;
		else	abort();				//除0异常退出
	}
}
int main() {
	BTNode *b;
	char s[MaxSize] = "1+2*3-4/5";
	printf("算术表达式%s\n", s);
	b = CRTree(s, 0, strlen(s) - 1);
	printf("对应二叉树：");
	DispBTree(b);
	printf("\n算术表达式的值：%g\n", Comp(b));
	DestroyBTree(b);
	system("pause");
	return 1;
}
	