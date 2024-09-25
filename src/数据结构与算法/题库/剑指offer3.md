## 61、

`剑指 Offer II 061. 和最小的 k 个数对`

给定两个升序数组，找到前n小的数对

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/3/arr_minsum_k.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/3/arr_minsum_k.go}}
<<<<<
```

## 62、

`剑指 Offer II 062. 实现前缀树`

设计一个前缀树，提供数据插入，数据搜索，判断是否存在某个前缀

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/3/trie_teee.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/3/trie_tree.go}}
<<<<<
```

## 63、

`剑指 Offer II 063. 替换单词`

当一个词为另一个词的前缀那么称其为词根，后者称为继承词

给定一个词根数组，一个句子，将句子中的所有词语，如果存在其词根，那么就用词根进行替换

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/3/check_prefix_replace.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/3/check_prefix_replace.go}}
<<<<<
```

## 64、

`剑指 Offer II 064. 神奇的字典`

一个初始字符串列表，提供一个搜索方法，判断需要搜索的字符串进行一次字符替换后是否出现在初始字符串列表。

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/3/check_str_onereplace.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/3/check_str_onereplace.go}}
<<<<<
```

## 65、

`剑指 Offer II 065. 最短的单词编码`

> 暂时没理解到含义，详情查看https://leetcode.cn/problems/iSwD2y/?favorite=e8X3pBZi

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/3/short_word_encode.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/3/short_word_encode.go}}
<<<<<
```

## 66、

`剑指 Offer II 066. 单词之和`

提供两个方法，插入字符串以及个数，查询一个前缀所包含的值的大小。

如果该key已经存在则进行替换，给定一个字符串查询以该字符串为前缀的元素总和

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/3/trie_tree_count.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/3/trie_tree_count.go}}
<<<<<
```

## 67、

`剑指 Offer II 067. 最大的异或`

给定一个整数数组，两两元素进行异或，找到最大值

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/3/arr_xor_max.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/3/arr_xor_max.go}}
<<<<<
```

## 68、

`剑指 Offer II 068. 查找插入位置`

往一个有序数组中进行数据插入，查找数据的插入位置，要求使用O(logn)复杂度

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/3/sortarr_insert.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/3/sortarr_insert.go}}
<<<<<
```

## 69、

`剑指 Offer II 069. 山峰数组的顶部`

找到下标i，在i之前是递增数据，在i之后是递减数据

题目保证满足存在这样的i

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/3/arr_mountain_item.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/3/arr_mountain_item.go}}
<<<<<
```

## 70、

剑指 Offer II 070. 排序数组中只出现一次的数字

一个有序数组，有一个元素只出现一次，其他元素出现了两次，找到这个只出现了一次的元素，满足O(logn)时间复杂度，O(1)空间复杂度

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/3/sortarr_onlyone.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/3/sortarr_onlyone.go}}
<<<<<
```

## 71、

`剑指 Offer II 071. 按权重生成随机数`

按照值的大小作为权重占比进行随机数获取，返回其数据下标

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/3/weight_random.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/3/weight_random.go}}
<<<<<
```

```go

```

## 72、

`剑指 Offer II 072. 求平方根`

计算一个整数的开平方根，只取正数那一个

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/3/int_sqrt.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/3/int_sqrt.go}}
<<<<<
```

## 73、

`剑指 Offer II 073. 狒狒吃香蕉`

n堆香蕉，在h小时内要吃完，选择要吃完所有香蕉的最小速度，不过需要注意如果选择了一堆香蕉后，小于k个也会等待下一个小时才会继续吃。

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/3/arr_limith_mincost.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/3/arr_limith_mincost.go}}
<<<<<
```

## 74、

`剑指 Offer II 074. 合并区间`

给定一个元组数组，其中的元素即为一个左右区间，将所有重叠的区间进行合并，并返回一个不重叠的区间数组

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/3/combine_range.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/3/combine_range.go}}
<<<<<
```

