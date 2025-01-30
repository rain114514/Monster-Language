/*
本文件用于实现链队列、链栈及它们的操作，内容包括：
1. 链队列、链栈基本节点定义
2. 链队列结构体的定义和名称
3. 链栈结构体的定义和名称
4. 链队列基本操作实现代码
5. 链栈基本操作实现代码
链队列的基本操作包括：
1. 创建空队列Q
2. 判断队列Q是否为空
3. 将元素x入队
4. 出队列并返回队头元素值
5. 销毁队列Q
链栈的基本操作包括：
1. 创建空栈S
2. 判断栈S是否为空
3. 将元素x入栈
4. 出栈并返回栈顶元素值
5. 销毁栈S
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    struct Node *next;
} Node; //存储单个字符的链节点

Node *CreateNode() {
    //返回一个空节点
    Node *p = (Node*)malloc(sizeof(Node));

    return p;
} //CreateNode

typedef Node *QNode, *SNode;

typedef struct Queue {
    QNode front; //队头
    QNode rear; //队尾
}Queue, *QList; //包含队头队尾的链队列

typedef struct Stack {
    SNode top; //栈顶
} Stack, *SList; //包含栈顶的链栈

QList InitQueue() {
    //创建空队列Q并返回
    QList Q = (QList)malloc(sizeof(QNode));

    Q->front = CreateNode();
    Q->rear = CreateNode();
    Q->front->next = Q->rear; //队空时队头直接链接队尾

    return Q;
} //InitQueue

int QueueEmpty(QList Q) {
    //判断已存在的队列Q是否为空
    return Q->front->next == Q->rear;
} //QueueEmpty

void EnQueue(QList Q, char x) {
    //将元素x入队Q
    QNode p = CreateNode(), q = Q->front;

    p->data = x; //创建队列新节点
    while (q->next != Q->rear) q = q->next; //找到rear前一个节点
    p->next = Q->rear;
    q->next = p; //将新节点插入Q->rear前
} //EnQueue

char DeQueue(QList Q) {
    //返回非空队列Q的队头元素值后将队头节点出队
    QNode p;
    char x;

    if (!QueueEmpty(Q)) { //队列非空时执行
        p = Q->front->next;
        x = p->data; //获取队头元素值
        Q->front->next = p->next;
        free(p); //释放队头节点

        return x;
    } //if
} //DeQueue

void DestroyQueue(QList Q) {
    //销毁队列Q
    while (!QueueEmpty(Q)) DeQueue(Q); //逐个释放节点
    free(Q->front);
    free(Q->rear);
    free(Q); //将Q的结构彻底销毁
} //DestroyQueue


SList InitStack() {
    //创建空栈S并返回
    SList S = (SList)malloc(sizeof(Stack));

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
    SNode p = CreateNode();

    p->data = x; //创建栈新节点
    p->next = S->top->next;
    S->top->next = p; //将新节点插入S->top后
} //Push
char Pop(SList S) {
    //返回非空栈S的栈顶元素值后将栈顶节点出栈
    SNode p;
    char x;

    if (!StackEmpty(S)) { //栈非空时执行
        p = S->top->next;
        x = p->data; //获取栈顶元素值
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