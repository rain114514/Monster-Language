/*
本文件用于实现链栈及其操作，内容包括：
1. 链栈结构体的定义和名称
2. 链栈基本操作实现代码
链栈的基本操作包括：
1. 创建空栈S
2. 判断栈S是否为空
3. 将元素x入栈
4. 出栈并返回栈顶元素值
5. 直接返回栈顶元素的值
6. 销毁栈S
*/

#include "Node.c"

typedef struct Stack {
    SNode top; //栈顶
} Stack, *SList;

SList InitStack() {
    //创建空栈S并返回
    SList S;

    S = (SList)malloc(sizeof(Stack));
    S->top = CreateNode();
    S->top->next = NULL; //空栈的top指向NULL

    return S;
} //InitStack

int StackEmpty(SList S) {
    //判断已存在的栈S是否为空
    return !S->top->next;
} //StackEmpty

void Push(SList S, char x) {
    //将字符变量x推入栈S
    SNode p;

    p = CreateNode();
    p->data = x; //创建栈节点
    p->next = S->top->next;
    S->top->next = p; //将节点插入S->top后
} //Push

char GetTop(SList S) {
    //返回非空栈S的栈顶元素值
    if (!StackEmpty(S)) return S->top->next->data;
} //GetTop

char Pop(SList S) {
    //返回非空栈S的栈顶元素值后将栈顶节点出栈
    SNode p;
    char x;

    if (!StackEmpty(S)) {
        x = GetTop(S); //获取栈顶元素值
        p = S->top->next;
        S->top->next = p->next;
        free(p); //释放栈顶节点

        return x;
    } //if
} //Pop

void DestroyStack(SList S) {
    //销毁栈S
    while (!StackEmpty(S)) Pop(S);
    free(S->top);
    free(S); //将S的结构彻底销毁
} //DestroyStack