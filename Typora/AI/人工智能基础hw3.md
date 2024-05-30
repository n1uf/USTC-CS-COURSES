# 人工智能基础hw3

## 牛庆源 PB21111733

### 6.5 同时用带有前向检验、MRV和最少约束值启发式的回溯算法手工求解图6.2中的密码算数问题。

![](img\AI_figure6.2.png)

1. 由于$C_3 = F$且$F \neq 0$可以得到$C_3 = F = 1$。
1. 取$C_2 = 0$，由$C_1 + W + W = U + 10 \times C_2$即$C_1 + W + W = U$。
1. 取$C_1 = 0$，由$O + O = R + 10 \times C_1$即$O + O = R < 10$。又由于$T + T = O + 10$ 和 $alldiff$ 可知$O = 2/4$，取$O = 4$，则有$R = 8$和$T = 7$。
1. 由$C_1$和$C_2$取0，可以得到$W + W = U$，由$alldiff$可以得到$W = 3$且$U = 6$。
1. 该问题的解为：$F = 1$，$R = 8$，$T = 7$，$W = 3$，$U = 6$。



### 6.11 用AC-3算法说明弧相容对图6.1中问题能够检测出部分赋值 WA = green， V = red 的不相容。

![](img\AI_figure6.1.png)

1. 着色WA = green, V = red。
2. 移除WA-SA，SA$\neq$green。
3. 移除V-SA，SA$\neq$red，SA=blue。
4. 移除WA-NT，NT$\neq$green。
5. 移除NT-SA，NT$\neq$blue。
6. 移除NSW-V，NSW$\neq$red。
7. 移除NSW-SA，NSW$\neq$blue,NSW=green。
8. 移除NSW-Q，Q$\neq$green。
9. 移除SA-Q，Q$\neq$blue，Q=red。
10. 移除NT-Q，NT$\neq$red。
11. 则由4.5.10.NT没有可以选择的染色。
12. 得出 WA = green，V = red 不相容。



### 6.12用AC-3算法求解树结构CSP在最坏情况下的复杂度是多少？

最坏情况为遍历所有端点的每种取值。时间复杂度为$O(ED^2)$，其中E为边数，D为取值域最大的大小。