#pragma once
#include <iostream>
#include <stdexcept>
#include <vector>
//优先队列支持两个基本操作:insert deleteMin
//二叉堆实现的优先队列,底层我们用简单的数组实现
//节点t的左子为2t,右儿子为2t+1,根为t/2下取整.
//二叉堆是一个完全二叉树
template <typename T>
class MyBinaryHeap {
 public:
  explicit MyBinaryHeap(int capacity = 100) : currentSize(0) {
    heap_arry.resize(capacity);
  }
  //该构造函数先填入数据，在全部节点下滤。buildHeap()即为全部节点下滤。
  explicit MyBinaryHeap(const std::vector<T> &items)
      : heap_arry(items.size() + 10), currentSize(items.size()) {
    for (int i = 0; i < items.size(); i++) heap_arry[i + 1] = items[i];
    buildHeap();
  }

  bool isEmpty() const;
  const T &findMin() const;

  void insert(const T &x);
  void deleteMin();
  void deleteMin(T &minItem);
  void makeEmpty();

  void decreaseKey(int pos, const T &diff);
  void increaseKey(int pos, const T &diff);
  // remove(p)首先将p节点decreaseKey(p,无穷大),再deleteMin();
  void remove(int pos);

  void printInfo() const;

 private:
  int currentSize;
  std::vector<T> heap_arry;  //数据从下标1开始保存
  void buildHeap();
  void percolateDown(int hole);  //下滤操作
  void percolateUp(int hole);    //上滤操作
};

template <typename T>
inline bool MyBinaryHeap<T>::isEmpty() const {
  return currentSize == 0;
}

template <typename T>
inline const T &MyBinaryHeap<T>::findMin() const {
  return heap_arry[1];
}

//最坏情况为O(logN)
template <typename T>
void MyBinaryHeap<T>::insert(const T &x) {
  if (currentSize == heap_arry.size() - 1)
    heap_arry.resize(heap_arry.size() << 1);
  //实际为上滤操作
  int hole = ++currentSize;
  heap_arry[hole] = x;
  percolateUp(hole);
  // Practice 6.5
  // heap_arry[0] = x;
}

template <typename T>
void MyBinaryHeap<T>::deleteMin() {
  try {
    if (isEmpty()) throw std::underflow_error("heap_arry is empty!");
  } catch (std::underflow_error &e) {
    std::cout << e.what() << std::endl;
    return;
  }

  heap_arry[1] = heap_arry[currentSize--];
  percolateDown(1);
}

template <typename T>
void MyBinaryHeap<T>::deleteMin(T &minItem) {
  try {
    if (isEmpty()) throw std::underflow_error("heap_arry is empty!");
  } catch (std::underflow_error &e) {
    std::cout << e.what() << std::endl;
    return;
  }

  minItem = heap_arry[1];
  heap_arry[1] = heap_arry[currentSize--];
  percolateDown(1);
}

template <typename T>
inline void MyBinaryHeap<T>::makeEmpty() {
  heap_arry.clear();
  currentSize = 0;
}

template <typename T>
void MyBinaryHeap<T>::percolateDown(int hole) {
  T temp = heap_arry[hole];
  int child;
  for (; (hole << 1) <= currentSize; hole = child) {
    child = (hole << 1);
    //选择两个兄弟节点中较小的那个
    if (child != currentSize && heap_arry[child + 1] < heap_arry[child])
      child++;
    if (heap_arry[child] < temp)
      heap_arry[hole] = heap_arry[child];
    else
      break;
  }
  heap_arry[hole] = temp;
}

template <typename T>
void MyBinaryHeap<T>::percolateUp(int hole) {
  T temp = heap_arry[hole];
  for (; hole > 1 && temp < heap_arry[hole >> 1]; hole >>= 1)
    heap_arry[hole] = heap_arry[hole >> 1];  //赋值,避免交换
  heap_arry[hole] = temp;
}

template <typename T>
void MyBinaryHeap<T>::decreaseKey(int pos, const T &diff) {
  try {
    if (pos > currentSize || pos <= 0)
      throw std::out_of_range("pos to decrease is valid!");
  } catch (std::out_of_range &e) {
    std::cout << e.what() << std::endl;
    return;
  }
  heap_arry[pos] = heap_arry[pos] - diff;
  percolateUp(pos);  //上滤
}

template <typename T>
void MyBinaryHeap<T>::increaseKey(int pos, const T &diff) {
  try {
    if (pos > currentSize || pos <= 0)
      throw std::out_of_range("pos to decrease is valid!");
  } catch (std::out_of_range &e) {
    std::cout << e.what() << std::endl;
    return;
  }
  heap_arry[pos] = heap_arry[pos] + diff;
  percolateDown(pos);  //下滤
}

template <typename T>
void MyBinaryHeap<T>::remove(int pos) {
  //思路即:先变的很小,在进行下滤
  heap_arry[pos] = INT_MIN;
  percolateUp(pos);
  deleteMin();
}

template <typename T>
void MyBinaryHeap<T>::printInfo() const {
  if (currentSize == 0) {
    std::cout << "该堆为空堆" << std::endl;
    return;
  }
  std::cout << "堆大小为: " << currentSize << std::endl;
  int layers = 1, i = layers, num = layers;
  while (i <= currentSize) {
    std::cout << heap_arry[i] << " ";
    if (i++ == layers) {
      std::cout << std::endl;
      layers += (num <<= 1);
    }
  }
  std::cout << std::endl;
}

template <typename T>
void MyBinaryHeap<T>::buildHeap() {
  for (int i = currentSize / 2; i > 0; i--) percolateDown(i);
}
