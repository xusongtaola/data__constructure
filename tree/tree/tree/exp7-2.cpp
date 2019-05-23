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
void PreOrder(BTNode *b) {				//��������ĵݹ��㷨
	if (b != NULL) {
		printf("%c", b->data);			//���ʸ����
		PreOrder(b->lchild);			//�ݹ����������
		PreOrder(b->rchild);			//�ݹ����������
	}
}
void PreOrder1(BTNode *b) {					//����ǵݹ�����㷨
	BTNode * St[MaxSize], *p;
	int top = -1;
	if (b != NULL) {
		top++;
		St[top] = b;						//������ջ
		while (top > -1) {
			p = St[top];					//ջ��Ϊ��ʱ��ջ
			top--;							//��ջ�����ʸý��
			printf("%c", p->data);
			if (p->rchild != NULL) {		//���Һ��ӣ������ջ(ջΪ�Ƚ�����������Һ����Ƚ�ջ���Դ�ɸ����ҵ�Ŀ��)
				top++;
				St[top] = p->rchild;
			}
			if (p->lchild != NULL) {		//�����ӣ������ջ
				top++;
				St[top] = p->lchild;
			}
		}
		printf("\n");
	}
}
void InOrder(BTNode *b) {				//��������ĵݹ��㷨
	if (b != NULL) {
		InOrder(b->lchild);				//�ݹ����������
		printf(" %c ", b->data);		//���ʸ����
		InOrder(b->rchild);				//�ݹ����������
	}
}
void InOrder1(BTNode *b) {					//����ǵݹ�����㷨
	BTNode *St[MaxSize], *p;
	int top = -1;
	if (b != NULL) {
		p = b;
		while (top > -1 || p != NULL) {
			while (p != NULL) {				//ɨ����p���������½�㲢��ջ(�Ӹ���㿪ʼ����������ջ���ﵽ����ҵ�Ŀ��)
				top++;
				St[top] = p;
				p = p->lchild;
			}
			if (top > -1) {
				p = St[top];				//��ջ���p������
				top--;
				printf(" %c ", p->data);
				p = p->rchild;
			}
		}
		printf("\n");
	}
}
void PostOrder(BTNode *b) {				//��������ĵݹ��㷨
	if (b != NULL) {
		PostOrder(b->lchild);			//�ݹ����������
		PostOrder(b->rchild);			//�ݹ����������
		printf(" %c ", b->data);		//���ʸ����
	}
}
void PostOredr1(BTNode *b) {			//����ǵݹ�����㷨
	BTNode *St[MaxSize];
	BTNode *p;
	int top = -1;						//ջָ���ó�ֵ
	bool flag;
	if (b != NULL) {
		do {
			while (b != NULL) {			//��b����µ��������½���ջ
				top++;
				St[top] = b;
				b = b->lchild;
			}
			p = NULL;					//pָ��ǰ����ǰһ���ѷ��ʵĽ��
			flag = true;				//flagΪ���ʾ���ڴ���ջ�����
			while (top != -1 && flag) {
				b = St[top];			//ȡ����ǰ��ջ��Ԫ���ڣ�����㣩����ʱĬ�������������ѷ�����ϣ�
				if (b->rchild == p) {	//�����������ڻ����ѱ����ʣ�����֮
					printf(" %c ", b->data);//����b���
					top--;
					p = b;				//pָ�򱻷��ʵĽ��
				}
				else {
					b = b->rchild;		//bָ��������
					flag = false;		//��ʾ��ǰ���Ǵ���ջ�����
				}
			}
		} while (top != -1);
		printf("\n");
	}
}
void TravLevel(BTNode *b) {					//��α���
	BTNode *Qu[MaxSize];					//���廷�ζ���
	int front, rear;						//������׺Ͷ�βָ��
	front = rear = 0;						//�ö���Ϊ�ն�
	if (b != NULL)printf(" %c ", b->data);
	rear++;									//��������
	Qu[rear] = b;
	while (rear != front) {					//���в�Ϊ��
		front = (front + 1) % MaxSize;
		b = Qu[front];						//���ӽ��b
		if (b->lchild != NULL) {			//������ӣ�������
			printf(" %c ", b->lchild->data);
			rear = (rear + 1) % MaxSize;
			Qu[rear] = b->lchild;
		}
		if (b->rchild != NULL) {			//����Һ��ӣ�������
			printf(" %c ", b->rchild->data);
			rear = (rear + 1) % MaxSize;
			Qu[rear] = b->rchild;
		}
	}
	printf("\n");
} 