#pragma once
#include "MyPair.h"
#include "MyHashProbing.h"
//注意map字典中的底层散列表的元素类型为MyPair<HashedObj,Object>,这就要求我们的hash()函数要支持这种类型的计算。
//同时在MyProbingHash类中也要进行一定的修改。
template <typename HashedObj,typename Object>
class Dictionary{
 public:
	Dictionary() {};
	void insert(const HashedObj & key, const Object & val) {
		items.insert(MyPair<HashedObj, Object>(key, val));
	}
	const Object & lookup(const HashedObj &key) const {
		return items.retrive(key).second();
	}
	bool isEmpty() const { return items.isEmpty(); }
	void makeEmpty() { return items.makeEmpty(); }
 private:
	MyProbingHash<MyPair<HashedObj, Object> > items;
};