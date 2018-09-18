#pragma once
#include <vector>
#include <list>
#include <string>
//哈希表(解决冲突为分离链接法)
template <typename HashedObj>
//此处哈希表要求HashedObj类型提供operator==或者operator!=操作
class MyHashTable {
 public:
	 explicit MyHashTable(int sz = 101): currentSize(0) {
		 theLists.reserve(sz);
	 }  //哈希表的大小最好是素数,利于分布均匀.
	bool contains(const HashedObj &x) const;
	void makeEmpty();
	void insert(const HashedObj &x) const;
	void remove(const HashedObj &x) const;
 private:
	std::vector<std::list<HashedObj> > theLists;  //哈希表,其元素为一个解决冲突的链表.
	int currentSize;
	void rehash();  //一般情况下,使元素的个数和哈希表的大小相等使得装填因子≈1,查找效率高.
									//rehash()用来扩充哈希表大小
	int myhash(const HashedObj &t) const;  //哈希函数
};

//通用的两个哈希函数
int hash(int key) {
	return 0;
}

int hash(const std::string & str) {
	return 0;
}

template<typename HashedObj>
inline bool MyHashTable<HashedObj>::contains(const HashedObj & x) const {
	int temp = myhash(x);
	return std::find(theLists[temp].begin(), theLists[temp].end(),x);
}

template<typename HashedObj>
inline void MyHashTable<HashedObj>::makeEmpty() {
	for (int i = 0; i < theLists.size();i++) {
		theLists[i].clear();
	}
	currentSize = 0;
}

template<typename HashedObj>
inline void MyHashTable<HashedObj>::insert(const HashedObj & x) const {
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
inline void MyHashTable<HashedObj>::remove(const HashedObj & x) const {
	std::list<HashedObj> & whichlist = theLists[hash(x)];
	std::list<HashedObj>::iterator itr = std::find(whichlist.begin(), whichlist.end(), x);
	if (itr == whichlist.end()) return false;
	whichlist.erase(itr);
	--currentSize;
	return true;
}

template<typename HashedObj>
inline int MyHashTable<HashedObj>::myhash(const HashedObj & t) const {
	int hashVal = hash(x);
	hashVal %= theLists.size();  //由于有的哈希函数得到的哈希值过大导致溢出,可能出现负值.
	if (hashVal < 0) {
		hashVal += theLists.size();
	}
	return hashVal;
}
