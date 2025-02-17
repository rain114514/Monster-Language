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
第一次设计可以分为以下五个部分：

1. 规则简化
2. 输入设计
3. 合法性检验
4. 错误处理
5. 翻译设计

下面将围绕这五个部分展开详细叙述。

## 规则简化
括号的处理规则较为复杂，故在第一次设计种，需要对输入进行限制；第一次设计中，输入的魔王语最多出现一层括号，不会出现多层括号。即形似`A(B(abcd)A)B`的魔王语言在第一次设计中属于非法输入，不会被程序翻译。

同时，注意到设计要求中的两条具体规则可以结合变形，最终变成两条从大写字母到小写字母串的具体规则：

- $B\rightarrow tsaedsae$
- $A\rightarrow sae$

这样转化后，两条规则都可以简单地用“遇到特定大写字母就输出特定小写字母字符串”的一步处理法实现。

## 输入设计
输入可以被视作一个以换行符`\n`结尾的字符串，但输入字符串的长度是未知的，故应将输入的各个字符逐个链接起来，构成类似链表的结构。

由于魔王语言的翻译是对输入字符串逐个字符地进行处理，故翻译过程中先输入的字符会先被处理，正符合队列“先进先出”的特性；因此，第一次设计中使用链队列存储输入的字符串，从而拥有对各种长度的字符串的兼容能力。

## 合法性检验
由于输入的不可干预性，不可能保证程序不接受到非法输入；因此在输入完成后，应当对得到的字符串进行合法性检验，确保程序翻译的字符串符合题目要求的同时能够被翻译。

输入字符串应当满足如下五条性质，否则无法得到结果：

- 不是空串
- 不包含非法字符
- 最多只有一层括号
- 括号必须全部匹配
- 括号内必须有字母

这五条性质可以分步检验，减少设计的压力并提升设计的条理性；而且这五条性质的检验方法非常简单，这里不再赘述。

## 错误处理
在合法性检验完成后，会得到一个参数，参数的值、其对应的含义以及处理方法可见下表：

| 参数值 | 参数含义 | 处理方法 |
| :------: | :------: | :------: |
| `1` | 输入合法 | 输出信息“该字符串合法” |
| `0` | 输入为空串 | 输出错误“该字符串为空串” |
| `-1` | 输入包含非法字符 | 输出错误“该字符串包含非法字符”，随后输出第`1`个非法字符及其位置 |
| `-2` | 输入包含多层括号 | 输出错误“该字符串包含多层括号” |
| `-3` | 输入有左括号匹配失败 | 输出错误“该字符串存在左括号匹配失败”，随后输出第`1`个匹配失败的左括号的位置 |
| `-4` | 输入有右括号匹配失败 | 输出错误“该字符串存在右括号匹配失败”，随后输出第`1`个匹配失败的右括号的位置 |
| `-5`` | 输入存在空心括号 | 输出错误“该字符串存在空心括号”，随后输出第`1`个空心括号的左括号的位置 |

## 翻译设计
总体来看，魔王语言的翻译可以分为两步：

1. 遍历字符串，将其中所有括号按照规则`(2)`消去
2. 遍历步骤`1`得到的无括号字符串，按照两条具体规则对大写字母进行替换

规则`(2)`需要借助栈实现括号内部分字符串的逆序排列，由于队列已经是链式结构，因此栈也采用链式结构实现。

# 第二次设计
第一次设计中认为输入只能有一层括号，实际上输入肯定不可能都只有一层括号，所以第二次设计的目标是解决多层括号的翻译问题。

第二次设计可分为以下两个部分：

1. 多层括号的处理
2. 其他模块的改动

下面将围绕这两个部分展开详细叙述。

## 多层括号的处理
想要翻译括号，需要先将括号内部的内容的括号处理掉，因此处理括号的步骤是具有递归性的。

而且不包含括号的字符串在经过消去括号的步骤后，不会发生任何变化，因此递归就拥有了自然的终点

根据递归性，可以设计出如下处理步骤：

1. 提取出括号内的字符串，不论有没有括号
2. 将提取出的字符串进行消去括号的处理
3. 根据规则`(2)`将去括号的字符串进行处理

消去括号的步骤就是上面`3`步，因此步骤`2`中的消去括号实际上是以提取出的字符串为基础，将步骤`1~3`再进行一次。

## 其他模块的改动
删除一种错误：字符串包含多层括号。参数值表修改成如下形式：

| 参数值 | 参数含义 | 处理方法 |
| :------: | :------: | :------: |
| 1 | 输入合法 | 输出信息“该字符串合法” |
| 0 | 输入为空串 | 输出错误“该字符串为空串” |
| -1 | 输入包含非法字符 | 输出错误“该字符串包含非法字符”，随后输出第`1`个非法字符及其位置 |
| -2 | 输入有左括号匹配失败 | 输出错误“该字符串存在左括号匹配失败”，随后输出第`1`个匹配失败的左括号的位置 |
| -3 | 输入有右括号匹配失败 | 输出错误“该字符串存在右括号匹配失败”，随后输出第`1`个匹配失败的右括号的位置 |
| -4 | 输入有空心括号 | 输出错误“该字符串存在空心括号”，随后输出第`1`个空心括号的左括号的位置 |