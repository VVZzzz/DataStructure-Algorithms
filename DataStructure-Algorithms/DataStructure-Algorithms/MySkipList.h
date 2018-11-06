#pragma once
#include <iostream>
#include "MyRandom.hpp"
/**
 * ��Ծ���ʵ��
 */

//������: 16
static const int MAX_LEVEL = 16;
template <typename T>
class SkipList {
 public:
  SkipList() : rnd(0xdeadbeef) { createList(); }
  ~SkipList() { freeList(); }
  bool search(const T &key);
  bool insert(const T &key);
  bool delete (const T &key);
  size_t size() const { return size; }
  int GetCurrentLevel();

 private:
  void createList();
  void freeList();
  int createRndLevel();  //�������һ��level

  struct Node {
    T key;           //����ֵ
    Node **forward;  //�洢����һЩ����ָ������
    Node() : key(T()), forward(nullptr) {}
    Node(const T &k, const int level)
        : key(k), forward(level == 0 ? nullptr : new Node *[level]) {}
    ~Node() {
      if (forward) {
        delete[] forward;
        forward = nullptr;
      }
    }
  };
  int level;     //��Ծ�����,����MAX_LEVEL(��ʡ�ռ�)
  Node *header;  //��ͷ���
  Node *tail;    //��β���
  size_t size;   //Ԫ����Ŀ
  Random rnd;    //�����������
};

/**
 * ��Ծ����Ҳ���
 * ֻ������true false,���Լ��Ϸ��ص�ָ��
 */
template <typename T>
bool SkipList<T>::search(const T &key) {
  auto p = header;
  for (int i = level - 1; i >= 0; --i) {
    while (p->forward[i]->key < key) {
      p = p->forward[i];
      std::cout << p->key << std::endl;
    }
  }
  //��ʱ��pӦ����С��key�����Ԫ��
  p = p->forward[0];
  std::cout << p->key << std::endl;
  if (p->key == key) {
    return true;
  } else {
    return false;
  }
}

template <typename T>
bool SkipList<T>::insert(const T &key) {
  Node *update[MAX_LEVEL];  //��������Ѱ�ҵ�·��
  int i;
  Node *p = header;
  for (int i = level - 1; i >= 0; i--) {
    while (p->forward[i]->key < key) {
      std::cout << p->key << std::endl;
      p = p->forward[i];
    }
    update[i] = p;
  }
  p = p->forward[0];
  if (p->key == key) {
    std::cout << "There has been " << key << std::endl;
    return false;
  } else {
    int lv = rnd.randomInt(1, MAX_LEVEL);
    if (lv > level) {
      for (int i = level; i < lv; i++) update[i] = tail;
      level = lv;
    }

    // newһ���½ڵ�
    Node *toinsertp = new Node(key, lv);

    //����������forwardָ��
    for (int i = 0; i < lv; i++) {
      toinsertp->forward[i] = update[i]->forward[i];
      update[i]->forward[i] = toinsertp;
    }
    return true;
  }
}

template <typename T>
void SkipList<T>::createList() {
  tail = new Node(0x7fffffff, 0);
  header = new Node(0, MAX_LEVEL);
  for (int i = 0; i < MAX_LEVEL; i++) {
    header->forward[i] = tail;
  }
  size = 0;
  level = 1;
}

/**
 * �����Ծ�����
 * ��ÿһ��������delete forward[0]����
 */
template <typename T>
void SkipList<T>::freeList() {
  auto p = header->forward[0];
  while (p != tail) {
    auto q = p->forward[0];
    delete p;
    p = q;
  }
  delete header;  // delete Node* �����Node����������
  delete tail;
  size = 0;
}
