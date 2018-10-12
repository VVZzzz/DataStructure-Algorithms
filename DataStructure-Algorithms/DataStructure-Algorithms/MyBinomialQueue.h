#pragma once
#include <iostream>
#include <stdexcept>
#include <vector>
//�������,�ɶ������������,��vector��������������ĸ�
template <typename T>
class MyBinomialQueue {
 public:
  MyBinomialQueue() {}
  MyBinomialQueue(const MyBinomialQueue &rhs);
  MyBinomialQueue(const T &item);
  ~MyBinomialQueue();

  bool isEmpty() const;
  const T &findMin() const;
  // int getSize() const { return theTrees.size(); }

  void insert(const T &x);
  // 6.34 insert2Ϊ������merge�ĸ�Ч����
  void insert2(const T &x);
  void deleteMin();
  void deleteMin(T &minItem);

  void makeEmpty();
  void merge(MyBinomialQueue &rhs);

  const MyBinomialQueue &operator=(const MyBinomialQueue &rhs);

 private:
  //��������ж������Ľڵ�
  struct BinomialNode {
    T data;
    BinomialNode *left;
    BinomialNode *nextSibling;
    BinomialNode(const T &element, BinomialNode *l, BinomialNode *n)
        : data(element), left(l), nextSibling(n) {}
    BinomialNode() : data(T()), left(nullptr), nextSibling(nullptr) {}
  };
  enum { DEFAULT_TREES = 1 };
  int currentSize;                       // vector�е�ǰ�Ľڵ���
  std::vector<BinomialNode *> theTrees;  // An array of tree roots;

  int findMinIndex() const;
  // capacity()���������˼�Ʋ�Ϊ��vector�ܷŵ����Ľڵ���
  int capacity() const {
    int num = 1;
    for (int i = 0; i < theTrees.size(); i++) {
      num <<= 1;
    }
    return --num;
  }

  BinomialNode *combineTrees(BinomialNode *t1, BinomialNode *t2) {
    if (t2->data < t1->data) return combineTrees(t2, t1);
    t2->nextSibling = t1->left;
    t1->left = t2;
    return t1;
  }
  void makeEmpty(BinomialNode *&t);
  BinomialNode *clone(BinomialNode *t) const {
    if (t == nullptr) return nullptr;
    return new BinomialNode(t->data, clone(t->left), clone(t->nextSibling));
  }
};

template <typename T>
inline void MyBinomialQueue<T>::insert(const T &x) {
  merge(MyBinomialQueue(x));
}

template <typename T>
void MyBinomialQueue<T>::insert2(const T &x) {
  if (theTrees[0] == nullptr) {
    theTrees[0] = new BinomialNode(x, nullptr, nullptr);
    return;
  }
  size_t i = 0;
  BinomialNode *res = new BinomialNode(x, nullptr, nullptr);
  for (; size_t i < theTrees.size(); i++) {
    if (theTrees[i] == nullptr) break;
  }
  if (i == theTrees.size()) theTrees.push_back(nullptr);
  for (size_t j = 0; j < i; j++) {
    if (res->data < theTrees[j]->data) {
      theTrees[j]->nextSibling = res->left;
      res->left = theTrees[j];
    } else {
      res->nextSibling = theTrees[j]->left;
      theTrees[j]->left = res;
      res = theTrees[j];
    }
    theTrees[j] = nullptr;
  }
  theTrees[j] = res;
}