## 75

`剑指 Offer II 075. 数组相对排序`

给定两个数组arr1和arr2，将arr1按照arr2的顺序进行排序，未出现过的就按照升序之后放在arr1的末尾。

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/3/arr_sort_base_arr2.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/3/arr_sort_base_arr2.go}}
<<<<<
```

## 76

`剑指 Offer II 076. 数组中的第 k 大的数字`

给定一个整数数组和整数，返回数组中第k个最大的元素

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/3/arr_kth_large.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/3/arr_kth_large.go}}
<<<<<
```

## 77

`剑指 Offer II 077. 链表排序`

对链表节点进行升序排序

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/3/linklist_sort.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/3/linklist_sort.go}}
<<<<<
```

## 78

`剑指 Offer II 078. 合并排序链表`

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/3/linklist_multi_merge.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/3/linklist_multi_merge.go}}
<<<<<
```

## 79

`剑指 Offer II 079. 所有子集`

给定一个元素各不相同的的数组，返回所有不重复的子集

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/3/uniquearr_subset.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/3/uniquearr_subset.go}}
<<<<<
```

## 80

`剑指 Offer II 080. 含有 k 个元素的组合`

给定整数n和k，返回`1...n`中所有可能的k个数的组合

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/3/irange_n_length_k.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/3/irange_n_length_k.go}}
<<<<<
```

## 81

`剑指 Offer II 081. 允许重复选择元素的组合`

从数组中寻找和为目标值的组合，数组中的元素可以重复选择

> 下面这种题解是标准解法，不过不能去除重复的情况，详情看82

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/3/arr_all_subset.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/3/arr_all_subset.go}}
<<<<<
```

## 82

`剑指 Offer II 082. 含有重复元素集合的组合`

与81题类似，不过这里元素只能使用一次

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/3/arr_once_subset.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/3/arr_once_subset.go}}
<<<<<
```

## 83

`剑指 Offer II 083. 没有重复元素集合的全排列`

给定一个不包含重复数字的整数数组，返回所有可能的全排列

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/3/uniquearr_all_subset.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/3/uniquearr_all_subset.go}}
<<<<<
```

## 84

`剑指 Offer II 084. 含有重复元素集合的全排列`

给定一个可包含重复数字的整数集合 nums ，按任意顺序 返回它所有不重复的全排列。

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/3/arr_unique_subset.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/3/arr_unique_subset.go}}
<<<<<
```

## 85

`剑指 Offer II 085. 生成匹配的括号`

正整数 n 代表生成括号的对数，请设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/3/genstr_quote_n.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/3/genstr_quote_n.go}}
<<<<<
```

## 86

`剑指 Offer II 086. 分割回文子字符串`

将字符串分割成回文串, 返回所有可能的方案

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/3/substr_palindrome_all.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/3/substr_palindrome_all.go}}
<<<<<
```

## 87

`剑指 Offer II 087. 复原 IP`

将字符串格式化成所有合法的ipv4地址

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/3/repair_ipv4.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/3/repair_ipv4.go}}
<<<<<
```

## 88

`剑指 Offer II 088. 爬楼梯的最少成本`

给定一个一维数组表示爬楼梯需要的成本，并且每次支付一次就可以往上爬一个阶梯或者爬两个阶梯, 计算爬楼梯的最少成本。

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/3/dp_mincost.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/3/dp_mincost.go}}
<<<<<
```

## 89

`剑指 Offer II 089. 房屋偷盗`

给定一个一维数组表示每间房子的价值，不能偷相邻的两家，问能够偷窃到的最高金额

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/3/dp_maxvalue.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/3/dp_maxvalue.go}}
<<<<<
```

## 90

`剑指 Offer II 090. 环形房屋偷盗`

与上一题类似，不过这一题房屋是首位相连的，问能够偷窃到的最大价值


```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/3/dp_circle_maxvalue.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/3/dp_circle_maxvalue.go}}
<<<<<
```
