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
QList PreTranslate(QList Q);
void Translate(QList Q);

int main() {
    //主函数
    QList Q; //用队列存储字符串
    int flag;

    while (1) {
        Q = GetString(); //获得输入字符串
        flag = CheckString(Q); //合法性检查
        if (flag != 1) ErrorPrint(Q, flag); //显示字符串的非法之处
        else { //字符串合法，进行翻译
            printf("The string is legal!\n");
            Translate(Q); //对字符串Q进行翻译并输出
        } //if
    } //while

    return 0;
} //main

QList GetString() {
    //获取一行内输入的字符串并存储到队列Q
    QList Q = InitQueue();
    char ch = getchar();

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
    int Layer = 0;

    if (QueueEmpty(Q)) return 0; //输入为空
    while (p != Q->rear) {
        if (!IsLegal(p->data)) return -1; //非法字符
        if (p->data == '(') Layer++;
        else if (p->data == ')') {
            Layer--;
            if (Layer < 0) return -3; //右括号匹配失败
        } //if
        p = p->next;
    } //while
    if (Layer != 0) return -2; //左括号匹配失败

    return 1; //合法
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
        } case -2: { //输入中存在左括号匹配失败
            while (p != Q->rear) { //寻找第一个匹配失败的左括号
                if (p->data == '(') {
                    if (Layer == 0) Lpos = pos; //记录最早匹配失败的左括号
                    Layer++;
                } else if (p->data == ')') Layer--;
                p = p->next;
                pos++;
            } //while
            printf("Error: Unmatched left bracket!\n");
            printf("The first unmatched left bracket is at %d!\n", Lpos);
            break;
        } case -3: { //输入中存在右括号匹配失败
            while (p != Q->rear) { //寻找第一个匹配失败的右括号
                if (p->data == '(') Layer++;
                else if (p->data == ')') {
                    Layer--;
                    if (Layer < 0) break; //匹配失败
                } //if
                p = p->next;
                pos++;
            } //while
            printf("Error: Unmatched right bracket!\n");
            printf("The first unmatched right bracket is at %d!\n", pos);
            break;
        } default: break; //其他情况不处理
    } //switch
    DestroyQueue(Q); //已经非法，直接销毁
} //ErrorPrint

QList PreTranslate(QList Q) {
    //翻译字符串Q内的所有括号(不替换魔王词汇)
    QList NQ = InitQueue(), TQ;
    SList S = InitStack();
    QNode p = Q->front->next;
    char ch, ch0;
    int Layer = 0;

    while (p != Q->rear) {
        if (p->data == '(') { //遇到左括号，开始处理括号
            Layer++;
            TQ = InitQueue(); //将括号内的内容装进去
            p = p->next;
            while (Layer > 0) {
                if (p->data == '(') Layer++;
                else if (p->data == ')') {
                    Layer--;
                    if (Layer == 0) break; //遇到对应右括号后退出
                } //if
                EnQueue(TQ, p->data);
                p = p->next; //括号内字符依次入子队列
            } //while
            TQ = PreTranslate(TQ); //将子串的括号处理掉
            ch = DeQueue(TQ); //取首位字符
            while (!QueueEmpty(TQ)) {
                ch0 = DeQueue(TQ);
                Push(S, ch0); //剩余字符依次入栈
            } //while
            EnQueue(NQ, ch);
            while (!StackEmpty(S)) { //按规则翻译
                ch0 = Pop(S);
                EnQueue(NQ, ch0);
                EnQueue(NQ, ch);
            } //while
            DestroyQueue(TQ); //子队列释放掉
        } else if (IsLegal(p->data)) { //不在括号内，直接入队
            EnQueue(NQ, p->data);
        } //if
        p = p->next;
    } //while
    DestroyQueue(Q); //原先的字符串释放掉
    DestroyStack(S); //栈也释放掉

    return NQ;
} //Translate1

void Translate(QList Q) {
    //翻译，先进行括号处理，随后替换
    QList NQ;
    QNode p;

    NQ = PreTranslate(Q);
    p = NQ->front->next;
    while (p != NQ->rear) {
        if (p->data >= 'a' && p->data <= 'z') {
            printf("%c", p->data);
        } else if (p->data == 'A') { //替换'A'
            printf("sae");
        } else if (p->data == 'B') { //替换'B'
            printf("tsaedsae");
        } //if
        p = p->next;
    } //while
    printf("\nSucceed to translate!\n");
    DestroyQueue(NQ); //销毁字符串
} //Translate