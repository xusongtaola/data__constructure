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
int Nodes(BTNode *b){					//求二叉树结点个数
	int num1,num2;
	if(b==NULL)
		return 0;
	else if(b->lchild==NULL&&b->rchild==NULL)
		return 1;
	else{
		num1=Nodes(b->lchild);
		num2=Nodes(b->rchild);
		return (num1+num2+1);			//返回子树b及其左右结点的个数，因此要加1
	}
}
int LeafNodes(BTNode *b){				//求二叉树b的叶子节点个数
	int num1,num2;
	if(b==NULL)
		return 0;
	else if (b->data==x)
		return(h);
	else{
		num1=Nodes(b->lchild);
		num2=Nodes(b->rchild);
		return (num1+num2);				//这里不加1，是因为只计算叶子节点个数，不计算根节点（最简模型），不断往上叠加
	}
}
int Level(BTNode *b,ElemType x,int h){			//求二叉树b中结点值为x的结点的层次（与FindNode函数做对比，只是把返回结点地址改成了返回层次，返回一个int型就可以了）
	int l;
	if(b==NULL)
		return(0);
	else if(b->data==x)
		return(h);
	else{
		l=Level(b->lchild,x,h+1);				//在左子树中查找(随着h不断弹栈（递归）向上，h不断增加)
		if(l!=0)return(1);
		else return(Level(b->rchild,x,h+1));	//在左子树中未找到，再到右子树中去寻找
	}
}
int BTWidth(BTNode *b){					//求二叉树b的宽度（采用非环形队列进行层次遍历）
	struct{
		int lno;			//结点层次
		BTNode *p;			//结点指针
	}Qu[MaxSize];			//定义非环形队列
	int front,rear;			//定义队首队尾指针
	int lnum,max,i,n;
	front=rear=0;			//置队列为空
	if(b!=NULL){
		rear++;Qu[rear].p=b;		//根节点进队
		Qu[rear].lno=1;				//根节点层次为1
		while(rear!=front){			//队空条件
			front++;b=Qu[front].p;	//队尾指针指向根节点，表示出队(不断有每一层的根节点进队)
			lnum=Qu[front].lno;
			if(b->lchild!=NULL){
				rear++;Qu[rear].p=b->lchild;		//左孩子进队
				Qu[rear].lno=lnum+1;
			}
			if(b->rchild!=NULL){
				rear++;Qu[rear].p=b->rchild;		//右孩子进队
				Qu[rear].lno=lnum+1;
			}
		}
		max=0;lnum=1;i=1;					//max存放宽度
		while(i<rear){
			n=0;
			while(i<=rear&&Qu[i].lno==lnum){		//对于每一个相同的层次（lno）进行统计
				n++;								//n计数一层中总的结点个数，统计出对应的一层宽度
				i++;								//i扫描队列中所有节点，便于之后进行统计新一层的编号
			}
			lnum=Qu[i].lno;							//根据上文的i统计处新一层的层次编号
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