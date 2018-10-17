#pragma once
#include <vector>
namespace MySort {
/**
 * 较大对象进行排序时,使用指针数组策略.
 * 为此定义其对象的指针
 */
template <typename T>
class Pointer {
 public:
  //合成的构造函数,pointee被初始化为nullptr
  Pointer(T *rhs = nullptr) : pointee(rhs) {}
  bool operator<(const Pointer &rhs) const { return *pointee < *rhs.pointee; }
  operator T *() const { return *pointee; }

 private:
  T *pointee;
};

//大对象的排序方法,此处可以修改接口添加函数对象.
template <typename T>
void largeObjectSort(std::vector<T> &a);

/**
 * 插入排序 , 时间O(N^2),空间O(1)
 * 注意for循环是从1开始,循环N-1次
 */
template <typename T>
void insertionSort(std::vector<T> &a);
template <typename T>
void insertionSort(std::vector<T> &a, int left, int right);

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

//归并排序的非递归形式
template <typename T>
void mergeSort2(std::vector<T> &a);

/**
 * 快速排序,枢纽元选为a[left] a[center] a[right]的中间值
 * 时间: 平均O(NlogN) 最坏O(N^2)
 * 空间: O(1)
 * 若递归时元素个数<=10,则使用插入排序(如果不加这个判断,则这个quickSort无法处理只有1个元素的情况(没有添加))
 */
template <typename T>
void quickSort(std::vector<T> &a);

template <typename T>
void quickSort(std::vector<T> &a, int left, int right);

//快速排序的非递归形式：主要是借助一个栈(或数组模拟栈）
template <typename T>
void quickSort2(std::vector<T> &a);

template <typename T>
void quickSort2(std::vector<T> &a, int left, int right);

//三数中值分割,将a[left] a[center] a[right]进行排序,并将min放在[left]
// max放入[right] mid 放入[right-1],返回mid值
template <typename T>
const T &median3(std::vector<T> &a, int left, int right);

/**
 * 快速选择:第k个最大值在[k-1]上
 * 原理同快速排序
 */
template <typename T>
void quickSelect(std::vector<T> &a, int left, int right, int k);

/**
 * 求已排序的序列A B:AUB的中值
 * 要求A B已排序,且元素个数相等
 * 时间：O(logN)
 * A
 * B长度不一样时，https://www.geeksforgeeks.org/median-of-two-sorted-arrays-of-different-sizes/
 */
template <typename T>
int mid_AUB(std::vector<T> &a, int la, int ra, std::vector<T> &b, int lb,
            int rb);
}  // namespace MySort

template <typename T>
void MySort::largeObjectSort(std::vector<T> &a) {
  vector<Pointer<T>> p(a.size());
  for (size_t i = 0; i < a.size(); i++) {
    p[i] = &a[i];
  }
  int j, nextj;
  quickSort(p);  //此处可以为任意排序,修改为函数对象
  for (size_t i = 0; i < a.size(); i++) {
    if (p[i] != &a[i]) {
      for (j = i; p[j] != a[i]; j = nextj) {
        nextj = p[j] - &a[0];
        a[j] = *p[j];
        p[j] = &a[j];
      }
    }
    a[j] = temp;
    p[j] = &a[j];
  }
}

template <typename T>
void MySort::insertionSort(std::vector<T> &a) {
  insertionSort(a, 0, a.size() - 1);
}

