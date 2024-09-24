# 剑指offer

> 题库链接: https://leetcode.cn/problem-list/e8X3pBZi/

## 整数除法

`剑指 Offer II 001. 整数除法`

给定整数a、b，求得商的结果

条件:

1、不能使用除法、取余数等运算
2、只能存储32位有符号整数(范围是[-2^31,2^31-1])，如果溢出了就返回`2^31-1`

`解法`

- 处理边界条件，当a是最小值，判断b是1或者-1；当b是最小值，a是最小值则为1，其他都为0
- 使用二分法+快速乘来判断是否满足

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/1/intdevide.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/1/intdevide.go}}
<<<<<
```

## 2、

`剑指 Offer II 002. 二进制加法`

给定两个01字符串，求得加法字符串

`解法`

- 相对应下标(len-i-1)不断相加，计算商继续作为carry、模作为当前下标的值。

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/1/bstradd.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/1/bstradd.go}}
<<<<<
```

## 3、

`剑指 Offer II 003. 前 n 个数字二进制中 1 的个数`

给定一个数字n，从[0,n]中计算出二进制表示中1的个数

`解法`

- 计算一个数的二进制表示中有多少个1，`x>0`的循环条件中，能有多少次`x&=x-1`满足条件


```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/1/bitcount.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/1/bitcount.go}}
<<<<<
```

## 4、

`剑指 Offer II 004. 只出现一次的数字`

给定一个整数数组，其中一个元素出现了一次，其他元素出现了三次，找到那个只出现了一次的元素

要求: `O(n)`时间复杂度, `O(1)`空间复杂度

`解法`

- 将数组中的数字看成二进制格式，对于出现了三次的数字，他们对应的比特位数字和为0或者3，对于出现一次的数字，对应的比特位数字和为1或者4，将每一位的和取余所得到的余数就是结果对应的元素对应的位置。


```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/1/foundonetime.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/1/foundonetime.go}}
<<<<<
```


## 5、

`剑指 Offer II 005. 单词长度的最大乘积`

一个字符串数组，寻找满足 不包含相同字符 的两个字符串的长度乘积，找到满足条件的最大长度

`解法`

- 将字符串转为int类型mask来表示哪些字母是出现了的
- 使用位运算来判断是否存在相同的字符

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/1/unistr_maxlen.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/1/unistr_maxlen.go}}
<<<<<
```

## 6、

`剑指 Offer II 006. 排序数组中两个数字之和`

一个升序数组，找到其中的两个元素和为目标值，返回其目标下标。同一个数字不能使用两次，并且题目要求一定会存在满足条件的答案。


```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/1/target_twosum.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/1/target_twosum.go}}
<<<<<
```

## 7、

`剑指 Offer II 007. 数组中和为 0 的三个数`

给定一个整数数组，返回其中和为0的三元组，并且需要答案不能重复

`解法`

- 先进行排序，优化搜索条件
- 记得跳过相同的值，即相同的一段，只计算第一个进行剪枝。


```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/1/zero_threesum.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/1/zero_threesum.go}}
<<<<<
```

## 8、

`剑指 Offer II 008. 和大于等于 target 的最短子数组`

给定一个整数数组，寻找满足数组和大于target的一个最短连续子数组

`解法`

- 滑动窗口: 计算满足和大于目标值的最短子数组长度


```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/1/short_subarr.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/1/short_subarr.go}}
<<<<<
```

## 9、

`剑指 Offer II 009. 乘积小于 K 的子数组`

给定一个数组，寻找其中满足数组乘积小于k的子数组的个数


```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/1/mul_lessk_subarr.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/1/mul_lessk_subarr.go}}
<<<<<
```

## 10、

`剑指 Offer II 010. 和为 k 的子数组`

给定一个数组，寻找其中满足数组和为k的子数组的个数

`解法`

- 数组和在计算过程中需要记录下来，并且同时计算该数组和对应的个数


```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/1/sumk_subarr.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/1/sumk_subarr.go}}
<<<<<
```

## 11、

`剑指 Offer II 011. 0 和 1 个数相同的子数组`

给定一个只包含0和1的数组，找到其中含有相同`0和1`数量的最大长度的子数组

`解法`

- 使用map记录某个前缀和最左边的下标是多少

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/1/onezero_same_long.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/1/onezero_same_long.go}}
<<<<<
```

## 12、

`剑指 Offer II 012. 左右两边子数组的和相等`

找到数组的最左边的中心下标，中心下标是指以该下标为分界，左右数组元素和相同的下标

`解法`

- 判断`2 * 前缀和 + 当前值`是否等于数组总和

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/1/sep_two_array.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/1/sep_two_array.go}}
<<<<<
```

## 13、

`剑指 Offer II 013. 二维子矩阵的和`

给定一个二维矩阵，提供多次查询，计算子矩阵的和

`解法`

- 预处理(0,0)到(i,j)的子数组的和


```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/1/2matrix_sum.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/1/2matrix_sum.go}}
<<<<<
```

## 14、

`剑指 Offer II 014. 字符串中的变位词`

给定两个字符串，判断字符串的排列之一是否是另一个字符串的子串

`解法`

- 使用26长度的数组来保存字符情况

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/1/check_nosort_substr.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/1/check_nosort_substr.go}}
<<<<<
```

