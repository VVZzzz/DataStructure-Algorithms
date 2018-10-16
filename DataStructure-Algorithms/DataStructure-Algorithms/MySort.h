#pragma once
#include <vector>
namespace MySort {
/**
 * �ϴ�����������ʱ,ʹ��ָ���������.
 * Ϊ�˶���������ָ��
 */
template <typename T>
class Pointer {
 public:
  //�ϳɵĹ��캯��,pointee����ʼ��Ϊnullptr
  Pointer(T *rhs = nullptr) : pointee(rhs) {}
  bool operator<(const Pointer &rhs) const { return *pointee < *rhs.pointee; }
  operator T *() const { return *pointee; }

 private:
  T *pointee;
};

//���������򷽷�,�˴������޸Ľӿ���Ӻ�������.
template <typename T>
void largeObjectSort(std::vector<T> &a);

/**
 * �������� , ʱ��O(N^2),�ռ�O(1)
 * ע��forѭ���Ǵ�1��ʼ,ѭ��N-1��
 */
template <typename T>
void insertionSort(std::vector<T> &a);
template <typename T>
void insertionSort(std::vector<T> &a, int left, int right);

/**j
 * л������, ʱ�䲻��,������������,ʱ�� O(N^(4/3)),�ռ�O(1)
 * ��л����������,Ht=size()/2,H(k)=H(k+1)/2
 */
template <typename T>
void shellSort(std::vector<T> &a);

/**
 * ������,�˴�������ADT
 * �Ͷ���Ѳ�ͬ,Ԫ���±��0��ʼ
 * ʱ��:O(NlogN) �ռ�:O(1)
 */
template <typename T>
void heapSort(std::vector<T> &a);

inline int leftChild(int i) { return (i * 2) + 1; }

/**
 * ���˲���,i:Ҫ���˵�λ��,n:heap���߼���С
 */
template <typename T>
void percDown(std::vector<T> &a, int i, int n);

/**
 * �鲢����
 * ʱ��:O(NlogN) �ռ�:O(N)
 * ע��˴�,���ڵݹ��ⶨ��һ��O(N)�ĸ���Array
 * ����ÿ�εݹ鶼����һ���ֲ�Array,����Ҫע������Ƶ�ʱ��ķ�Χ
 */
template <typename T>
void mergeSort(std::vector<T> &a);
template <typename T>
void mergeSort(std::vector<T> &a, std::vector<T> &tempArray, int left,
               int right);
template <typename T>
void merge(std::vector<T> &a, std::vector<T> &tempArray, int leftPos,
           int rightPos, int rightEnd);

//�鲢����ķǵݹ���ʽ
template <typename T>
void mergeSort2(std::vector<T> &a);

/**
 * ��������,��ŦԪѡΪa[left] a[center] a[right]���м�ֵ
 * ʱ��: ƽ��O(NlogN) �O(N^2)
 * �ռ�: O(1)
 * ���ݹ�ʱԪ�ظ���<=10,��ʹ�ò�������
 */
template <typename T>
void quickSort(std::vector<T> &a);

template <typename T>
void quickSort(std::vector<T> &a, int left, int right);

//��������ķǵݹ���ʽ����Ҫ�ǽ���һ��ջ(������ģ��ջ��
template <typename T>
void quickSort2(std::vector<T> &a);

template <typename T>
void quickSort2(std::vector<T> &a, int left, int right);

//������ֵ�ָ�,��a[left] a[center] a[right]��������,����min����[left]
// max����[right] mid ����[right-1],����midֵ
template <typename T>
const T &median3(std::vector<T> &a, int left, int right);

/**
 * ����ѡ��:��k�����ֵ��[k-1]��
 * ԭ��ͬ��������
 */
template <typename T>
void quickSelect(std::vector<T> &a, int left, int right, int k);

}  // namespace MySort

template <typename T>
void MySort::largeObjectSort(std::vector<T> &a) {
  vector<Pointer<T>> p(a.size());
  for (size_t i = 0; i < a.size(); i++) {
    p[i] = &a[i];
  }
  int j, nextj;
  quickSort(p);  //�˴�����Ϊ��������,�޸�Ϊ��������
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
  insertionSort(a, 0, a.size());
}

template <typename T>
void MySort::insertionSort(std::vector<T> &a, int left, int right) {
  int j;
  for (size_t i = left + 1; i < right; i++) {
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
  int startArray[a.size()]{0};
  int endArray[a.size()]{0};
  int p = 0;
  startArray[p] = left;
  endArray[p] = right;
  while (p) {
    int ltemp = startArray[--p];
    int rtemp = endArray[p];
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
    std::swap(a[i], a[right - 1]);
    startArray[p++] = left;
    endArray[p] = i - 1;
    startArray[p++] = i + 1;
    endArray[p] = right;
  }
}

template <typename T>
const T &MySort::median3(std::vector<T> &a, int left, int right) {
  int center = (left + right) >> 1;
  //ע��Ƚ�˳��,���������Ƕ�ʹ��<�� ������<
  //>����,��ΪֻҪ����T������һ������ż���
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
      while (a[--i] > pivot)
        ;
      if (i < j) std::swap(a[i], a[j]);
      if (k <= i /*k-1 < i*/)
        quickSelect(a, left, i - 1, k);
      else if (k > i + 1) {
        quickSelect(a, i + 1, right, k);
      }
      // else [i]��Ϊ��k���ֵ
    }
  } else {
    insertionSort(a);
  }
}
