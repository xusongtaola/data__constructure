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
void PreOrder(BTNode *b) {				//先序遍历的递归算法
	if (b != NULL) {
		printf("%c", b->data);			//访问根结点
		PreOrder(b->lchild);			//递归访问左子树
		PreOrder(b->rchild);			//递归访问右子树
	}
}
void PreOrder1(BTNode *b) {					//先序非递归遍历算法
	BTNode * St[MaxSize], *p;
	int top = -1;
	if (b != NULL) {
		top++;
		St[top] = b;						//根结点进栈
		while (top > -1) {
			p = St[top];					//栈不为空时进栈
			top--;							//退栈并访问该结点
			printf("%c", p->data);
			if (p->rchild != NULL) {		//有右孩子，将其进栈(栈为先进后出，所以右孩子先进栈，以达成根左右的目的)
				top++;
				St[top] = p->rchild;
			}
			if (p->lchild != NULL) {		//有左孩子，将其进栈
				top++;
				St[top] = p->lchild;
			}
		}
		printf("\n");
	}
}
void InOrder(BTNode *b) {				//中序遍历的递归算法
	if (b != NULL) {
		InOrder(b->lchild);				//递归访问左子树
		printf(" %c ", b->data);		//访问根结点
		InOrder(b->rchild);				//递归访问右子树
	}
}
void InOrder1(BTNode *b) {					//中序非递归遍历算法
	BTNode *St[MaxSize], *p;
	int top = -1;
	if (b != NULL) {
		p = b;
		while (top > -1 || p != NULL) {
			while (p != NULL) {				//扫描结点p的所有左下结点并进栈(从根结点开始，到左结点入栈，达到左根右的目的)
				top++;
				St[top] = p;
				p = p->lchild;
			}
			if (top > -1) {
				p = St[top];				//出栈结点p并访问
				top--;
				printf(" %c ", p->data);
				p = p->rchild;
			}
		}
		printf("\n");
	}
}
void PostOrder(BTNode *b) {				//后序遍历的递归算法
	if (b != NULL) {
		PostOrder(b->lchild);			//递归访问左子树
		PostOrder(b->rchild);			//递归访问右子树
		printf(" %c ", b->data);		//访问根结点
	}
}
void PostOredr1(BTNode *b) {			//后序非递归遍历算法
	BTNode *St[MaxSize];
	BTNode *p;
	int top = -1;						//栈指针置初值
	bool flag;
	if (b != NULL) {
		do {
			while (b != NULL) {			//将b结点下的所有左下结点进栈
				top++;
				St[top] = b;
				b = b->lchild;
			}
			p = NULL;					//p指向当前结点的前一个已访问的结点
			flag = true;				//flag为真表示正在处理栈顶结点
			while (top != -1 && flag) {
				b = St[top];			//取出当前的栈顶元素在（根结点）（此时默认左右自述皆已访问完毕）
				if (b->rchild == p) {	//右子树不存在或者已被访问，访问之
					printf(" %c ", b->data);//访问b结点
					top--;
					p = b;				//p指向被访问的结点
				}
				else {
					b = b->rchild;		//b指向右子树
					flag = false;		//表示当前不是处理栈顶结点
				}
			}
		} while (top != -1);
		printf("\n");
	}
}
void TravLevel(BTNode *b) {					//层次遍历
	BTNode *Qu[MaxSize];					//定义环形队列
	int front, rear;						//定义队首和队尾指针
	front = rear = 0;						//置队列为空队
	if (b != NULL)printf(" %c ", b->data);
	rear++;									//根结点进队
	Qu[rear] = b;
	while (rear != front) {					//队列不为空
		front = (front + 1) % MaxSize;
		b = Qu[front];						//出队结点b
		if (b->lchild != NULL) {			//输出左孩子，并进队
			printf(" %c ", b->lchild->data);
			rear = (rear + 1) % MaxSize;
			Qu[rear] = b->lchild;
		}
		if (b->rchild != NULL) {			//输出右孩子，并进队
			printf(" %c ", b->rchild->data);
			rear = (rear + 1) % MaxSize;
			Qu[rear] = b->rchild;
		}
	}
	printf("\n");
} 