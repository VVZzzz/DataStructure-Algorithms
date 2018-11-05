#pragma once
#include <math.h>
#include <vector>
using namespace std;

//前置声明模板类
template <typename T>
class Matrix;

/*
 *计算矩阵乘法的最优排序。
 * 递归式为M(left,right)=min{M(left,i)+M(i+1,right)+C(left-1)*C(i)*C(Right)}
 * (left<=i<right)
 * c包含n个矩阵中每个矩阵的列数。
 * c [0]是矩阵1中的行数。
 *
 * m[left][right]保存矩阵A(left)*A(left+1)*...
 * A(right-1)A(right)乘法所需要的最小乘法数
 *
 *
lastChange保存最小乘法数的路径,即:(A(left)...A(i))*(A(i+1)...A(right))这样是乘法数最小
 * m和lastChange从1开始索引，而不是0。
 * 注意：m和lastChange主要对角线下方的条目无意义且未初始化。
 */
template <typename T>
void optMatrix(const vector<int> &c, Matrix<long> &m, Matrix<int> &lastChange) {
  int n = c.size() - 1;
  for (int left = 1; left <= n; left++) {
    m[left][left] = 0;
  }
  for (int k = 1; k < n; k++)
    for (int left = 1; left <= n - k; left++) {
      int right = left + k;
      m[left][right] = LONG_MAX;
      for (int i = left; i < right; i++) {
        long thisCost =
            m[left][i] + m[i + 1][right] + c[left - 1] * c[i] * c[right];
        if (thisCost < m[left][right]) m[left][right] = thisCost;
        lastChange[left][right] = i;
      }
    }
}

/**
  * 计算所有最短路径。
  * a包含邻接矩阵，其中[i] [i]假定为零。
  * d包含最短路径的值。
  * 顶点从0开始编号; 所有数组都有相同的维度。 如果d [i]
[i]被设置为负值，则存在负循环。   * 可以使用path [] []计算实际路径。   *
NOT_A_VERTEX为-1  */
void allParis(const Matrix<int> &a, Matrix<int> &d, Matrix<int> &path) {
  int n = a.numrows();
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      d[i][j] = a[i][j];
      path[i][j] = -1;
    }
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (d[i][k] + d[k][j] < d[i][j]) {
          d[i][j] = d[i][k] + d[k][j];
          path[i][j] = k;
        }
      }
    }
  }
}