## 15、

`剑指 Offer II 015. 字符串中的所有变位词`

给定两个字符串，返回一个子串的所有变位形式判断在另一个字符串中是子串的话，就返回其起始下标

`解法`

- 26位长度数组
- 滑动窗口

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/1/all_nosort_substr.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/1/all_nosort_substr.go}}
<<<<<
```

## 16、

`剑指 Offer II 016. 不含重复字符的最长子字符串`

给定一个字符串，返回不包含重复字符的最长子字符串长度

`解法`

- 滑动窗口，记录在窗口中字符的个数


```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/1/norepeat_long_substr.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/1/norepeat_long_substr.go}}
<<<<<
```

## 17、

`剑指 Offer II 017. 含有所有字符的最短字符串`

给定两个字符串s和t，找到s中的一个最短字符串，包含t的所有字符，如果不存在这样的子字符串，则返回空字符串


```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/1/allch_short_substr.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/1/allch_short_substr.go}}
<<<<<
```

## 18、

`剑指 Offer II 018. 有效的回文`

给定一个字符串，验证是否是回文字符串, 只考虑字母和数字字符，可以忽略字母的大小写。

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/1/check_palindrome.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/1/check_palindrome.go}}
<<<<<
```

## 19、

`剑指 Offer II 019. 最多删除一个字符得到回文`

给定一个字符串，删除其中一个字符判断是否是回文


```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/1/check_delone_palindrome.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/1/check_delone_palindrome.go}}
<<<<<
```

## 20、

`剑指 Offer II 020. 回文子字符串的个数`

计算一个字符串中有多少个回文子字符串

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/1/cnt_palindrome_substr.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/1/cnt_palindrome_substr.go}}
<<<<<
```

## 21、

`剑指 Offer II 021. 删除链表的倒数第 n 个结点`

给定一个链表，删除链表的倒数第n个节点，并且返回头节点

`解法`

- 快慢指针

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/1/linklist_delone.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/1/linklist_delone.go}}
<<<<<
```

## 22、

`剑指 Offer II 022. 链表中环的入口节点`

给定一个数组形式的链表，数组中每个元素对应着下一个节点的下标，如果该链表没有环，就返回-1，如果有环，则返回环入口的下标

`解法`

- 快慢指针，当相遇了之后从当前以及初始位置以相同速度前进，当再次相遇就是环的入口

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/1/linklist_circlepoint.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/1/linklist_circlepoint.go}}
<<<<<
```

## 23、

`剑指 Offer II 023. 两个链表的第一个重合节点`

给定两个链表，题目保证该链式结构没有环，找到该两个链表的相交节点，如果不存在相交节点，就返回空

`解法`

- 链表走完了之后到另外一个上，这样到达相交节点的节点数相同，是会相遇的


```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/1/linklist_common_point.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/1/linklist_common_point.go}}
<<<<<
```

## 24、

`剑指 Offer II 024. 反转链表`

给定一个链式结构，反转后返回其头节点

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/1/linklist_reverse.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/1/linklist_reverse.go}}
<<<<<
```

## 25、

`剑指 Offer II 025. 链表中的两数相加`

使用两个链表表示非负整数，尾节点为个位数，返回两个链表的相加结果，并以链表形式返回

`解法`

- 将链表转为数组，然后计算完后进行重新构造成链表

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/1/linklist_add.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/1/linklist_add.go}}
<<<<<
```

## 26、

`剑指 Offer II 026. 重排链表`

给定一个链表结构，原始为'1 2 3 4 5 6 ... n-1 n' 修改为'1 n 2 n-1 3 n-2 ...'

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/1/linklist_x_sort.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/1/linklist_x_sort.go}}
<<<<<
```

## 27、

`剑指 Offer II 027. 回文链表`

给定一个链表结构，判断该链表是否是回文

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/1/linklist_palindrome.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/1/linklist_palindrome.go}}
<<<<<
```

## 28、

`剑指 Offer II 028. 展平多级双向链表`

将多级双向链表展平

这里多级双向链表就是包含前后指针，还包含子链表的指针，(其实就相当于链表)

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/1/linklist_flatten.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/1/linklist_flatten.go}}
<<<<<
```

## 29、

`剑指 Offer II 029. 排序的循环链表`

给定一个循环链表，它的值是单调非递减的，提供一个元素插入的方法，使得元素插入之后值依然是单调非递减的

`解法`

- 第一种情况 `cur.val <= val <= next.val`, 直接插入到这里
- 第二种情况 `cur.val > next.val`, 说明是链表遍历完了，break，直接加入到cur的后面

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/1/linklist_sort_insert.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/1/linklist_sort_insert.go}}
<<<<<
```

## 30、

`剑指 Offer II 030. 插入、删除和随机访问都是 O(1) 的容器`

创造一个数据结构，它的插入、删除、随机访问都是O(1)时间复杂度

`解法`

- 由于需要随机访问，所以将数据存储到数组中，通过对下标进行随机来进行访问
- 插入和删除也需要O(1), 使用map来存储值与下标
- 当删除的时候，将末尾的一个移动到要删除的位置并且更新下对应下标，然后数组只需要减一个长度即可

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/1/container_o1.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/1/container_o1.go}}
<<<<<
```