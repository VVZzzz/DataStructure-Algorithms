#pragma once
//�����ͻ����Ϊ̽��ɢ�е�ɢ�б�
//̽��ɢ��"ƽ��̽��"ʱע��:1.ɢ�б�Ĵ�С����Ϊ���� 2.̽��ɢ�е�ɾ����������Ϊ����ɾ��,����ɾ��֮��
//��find��������� 3.�Ѳ���Ԫ���������ɢ�б��С��һ��,�����޷��ҵ���λ����insert.
//̽��ɢ��"����̽��"ʱ,û��3Ҫ��,��Ϊ��������Ҳ����Ҫ��

//���ļ�ʹ��"����̽��"�����LINEAR_DETEC_HASH
//"ƽ��̽��"�����SQUARE_DETEC_HASH

//��Ϊ�㷺��ʹ��Ϊ�ڹ���ɢ�б�ʱ���ṩһ������ָ�������ṩ�Լ��Ĺ�ϣ�������߽����ͻ������
#include <string>
#include <vector>
#include "HashFunc.h"
#include "nextPrime.h"

template <typename HashedObj>
class MyProbingHash {
 public:
  explicit MyProbingHash(int sz = 101) : currentSize(0) {
    theLists.resize(nextPrime(sz));
    makeEmpty();
  }  //��ϣ��Ĵ�С���������,���ڷֲ�����.
  bool contains(const HashedObj &x) const;
  void makeEmpty();
  bool insert(const HashedObj &x);
  bool remove(const HashedObj &x);
  bool isEmpty() const;
  enum EntryType { ACTIVE, EMPTY, DELETED };

  //����������������⣬���Ҵ���KeyType���͵Ĳ�����Ӧ�õ���ͬ������ΪKeyType��findPos����������?
  template <typename KeyType>
  const HashedObj &retrive(const KeyType &key) const {
    return theLists[findPos(key)];
  }

  int getTableSize() const { return theLists.size(); }
  int getElementSize() const { return currentSize; }
  void printInfo() const;

 private:
  struct HashEntry {
    HashedObj data;
    EntryType info;  //��ʾ��Ԫ�ص�״̬,�Ƿ�ɾ��
    HashEntry(const HashedObj &t = HashedObj(), EntryType i = EMPTY)
        : data(t), info(i) {}
    const HashEntry &operator=(const HashEntry &rhs) {
      if (this == &rhs) return *this;
      data = rhs.data;
      info = rhs.info;
    }
  };
  std::vector<HashEntry> theLists;  //��ϣ��,��Ԫ��ΪHashEntry
  int currentSize;  //ע�������SeparateChain��һ������һ��Ԫ������ΪDELETEDʱ��currentsize����1.
                    //������Ϊ̽��ɢ�б���ִ������ɾ������ֻ�е�rehash��ʱ����Щdeleted��Ԫ�زŻ�����
                    //��ɾ����currentsize��ʾ�����Ѿ���ɢ�б���ռ��λ�õ�Ԫ�ظ�����
                    //ͬ��������������Ƿ�Ϊ��isEmpty��Ҳֻ�ܲ鿴theLists��Ԫ��״̬�Ƿ�ȫ��Ϊfalse�ſ��ԡ�
                    //��isEmpty();
  bool isActive(int currentPos) const;
  int findPos(const HashedObj &x) const;  //�˺��������ͻ
  void
  rehash();  //һ�������,ʹԪ�صĸ����͹�ϣ��Ĵ�С���ʹ��װ�����ӡ�1,����Ч�ʸ�.
             // rehash()���������ϣ���С
  int myhash(const HashedObj &t) const;  //��ϣ����
};

template <typename HashedObj>
bool MyProbingHash<HashedObj>::contains(const HashedObj &x) const {
  int pos = findPos(x);
  std::cout << "���� " << x << "����λ��Ϊ " << pos << " ״̬�Ƿ�ΪACTIVE "
            << std::endl;
  return isActive(pos);
}

template <typename HashedObj>
void MyProbingHash<HashedObj>::makeEmpty() {
  for (int i = 0; i < theLists.size(); i++) {
    theLists[i].info = EMPTY;
  }
}

