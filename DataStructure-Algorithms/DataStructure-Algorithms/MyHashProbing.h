#pragma once
//解决冲突策略为探测散列的散列表
//探测散列注意:1.散列表的大小必须为素数 2.探测散列的删除操作必须为懒惰删除,否则删除之后
//的find操作会出错 3.已插入元素数必须≤散列表大小的一半,否则无法找到空位进行insert.

//此文件使用"平方探测法"

//更为广泛的使用为在构造散列表时，提供一个函数指针用来提供自己的哈希函数或者解决冲突函数。
#include <string>
#include <vector>
#include "HashFunc.h"
#include "nextPrime.h"

template <typename HashedObj>
class MyProbingHash {
 public:
	explicit MyProbingHash(int sz = 101): currentSize(0) {
		theLists.resize(nextPrime(sz));
		 makeEmpty();
	 }  //哈希表的大小最好是素数,利于分布均匀.
	bool contains(const HashedObj &x) const;
	void makeEmpty();
	bool insert(const HashedObj &x);
	bool remove(const HashedObj &x);
	bool isEmpty() const;
	enum EntryType {
		ACTIVE,
		EMPTY,
		DELETED
	};

	//下面这个函数有问题，即我传入KeyType类型的参数，应该调用同样类型为KeyType的findPos，该怎样做?
	template<typename KeyType>
	const HashedObj &retrive(const KeyType &key) const{
		return theLists[findPos(key)];
	}

	int getTableSize() const { return theLists.size(); }
	int getElementSize() const { return currentSize; }
 private:
  struct HashEntry {
		HashedObj data;
		EntryType info;															//表示该元素的状态,是否被删除
		HashEntry(const HashedObj &t=HashedObj(),
							EntryType i=EMPTY)
			  : data(t),
					info(i) { }
		const HashEntry &operator=(const HashEntry &rhs){
			if (this == &rhs) return *this;
			data = rhs.data;
			info = rhs.info;
		}
  };
	std::vector<HashEntry> theLists;						 //哈希表,其元素为HashEntry
	int currentSize;	//注意这里和SeparateChain不一样，当一个元素设置为DELETED时，currentsize不减1.
										//这是因为探测散列必须执行懒惰删除，而只有当rehash的时候，这些deleted的元素才会真正
										//的删除。currentsize表示的是已经在散列表中占据位置的元素个数。
										//同样，考察这个表是否为空isEmpty。也只能查看theLists中元素状态是否全部为false才可以。
										//见isEmpty();
	bool isActive(int currentPos) const;
	int findPos(const HashedObj &x) const;			 //此函数解决冲突
	void rehash();	 //一般情况下,使元素的个数和哈希表的大小相等使得装填因子≈1,查找效率高.
									 //rehash()用来扩充哈希表大小
	int myhash(const HashedObj &t) const;  //哈希函数
};

template<typename HashedObj>
inline bool MyProbingHash<HashedObj>::contains(const HashedObj & x) const {
	return isActive(findPos(x));
}

template<typename HashedObj>
inline void MyProbingHash<HashedObj>::makeEmpty() {
	for (int i = 0; i < theLists.size(); i++) {
		theLists[i].info = EMPTY;
	}
}

template<typename HashedObj>
inline bool MyProbingHash<HashedObj>::insert(const HashedObj & x) {
	int currpos = findPos(x);
	if (isActive(currpos)) return false;	//已经存在
	theLists[currpos] = HashEntry(x, ACTIVE);
	//如果大于一半的长度
	if (++currentSize > theLists.size() / 2) rehash();
	return true;
}

template<typename HashedObj>
inline bool MyProbingHash<HashedObj>::remove(const HashedObj & x) {
	int currpos = findPos(x);
	if (!isActive(currpos)) return false;
	theLists[currpos].info = DELETED;
	return true;
}

template<typename HashedObj>
inline bool MyProbingHash<HashedObj>::isEmpty() const {
	for (auto &c : theLists)
		if (c.info == ACTIVE)
			return false;
	return true;
}

template<typename HashedObj>
inline bool MyProbingHash<HashedObj>::isActive(int currentPos) const {
	return theLists[currentPos].info == ACTIVE;
}

//此处的f(i)=i^2.hi(x)=(hash(x)+i^2)%TableSize
//计算f(i)=f(i-1)+2i-1,可避免做乘法运算.即+1 +3 +5......
//返回那些为EMPTY和data==x的结点
template<typename HashedObj>
inline int MyProbingHash<HashedObj>::findPos(const HashedObj & x) const {
	int offset = 1;
	int currpos = myhash(x);
	while (theLists[currpos].info!=EMPTY&&
				 theLists[currpos].data!=x) {
		currpos += offset;
		offset += 2;
		if (currpos>=theLists.size()) {
			currpos -= theLists.size();
		}
	}
	return currpos;
}

template<typename HashedObj>
inline void MyProbingHash<HashedObj>::rehash() {
	std::vector<HashEntry> oldLists = theLists;
	theLists.resize(nextPrime(oldLists.size()));
	for (auto &c : theLists)
		c.info = EMPTY;
	currentSize = 0;	//将旧表的元素重新插入到新表中,故currentSize变为0
	for (auto &d : oldLists)
		if (d.info == ACTIVE)
			insert(d.data);
}

template<typename HashedObj>
inline int MyProbingHash<HashedObj>::myhash(const HashedObj & t) const {
	int hashVal = hash(t);
	hashVal %= theLists.size();  //由于有的哈希函数得到的哈希值过大导致溢出,可能出现负值.
	if (hashVal < 0) {
		hashVal += theLists.size();
	}
	return hashVal;
}
