#pragma once
#include "MyPair.h"
#include "MyHashProbing.h"
//ע��map�ֵ��еĵײ�ɢ�б��Ԫ������ΪMyPair<HashedObj,Object>,���Ҫ�����ǵ�hash()����Ҫ֧���������͵ļ��㡣
//ͬʱ��MyProbingHash����ҲҪ����һ�����޸ġ�
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