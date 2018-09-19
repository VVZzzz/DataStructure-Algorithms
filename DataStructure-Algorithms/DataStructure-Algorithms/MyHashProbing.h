#pragma once
//�����ͻ����Ϊ̽��ɢ�е�ɢ�б�
//̽��ɢ��ע��:1.ɢ�б�Ĵ�С����Ϊ���� 2.̽��ɢ�е�ɾ����������Ϊ����ɾ��,����ɾ��֮��
//��find��������� 3.�Ѳ���Ԫ���������ɢ�б��С��һ��,�����޷��ҵ���λ����insert.

//���ļ�ʹ��"ƽ��̽�ⷨ"
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
	 }  //��ϣ��Ĵ�С���������,���ڷֲ�����.
	bool contains(const HashedObj &x) const;
	void makeEmpty();
	bool insert(const HashedObj &x) const;
	bool remove(const HashedObj &x) const;
	bool isEmpty() const;
	enum EntryType {
		ACTIVE,
		EMPTY,
		DELETED
	};
 private:
  struct HashEntry {
		HashedObj data;
		EntryType info;															//��ʾ��Ԫ�ص�״̬,�Ƿ�ɾ��
		HashEntry(const HashedObj &t=HashedObj(),
							EntryType i=EMPTY)
			  : data(t),
					info(i) { }
  };
	std::vector<HashEntry> theLists;						 //��ϣ��,��Ԫ��ΪHashEntry
	int currentSize;	//ע�������SeparateChain��һ������һ��Ԫ������ΪDELETEDʱ��currentsize����1.
										//������Ϊ̽��ɢ�б���ִ������ɾ������ֻ�е�rehash��ʱ����Щdeleted��Ԫ�زŻ�����
										//��ɾ����currentsize��ʾ�����Ѿ���ɢ�б���ռ��λ�õ�Ԫ�ظ�����
										//ͬ��������������Ƿ�Ϊ��isEmpty��Ҳֻ�ܲ鿴theLists��Ԫ��״̬�Ƿ�ȫ��Ϊfalse�ſ��ԡ�
										//��isEmpty();
	bool isActive(int currentPos) const;
	int findPos(const HashedObj &x) const;			 //�˺��������ͻ
	void rehash();	 //һ�������,ʹԪ�صĸ����͹�ϣ��Ĵ�С���ʹ��װ�����ӡ�1,����Ч�ʸ�.
									 //rehash()���������ϣ���С
	int myhash(const HashedObj &t) const;  //��ϣ����
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
inline bool MyProbingHash<HashedObj>::insert(const HashedObj & x) const {
	int currpos = findPos(x);
	if (isActive(currpos)) return false;	//�Ѿ�����
	theLists[currpos] = HashEntry(x, ACTIVE);
	//�������һ��ĳ���
	if (++currentSize > theLists.size() / 2) rehash();
	return true;
}

template<typename HashedObj>
inline bool MyProbingHash<HashedObj>::remove(const HashedObj & x) const {
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

//�˴���f(i)=i^2.hi(x)=(hash(x)+i^2)%TableSize
//����f(i)=f(i-1)+2i-1,�ɱ������˷�����.��+1 +3 +5......
//������ЩΪEMPTY��data==x�Ľ��
template<typename HashedObj>
inline int MyProbingHash<HashedObj>::findPos(const HashedObj & x) const {
	int offset = 1;
	int currpos = hash(x);
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
	currentSize = 0;	//���ɱ��Ԫ�����²��뵽�±���,��currentSize��Ϊ0
	for (auto &c : oldLists)
		if (c.info == ACTIVE)
			insert(c.data);
}

template<typename HashedObj>
inline int MyProbingHash<HashedObj>::myhash(const HashedObj & t) const {
	int hashVal = hash(t);
	hashVal %= theLists.size();  //�����еĹ�ϣ�����õ��Ĺ�ϣֵ���������,���ܳ��ָ�ֵ.
	if (hashVal < 0) {
		hashVal += theLists.size();
	}
	return hashVal;
}
