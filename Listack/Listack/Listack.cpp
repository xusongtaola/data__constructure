#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
typedef char ElemType;
typedef struct linknode {
	ElemType data;					//数据域
	struct linknode * next;			//指针域
}LinkStNode;
void InitStack(LinkStNode *&s) {								//初始化链栈
	s = (LinkStNode *)malloc(sizeof(LinkStNode));
	s->next = NULL;
}
void DestroyStack(LinkStNode *&s) {				//销毁链栈
	LinkStNode *p = s->next;
	while (p != NULL) {
		free(s);
		s = p;
		p = p->next;
	}
	free(s);
}
bool StackEmpty(LinkStNode *s) {				//判断栈空否
	return(s->next == NULL);
}
void Push(LinkStNode *&s, ElemType e) {				//进栈
	LinkStNode *p;
	p = (LinkStNode *)malloc(sizeof(LinkStNode));
	p->data = e;				//新建元素e对应的结点p
	p->next = s->next;			//插入p结点作为开始结点
	s->next = p;
}
bool Pop(LinkStNode *&s, ElemType &e) {				//出栈
	LinkStNode *p;
	if (s->next == NULL)
		return false;
	p = s->next;
	e = p->data;
	s->next = p->next;
	free(p);
	return true;
}
bool GetTop(LinkStNode *s, ElemType &e) {				//取栈顶元素
	if (s->next == NULL)
		return false;
	e = s->next->data;
	return true;
}
int main() {
	ElemType e;
	LinkStNode *s;
	printf("链栈s的基本运算如下：\n");
	printf("  (1)初始化栈s\n");
	InitStack(s);
	printf("  (2)栈为%s\n", (StackEmpty(s) ? "空" : "非空"));
	printf("  (3)依次进栈顺序a,b,c,d,e\n");
	Push(s, 'a');
	Push(s, 'b');
	Push(s, 'c');
	Push(s, 'd');
	Push(s, 'e');
	printf("  (4)栈为%s\n", (StackEmpty(s) ? "空" : "非空"));
	printf("  (5)出栈序列：");
	while (!StackEmpty(s)) {
		Pop(s, e);
		printf(" %c ", e);
	}
	printf("\n");
	printf("  (6)栈为%s\n", (StackEmpty(s) ? "空" : "非空"));
	printf("  (7)释放栈\n");
	DestroyStack(s);
	system("pause");
	return 1;
}