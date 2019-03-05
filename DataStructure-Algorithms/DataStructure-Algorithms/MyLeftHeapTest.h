#pragma once
//���ļ�������ʽ��
#include <vector>
#include "MyLeftisHeap.h"
void leftist_heap_test() {
  //������ʽ��Ĭ�Ϲ��캯��
  std::cout << "\n���Թ��캯��" << std::endl;
  MyLeftistHeap<int> leftist_heap;
  leftist_heap.printInfo();

  //������ʽ��insert()����,����insert,merge,��������
  std::cout << "\n\n����insert()" << std::endl;
  std::vector<int> ivec{6, 10, 7, 14, 12, 11, 8};
  for (auto i : ivec) {
    leftist_heap.insert(i);
    std::cout << "\n\n";
    leftist_heap.printInfo();
  }

  //������ʽ�ѿ������캯��
  std::cout << "\n\n���Կ������캯��" << std::endl;
  MyLeftistHeap<int> leftist_heap2(leftist_heap);
  leftist_heap2.printInfo();

  //������ʽ��findMin()����
  std::cout << "\n\n����findMin()" << std::endl;
  std::cout << "finMin() result is " << leftist_heap.findMin() << std::endl;

  //������ʽ��deleteMin()
  std::cout << "\n\n����deleteMin()" << std::endl;
  for (int i = 0; i < ivec.size() / 2; i++) {
    leftist_heap.deleteMin();
    std::cout << "\n\n";
    leftist_heap.printInfo();
  }

  //������ʽ��buidHeap()�����ϲ����Ѳ���
  std::cout << "\n\n����buildHeap()" << std::endl;
  MyLeftistHeap<int> leftist_heap3;
  leftist_heap3.buildHeap(ivec);
  leftist_heap3.printInfo();

  //������ʽ�ѵ�����ɾ������
  //lazyFindMin,lazyDeleteMin,���˸о���ʹ���������Ϊ��,��Ϊ��ʽ����Ҫһֱά��,�Ͷ����һ��
  /*
  std::cout << "\n\n����lazyDeleteMin()" << std::endl;
  for (int i = 0; i < ivec.size() / 2; i++) {
    leftist_heap.lazyDeleteMin();
    std::cout << "\n\n";
    leftist_heap.printInfo();
  }
  */
}
