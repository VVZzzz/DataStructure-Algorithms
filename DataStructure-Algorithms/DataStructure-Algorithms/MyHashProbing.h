#pragma once
//�����ͻ����Ϊ̽��ɢ�е�ɢ�б�
//̽��ɢ��ע��:1.ɢ�б�Ĵ�С����Ϊ���� 2.̽��ɢ�е�ɾ����������Ϊ����ɾ��,����ɾ��֮��
//��find��������� 3.�Ѳ���Ԫ���������ɢ�б��С��һ��,�����޷��ҵ���λ����insert.

//���ļ�ʹ��"ƽ��̽�ⷨ"
#include <string>
#include <vector>
#include "HashFunc.h"

template <typename HashedObj>
class MyProbingHash {
 public:
	explicit MyProbingHash(int sz = 101): currentSize(0) {
		 theLists.reserve(sz);
		 makeEmpty();
	 }  //��ϣ��Ĵ�С���������,���ڷֲ�����.
	bool contains(const HashedObj &x) const;
	void makeEmpty();
	bool insert(const HashedObj &x) const;
	void remove(const HashedObj &x) const;
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
	int currentSize;
	bool isActive(int currentPos) const;
	int findPos(const HashedObj &x) const;			 //�˺��������ͻ
	void rehash();	//һ�������,ʹԪ�صĸ����͹�ϣ��Ĵ�С���ʹ��װ�����ӡ�1,����Ч�ʸ�.
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
