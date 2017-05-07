## phase5



1. 应该输入一个字符串，可以知道字符串长度为6；rbx是这个字符串所在位置；

![1](C:\Users\Administrator\Desktop\bomb\1.png)

2. 从最下面可以知道，这一段是循环，循环六次跳出；从+41开始，首先是rbx+rax所指向的值赋予给ecx，ecx的低八位赋给rsp的所指向的地址，然后再赋值给rdx，然后将这个值的低八位再赋值给rsp+rax+16;<br>

   总结一下，由于rbx存着输入字符串的地址，eax贡献了从0~5的偏移，也就是把输入字符串的六个字符分别赋值给rdx，然后通过与0xf与操作，取出低4位，这个值作为偏移量取0x4024b0后某个变量的值，将这个变量的低八位放到rsp+rax+16上，也就是循环结束时，rsp+16 ～ rsp+21 这6个字节上存储着从0x4024b0开始的一段地址内搬运来的6个变量。

![2](C:\Users\Administrator\Desktop\bomb\2.png)

3. 紧接着是比较新的字符串和0x40245e内的字符串是否相等，如果相等，则返回0，成功跳出函数

![3](C:\Users\Administrator\Desktop\bomb\3.png)

4. 查看0x4024b0和0x40245e的值，计算偏移量为9 15 14 5 6 7，对应的二进制1001 1111 1100 0101 0110 0111<br>

   然后查看ascii码表，找出对应的低四位为上面哪几个字符就好，例如9FC567

![4](C:\Users\Administrator\Desktop\bomb\4.png)

## phase6

参考资料：http://blog.csdn.net/jason_ranger/article/details/51593255

第六个非常长啊。。。。看了我好久，还好有前人的解题报告可以参考；<br>

首先：

![p6_1](C:\Users\Administrator\Desktop\bomb\p6_1.png)

第一部分，函数（read_six_numbers）将输入两个数字存在**rsp**连续的24个字节中；然后将rsp存在r14中，r12被赋值0；r13所指的值是第一个输入数<br>

开始while循环，将r13的值赋予rbp，r13所指的值赋给eax，然后eax-1要小于或者等于5，则输入第一个数要小于或者等于6；然后r12加1，与6比较(while循环6次)，然后将r12赋值给**ebx**，再将其赋值给eax（也就是由1~6）；接着rsp+4*rax与rbp（rbp与r13挂钩）比较，必须不想等，否则bomb；如果成功跳过，ebx+1与5比较（for循环）；这一段就是num1要与num2,num3,num4,num5,num6都不相等；<br>

然后r13加4，也就是，重复while循环，num2分别与num3,num4,num5,num6都不相等。。。。。。。。。<br>



第二部分：

![p6_2](C:\Users\Administrator\Desktop\bomb\p6_2.png)

就是把输入的六个数变为7-num，例如1，2，3，4，5，6变为6，5，4，3，2，1

第三部分：

![p7_2](C:\Users\Administrator\Desktop\bomb\p7_2.png)

这一部分是参考上述链接的：

如果小于等于1则跳到401183：edx赋成0x6032d0，rdx被赋给rsp+2*rsi+32所指向的为止，然后rsi加上4，与24比较，如果相等则跳出这个循环，否则将ecx被赋值成rsp+rsi所指向的值，继续与1比较的过程<br>

不妨假设我们输入的第一个数就是6，所以从401174跳到401197，ecx到这里变成了1，这样满足40119d的跳跃条件，跳到401183，edx赋成6032d0，然后把rdx存到rsp+32的位置（这时rsi是0），然后rsi加上4;<br>

这时可以查看0x6032d0及其后面连续的地址存着什么：

![num](C:\Users\Administrator\Desktop\bomb\num.png)

例如我们输入的1，2，3，4，5，6，7-num之后，链表顺序变为node6，node5，node4，node3，node2，node1

第四部分是将其连起来：

![p6_3](C:\Users\Administrator\Desktop\bomb\p6_3.png)

第五部分：

![p6_4](C:\Users\Administrator\Desktop\bomb\p6_4.png)

这首先把eax赋值成rbx+8的值（rbx在上一个循环中等于rsp+32，第一个节点的地址），然后将eax与rbx所指的结点比较，这里是一个循环，循环五次，依次将前一个结点与后一个比较，要求前面的更大；<br>

观察第三部分的第二张图，可以知道重排链表是: node3 node4 node5 node6 node1 node2；由于7-num；因此输入的是**4 3 2 1 6 5**；

