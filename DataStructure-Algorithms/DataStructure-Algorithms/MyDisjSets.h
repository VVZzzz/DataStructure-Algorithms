#pragma once
#include <vector>
/*
 * 不相交集类
 * key为结点值,value为其根的位置
 * find 操作:找到x的根
 * union操作:合并两个节点
 */
class MyDisjSets {
 public:
  explicit MyDisjSets(int numElements) : s(numElements, -1) {}

  //简单find,找出x的根
  int find_simple(int x) const;
  int find_simple(int x);
  //路径压缩的find
  int find_pathcompress(int x);
  //偏路径压缩的find
  int find_partialPathCompress(int x);

  //简单union,简单的把root1作为root2的根
  void unionSets_simple(int root1, int root2);
  //按大小求并
  void unionSets_size(int root1, int root2);
  //按高度求并
  void unionSets_height(int root1, int root2);

  //是否是全部连通
  bool isSingleTree();

 private:
  std::vector<int> s;
};

inline int MyDisjSets::find_simple(int x) const {
  if (s[x] < 0)
    return x;
  else
    return find_simple(s[x]);
}

inline int MyDisjSets::find_simple(int x) {
  if (s[x] < 0)
    return x;
  else
    return find_simple(s[x]);
}

inline int MyDisjSets::find_pathcompress(int x) {
  if (s[x] < 0)
    return x;
  else
    return s[x] = find_pathcompress(s[x]);
}

inline int MyDisjSets::find_partialPathCompress(int x) {
  if (s[x] < 0)
    return x;
  else {
    if (s[s[x]] < 0)
      return s[x];
    else {
      while (s[s[x]] >= 0) {
        int temp = s[x];
        s[x] = s[temp];
        x = temp;
      }
      return s[x];
    }
  }
}

inline void MyDisjSets::unionSets_simple(int root1, int root2) {
  if (root1 != root2) s[root2] = root1;
}

inline void MyDisjSets::unionSets_size(int root1, int root2) {
  if (root1 != root2) {
    if (s[root1] > s[root2]) {
      s[root2] += s[root1];
      s[root1] = root2;
    } else {
      s[root1] += s[root2];
      s[root2] = root1;
    }
  }
}

inline void MyDisjSets::unionSets_height(int root1, int root2) {
  if (root1 != root2) {
    if (s[root2] < s[root1])  // root2深度更深
      s[root1] = root2;
    else {
      if (s[root2] == s[root1]) {
        s[root1]--;
      }
      s[root2] = root1;
    }
  }
}

bool MyDisjSets::isSingleTree() {
  int c = 0;
  for (auto i : s) {
    if (i < 0) c++;
    if (c > 1) return false;
  }
  if (c == 1)
    return true;
  else
    return false;
}
