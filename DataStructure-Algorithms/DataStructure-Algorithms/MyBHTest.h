#pragma once
//���ļ����Զ����
#include <vector>
#include "MyBinaryHeap.h"
void binary_heap_test() {
  //����Ĭ�Ϲ��캯��
  std::cout << "\n����Ĭ�Ϲ��캯��" << std::endl;
  MyBinaryHeap<int> binary_heap;
  binary_heap.printInfo();

  //���Բ���Ϊvector<T>�Ĺ��캯��
  std::vector<int> test_data{21, 13, 16, 24, 31, 27, 19, 68, 65, 26, 32};
  std::cout << "\n���Բ���Ϊvevector<T>�Ĺ��캯��" << std::endl;
  MyBinaryHeap<int> binary_heap2(test_data);
  binary_heap2.printInfo();

  //����insert()����
  std::cout << "\n����insert()" << std::endl;
  for (auto i : test_data) binary_heap.insert(i);
  binary_heap.printInfo();

  //����deletMin()����
  std::cout << "\n����deletMin()" << std::endl;
  binary_heap.deleteMin();
  binary_heap.printInfo();

  //����deletMin(int)����
  int delete_data = 1;
  std::cout << "\n����deleteMin(int)" << std::endl;
  binary_heap.deleteMin(delete_data);
  binary_heap.printInfo();
  std::cout << "\ndelete��ֵΪ: " << delete_data << std::endl;

  //���µĲ�����Ϊ��������
  /* 
   * ��ʱbinary_heapΪ:
   *       19 
   *   21     27 
   *  24 26  31 32
   * 68 65
   */

  //����remove(int pos)
  std::cout << "\n����remove(int pos)" << std::endl;
  binary_heap.remove(2);
  binary_heap.printInfo();

  //����increaseKey(int pos,const T &diff)
  std::cout << "\n����increaseKey" << std::endl;
  binary_heap.increaseKey(2, 100);
  binary_heap.printInfo();

  //����decreaseKey(int pos,const T &diff)
  std::cout << "\n����decreaseKey" << std::endl;
  binary_heap.decreaseKey(2, 100);
  binary_heap.printInfo();
}
