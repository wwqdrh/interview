## 91

`剑指 Offer II 091. 粉刷房子`

一排房子n个，可以涂成红色、蓝色、绿色这三种颜色中的一种，需要让各个颜色并不相同

给定一个花费数组，其中的每个元素就是该房子涂成红、蓝、绿三种颜色所需要的花费

计算粉刷完所有房子最少的花费成本


```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/4/binary_graph.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/4/binary_graph.go}}
<<<<<
```

## 92

`剑指 Offer II 092. 翻转字符`

一个`0 1`组成的字符串，求使得s单调递增(前面全是0 后面全是1)的最小翻转次数

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/4/01str_sort_minreplace.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/4/01str_sort_minreplace.go}}
<<<<<
```

## 93

`剑指 Offer II 093. 最长斐波那契数列`

给定一个递增的正整数数组，找到其中最长的一个满足斐波那契数列的元素

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/4/arr_subseq_fib.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/4/arr_subseq_fib.go}}
<<<<<
```

## 94

`剑指 Offer II 094. 最少回文分割`

给定一个字符串s，找到分割的最小次数，将s分割成字串，且每个字串都是回文串，

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/4/str_split_all_palindrom.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/4/str_split_all_palindrom.go}}
<<<<<
```

## 95

`剑指 Offer II 095. 最长公共子序列`

找到两个字符串的最长的公共子序列(即满足不改变字符的相对顺序的情况下删除某些字符)

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/4/twostr_long_common.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/4/twostr_long_common.go}}
<<<<<
```

## 96

`剑指 Offer II 096. 字符串交织`

判断两个字符串s1 s2交织(轮流选择元素)后是否与s3相等

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/4/twostr_x_equal_str.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/4/twostr_x_equal_str.go}}
<<<<<
```

## 97

`剑指 Offer II 097. 子序列的数目`

判断字符串s中有多少个子序列是在t中出现了

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/4/subseq_s_in_t_count.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/4/subseq_s_in_t_count.go}}
<<<<<
```

## 98

`剑指 Offer II 098. 路径的数目`

一个`m*n`的网格，从左上到右下，只能向下或者向右移动一步，问总共有多少条不同的路径。

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/4/grid_rb_path.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/4/grid_rb_path.go}}
<<<<<
```

## 99

`剑指 Offer II 099. 最小路径之和`

一个`m*n`的网格，从左上角到右下角的路径，使得路径上的数字总和为最小。

每次向下或者向右移动一步

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/4/grid_rb_path_minsum.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/4/grid_rb_path_minsum.go}}
<<<<<
```

## 100

`剑指 Offer II 100. 三角形中最小路径之和`

一个三角形的矩阵，从上往下找到最小路径之和

下标移动的时候只能移动到`i`以及`i+1`

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/4/triple_rb_minsum.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/4/triple_rb_minsum.go}}
<<<<<
```

## 101

`剑指 Offer II 101. 分割等和子集`

给定一个非空的正整数数组 nums ，请判断能否将这些数字分成元素和相等的两部分。


```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/4/arr_twopart_equal.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/4/arr_twopart_equal.go}}
<<<<<
```

## 102

`剑指 Offer II 102. 加减的目标值`

给定一个数组以及target值，提供正负符号使得数组中的和等于目标值

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/4/arr_addflag_sum_equal_target.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/4/arr_addflag_sum_equal_target.go}}
<<<<<
```

## 103

剑指 Offer II 103. 最少的硬币数目

给定不同面额的硬币 coins 和一个总金额 amount。编写一个函数来计算可以凑成总金额所需的最少的硬币个数。如果没有任何一种硬币组合能组成总金额，返回 -1。

每种硬币的数量是无限的。

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/4/dp_target_minitem.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/4/dp_target_minitem.go}}
<<<<<
```

## 104

剑指 Offer II 104. 排列的数目

给定一个由 不同 正整数组成的数组 nums ，和一个目标整数 target 。请从 nums 中找出并返回总和为 target 的元素组合的个数。数组中的数字可以在一次排列中出现任意次，但是顺序不同的序列被视作不同的组合。

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/4/dp_sum_target_subset.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/4/dp_sum_target_subset.go}}
<<<<<
```

