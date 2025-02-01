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
} Node, *QNode, *SNode; //链式节点定义

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
    if (N == NULL) return OVERFLOW; //申请失败

    return OK;
} //InitNode

Status InitStack(SList S) {
    //创建一个空的链式栈S并返回
    S = (SList)malloc(sizeof(Stack));
    if (S == NULL) return OVERFLOW; //申请失败
    if (InitNode(S->top) == OVERFLOW) return OVERFLOW; //栈顶申请失败
    S->top->next = NULL; //空链式栈中，top->next为NULL

    return OK;
} //InitStack

Status StackEmpty(SList S) {
    //判断链式栈S是否为空
    if (S == NULL) return ERROR; //链式栈S不存在
    if (S->top->next == NULL) return TRUE;

    return FALSE;
} //StackEmpty

Status Push(SList S, Elemtype x) {
    //将元素x压入链式栈S
    SNode p;
    int flag;

    if (S == NULL) return ERROR; //链式栈S不存在
    if (InitNode(p) == OK) { //新节点申请成功
        p->data = x;
        p->next = S->top->next;
        S->top->next = p; //将新节点p插在top后
    } else return OVERFLOW; //新节点申请失败

    return OK;
} //Push

Status Pop(SList S, Elemtype *x) {
    //将链式栈S的栈顶元素弹出，并返回它的元素值
    SNode p;

    if (S == NULL) return ERROR; //链式栈S不存在
    if (StackEmpty(S)) return INFEASIBLE; //链式栈S为空栈
    p = S->top->next;
    *x = p->data; //取出栈顶元素值
    S->top->next = p->next;
    free(p); //将原先的栈顶节点释放

    return OK;
} //Pop

Status DestroyStack(SList S) {
    //彻底销毁链式栈S
    Elemtype x;

    if (S == NULL) return OK;
    while (!StackEmpty(S)) Pop(S, &x);
    free(S->top);
    free(S); //彻底销毁链式栈的结构
    S = NULL;

    return OK;
} //DestroyStack

Status InitQueue(QList Q) {
    //创建一个空的链式队列Q并返回
    Q = (QList)malloc(sizeof(Queue));
    if (Q == NULL) return OVERFLOW; //申请失败
    if (InitNode(Q->front) == OVERFLOW) return OVERFLOW; //队头申请失败
    if (InitNode(Q->rear) == OVERFLOW) return OVERFLOW; //队尾申请失败
    Q->front->next = Q->rear; //空的链式队列中，front->next为rear

    return OK;
} //InitQueue

Status QueueEmpty(QList Q) {
    //判断链式队列Q是否为空
    if (Q == NULL) return ERROR; //链式队列Q不存在
    if (Q->front->next == Q->rear) return TRUE;

    return FALSE;
} //QueueEmpty

Status EnQueue(QList Q, Elemtype x) {
    //将元素x推入链式队列Q
    QNode p, q;

    if (Q == NULL) return ERROR; //链式队列Q不存在
    if (InitNode(p) == OK) { //新节点申请成功
        p->data = x;
        q = Q->front; //找到rear前一个节点
        while (q->next != Q->rear) q = q->next;
        p->next = Q->rear;
        q->next = p; //将新节点p插入rear前
    } else return OVERFLOW; //新节点申请失败

    return OK;
} //EnQueue

Status DeQueue(QList Q, Elemtype *x) {
    //将链式队列Q的队头元素取出，并返回它的元素值
    QNode p;

    if (Q == NULL) return ERROR; //链式队列Q不存在
    if (QueueEmpty(Q)) return INFEASIBLE; //链式队列Q为空
    p = Q->front->next;
    *x = p->data; //取出队头元素值
    Q->front->next = p->next;
    free(p); //将原先的栈顶节点释放

    return OK;
} //DeQueue

Status DestroyQueue(QList Q) {
    //将链式队列Q彻底销毁
    Elemtype x;

    if (Q == NULL) return OK;
    while (!QueueEmpty(Q)) Pop(Q, &x);
    free(Q->front);
    free(Q->rear);
    free(Q); //彻底销毁链式队列Q的结构
    Q = NULL;

    return OK;
} //DestroyQueue