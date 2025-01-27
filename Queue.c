/*
本文件用于实现链队列及其操作，内容包括：
1. 链队列结构体的定义和名称
2. 链队列基本操作实现代码
链队列的基本操作包括：
1. 创建空队列Q
2. 判断队列Q是否为空
3. 将元素x入队
4. 出队列并返回队头元素值
5. 直接返回队头元素值
6. 销毁队列Q
*/

#include "Node.c"

typedef struct Queue {
    QNode front; //队头
    QNode rear; //队尾
}Queue, *QList;

QList InitQueue() {
    //创建空队列Q并返回
    QList Q;

    Q = (QList)malloc(sizeof(QNode));
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
    QNode p, q = Q->front;

    p = CreateNode();
    p->data = x; //创捷队列节点
    while (q->next != Q->rear) q = q->next; //找到队尾前一个节点
    p->next = Q->rear;
    q->next = p; //将节点插入Q->rear前
} //EnQueue

char GetFront(QList Q) {
    //返回非空队列队头元素值
    if (!QueueEmpty(Q)) return Q->front->next->data;
} //GetFront

char DeQueue(QList Q) {
    //返回非空队列队头元素值后将队头节点出栈
    QNode p;
    char x;

    if (!QueueEmpty(Q)) {
        x = GetFront(Q);
        p = Q->front->next;
        Q->front->next = p->next;
        free(p); //释放队头节点

        return x;
    } //if
} //DeQueue

void DestroyQueue(QList Q) {
    //销毁队列Q
    while (!QueueEmpty(Q)) DeQueue(Q);
    free(Q->front);
    free(Q->rear);
    free(Q); //将Q的结构彻底销毁
} //DestroyQueue