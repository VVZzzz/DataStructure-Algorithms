#pragma once
#include <iostream>
#include "MyList.h"
/*此文件用来测试MyList*/
void mylist_test() {
  std::cout << "********测试MyList********" << std::endl;
  std::cout << std::endl;
  /*测试默认初始化*/
  std::cout << "默认初始化" << std::endl;
  MyList<int> mylist;
  mylist.printInfo();
  std::cout << std::endl;

  /*测试迭代器操作*/
  std::cout << "迭代器操作" << std::endl;
  std::cout << std::endl;

  std::cout << "测试push_back()" << std::endl;
  for (int i = 1; i < 10; i++) {
    mylist.push_back(i);
  }
  mylist.printInfo();
  std::cout << std::endl;

  std::cout << "测试push_front()" << std::endl;
  for (int i = 1; i < 10; i++) {
    mylist.push_front(-i);
  }
  mylist.printInfo();
  std::cout << std::endl;

  std::cout << "测试insert(iterator,data)" << std::endl;
  int c = mylist.size() / 2;
  auto itr = mylist.begin();
  while (c-- > 0) itr++;
  mylist.insert(itr, 1000);
  mylist.printInfo();
  std::cout << std::endl;

  std::cout << "测试erase(iterator)" << std::endl;
  auto itr2 = mylist.erase(mylist.begin());
  mylist.erase(itr2);
  mylist.printInfo();
  std::cout << std::endl;

  std::cout << "测试erase(iterator1,iterator2)" << std::endl;
  auto itr3 = mylist.begin(), itr4 = itr3;
  int c2 = 3;
  while (c2-- > 0) itr4++;
  mylist.erase(itr3, itr4);
  mylist.printInfo();
  std::cout << std::endl;

  std::cout << "测试pop_back()" << std::endl;
  mylist.pop_back();
  mylist.printInfo();
  std::cout << std::endl;

  std::cout << "测试pop_front()" << std::endl;
  mylist.pop_front();
  mylist.printInfo();
  std::cout << std::endl;

  std::cout << "测试front(),back()" << std::endl;
  std::cout << "front: " << mylist.front() << std::endl;
  std::cout << "back: " << mylist.back() << std::endl;
  std::cout << std::endl;

  std::cout << "测试反向迭代器" << std::endl;
  for (MyList<int>::reverse_iterator itr = mylist.rbegin();
       itr != mylist.rend(); itr++) {
    std::cout << *itr << " ";
  }
  std::cout << std::endl;
  std::cout << std::endl;


  /*测试懒惰删除,LazyErase*/
  /* 注意这个懒惰删除只完成了标记应该删除的结点,一般被标记的点超过一般,就是真正意义上的erase;
   * 并且懒惰删除之后,再调用list.begin(),是没有更新的,即仍旧返回懒惰删除之前的begin.(需完善)
   * size(),end()等成员函数也是相同情况.
   */
  MyList<int> lazyList;
  for (int i = 0; i < 15; i++) {
    lazyList.push_back(i);
  }
  std::cout << "初始状态:" << std::endl;
  lazyList.printInfo();

  std::cout << "懒惰删除5个元素" << std::endl;
  std::cout << std::endl;
  auto ptr = lazyList.begin();
  for (int j = 0; j < 5; j++) ptr = lazyList.lazy_erase(ptr);
  lazyList.printInfo();
  std::cout << std::endl;
  std::cout << "继续删除8个元素" << std::endl;
  //懒惰删除个数大于一半的元素数时,就执行真正的erase
  for (int k = 0; k < 8; k++) {
    ptr = lazyList.lazy_erase(ptr);
  }
  lazyList.printInfo();
  std::cout << std::endl;
  


}