## 105

`剑指 Offer II 105. 岛屿的最大面积`

01二维矩阵，全1代表陆地，找到岛屿的最大面积

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/4/grid01_max1.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/4/grid01_max1.go}}
<<<<<
```

## 106

`剑指 Offer II 106. 二分图`

二分图 定义：如果能将一个图的节点集合分割成两个独立的子集 A 和 B ，并使图中的每一条边的两个节点一个来自 A 集合，一个来自 B 集合，就将这个图称为 二分图 。

如果图是二分图，返回 true ；否则，返回 false 。

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/4/binarygraph_def.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/4/binarygraph_def.go}}
<<<<<
```

## 107

`剑指 Offer II 107. 矩阵中的距离`

一个01矩阵，找到每个元素距离其最近0的距离长度，结果用二维矩阵表达

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/4/grid01_each_min_distance.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/4/grid01_each_min_distance.go}}
<<<<<
```

## 108

`剑指 Offer II 108. 单词演变`

将单词从begin转换成end需要的最小步骤，并且每次的转换中间节点要在wordList中出现

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/4/str_trans_path.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/4/str_trans_path.go}}
<<<<<
```


## 109

`剑指 Offer II 109. 开密码锁`

四个环形波轮组成的锁，找到转到目标值target的最小转动次数，另外不能转动到deadends列表中的数据

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/4/str_trans_path_hasdead.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/4/str_trans_path_hasdead.go}}
<<<<<
```

## 110

`剑指 Offer II 110. 所有路径`

给定一个邻接矩阵结构，用于表示一个有向有环图，找到其中的所有的从0到n-1节点的路径

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/4/dir_cir_graph_allpath.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/4/dir_cir_graph_allpath.go}}
<<<<<
```

## 111

`剑指 Offer II 111. 计算除法`

给定一些已知变量除法获取到的值，提供数据查询结果

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/4/queryvalue_bybase.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/4/queryvalue_bybase.go}}
<<<<<
```

## 112

`剑指 Offer II 112. 最长递增路径`

给定一个 m x n 整数矩阵 matrix ，找出其中 最长递增路径 的长度。

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/4/matrix_asc_maxpath.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/4/matrix_asc_maxpath.go}}
<<<<<
```

## 113

`剑指 Offer II 113. 课程顺序`

总共n门课，并且有一些先后依赖顺序，返回要完成所有课程所需要的一个正确的课程顺序

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/4/graph_tuopu.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/4/graph_tuopu.go}}
<<<<<
```

## 114

`剑指 Offer II 114. 外星文字典`

通过已知的满足特定顺序的字符串数组，来推导出这个而特定的顺序

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/4/getsortrule_bybase.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/4/getsortrule_bybase.go}}
<<<<<
```

## 115

`剑指 Offer II 115. 重建序列`

https://leetcode.cn/problems/ur2n8P/?favorite=e8X3pBZi

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/4/resort_bybase.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/4/resort_bybase.go}}
<<<<<
```

## 116

`剑指 Offer II 116. 省份数量`

省份 是一组直接或间接相连的城市，组内不含其他没有相连的城市。

给你一个 n x n 的矩阵 isConnected ，其中 isConnected[i][j] = 1 表示第 i 个城市和第 j 个城市直接相连，而 isConnected[i][j] = 0 表示二者不直接相连。

返回矩阵中 省份 的数量。

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/4/unionfind_count.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/4/unionfind_count.go}}
<<<<<
```

## 117

`剑指 Offer II 117. 相似的字符串`

寻找一个字符串数组中，有多少个分组，这些分组里面都是同一种字母异位词。

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/4/unionfind_count_customrule.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/4/unionfind_count_customrule.go}}
<<<<<
```

## 118

`剑指 Offer II 118. 多余的边`

给定一个无向图，找到找出一条可以删除的边，使其变为树

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/4/nodir_graph_totree.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/4/nodir_graph_totree.go}}
<<<<<
```

## 119

`剑指 Offer II 119. 最长连续序列`

给定一个未排序的整数数组 nums ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。

要求时间复杂度为O(n)

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/4/arr_subset_asc_max.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/4/arr_subset_asc_max.go}}
<<<<<
```