template <typename T>
inline void MyBinomialQueue<T>::deleteMin() {
  try {
    if (empty()) throw std::underflow_error("the BinomialQueue is empty!");
  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  int minIndex = findMinIndex();
  // minItem = theTrees[minIndex]->data;
  BinomialNode *oldminTree = theTrees[minIndex];
  BinomialNode *newminTree = oldminTree->left;
  delete oldminTree;

  //��ɾ�����ڵ���ǿ����ŵ�һ���µĶ��������
  MyBinomialQueue newQueue;
  newQueue.theTrees.resize(minIndex + 1);
  newQueue.currentSize = (1 << minIndex) - 1;
  for (int i = minIndex - 1; i >= 0; i--) {
    newQueue.theTrees[i] = newminTree;
    newminTree = newminTree->nextSibling;
    newQueue.theTrees[i]->nextSibling = nullptr;
  }

  theTrees[minIndex] = nullptr;
  currentSize -= newQueue.currentSize + 1;
  merge(newQueue);
}

template <typename T>
void MyBinomialQueue<T>::makeEmpty() {
  for (auto &p : theTrees) {
    makeEmpty(p);
  }
  currentSize = 0;
}

template <typename T>
void MyBinomialQueue<T>::merge(MyBinomialQueue &rhs) {
  if (this == &rhs) return;
  currentSize += rhs.currentSize;
  if (currentSize > capacity()) {
    int oldSize = theTrees.size();
    int newSize = std::max(theTrees.size(), rhs.theTrees.size()) + 1;
    theTrees.resize(newSize);
    for (int i = oldSize; i < newSize; i++) {
      theTrees[i] = nullptr;
    }
  }
  BinomialNode *carry = nullptr;
  for (int i = 0, j = 1; j <= currentSize; i++, j *= 2) {
    BinomialNode *t1 = theTrees[i];
    BinomialNode *t2 = i < rhs.theTrees.size() ? rhs.theTrees[i] : nullptr;
    int whichcase = t1 == nullptr ? 0 : 1;
    whichcase += t2 == nullptr ? 0 : 2;
    whichcase += carry == nullptr ? 0 : 4;
    switch (whichcase) {
      case 0:  // all is nullptr
        break;
      case 1:  // only this
        break;
      case 2:  // only rhs
        theTrees[i] = t2;
        rhs.theTrees[i] = nullptr;  //��ʱ��i���ᳬ��rhs.theTrees��size
        break;
      case 3:  // only this and rhs
        carry = combineTrees(t1, t2);
        theTrees[i] = rhs.theTrees[i] = nullptr;
      case 4:  // only carry
        theTrees[i] = carry;
        carry = nullptr;
        break;
      case 5:  // only this and carry
        carry = combineTrees(t1, carry);
        theTrees[i] = nullptr;
        break;
      case 6:  // only t2 and carry
        carry = combineTrees(t2, carry);
        rhs.theTrees[i] = nullptr;
        break;
      case 7:  // all trees
        theTrees[i] = carry;
        carry = combineTrees(t1, t2);
        rhs.theTrees[i] = nullptr;
        break;
      default:
        break;
    }
  }
  for (int k = 0; k < rhs.theTrees.size(); k++) rhs.theTrees[k] = nullptr;
  rhs.currentSize = 0;
}

template <typename T>
const MyBinomialQueue<T> &MyBinomialQueue<T>::operator=(
    const MyBinomialQueue &rhs) {
  if (this != &rhs) {
    makeEmpty();
    currentSize = rhs.currentSize;
    theTrees.reserve(currentSize + 10);
    for (auto &p : rhs.theTrees) {
      theTrees.push_back(clone(p));
    }
  }
  return *this;
}

template <typename T>
int MyBinomialQueue<T>::findMinIndex() const {
  int i, minIndex;
  for (i = 0; theTrees[i] == nullptr; i++)
    ;
  for (minIndex = i; i < theTrees.size(); i++) {
    if (theTrees[i] != nullptr && theTrees[i] < theTrees[minIndex])
      minIndex = i;
  }
  return minIndex;
}

template <typename T>
inline void MyBinomialQueue<T>::makeEmpty(BinomialNode *&t) {
  if (t == nullptr) return;
  if (t->left == nullptr && t->nextSibling == nullptr) {
    delete t;
    t == nullptr;
  }
  makeEmpty(t->left);
  makeEmpty(t->nextSibling);
}

template <typename T>
inline MyBinomialQueue<T>::MyBinomialQueue(const MyBinomialQueue &rhs) {
  currentSize = rhs.currentSize;
  theTrees.reserve(currentSize + 10);
  for (auto &p : rhs.theTrees) {
    theTrees.push_back(clone(p));
  }
}

template <typename T>
inline MyBinomialQueue<T>::MyBinomialQueue(const T &item) {
  theTrees.push_back(new BinomialNode(item, nullptr, nullptr));
  currentSize = 1;
}

template <typename T>
inline MyBinomialQueue<T>::~MyBinomialQueue() {
  makeEmpty();
  currentSize = 0;
}

template <typename T>
inline bool MyBinomialQueue<T>::isEmpty() const {
  return currentSize == 0;
}
