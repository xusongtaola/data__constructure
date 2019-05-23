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
void CreateBTree(BTNode * &b, const char * str) {			//��������������Ҫһ����ջ�����游�ڵ㣩��һ���յĶ��������Ա����������ݣ�
	BTNode * St[MaxSize], *p;
	p = NULL;
	int top = -1, k, j = 0; char ch;
	b = NULL;				//������������ʼʱΪ��
	ch = str[j];			//�����ַ������Խ���������
	while (ch != '\0') {						//strδɨ����ʱѭ��
		switch (ch) {
		case '(':
			top++; St[top] = p; k = 1; break;		//��ʼ������������ǰһ������ջ����k��1���Կ�ʼ���㣩
		case ')':
			top--; break;							//ǰһ����㵯ջ����������
		case ',':
			k = 2; break;							//��ʼ����������(k��2)
		default:									//���һ����������ַ�Ϊ���
			p = (BTNode *)malloc(sizeof(BTNode));
			p->data = ch; p->lchild = p->rchild = NULL;
			if (b == NULL)							//��bΪ�գ�p��Ϊ�������ĸ����
				b = p;
			else {									//�ѽ�������������㣬������ջ��������ָ�򲢽���������
				switch (k) {
				case 1:St[top]->lchild = p; break;
				case 2:St[top]->rchild = p; break;
				}
			}
		}
		j++; ch = str[j];
	}
}
void DestroyBTree(BTNode *&b) {					//���ٶ�����
	if (b != NULL) {
		DestroyBTree(b->lchild);
		DestroyBTree(b->rchild);
		free(b);
	}
}
BTNode * FindNode(BTNode *b, ElemType x) {			//����ֵΪx�Ľ��
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
BTNode * LchildNode(BTNode * p) {			//����p�������ӽ��ָ��
	return p->lchild;
}
BTNode * RchildNode(BTNode * p) {					//����p�����Һ��ӽ��ָ��
	return p->rchild;
}
int BTHeight(BTNode *b) {				//�������b�ĸ߶�
	int lchildh, rchildh;
	if (b == NULL) return(0);				//�����ĸ߶�Ϊ0
	else {
		lchildh = BTHeight(b->lchild);			//���������ĸ߶�Ϊlchild
		rchildh = BTHeight(b->rchild);			//���������ĸ߶�Ϊrchild
		return(lchildh > rchildh) ? (lchildh + 1) : (rchildh + 1);
	}
}
void DispBTree(BTNode * b) {				//�����ű�ʾ�����������
	if (b != NULL) {
		printf("%c", b->data);
		if (b->lchild != NULL || b->rchild != NULL) {
			printf("(");			//�к��ӽ��ʱ�������
			DispBTree(b->lchild);	//�ݹ鴦��������
			if (b->rchild != NULL)	//���Һ��ӽ��ʱ�����
				printf(",");
			DispBTree(b->rchild);	//�ݹ鴦��������
			printf(")");			//�к��ӽ��ʱ�������
		}
	}
}
void AllPath1(BTNode *b, ElemType path[], int pathlen) {		//���������������������д�Ҷ�ӽڵ㵽��������·��
	if (b != NULL) {
		if (b->lchild == NULL && b->rchild == NULL) {			//�ж�b�Ƿ�ΪҶ�ӽڵ�
			printf("	%c���������·����%c->", b->data, b->data);
			for (int i = pathlen - 1; i > 0; i--)
				printf(" %c->", path[i]);
			printf("%c\n", path[0]);
		}
		else {								//����������������нڵ��·�����뵽path[]������ȥ����ʹ��pathlen��������
			path[pathlen] = b->data;
			pathlen++;
			AllPath1(b->lchild, path, pathlen);		//�ݹ�ɨ��������
			AllPath1(b->rchild, path, pathlen);		//�ݹ�ɨ��������
		}
	}
}
void LongPath1(BTNode *b, ElemType path[], int pathlen, ElemType longpath[], 
	int &longpathlen) {				//��������������������һ�������·��
	if (b == NULL) {
		if (pathlen > longpathlen) {				//ͨ���Ƚϣ�ѡ������·����������longpath��
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
void AllPath2(BTNode *b) {			//���ú���ǵݹ��㷨�����·��
	BTNode *st[MaxSize];			//����˳��ջ
	int top = -1;					//ջ��ָ���ʼ��
	BTNode *p, *r;
	bool flag;
	p = b;
	do {
		while (p != NULL) {			//ɨ����p�������½�㲢��ջ
			top++;
			st[top] = p;
			p = p->lchild;
		}
		r = NULL;					//rָ��շ��ʹ��Ľ�㣬��ʼΪ��
		flag = true;				//flagΪ���ʾ���ڴ���ջ�����
		while (top > -1 && flag) {	//ջ��Ϊ����flagΪ��ʱѭ��
			p = st[top];			//ȡ����ǰջ�����p
			if (p->rchild == r) {	//�����p���Һ���Ϊ�ջ����Ǹոշ��ʹ��Ľ��
				if (p->lchild == NULL && p->rchild == NULL) {		//��ΪҶ�ӽڵ������ջ�����нڵ�
					printf("	%c���������·����", p->data);
					for (int i = top; i > 0; i--)
						printf(" %c->", st[i]->data);
					printf(" %c\n", st[0]->data);
				}
				top--;			//��ջ���൱�ڵݹ鵽��һ��
				r = p;			//rָ��ոշ��ʹ��Ľ��
			}
			else {
				p = p->rchild;		//ת������������
				flag = false;		//��ʾ��ǰ���Ǵ���ջ���ڵ�
			}
		}
	} while (top > -1);				//ջ����ѭ��
}
void AllPath3(BTNode *b) {				//���ò�α����������·�������У�
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
			printf("	%c���������·����", b->data);
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
	printf("������b��"); DispBTree(b); printf("\n");
	printf("�������������\n"); AllPath1(b, path, 0);
	LongPath1(b, path, 0, longpath, longpathlen);
	printf("	��һ�����·�����ȣ�%d\n", longpathlen);
	printf("	��һ�����·��");
	for (i = longpathlen - 1; i >= 0; i--)
		printf("%c", longpath[i]);
	printf("\n");
	printf("����ǵݹ�����㷨��\n"); AllPath2(b);
	printf("��α����㷨��\n"); AllPath3(b);
	DestroyBTree(b);
	system("pause");
	return 1;
}