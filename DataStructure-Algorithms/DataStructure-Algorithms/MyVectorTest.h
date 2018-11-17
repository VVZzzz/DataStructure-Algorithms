#pragma once
#include <iostream>
#include "MyVector.h"
/*���ļ���������MyVector*/
void myvec_test() {
  std::cout << "********����MyVector********" << std::endl;
  std::cout << std::endl;
  /*����Ĭ�ϳ�ʼ��*/
  std::cout << "Ĭ�ϳ�ʼ��" << std::endl;
  MyVector<int> myvec;
  std::cout << std::endl;

  /*���Գ�ʼ��*/
  int para = 10;
  std::cout << "���γ�ʼ��" << std::endl;
  MyVector<int> myvec2(10);
  std::cout << std::endl;

  /*����operator[]*/
  std::cout << "OPERATOR[]" << std::endl;
  myvec2[0] = 1;
  myvec2[1] = 2;
  /*out of range */
  // myvec2[10] = 10;
  myvec2.printInfo();
  std::cout << std::endl;

  /*����operatro=*/
  std::cout << "OPERATOR=" << std::endl;
  myvec = myvec2;
  myvec.printInfo();
  std::cout << std::endl;

  /*���Կ�����ʼ��*/
  std::cout << "������ʼ��" << std::endl;
  MyVector<int> myvec3(myvec2);
  myvec3.printInfo();
  std::cout << std::endl;

  /*����push_back*/
  std::cout << "PUSH_BACK" << std::endl;
  MyVector<int> myvec4;
  for (int i = 0; i < 17; i++) {
    myvec4.push_back(i);
  }
  myvec4.printInfo();
  std::cout << std::endl;

  /*����pop_back*/
  std::cout << "POP_BACK" << std::endl;
  myvec4.pop_back();
  myvec4.printInfo();
  std::cout << std::endl;

  /*���Ե�����*/
  std::cout << "���Ե�����" << std::endl;

  for (Iterator<int> itr = myvec4.begin(); itr != myvec4.end(); itr++) {
    std::cout << *itr << " ";
  }
  std::cout << std::endl;
  std::cout << "����back()" << std::endl;
  std::cout << myvec4.back() << std::endl;

  std::cout << "����insert(pos)" << std::endl;
  std::cout << "BEFORE INSERT" << std::endl;
  myvec4.printInfo();
  std::cout << "AFTER INSERT" << std::endl;
  Iterator<int> itr = myvec4.begin();
  for (int i = 1; i < 20; i++) {
    itr = myvec4.insert(itr, -i);
  }
  myvec4.printInfo();

  std::cout << "����erase(pos)" << std::endl;
  itr = myvec4.begin();
  std::cout << "BEFORE ERASE" << std::endl;
  myvec4.printInfo();
  std::cout << "AFTER ERASE" << std::endl;
  for (int i = 1; i < 20; i++) {
    itr = myvec4.erase(itr);
  }
  myvec4.printInfo();
  std::cout << "********�������********" << std::endl;
  std::cout << std::endl;
}