template <typename HashedObj>
bool MyProbingHash<HashedObj>::insert(const HashedObj &x) {
  int currpos = findPos(x);
  if (isActive(currpos)) return false;  //�Ѿ�����
  theLists[currpos] = HashEntry(x, ACTIVE);
  //�������һ��ĳ���
  if (++currentSize > theLists.size() / 2) rehash();
  return true;
}

template <typename HashedObj>
bool MyProbingHash<HashedObj>::remove(const HashedObj &x) {
  int currpos = findPos(x);
  if (!isActive(currpos)) return false;
  theLists[currpos].info = DELETED;
  return true;
}

template <typename HashedObj>
bool MyProbingHash<HashedObj>::isEmpty() const {
  for (auto &c : theLists)
    if (c.info == ACTIVE) return false;
  return true;
}

template <typename HashedObj>
void MyProbingHash<HashedObj>::printInfo() const {
  if (theLists.empty()) {
    std::cout << "��ǰɢ�б�Ϊ��" << std::endl;
    return;
  }
  std::cout << "ɢ�б��СΪ: " << theLists.size()
            << " ������Ԫ����Ϊ: " << currentSize << std::endl;
  std::string state;
  for (int i = 0; i < theLists.size(); i++) {
    switch (theLists[i].info) {
      case ACTIVE:
        state = "ACTIVE";
        break;
      case EMPTY:
        state = "EMPTY";
        break;
      case DELETED:
        state = "DELETED";
        break;
      default:
        break;
    }
    std::cout << "ɢ�б�λ�� " << i << " ״̬Ϊ " << state << " ����Ϊ "
              << theLists[i].data << std::endl;
  }
}

template <typename HashedObj>
bool MyProbingHash<HashedObj>::isActive(int currentPos) const {
  return theLists[currentPos].info == ACTIVE;
}

//��Ϊ����̽��(LINEAR_DETEC_HASH),��f(i)=i,hi(x)=(hash(x)+i)%TableSize
//����posʱ,����+1����

//��Ϊƽ��̽��(SQUARE_DETEC_HASH),��f(i)=i,hi(x)=(hash(x)+i^2j)%TableSize
//����f(i)=f(i-1)+2i-1,�ɱ������˷�����.��+1 +3 +5......

//��Ϊ˫ɢ��,��fi=hash2(x),������һ��ɢ�к���. hi(x)=(hash(x)+fi)%TableSize
//������ЩΪEMPTY��data==x�Ľ��
template <typename HashedObj>
int MyProbingHash<HashedObj>::findPos(const HashedObj &x) const {
  int offset = 1;
  int double_hash_i = 1;
  int currpos = myhash(x);
  while (theLists[currpos].info != EMPTY && theLists[currpos].data != x) {
#ifdef SQUARE_DETECT_HASH
    currpos += offset;
    offset += 2;
#elif define LINEAR_DETECT_HASH
    currpos += offset;
    offset += 0;
#elif define DOUBLE_HASH_HASH
    currpos += double_hash_i * hash2(x);
    double_hash_i++;
#endif
    if (currpos >= theLists.size()) {
      currpos -= theLists.size();
    }
  }

  return currpos;
}

template <typename HashedObj>
void MyProbingHash<HashedObj>::rehash() {
  std::cout << "rehash happened!" << std::endl;
  std::vector<HashEntry> oldLists = theLists;
  theLists.resize(nextPrime(oldLists.size()));
  makeEmpty();
  currentSize = 0;  //���ɱ��Ԫ�����²��뵽�±���,��currentSize��Ϊ0
  for (auto &d : oldLists)
    if (d.info == ACTIVE) insert(d.data);
}

template <typename HashedObj>
int MyProbingHash<HashedObj>::myhash(const HashedObj &t) const {
  int hashVal = hash(t);
  hashVal %=
      theLists.size();  //�����еĹ�ϣ�����õ��Ĺ�ϣֵ���������,���ܳ��ָ�ֵ.
  if (hashVal < 0) {
    hashVal += theLists.size();
  }
  return hashVal;
}
