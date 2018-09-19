#pragma once
#include <vector>
#include <list>
#include <string>
#include "HashFunc.h"
#include "nextPrime.h"
//��ϣ��(�����ͻΪ�������ӷ�)
template <typename HashedObj>
//�˴���ϣ��Ҫ��HashedObj�����ṩoperator==����operator!=����
class MyHashSeparate {
 public:
	 explicit MyHashSeparate(int sz = 101): currentSize(0) {
		 theLists.resize(nextPrime(sz));
		 makeEmpty();
	 }  //��ϣ���Ĵ�С���������,���ڷֲ�����.
	bool contains(const HashedObj &x) const;
	void makeEmpty();
	bool insert(const HashedObj &x) const;
	bool remove(const HashedObj &x) const;
 private:
	std::vector<std::list<HashedObj> > theLists;  //��ϣ��,��Ԫ��Ϊһ�������ͻ������.
	int currentSize;
	void rehash();  //һ�������,ʹԪ�صĸ����͹�ϣ���Ĵ�С���ʹ��װ�����ӡ�1,����Ч�ʸ�.
									//rehash()���������ϣ����С
	int myhash(const HashedObj &t) const;  //��ϣ����
};


template<typename HashedObj>
inline bool MyHashSeparate<HashedObj>::contains(const HashedObj & x) const {
	int temp = myhash(x);
	return std::find(theLists[temp].begin(), theLists[temp].end(),x);
}

template<typename HashedObj>
inline void MyHashSeparate<HashedObj>::makeEmpty() {
	for (int i = 0; i < theLists.size();i++) {
		theLists[i].clear();
	}
	currentSize = 0;
}

template<typename HashedObj>
inline bool MyHashSeparate<HashedObj>::insert(const HashedObj & x) const {
	std::list<HashedObj> & whichlist = theLists[hash(x)];
	if (std::find(whichlist.begin(), whichlist.end(), x) == whichlist.end())
		return false;
	whichlist.push_front(x);
	if (++currentSize>theLists.size()) {
		rehash();
	}
	return true;
}

template<typename HashedObj>
inline bool MyHashSeparate<HashedObj>::remove(const HashedObj & x) const {
	std::list<HashedObj> & whichlist = theLists[hash(x)];
	std::list<HashedObj>::iterator itr = std::find(whichlist.begin(), whichlist.end(), x);
	if (itr == whichlist.end()) return false;
	whichlist.erase(itr);
	--currentSize;
	return true;
}

template<typename HashedObj>
inline void MyHashSeparate<HashedObj>::rehash() {
	std::vector<std::list<HashedObj> > oldList = theLists;
	theLists.resize(oldList.size());
	for (auto &c : theLists)
		c.clear();
	currentSize = 0;
	for (auto &c : oldList)
		for (auto &element : c)
			insert(element);
}

template<typename HashedObj>
inline int MyHashSeparate<HashedObj>::myhash(const HashedObj & t) const {
	int hashVal = hash(t);
	hashVal %= theLists.size();  //�����еĹ�ϣ�����õ��Ĺ�ϣֵ���������,���ܳ��ָ�ֵ.
	if (hashVal < 0) {
		hashVal += theLists.size();
	}
	return hashVal;
}