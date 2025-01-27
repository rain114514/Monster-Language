/*
本文件用于实现链节点结构，内容包括：
1. 链节点结构体的定义和名称
2. 链节点的部分操作实现代码
3. 链队列和链栈操作实现所需头文件
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data; //数据是单个字符
    struct Node *next; //链指针
} Node, *QNode, *SNode;

Node *CreateNode() {
    //返回一个空节点
    Node *p;

    p = (Node*)malloc(sizeof(Node));

    return p;
} //CreateNode