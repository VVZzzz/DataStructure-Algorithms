#pragma once
#include <iostream>
#include "MyList.h"
/*���ļ���������MyList*/
void mylist_test() {
  std::cout << "********����MyList********" << std::endl;
  std::cout << std::endl;
  /*����Ĭ�ϳ�ʼ��*/
  std::cout << "Ĭ�ϳ�ʼ��" << std::endl;
  MyList<int> mylist;
  mylist.printInfo();
  std::cout << std::endl;

  /*���Ե���������*/
  std::cout << "����������" << std::endl;
  std::cout << std::endl;

  std::cout << "����push_back()" << std::endl;
  for (int i = 1; i < 10; i++) {
    mylist.push_back(i);
  }
  mylist.printInfo();
  std::cout << std::endl;

  std::cout << "����push_front()" << std::endl;
  for (int i = 1; i < 10; i++) {
    mylist.push_front(-i);
  }
  mylist.printInfo();
  std::cout << std::endl;

  std::cout << "����insert(iterator,data)" << std::endl;
  int c = mylist.size() / 2;
  auto itr = mylist.begin();
  while (c-- > 0) itr++;
  mylist.insert(itr, 1000);
  mylist.printInfo();
  std::cout << std::endl;

  std::cout << "����erase(iterator)" << std::endl;
  auto itr2 = mylist.erase(mylist.begin());
  mylist.erase(itr2);
  mylist.printInfo();
  std::cout << std::endl;

  std::cout << "����erase(iterator1,iterator2)" << std::endl;
  auto itr3 = mylist.begin(), itr4 = itr3;
  int c2 = 3;
  while (c2-- > 0) itr4++;
  mylist.erase(itr3, itr4);
  mylist.printInfo();
  std::cout << std::endl;

  std::cout << "����pop_back()" << std::endl;
  mylist.pop_back();
  mylist.printInfo();
  std::cout << std::endl;

  std::cout << "����pop_front()" << std::endl;
  mylist.pop_front();
  mylist.printInfo();
  std::cout << std::endl;

  std::cout << "����front(),back()" << std::endl;
  std::cout << "front: " << mylist.front() << std::endl;
  std::cout << "back: " << mylist.back() << std::endl;
  std::cout << std::endl;

  std::cout << "���Է��������" << std::endl;
  for (MyList<int>::reverse_iterator itr = mylist.rbegin();
       itr != mylist.rend(); itr++) {
    std::cout << *itr << " ";
  }
  std::cout << std::endl;
  std::cout << std::endl;


  /*��������ɾ��,LazyErase*/
  /* ע���������ɾ��ֻ����˱��Ӧ��ɾ���Ľ��,һ�㱻��ǵĵ㳬��һ��,�������������ϵ�erase;
   * ��������ɾ��֮��,�ٵ���list.begin(),��û�и��µ�,���Ծɷ�������ɾ��֮ǰ��begin.(������)
   * size(),end()�ȳ�Ա����Ҳ����ͬ���.
   */
  MyList<int> lazyList;
  for (int i = 0; i < 15; i++) {
    lazyList.push_back(i);
  }
  std::cout << "��ʼ״̬:" << std::endl;
  lazyList.printInfo();

  std::cout << "����ɾ��5��Ԫ��" << std::endl;
  std::cout << std::endl;
  auto ptr = lazyList.begin();
  for (int j = 0; j < 5; j++) ptr = lazyList.lazy_erase(ptr);
  lazyList.printInfo();
  std::cout << std::endl;
  std::cout << "����ɾ��8��Ԫ��" << std::endl;
  //����ɾ����������һ���Ԫ����ʱ,��ִ��������erase
  for (int k = 0; k < 8; k++) {
    ptr = lazyList.lazy_erase(ptr);
  }
  lazyList.printInfo();
  std::cout << std::endl;
  


}
