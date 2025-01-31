# 问题描述
有一个魔王总是使用自己的一种非常精炼而抽象的语言讲话，没有人能听得懂，但他的语言是可以逐步解释成人能听懂的语言，因为他的语言是由以下两种形式的规则由人的语言逐步抽象出来的：

1. $\alpha\rightarrow\beta_1\beta_2...\beta_m$
2. $(\theta\delta_1\delta_2...\delta_n)\rightarrow\theta\delta_n\theta\delta_{n-1}...\theta\delta_1\theta$

在两种形式中，从左到右均表示解释。

# 设计要求
用下述两条具体规则和上述规则形式`(2)`，试写一个魔王语言的解释系统，借助于栈和队列把他的话解释成人能听得懂的语言。

设大写字母表示魔王语言的词汇，小写字母表示人的语言词汇，希腊字母表示可以用大写字母或小写字母代换的变量。魔王语言可含人的词汇。

- $B\rightarrow tAdA$
- $A\rightarrow sae$

例如：`A(abcd)B`可解释为：`saeadacabatsaedsae`。

# 第一次设计
第一次设计可以分为以下部分：

1. 规则简化
2. 输入设计
3. 合法性检验
4. 错误处理
5. 翻译设计

下面将围绕这五个部分展开详细叙述。

## 规则简化
括号的处理规则较为复杂，故第一次设计对输入进行限制，认为输入的魔王语最多出现一层括号，不会出现多层括号。即形似`A(B(abcd)A)B`的魔王语在本次设计中属于非法输入，不会被程序翻译。

同时，注意到设计要求中的两条具体规则可以结合变形，最终变成两条从大写字母到小写字母串的具体规则：

- $B\rightarrow tsaedsae$
- $A\rightarrow sae$

## 输入设计
输入可以被视作一个以`\n`结尾的字符串，但字符串的长度是未知的，所以应当将输入的各个字符逐个链接起来，构成类似链表的结构。

由于翻译魔王语言是对输入字符串逐个字符地进行处理，故翻译过程中先输入的字符会先被处理，正符合队列“先进先出”的特性；因此，本次设计决定使用链式队列存储输入的字符串，达到对字符串存储的最佳兼容能力。

## 合法性检验
由于输入的不可干预性，不可能保证不出现非法输入；因此在输入完成后，应当对得到的字符串进行合法性检验，确保程序翻译的字符串能够被翻译。

字符串应当满足如下五条性质，否则无法得到结果：

- 不是空串
- 不包含非法字符
- 最多只有一层括号
- 括号必须全部匹配
- 括号内必须有字母

这五条性质可以分步检验，减少设计的压力并提升设计的条理性；而且这五条性质的检验方法非常简单，这里不再赘述。

## 错误处理
在合法性检验完成后，会得到一个参数，参数的值、其对应的含义以及处理方法可见下表：

| 参数值 | 参数含义 | 处理方法 |
| :-: | :-: | :-: |
| 1 | 字符串合法 | 输出信息“该字符串合法” |
| 0 | 字符串为空串 | 输出错误“该字符串为空串” |
| -1 | 字符串包含非法字符 | 输出错误“该字符串包含非法字符”，随后输出第一个非法字符及其位置 |
| -2 | 字符串包含多层括号 | 输出错误“该字符串包含多层括号” |
| -3 | 字符串存在左括号匹配失败 | 输出错误“该字符串存在左括号匹配失败”，随后输出第一个匹配失败的左括号的位置 |
| -4 | 字符串存在右括号匹配失败 | 输出错误“该字符串存在右括号匹配失败”，随后输出第一个匹配失败的右括号的位置 |
| -5 | 字符串存在没有内容的括号 | 输出错误“该字符串存在空括号”，随后输出第一个空括号的左括号的位置 |

## 翻译设计
总体来看，魔王语言的翻译可以分为两步：

1. 遍历字符串，将其中所有括号按照规则`(2)`处理掉
2. 遍历步骤1得到的无括号字符串，按照两条具体规则对大写字母进行替换

规则`(2)`需要借助栈实现括号内部分字符串的逆序排列，由于队列已经是链式结构，因此栈也采用链式结构实现。