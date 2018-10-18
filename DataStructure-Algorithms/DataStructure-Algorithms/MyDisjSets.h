#pragma once
#include <vector>
/*
 * ���ཻ����
 * keyΪ���ֵ,valueΪ�����λ��
 * find ����:�ҵ�x�ĸ�
 * union����:�ϲ������ڵ�
 */
class MyDisjSets {
 public:
  explicit MyDisjSets(int numElements) : s(numElements, -1) {}

  //��find,�ҳ�x�ĸ�
  int find_simple(int x) const;
  int find_simple(int x);
  //·��ѹ����find
  int find_pathcompress(int x);
  //ƫ·��ѹ����find
  int find_partialPathCompress(int x);

  //��union,�򵥵İ�root1��Ϊroot2�ĸ�
  void unionSets_simple(int root1, int root2);
  //����С��
  void unionSets_size(int root1, int root2);
  //���߶���
  void unionSets_height(int root1, int root2);

  //�Ƿ���ȫ����ͨ
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
    if (s[root2] < s[root1])  // root2��ȸ���
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
