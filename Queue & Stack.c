/*
本文件用于实现链式栈和链式队列，
链式栈的基本操作包括：
1. 初始化链式栈S
2. 判断链式栈S是否为空栈
3. 将元素x压入链式栈S
4. 将链式栈S的栈顶元素弹出栈，并返回其元素值
5. 彻底销毁链式栈S
链式队列的基本操作包括：
1. 初始化链式队列Q
2. 判断链式队列Q是否为空队列
3. 将元素x推入链式队列Q
4. 将链式队列的队头元素取出队列，并返回其元素值
5. 彻底销毁链式队列Q
*/

#include <stdio.h>
#include <stdlib.h>
#include "Basic parament.c"

typedef struct Node {
    Elemtype data;
    struct Node *next;
} Node, *QNode, *SNode; //链式结构的基础

typedef struct Stack {
    SNode top;
} Stack, *SList; //链式栈定义

typedef struct Queue {
    QNode front;
    QNode rear;
} Queue, *QList; //链式队列定义

Status InitNode(Node *N) {
    //创建一个空的链节点并返回
    N = (Node*)malloc(sizeof(Node));
    if (N == NULL) return OVERFLOW;

    return OK;
} //InitNode

Status InitStack(SList S) {
    //创建一个空的链式栈S并返回
    S = (SList)malloc(sizeof(SNode));
    if (S == NULL) return OVERFLOW;
    InitNode(S->top); //为栈顶申请空间
    if (S->top == NULL) return OVERFLOW;
    S->top->next = NULL; //空链式栈中，top->next为NULL

    return OK;
} //InitStack

Status StackEmpty(SList S) {
    //判断链式栈S是否为空
    if (S == NULL) return ERROR;
    if (S->top->next == NULL) return TRUE;

    return FALSE;
} //StackEmpty

Status Push(SList S, Elemtype x) {
    //将元素x压入链式栈S
    SNode p;
    int flag;

    if (S == NULL) return ERROR;
    if (InitNode(p) == OK) { //新节点申请成功
        p->data = x;
        p->next = S->top->next;
        S->top->next = p; //将新节点p插入top后
    } else return OVERFLOW;

    return OK;
} //Push

Status Pop(SList S, Elemtype *x) {
    //将链式栈S的栈顶元素弹出，并返回它的元素值
    SNode p;

    if (S == NULL) return ERROR;
    if (StackEmpty(S)) return INFEASIBLE;
    p = S->top->next;
    *x = p->data; //取出栈顶元素值
    S->top->next = p->next;
    free(p); //将原先的栈顶节点释放

    return OK;
} //Pop

Status DestroyStack(SList S) {
    //彻底销毁链式栈S
    Elemtype x;

    if (S == NULL) { //链式栈不存在
        free(S);

        return OK;
    } //if
    while (!StackEmpty(S)) { //逐个释放节点
        Pop(S, &x);
    } //while
    free(S->top);
    free(S); //彻底销毁链式栈的结构

    return OK;
} //DestroyStack