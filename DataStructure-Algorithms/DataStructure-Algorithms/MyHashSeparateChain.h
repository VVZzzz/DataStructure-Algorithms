#pragma once
#include <vector>
#include <list>
#include <string>
#include "HashFunc.h"
#include "nextPrime.h"
//哈希表(解决冲突为分离链接法)
template <typename HashedObj>
//此处哈希表要求HashedObj类型提供operator==或者operator!=操作
//更为广泛的使用为在构造散列表时，提供一个函数指针用来提供自己的哈希函数或者解决冲突函数。
//或者就固定使用hash(int);hash(const string &);在对应特定的类型时，hash(const T&);调用hash(T.getNameString());
class MyHashSeparate {
 public:
	 explicit MyHashSeparate(int sz = 101): currentSize(0) {
		 theLists.resize(nextPrime(sz));
		 makeEmpty();
	 }  //哈希表的大小最好是素数,利于分布均匀.
	bool contains(const HashedObj &x) const;
	void makeEmpty();
	bool insert(const HashedObj &x) ;
	bool remove(const HashedObj &x) ;
	int getTableSize() const { return theLists.size(); }
	int getElementSize() const { return currentSize; }
 private:
	std::vector<std::list<HashedObj> > theLists;  //哈希表,其元素为一个解决冲突的链表.
	int currentSize;  
	void rehash();    //一般情况下,使元素的个数和哈希表的大小相等使得装填因子≈1,查找效率高.
									  //rehash()用来扩充哈希表大小
	int myhash(const HashedObj &t) const;  //哈希函数
};


template<typename HashedObj>
inline bool MyHashSeparate<HashedObj>::contains(const HashedObj & x) const {
	int temp = myhash(x);
	return std::find(theLists[temp].begin(), theLists[temp].end(), x) != theLists[temp].end();
}

template<typename HashedObj>
inline void MyHashSeparate<HashedObj>::makeEmpty() {
	for (int i = 0; i < theLists.size();i++) {
		theLists[i].clear();
	}
	currentSize = 0;
}

template<typename HashedObj>
inline bool MyHashSeparate<HashedObj>::insert(const HashedObj & x) {
	std::list<HashedObj> & whichlist = theLists[myhash(x)];
	if (std::find(whichlist.begin(), whichlist.end(), x) != whichlist.end())
		return false;
	whichlist.push_front(x);
	if (++currentSize>theLists.size()) {
		rehash();
	}
	return true;
}

template<typename HashedObj>
inline bool MyHashSeparate<HashedObj>::remove(const HashedObj & x) {
	std::list<HashedObj> & whichlist = theLists[myhash(x)];
	std::list<HashedObj>::iterator itr = std::find(whichlist.begin(), whichlist.end(), x);
	if (itr == whichlist.end()) return false;
	whichlist.erase(itr);
	--currentSize;
	return true;
}

template<typename HashedObj>
inline void MyHashSeparate<HashedObj>::rehash() {
	std::vector<std::list<HashedObj> > oldList = theLists;
	theLists.resize(nextPrime(oldList.size()));
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
	hashVal %= theLists.size();  //由于有的哈希函数得到的哈希值过大导致溢出,可能出现负值.
	if (hashVal < 0) {
		hashVal += theLists.size();
	}
	return hashVal;
}
