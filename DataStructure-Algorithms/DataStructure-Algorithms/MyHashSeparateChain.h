#pragma once
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include "HashFunc.h"
#include "nextPrime.h"
//��ϣ��(�����ͻΪ�������ӷ�)
template <typename HashedObj>
//�˴���ϣ��Ҫ��HashedObj�����ṩoperator==����operator!=����
//��Ϊ�㷺��ʹ��Ϊ�ڹ���ɢ�б�ʱ���ṩһ������ָ�������ṩ�Լ��Ĺ�ϣ�������߽����ͻ������
//���߾͹̶�ʹ��hash(int);hash(const string &);�ڶ�Ӧ�ض�������ʱ��hash(const
// T&);����hash(T.getNameString());
class MyHashSeparate {
 public:
  explicit MyHashSeparate(int sz = 101) : currentSize(0) {
    theLists.resize(nextPrime(sz));
    makeEmpty();
  }  //��ϣ��Ĵ�С���������,���ڷֲ�����.
  bool contains(const HashedObj &x) const;
  void makeEmpty();
  bool insert(const HashedObj &x);
  bool remove(const HashedObj &x);
  int getTableSize() const { return theLists.size(); }
  int getElementSize() const { return currentSize; }
  void printInfo() const;

 private:
  std::vector<std::list<HashedObj> >
      theLists;  //��ϣ��,��Ԫ��Ϊһ�������ͻ������.
  int currentSize;
  void
  rehash();  //һ�������,ʹԪ�صĸ����͹�ϣ��Ĵ�С���ʹ��װ�����ӡ�1,����Ч�ʸ�.
             // rehash()���������ϣ���С
  int myhash(const HashedObj &t) const;  //��ϣ����
};

template <typename HashedObj>
bool MyHashSeparate<HashedObj>::contains(const HashedObj &x) const {
  int temp = myhash(x);
  return std::find(theLists[temp].begin(), theLists[temp].end(), x) !=
         theLists[temp].end();
}

template <typename HashedObj>
void MyHashSeparate<HashedObj>::makeEmpty() {
  for (int i = 0; i < theLists.size(); i++) {
    theLists[i].clear();
  }
  currentSize = 0;
}

template <typename HashedObj>
bool MyHashSeparate<HashedObj>::insert(const HashedObj &x) {
  std::list<HashedObj> &whichlist = theLists[myhash(x)];
  if (std::find(whichlist.begin(), whichlist.end(), x) != whichlist.end()) {
    std::cout << "found the same element!\n" << std::endl;
    return false;
  }
  whichlist.push_front(x);
  if (++currentSize > theLists.size()) {
    rehash();
  }
  return true;
}

template <typename HashedObj>
bool MyHashSeparate<HashedObj>::remove(const HashedObj &x) {
  std::list<HashedObj> &whichlist = theLists[myhash(x)];
  std::list<HashedObj>::iterator itr =
      std::find(whichlist.begin(), whichlist.end(), x);
  if (itr == whichlist.end()) return false;
  whichlist.erase(itr);
  --currentSize;
  return true;
}

template <typename HashedObj>
void MyHashSeparate<HashedObj>::printInfo() const {
  if (currentSize == 0) {
    std::cout << "��ǰɢ�б�Ϊ��!\n" << std::endl;
    return;
  }
  std::cout << "currentSize: " << currentSize << std::endl;
  for (size_t i = 0; i < theLists.size(); i++) {
    std::cout << "KeyΪ" << i << "������Ϊ: ";
    for (auto &c : theLists[i]) std::cout << c << " ";
    std::cout << std::endl;
  }
}

template <typename HashedObj>
void MyHashSeparate<HashedObj>::rehash() {
  std::cout << "rehash happened!" << std::endl;
  std::vector<std::list<HashedObj> > oldList = theLists;
  theLists.resize(nextPrime(oldList.size()));
  for (auto &c : theLists) c.clear();
  currentSize = 0;
  for (auto &c : oldList)
    for (auto &element : c) insert(element);
}

template <typename HashedObj>
int MyHashSeparate<HashedObj>::myhash(const HashedObj &t) const {
  int hashVal = hash(t);
  hashVal %=
      theLists.size();  //�����еĹ�ϣ�����õ��Ĺ�ϣֵ���������,���ܳ��ָ�ֵ.
  if (hashVal < 0) {
    hashVal += theLists.size();
  }
  return hashVal;
}
