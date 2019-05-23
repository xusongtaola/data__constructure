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
BTNode *CRTree(char s[], int i, int j) {		//�������������ʽs[i...j]��Ӧ�Ķ�����
	BTNode *p;
	int k, plus = 0, posi;						//plus��¼������ĸ���
	if (i == j) {								//����i=j�������˵��ֻ��һ���ַ�
		p = (BTNode*)malloc(sizeof(BTNode));
		p->data = s[i];
		p->lchild = p->rchild = NULL;
		return p;
	}
	for (k = i; k <= j; k++)					//����Ϊi������j�����
		if (s[k] == '+' || s[k] == '-') {		//�Ȳ���+��-�������
			plus++;								//plus��¼+-�ĸ���
			posi = k;							//��¼���һ��+-�ĸ���
		}
	if(plus==0)									//���û��+-
		for(k=i;k<=j;k++)
			if (s[k] == ' * ' || s[k] == ' / ') {
				plus++;							//plus��¼*��/�ĸ���
				posi = k;						//posi��¼���һ��*��/��λ��
			}
	if (plus != 0) {							//������������ÿ�εݹ���ͳ��+-,Ȼ��ͳ��*/������ж����޷��ţ�plus�����еĻ��ʹ�����㣩������һ���������Ľ��
		p = (BTNode*)malloc(sizeof(BTNode));
		p->data = s[posi];
		p->lchild = CRTree(s, i, posi - 1);			//�����������Ϊ�м�ֽ磨����������Ϊ������������
		p->rchild = CRTree(s, posi + 1, j);
		return p;
	}
	else
		return NULL;							//û����������ͷ���NULL
}
double Comp(BTNode  *b) {
	double v1, v2;
	if (b == NULL)return 0;
	if (b->lchild == NULL && b->rchild == NULL)
		return b->data - '0';				//Ҷ�ӽڵ�ֱ�ӷ��ؽ��ֵ
	v1 = Comp(b->lchild);					//�ݹ������������ֵv1
	v2 = Comp(b->rchild);					//�ݹ������������ֵv2
	switch (b->data) {						//����b�������Ӧ���㣨Ϊ��b�����ʱ��������ʱ��������ţ���
	case '+':
		return v1 + v2;
	case '-':
		return v1 - v2;
	case '*':
		return v1 * v2;
	case '/':
		if (v2 != 0)return v1 / v2;
		else	abort();				//��0�쳣�˳�
	}
}
int main() {
	BTNode *b;
	char s[MaxSize] = "1+2*3-4/5";
	printf("�������ʽ%s\n", s);
	b = CRTree(s, 0, strlen(s) - 1);
	printf("��Ӧ��������");
	DispBTree(b);
	printf("\n�������ʽ��ֵ��%g\n", Comp(b));
	DestroyBTree(b);
	system("pause");
	return 1;
}
	