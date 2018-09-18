#pragma once
#include <vector>
#include <list>
#include <string>
//��ϣ��(�����ͻΪ�������ӷ�)
template <typename HashedObj>
//�˴���ϣ��Ҫ��HashedObj�����ṩoperator==����operator!=����
class MyHashTable {
 public:
	 explicit MyHashTable(int sz = 101): currentSize(0) {
		 theLists.reserve(sz);
	 }  //��ϣ��Ĵ�С���������,���ڷֲ�����.
	bool contains(const HashedObj &x) const;
	void makeEmpty();
	void insert(const HashedObj &x) const;
	void remove(const HashedObj &x) const;
 private:
	std::vector<std::list<HashedObj> > theLists;  //��ϣ��,��Ԫ��Ϊһ�������ͻ������.
	int currentSize;
	void rehash();  //һ�������,ʹԪ�صĸ����͹�ϣ��Ĵ�С���ʹ��װ�����ӡ�1,����Ч�ʸ�.
									//rehash()���������ϣ���С
	int myhash(const HashedObj &t) const;  //��ϣ����
};

//ͨ�õ�������ϣ����
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
	hashVal %= theLists.size();  //�����еĹ�ϣ�����õ��Ĺ�ϣֵ���������,���ܳ��ָ�ֵ.
	if (hashVal < 0) {
		hashVal += theLists.size();
	}
	return hashVal;
}
