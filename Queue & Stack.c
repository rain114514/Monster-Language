#include <stdio.h>
#include <stdlib.h>

typedef struct Node { //定义链节点
    char data;
    struct Node *next;
} Node, *QNode, *SNode;

typedef struct Queue { //定义链队列
    QNode front;
    QNode rear;
} Queue, *QList;

typedef struct Stack { //定义链栈
    SNode top;
} Stack, *SList;

Node *InitNode() {
    //返回一个空链节点
    Node *p = (Node*)malloc(sizeof(Node));

    return p;
} //InitNode

QList InitQueue() {
    //返回一个空链队列
    QList Q = (QList)malloc(sizeof(Queue));

    Q->front = (QNode)malloc(sizeof(Node));
    Q->rear = (QNode)malloc(sizeof(Node));
    Q->front->next = Q->rear; //空链队列中, front->next = rear

    return Q;
} //InitQueue

int QueueEmpty(QList Q) {
    //返回链队列Q是否为空
    return Q->front->next == Q->rear;
} //QueueEmpty

void EnQueue(QList Q, char ch) {
    //将字符ch推入链队列Q
    QNode p = (QNode)malloc(sizeof(Node)), q = Q->front;

    p->data = ch; //创建新节点存放ch
    while (q->next != Q->rear) q = q->next; //找到rear前一个节点
    q->next = p;
    p->next = Q->rear; //将p插入rear前
} //EnQueue

char DeQueue(QList Q) {
    //将链队列Q的队头元素拉出
    QNode p;
    char ch;

    if (!QueueEmpty(Q)) { //链队列Q非空
        p = Q->front->next;
        ch = p->data; //取出队头元素值
        Q->front->next = p->next;
        free(p); //释放队头节点

        return ch;
    } //if
} //DeQueue

void DestroyQueue(QList Q) {
    //将链队列Q彻底销毁
    while (!QueueEmpty(Q)) DeQueue(Q); //释放所有节点
    free(Q->front);
    free(Q->rear);
    Q = NULL; //彻底销毁Q的结构
} //DestroyQueue

SList InitStack() {
    //返回一个空链栈
    SList S = (SList)malloc(sizeof(Stack));

    S->top = (SNode)malloc(sizeof(Node));
    S->top->next = NULL; //空链栈中, top->next = NULL

    return S;
} //InitStack

int StackEmpty(SList S) {
    //返回链栈S是否为空
    return S->top->next == NULL;
} //StackEmpty

void Push(SList S, char ch) {
    //将字符ch压入链栈S
    SNode p = (SNode)malloc(sizeof(Node));

    p->data = ch; //创建新节点存放ch
    p->next = S->top->next;
    S->top->next = p; //将p插入top后
} //Push

char Pop(SList S) {
    //将链栈S的栈顶元素弹出
    SNode p;
    char ch;

    if (!StackEmpty(S)) { //链栈S非空
        p = S->top->next;
        ch = p->data; //弹出栈顶元素值
        S->top->next = p->next;
        free(p); //释放栈顶节点

        return ch;
    } //if
} //Pop

void DestroyStack(SList S) {
    //彻底销毁链栈S
    while (!StackEmpty(S)) Pop(S);
    free(S->top);
    S = NULL; //彻底销毁S的结构
} //DestroyStack