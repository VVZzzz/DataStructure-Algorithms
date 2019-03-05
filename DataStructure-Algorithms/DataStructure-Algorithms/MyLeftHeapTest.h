#pragma once
//此文件测试左式堆
#include <vector>
#include "MyLeftisHeap.h"
void leftist_heap_test() {
  //测试左式堆默认构造函数
  std::cout << "\n测试构造函数" << std::endl;
  MyLeftistHeap<int> leftist_heap;
  leftist_heap.printInfo();

  //测试左式堆insert()函数,包括insert,merge,基本操作
  std::cout << "\n\n测试insert()" << std::endl;
  std::vector<int> ivec{6, 10, 7, 14, 12, 11, 8};
  for (auto i : ivec) {
    leftist_heap.insert(i);
    std::cout << "\n\n";
    leftist_heap.printInfo();
  }

  //测试左式堆拷贝构造函数
  std::cout << "\n\n测试拷贝构造函数" << std::endl;
  MyLeftistHeap<int> leftist_heap2(leftist_heap);
  leftist_heap2.printInfo();

  //测试左式堆findMin()函数
  std::cout << "\n\n测试findMin()" << std::endl;
  std::cout << "finMin() result is " << leftist_heap.findMin() << std::endl;

  //测试左式堆deleteMin()
  std::cout << "\n\n测试deleteMin()" << std::endl;
  for (int i = 0; i < ivec.size() / 2; i++) {
    leftist_heap.deleteMin();
    std::cout << "\n\n";
    leftist_heap.printInfo();
  }

  //测试左式堆buidHeap()两两合并建堆策略
  std::cout << "\n\n测试buildHeap()" << std::endl;
  MyLeftistHeap<int> leftist_heap3;
  leftist_heap3.buildHeap(ivec);
  leftist_heap3.printInfo();

  //测试左式堆的懒惰删除策略
  //lazyFindMin,lazyDeleteMin,个人感觉不使用懒惰策略为好,因为左式堆需要一直维护,和二叉堆一样
  /*
  std::cout << "\n\n测试lazyDeleteMin()" << std::endl;
  for (int i = 0; i < ivec.size() / 2; i++) {
    leftist_heap.lazyDeleteMin();
    std::cout << "\n\n";
    leftist_heap.printInfo();
  }
  */
}
