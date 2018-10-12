#pragma once
#include <vector>
namespace MySort {
/**
 * 插入排序 , 时间O(N^2),空间O(1)
 */
template <typename T>
void insertionSort(std::vector<T> &a);

/**
 * 谢尔排序, 时间不定,依赖增量序列,时间 O(N^(4/3)),空间O(1)
 * 用谢尔增量序列,Ht=size()/2,H(k)=H(k+1)/2
 */
template <typename T>
void shellSort(std::vector<T> &a);

/**
 * 堆排序,此处不适用ADT
 * 和二叉堆不同,元素下标从0开始
 * 时间:O(NlogN) 空间:O(1)
 */
template <typename T>
void heapSort(std::vector<T> &a);

inline int leftChild(int i) { return (i * 2) + 1; }

/**
 * 下滤操作,i:要下滤的位置,n:heap的逻辑大小
 */
template <typename T>
void percDown(std::vector<T> &a, int i, int n);

/**
 * 归并排序
 * 时间:O(NlogN) 空间:O(N)
 * 注意此处,是在递归外定义一个O(N)的辅助Array
 * 而非每次递归都声明一个局部Array,所以要注意最后复制的时候的范围
 */
template <typename T>
void mergeSort(std::vector<T> &a);
template <typename T>
void mergeSort(std::vector<T> &a, std::vector<T> &tempArray, int left,
               int right);
template <typename T>
void merge(std::vector<T> &a, std::vector<T> &tempArray, int leftPos,
           int rightPos, int rightEnd);
}  // namespace MySort

template <typename T>
void MySort::insertionSort(std::vector<T> &a) {
  int j;
  for (size_t i = 1; i < a.size(); i++) {
    T temp = a[i];
    for (j = i; j > 0 && temp < a[j - 1]; j--) {
      a[j] = a[j - 1];
    }
    a[j] = temp;
  }
}

template <typename T>
void MySort::shellSort(std::vector<T> &a) {
  for (int gap = a.size() / 2; gap > 0; gap /= 2) {
    for (int i = gap; i < a.size(); i++) {
      T temp = a[i];
      int j = i;
      for (; j >= gap && temp < a[j - gap]; j -= gap) {
        a[j] = a[j - gap];
      }
      a[j] = temp;
    }
  }
}

template <typename T>
void MySort::percDown(std::vector<T> &a, int i, int n) {
  int child;
  T temp;
  for (temp = a[i]; leftChild(i) < n; i = child) {
    child = leftChild(i);
    if ((child != n - 1) && a[child] < a[child + 1]) child++;
    if (temp < a[child])
      a[i] = a[child];
    else
      break;
  }
  a[i] = temp;
}

template <typename T>
void MySort::heapSort(std::vector<T> &a) {
  // buildHeap
  for (int i = a.size() / 2 - 1; i >= 0; i--) {
    percDown(a, i, a.size());
  }
  // deleteMax
  for (int j = a.size() - 1; j > 0; j--) {
    std::swap(a[0], a[j]);
    percDown(a, 0, j);
  }
}

template <typename T>
void MySort::mergeSort(std::vector<T> &a) {
  std::vector<T> tempArray(a.size());
  mergeSort(a, tempArray, 0, a.size() - 1);
}

template <typename T>
void MySort::mergeSort(std::vector<T> &a, std::vector<T> &tempArray, int left_,
                       int right_) {
  if (left_ < right_) {
    int center = (left_ + right_) / 2;
    mergeSort(a, tempArray, left_, center);
    mergeSort(a, tempArray, center + 1, right_);
    merge(a, tempArray, left_, center + 1, right_);
  }
}

template <typename T>
void MySort::merge(std::vector<T> &a, std::vector<T> &tempArray, int leftPos,
                   int rightPos, int rightEnd) {
  int leftEnd = rightPos - 1;
  int tempPos = leftPos;
  int elements_num = rightEnd - leftPos + 1;
  while (leftPos <= leftEnd && rightPos <= rightEnd) {
    if (a[leftPos] < a[rightPos])
      tempArray[tempPos++] = a[leftPos++];
    else
      tempArray[tempPos++] = a[rightPos++];
  }
  while (leftPos <= leftEnd) tempArray[tempPos++] = a[leftPos++];
  while (rightPos <= rightEnd) tempArray[tempPos++] = a[rightPos++];
  for (size_t i = 0; i < elements_num; i++,rightEnd--) {
    a[rightEnd] = tempArray[rightEnd];
  }
}