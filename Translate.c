#include "Queue & Stack.c"

QList GetString();
int IsLegal(char ch);
int CheckString(QList Q);
void ErrorPrint(QList Q, int E);
QList PreTranslate(QList Q);
void Translate(QList Q);

int main() {
    //主函数，程序的主体
    QList Q;
    int F;

    while (1) {
        Q = GetString();
        F = CheckString(Q);
        if (F != 1) ErrorPrint(Q, F); //非法字符串
        else { //合法字符串
            printf("The string is legal!\n");
            Translate(Q);
        } //if
    } //while

    return 0;
} //main

QList GetString() {
    //返回输入的字符串, 存储到链队列中
    QList Q = InitQueue();
    char ch = getchar();

    while (ch != '\n') { //获取一行内的字符
        EnQueue(Q, ch);
        ch = getchar();
    } //while

    return Q;
} //GetString

int IsLegal(char ch) {
    //返回字符ch是否合法
    return ch >= 'a' && ch <= 'z' || ch == 'A' || ch == 'B' || ch == '(' || ch <= ')';
} //IsLegal

int CheckString(QList Q) {
    //返回链队列Q存储的字符串是否合法
    QNode p = Q->front->next;
    int Layer = 0;

    if (QueueEmpty(Q)) return 0; //字符串为空串
    while (p != Q->rear) { //检查是否包含非法字符
        if (!IsLegal(p->data)) return -1; //包含非法字符
        p = p->next;
    } //while
    p = Q->front->next;
    while (p != Q->rear) { //检查是否包含多层括号
        if (p->data == '(') { //左括号
            if (Layer == 1) return -2; //多层括号
            Layer++;
        } else if (p->data == ')') Layer--; //右括号
        p = p->next;
    } //while
    p = Q->front->next;
    Layer = 0;
    while (p != Q->rear) { //检查是否存在括号匹配失败
        if (p->data == '(') Layer++; //左括号
        else if (p->data == ')') { //右括号
            if (Layer == 0) return -4; //右括号匹配失败
            Layer--;
        } //if
        p = p->next;
    } //while
    if (Layer > 0) return -3; //左括号匹配失败
    p = Q->front->next;
    while (p->next != Q->rear) { //检查是否存在括号为空
        if (p->data == '(' && p->next->data == ')') return -5; //存在括号为空
        p = p->next;
    } //while

    return 1;
} //CheckString

void ErrorPrint(QList Q, int E) {
    QNode p = Q->front->next;
    int pos = 1, Lpos, Layer = 0;

    switch (E) { //根据错误类型输出
        case 0: { //字符串为空串
            printf("Error: Empty Input!\n");
            break;
        } case -1: { //字符串包含非法字符
            printf("Error: Illegal character!\n");
            while (p != Q->rear) { //找到第一个非法字符
                if (!IsLegal(p->data)) break; //非法字符
                p = p->next;
                pos++;
            } //while
            printf("The first illegal character is %c, located at %d!\n", p->data, pos);
            break;
        } case -2: { //字符串包含多层括号
            printf("Error: Too much layers of brackets!\n");
            break;
        } case -3: { //字符串存在匹配失败的左括号
            printf("Error: Unmatched left bracket!\n");
            while (p != Q->rear) { //找到第一个匹配失败的左括号
                if (p->data == '(') { //左括号
                    if (Layer == 0) Lpos = pos; //最外层左括号
                    Layer++;
                } else if (p->data == ')') Layer--; //右括号
                p = p->next;
                pos++;
            } //while
            printf("The first unmatched left bracket locates at %d!\n", Lpos);
            break;
        } case -4: { //字符串存在匹配失败的右括号
            printf("Error: Unmatched right bracket!\n");
            while (p != Q->rear) { //找到第一个匹配失败的右括号
                if (p->data == '(') Layer++; //左括号
                else if (p->data == ')') { //右括号
                    if (Layer == 0) break; //右括号匹配失败
                    Layer--;
                } //if
                p = p->next;
                pos++;
            } //while
            printf("The first unmatched right bracket locates at %d!\n", pos);
            break;
        } case -5: { //字符串存在空括号
            printf("Error: Empty brackets!\n");
            while (p->next != Q->rear) { //找到第一个空括号
                if (p->data == '(' && p->next->data == ')') break;
                p = p->next;
                pos++;
            } //while
            printf("The first empty bracket locates at %d!\n", pos);
            break;
        } //case
    } //switch
    DestroyQueue(Q);
} //ErrorPrint

QList PreTranslate(QList Q) {
    //将链队列Q存储的字符串的括号处理掉后返回
    QList NQ = InitQueue();
    SList S = InitStack();
    char ch0, ch;

    while (!QueueEmpty(Q)) { //遍历所有字符
        ch = DeQueue(Q);
        if (ch == '(') { //左括号
            ch0 = DeQueue(Q);
            ch = DeQueue(Q);
            while (ch != ')') { //右括号之前的字符都入栈S
                Push(S, ch);
                ch = DeQueue(Q);
            } //while
            EnQueue(NQ, ch0);
            while (!StackEmpty(S)) { //栈S内字符全出栈
                ch = Pop(S);
                EnQueue(NQ, ch);
                EnQueue(NQ, ch0);
            } //while
        } else if (ch >= 'a' && ch <= 'z' || ch == 'A' || ch == 'B') EnQueue(NQ, ch); //其他字符直接入队NQ
    } //while
    DestroyQueue(Q);
    DestroyStack(S); //销毁队列Q和栈S

    return NQ;
} //PreTranslate

void Translate(QList Q) {
    //翻译字符串Q
    char ch;

    Q = PreTranslate(Q); //预翻译处理括号
    while (!QueueEmpty(Q)) { //遍历所有字符
        ch = DeQueue(Q);
        if (ch >= 'a' && ch <= 'z') printf("%c", ch); //小写字母
        else if (ch == 'A') printf("sae"); //大写字母A
        else if (ch == 'B') printf("tsaedsae"); //大写字母B
    } //while
    printf("\nSucceed to translate!\n");
    DestroyQueue(Q);
} //Translate