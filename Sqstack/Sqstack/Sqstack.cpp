#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define MaxSize 100
typedef char ElemType;
typedef struct {
	ElemType data[MaxSize];
	int top;				//ջ��ָ��
}Sqstack;
void InitStack(Sqstack *&s) {				//��ʼ������ջ
	s = (Sqstack *)malloc(sizeof(Sqstack));
	s->top = -1;
}
void DestroyStack(Sqstack *&s) {					//����˳��ջ
	free(s);
}
bool StackEmpty(Sqstack *s) {					//�ж�ջ�շ�
	return(s->top == -1);
}
bool Push(Sqstack *&s, ElemType e) {			//��ջ
	if (s->top == MaxSize - 1)					//ջ������ջ�����
		return false;
	s->top++;
	s->data[s->top] = e;
	return true;
}
bool Pop(Sqstack *&s, ElemType &e) {			//��ջ
	if (s->top == -1)							//ջ�գ���ջ�����
		return false;
	e = s->data[s->top];
	s->top--;
	return true;
}
bool GetTop(Sqstack *s, ElemType &e) {					//ȡջ��Ԫ��
	if (s->top == -1)									//ջ�����
		return false;
	e = s->data[s->top];
	return true;
}
int main() {
	ElemType e;
	Sqstack *s;
	printf("˳��ջs�Ļ����������£�\n");
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
	