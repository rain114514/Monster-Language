# 问题描述
有一个魔王总是使用自己的一种非常精炼而抽象的语言讲话，没有人能听得懂，但他的语言是可以逐步解释成人能听懂的语言，因为他的语言是由以下两种形式的规则由人的语言逐步抽象出来的：

1. $\alpha\rightarrow\beta_1\beta_2...\beta_m$
2. $(\theta\delta_1\delta_2...\delta_n)\rightarrow\theta\delta_n\theta\delta_{n-1}...\theta\delta_1\theta$

在两种形式中，从左到右均表示解释。

# 设计要求
用下述两条具体规则和上述规则形式`(2)`，试写一个魔王语言的解释系统，借助于栈和队列把他的话解释成人能听得懂的语言。  
设大写字母表示魔王语言的词汇，小写字母表示人的语言词汇，希腊字母表示可以用大写字母或小写字母代换的变量。魔王语言可含人的词汇。

1. $B\rightarrow tAdA$
2. $A\rightarrow sae$

例如：`A(abcd)B`可解释为：`saeadacabatsaedsae`