template <typename T>
void MySort::insertionSort(std::vector<T> &a, int left, int right) {
  int j;
  for (size_t i = left + 1; i <= right; i++) {
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
  for (size_t i = 0; i < elements_num; i++, rightEnd--) {
    a[rightEnd] = tempArray[rightEnd];
  }
}

template <typename T>
void MySort::mergeSort2(std::vector<T> &a) {
  int n = a.size();
  std::vector<T> tempArray(n);
  for (int sublistSize = 1; sublistSize <= n; sublistSize <<= 1;) {
    int startPos = 0;
    while (startPos + sublistSize < n) {
      int startPos2 = startPos + sublistSize;
      int endPos = min(startPos2 + sublistSize - 1, n);
      merge(a, tempArray, startPos, startPos2, endPos);
      startPos2 = endPos + 1;
    }
  }
}

template <typename T>
void MySort::quickSort(std::vector<T> &a) {
  quickSort(a, 0, a.size() - 1);
}

template <typename T>
void MySort::quickSort(std::vector<T> &a, int left, int right) {
  if (left + 10 <= right) {
    T pivot = median3(a, left, right);
    int i = left, j = right - 1;
    for (;;) {
      while (a[++i] < pivot)
        ;
      while (pivot < a[--j])
        ;
      if (i < j)
        std::swap(a[i], a[j]);
      else
        break;
    }
    std::swap(a[i], a[right - 1]);
    // recursive
    quickSort(a, left, i - 1);
    quickSort(a, i + 1, right);
  } else {
    insertionSort(a, left, right);
  }
}

template <typename T>
void MySort::quickSort2(std::vector<T> &a) {
  return quickSort2(a, 0, a.size() - 1);
}

template <typename T>
void MySort::quickSort2(std::vector<T> &a, int left, int right) {
  int *startArray = new int[a.size()]{0};
  int *endArray = new int[a.size()]{0};
  int p = 0;
  startArray[p] = left;
  endArray[p++] = right;
  while (p) {
    int ltemp = startArray[--p];
    int rtemp = endArray[p];
    if (ltemp + 10 > rtemp) {
      insertionSort(a, ltemp, rtemp);
      continue;
    }
    T pivot = median3(a, ltemp, rtemp);
    int i = ltemp, j = rtemp - 1;
    for (;;) {
      while (a[++i] < pivot)
        ;
      while (pivot < a[--j])
        ;
      if (i < j)
        std::swap(a[i], a[j]);
      else
        break;
    }
    std::swap(a[i], a[rtemp - 1]);
    startArray[p] = ltemp;
    endArray[p++] = i - 1;
    startArray[p] = i + 1;
    endArray[p++] = rtemp;
  }
  delete[] startArray;
  delete[] endArray;
}

template <typename T>
const T &MySort::median3(std::vector<T> &a, int left, int right) {
  int center = (left + right) >> 1;
  //注意比较顺序,且这里我们都使用<号 而不是<
  //>混用,因为只要类型T定义了一种运算号即可
  if (a[center] < a[left]) std::swap(a[center], a[left]);
  if (a[right] < a[left]) std::swap(a[right], a[left]);
  if (a[right] < a[center]) std::swap(a[center], a[right]);

  std::swap(a[center], a[right - 1]);
  return a[right - 1];
}

template <typename T>
void MySort::quickSelect(std::vector<T> &a, int left, int right, int k) {
  if (left + 10 <= right) {
    int pivot = median3(a, left, right);
    int i = left, j = right - 1;
    for (;;) {
      while (a[++i] < pivot)
        ;
      while (a[--j] > pivot)
        ;
      if (i < j)
        std::swap(a[i], a[j]);
      else
        break;
    }
    std::swap(a[i], a[right - 1]);
    if (k <= i /*k-1 < i*/)
      quickSelect(a, left, i - 1, k);
    else if (k > i + 1) {
      quickSelect(a, i + 1, right, k);
    }  // else [i]即为第k大的值
  } else
    insertionSort(a, left, right);
}

template <typename T>
int MySort::mid_AUB(std::vector<T> &a, int la, int ra, std::vector<T> &b,
                    int lb, int rb) {
  if (la == ra)
    return a[la];
  else if (lb == rb)
    return b[lb];
  int a_mid = (la + ra) / 2;
  int b_mid = (lb + rb) / 2;
  if (a[a_mid] > b[b_mid]) {
    if (!((ra - la + 1) & 1)) b_mid++;
    ra = a_mid;
    lb = b_mid;
  } else if (a[a_mid] < b[b_mid]) {
    if (!((rb - lb + 1) & 1)) a_mid++;
    la = a_mid;
    rb = b_mid;
  } else {
    return a[a_mid];
  }

  return mid_AUB(a, la, ra, b, lb, rb);
}
