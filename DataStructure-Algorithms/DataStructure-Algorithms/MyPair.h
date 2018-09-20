#pragma once
template <typename HashedObj,typename Object>
class MyPair{
 public:
	MyPair(const HashedObj &k, const Object &t) : key(k), val(t) {}
	HashedObj & first() { return key; }
	HashedObj & second() { return key; }
 private:
	HashedObj key;
	Object val;
};