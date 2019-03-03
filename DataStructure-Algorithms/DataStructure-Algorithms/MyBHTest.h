#pragma once
//此文件测试二叉堆
#include <vector>
#include "MyBinaryHeap.h"
void binary_heap_test() {
  //测试默认构造函数
  std::cout << "\n测试默认构造函数" << std::endl;
  MyBinaryHeap<int> binary_heap;
  binary_heap.printInfo();

  //测试参数为vector<T>的构造函数
  std::vector<int> test_data{21, 13, 16, 24, 31, 27, 19, 68, 65, 26, 32};
  std::cout << "\n测试参数为vevector<T>的构造函数" << std::endl;
  MyBinaryHeap<int> binary_heap2(test_data);
  binary_heap2.printInfo();

  //测试insert()函数
  std::cout << "\n测试insert()" << std::endl;
  for (auto i : test_data) binary_heap.insert(i);
  binary_heap.printInfo();

  //测试deletMin()函数
  std::cout << "\n测试deletMin()" << std::endl;
  binary_heap.deleteMin();
  binary_heap.printInfo();

  //测试deletMin(int)函数
  int delete_data = 1;
  std::cout << "\n测试deleteMin(int)" << std::endl;
  binary_heap.deleteMin(delete_data);
  binary_heap.printInfo();
  std::cout << "\ndelete的值为: " << delete_data << std::endl;

  //以下的操作不为基本操作
  /* 
   * 此时binary_heap为:
   *       19 
   *   21     27 
   *  24 26  31 32
   * 68 65
   */

  //测试remove(int pos)
  std::cout << "\n测试remove(int pos)" << std::endl;
  binary_heap.remove(2);
  binary_heap.printInfo();

  //测试increaseKey(int pos,const T &diff)
  std::cout << "\n测试increaseKey" << std::endl;
  binary_heap.increaseKey(2, 100);
  binary_heap.printInfo();

  //测试decreaseKey(int pos,const T &diff)
  std::cout << "\n测试decreaseKey" << std::endl;
  binary_heap.decreaseKey(2, 100);
  binary_heap.printInfo();
}
