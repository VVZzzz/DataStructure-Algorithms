#pragma once
#include <iostream>
#include "MyRandom.hpp"
/**
 * 跳跃表的实现
 * insert(key): O(logN)
 * deleteNode(key): O(logN)
 * search(key): O(logN)
 */

//最大层数: 16
static const int MAX_LEVEL = 16;
template <typename T>
class SkipList {
 public:
  SkipList() : rnd(0xdeadbeef) { createList(); }
  ~SkipList() { freeList(); }
  bool search(const T &key);
  bool insert(const T &key);
  bool deleteNode(const T &key);
  size_t size() const { return size; }
  int GetCurrentLevel() const { return level; }

 private:
  void createList();
  void freeList();
  int createRndLevel();  //随机生成一个level

  struct Node {
    T key;           //结点键值
    Node **forward;  //存储到下一些结点的指针数组
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
  int level;     //跳跃表层数,不是MAX_LEVEL(节省空间)
  Node *header;  //表头结点
  Node *tail;    //表尾结点
  size_t size;   //元素数目
  Random rnd;    //随机数生成器
};

/**
 * 跳跃表查找操作
 * 只返回了true false,可以加上返回的指针
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
  //此时的p应该是小于key的最大元素
  p = p->forward[0];
  std::cout << p->key << std::endl;
  if (p == tail || p->key == key) {
    return true;
  } else {
    return false;
  }
}

template <typename T>
bool SkipList<T>::insert(const T &key) {
  Node *update[MAX_LEVEL];  //用来保存寻找的路径
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
  if ( p->key == key) {
    std::cout << "There has been " << key << std::endl;
    return false;
  } else {
    int lv = createRndLevel();
    if (lv > level) {
      for (int i = level; i < lv; i++) update[i] = tail;
      level = lv;
    }

    // new一个新节点
    Node *toinsertp = new Node(key, lv);

    //更新链结点的forward指针
    for (int i = 0; i < lv; i++) {
      toinsertp->forward[i] = update[i]->forward[i];
      update[i]->forward[i] = toinsertp;
    }
    return true;
  }
}

template <typename T>
bool SkipList<T>::deleteNode(const T &key) {
  Node *update[MAX_LEVEL];
  auto p = header;
  for (int i = level - 1; i >= 0; i--) {
    while (p->forward[i]->key < key) {
      p = p->forward[0];
    }
    update[i] = p;
  }
  p = p->forward[0];
  //此时p即为要删除的结点
  if (p == tail || p->key != key) {
    std::cout << "can't find the key !" << std::endl;
    return false;
  } else {
    for (int i = 0; i < level; i++) {
      //将p的前驱结点的后继更新为p的后继结点
      if (update[i]->forward[i] != p) break;
      update[i]->forward[i] = p->forward[i];
    }
    delete p;

    //更新level,因为删除结点可能会导致level多了,浪费空间
    while (level > 0 && (header->forward[level - 1] == tail)) {
      level--;
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
 * 清除跳跃表操作
 * 对每一个结点进行delete forward[0]即可
 */
template <typename T>
void SkipList<T>::freeList() {
  auto p = header->forward[0];
  while (p != tail) {
    auto q = p->forward[0];
    delete p;
    p = q;
  }
  delete header;  // delete Node* 会调用Node的析构函数
  delete tail;
  size = 0;
}

template <typename T>
int SkipList<T>::createRndLevel() {
  return rnd.randomInt(1, MAX_LEVEL);
}
