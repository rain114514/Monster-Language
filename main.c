/*
本文件是主程序，包括以下内容：
1. 主函数实现代码
2. 其他功能函数代码
*/

#include "Queue & Stack.c"

QList GetString();
int IsLegal(char ch);
int CheckString(QList Q);
void ErrorPrint(QList Q, int E);

int main() {
    QList Q; //存储字符串
    int flag;

    Q = GetString(); //获得输入字符串
    flag = CheckString(Q); //合法性检查
    if (flag != 1) ErrorPrint(Q, flag); //显示字符串的非法之处
    else printf("The string is legal!\n");
} //main

QList GetString() {
    //获取一行内输入的字符串并存储到队列Q
    QList Q;
    char ch;

    Q = InitQueue();
    ch = getchar();
    while (ch != '\n') {
        EnQueue(Q, ch);
        ch = getchar();
    } //while

    return Q;
} //GetString

int IsLegal(char ch) {
    //判断字符ch是否合法
    return ch >= 'A' && ch <= 'B' || ch >= 'a' && ch <= 'z' || ch == '(' || ch == ')';
} //IsLegal

int CheckString(QList Q) {
    //对字符串Q进行合法性检验，并返回错误类型
    QNode p = Q->front->next;
    int Layer = 0, MaxLayer = 0;

    if (QueueEmpty(Q)) return 0;
    while (p != Q->rear) {
        if (!IsLegal(p->data)) return -1;
        if (p->data == '(') {
            Layer++;
            if (Layer > MaxLayer) MaxLayer = Layer;
        } else if (p->data == ')') {
            Layer--;
            if (Layer < 0) return -4;
        } //if
        p = p->next;
    } //while
    if (Layer != 0) return -3;
    else if (MaxLayer > 1) return -2;

    return 1;
} //CheckString

void ErrorPrint(QList Q, int E) {
    //根据字符串Q和错误类型E显示错误
    QNode p = Q->front->next;
    int pos = 1, Layer = 0, Lpos;

    switch (E) {
        case 0: { //输入为空
            printf("Error: EmptyInput!\n");
            break;
        } case -1: { //输入包含非法字符
            while (p != Q->rear && IsLegal(p->data)) {
                p = p->next;
                pos++; //找到第一个非法字符
            } //while
            printf("Error: Illegal character!\n");
            printf("The first illegal characher is %c, located at %d!\n", p->data, pos);
            break;
        } case -2: { //输入中包含多重括号
            while (p != Q->rear && Layer <= 1) {
                if (p->data == '(') Layer++;
                else if (p->data == ')') Layer--;
                p = p->next;
            } //while
            printf("Error: Too much bracket layer!\n");
            break;
        } case -3: { //输入中存在左括号匹配失败
            while (p != Q->rear) { //寻找第一个匹配失败的左括号
                if (p->data == '(') {
                    if (Layer == 0) Lpos = pos;
                    Layer++;
                } else if (p->data == ')') Layer--;
                p = p->next;
                pos++;
            } //while
            printf("Error: Unmatched left bracket!\n");
            printf("The first unmatched left bracket is at %d!\n", Lpos);
            break;
        } case -4: { //输入中存在右括号匹配失败
            while (p != Q->rear) { //寻找第一个匹配失败的右括号
                if (p->data == '(') Layer++;
                else if (p->data == ')') {
                    Layer--;
                    if (Layer < 0) break;
                } //if
                p = p->next;
                pos++;
            } //while
            printf("Error: Unmatched right bracket!\n");
            printf("The first unmatched right bracket is at %d!\n", pos);
            break;
        } default: break;
    } //switch
} //ErrorPrint