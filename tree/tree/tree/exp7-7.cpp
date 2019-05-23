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
void AllPath1(BTNode *b, ElemType path[], int pathlen) {		//采用先序遍历方法输出所有从叶子节点到根结点的逆路径
	if (b != NULL) {
		if (b->lchild == NULL && b->rchild == NULL) {			//判断b是否为叶子节点
			printf("	%c到根结点逆路径：%c->", b->data, b->data);
			for (int i = pathlen - 1; i > 0; i--)
				printf(" %c->", path[i]);
			printf("%c\n", path[0]);
		}
		else {								//采用先序遍历将所有节点的路径纳入到path[]数组中去，并使得pathlen不断增加
			path[pathlen] = b->data;
			pathlen++;
			AllPath1(b->lchild, path, pathlen);		//递归扫描左子树
			AllPath1(b->rchild, path, pathlen);		//递归扫描右子树
		}
	}
}
void LongPath1(BTNode *b, ElemType path[], int pathlen, ElemType longpath[], 
	int &longpathlen) {				//采用先序遍历方法输出第一条最长的逆路径
	if (b == NULL) {
		if (pathlen > longpathlen) {				//通过比较，选择出最长的路径，保存在longpath中
			for (int i = pathlen - 1; i >= 0; i--)
				longpath[i] = path[i];
			longpathlen = pathlen;
		}
	}
	else {
		path[pathlen] = b->data;
		pathlen++;
		LongPath1(b->lchild, path, pathlen, longpath, longpathlen);
		LongPath1(b->rchild, path, pathlen, longpath, longpathlen);
	}
}
void AllPath2(BTNode *b) {			//采用后序非递归算法输出逆路径
	BTNode *st[MaxSize];			//定义顺序栈
	int top = -1;					//栈顶指针初始化
	BTNode *p, *r;
	bool flag;
	p = b;
	do {
		while (p != NULL) {			//扫描结点p所有左下结点并进栈
			top++;
			st[top] = p;
			p = p->lchild;
		}
		r = NULL;					//r指向刚访问过的结点，初始为空
		flag = true;				//flag为真表示正在处理栈顶结点
		while (top > -1 && flag) {	//栈不为空且flag为真时循环
			p = st[top];			//取出当前栈顶结点p
			if (p->rchild == r) {	//若结点p的右孩子为空或者是刚刚访问过的结点
				if (p->lchild == NULL && p->rchild == NULL) {		//若为叶子节点则输出栈中所有节点
					printf("	%c到根结点逆路径：", p->data);
					for (int i = top; i > 0; i--)
						printf(" %c->", st[i]->data);
					printf(" %c\n", st[0]->data);
				}
				top--;			//退栈，相当于递归到上一层
				r = p;			//r指向刚刚访问过的结点
			}
			else {
				p = p->rchild;		//转向处理其右子树
				flag = false;		//表示当前不是处理栈顶节点
			}
		}
	} while (top > -1);				//栈不空循环
}
void AllPath3(BTNode *b) {				//采用层次遍历法输出逆路径（队列）
	struct snode {
		BTNode *node;
		int parent;
	}Qu[MaxSize];
	int front, rear, p;
	front = rear = -1;
	rear++;
	Qu[rear].node = b;
	Qu[rear].parent = -1;
	while (front < rear) {
		front++;
		b = Qu[front].node;
		if (b->lchild == NULL && b->rchild == NULL) {
			printf("	%c到根结点逆路径：", b->data);
			p = front;
			while (Qu[p].parent != -1) {
				printf("%c->", Qu[p].node->data);
				p = Qu[p].parent;
			}
			printf(" %c\n", Qu[p].node->data);
		}
		if (b->lchild != NULL) {
			rear++;
			Qu[rear].node = b->lchild;
			Qu[rear].parent = front;
		}
		if (b->rchild != NULL) {
			rear++;
			Qu[rear].node = b->rchild;
			Qu[rear].parent = front;
		}
	}
}
int main() {
	BTNode *b;
	ElemType path[MaxSize], longpath[MaxSize];
	int i, longpathlen = 0;
	CreateBTree(b, "A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))");
	printf("二叉树b："); DispBTree(b); printf("\n");
	printf("先序遍历方法：\n"); AllPath1(b, path, 0);
	LongPath1(b, path, 0, longpath, longpathlen);
	printf("	第一条最长逆路径长度：%d\n", longpathlen);
	printf("	第一条最长逆路径");
	for (i = longpathlen - 1; i >= 0; i--)
		printf("%c", longpath[i]);
	printf("\n");
	printf("后序非递归遍历算法：\n"); AllPath2(b);
	printf("层次遍历算法：\n"); AllPath3(b);
	DestroyBTree(b);
	system("pause");
	return 1;
}