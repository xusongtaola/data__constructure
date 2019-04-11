#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
typedef char ElemType;
typedef struct linknode {
	ElemType data;					//������
	struct linknode * next;			//ָ����
}LinkStNode;
void InitStack(LinkStNode *&s) {								//��ʼ����ջ
	s = (LinkStNode *)malloc(sizeof(LinkStNode));
	s->next = NULL;
}
void DestroyStack(LinkStNode *&s) {				//������ջ
	LinkStNode *p = s->next;
	while (p != NULL) {
		free(s);
		s = p;
		p = p->next;
	}
	free(s);
}
bool StackEmpty(LinkStNode *s) {				//�ж�ջ�շ�
	return(s->next == NULL);
}
void Push(LinkStNode *&s, ElemType e) {				//��ջ
	LinkStNode *p;
	p = (LinkStNode *)malloc(sizeof(LinkStNode));
	p->data = e;				//�½�Ԫ��e��Ӧ�Ľ��p
	p->next = s->next;			//����p�����Ϊ��ʼ���
	s->next = p;
}
bool Pop(LinkStNode *&s, ElemType &e) {				//��ջ
	LinkStNode *p;
	if (s->next == NULL)
		return false;
	p = s->next;
	e = p->data;
	s->next = p->next;
	free(p);
	return true;
}
bool GetTop(LinkStNode *s, ElemType &e) {				//ȡջ��Ԫ��
	if (s->next == NULL)
		return false;
	e = s->next->data;
	return true;
}
int main() {
	ElemType e;
	LinkStNode *s;
	printf("��ջs�Ļ����������£�\n");
	printf("  (1)��ʼ��ջs\n");
	InitStack(s);
	printf("  (2)ջΪ%s\n", (StackEmpty(s) ? "��" : "�ǿ�"));
	printf("  (3)���ν�ջ˳��a,b,c,d,e\n");
	Push(s, 'a');
	Push(s, 'b');
	Push(s, 'c');
	Push(s, 'd');
	Push(s, 'e');
	printf("  (4)ջΪ%s\n", (StackEmpty(s) ? "��" : "�ǿ�"));
	printf("  (5)��ջ���У�");
	while (!StackEmpty(s)) {
		Pop(s, e);
		printf(" %c ", e);
	}
	printf("\n");
	printf("  (6)ջΪ%s\n", (StackEmpty(s) ? "��" : "�ǿ�"));
	printf("  (7)�ͷ�ջ\n");
	DestroyStack(s);
	system("pause");
	return 1;
}