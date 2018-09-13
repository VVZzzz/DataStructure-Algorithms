#pragma once
// 4.11
//�˴�Set��ʹ�ü򵥵Ķ��������ʵ��
//��Set�������������������insert�������iterator��const_iterator
template <typename T>
class Set {
 public:
	struct BinaryNode;
  class const_iterator {
   friend class Set<T>;
   public: 
    const_iterator() : current(nullptr) {}
    const T & operator*() const { return retrive(); }
    //ǰ��++
    const_iterator & operator++() const { 
      if (current->right) {
        BinaryNode<T> *t = current->right;
        while (t->left!=nullptr) {
          t = t->left;
        }
        current = t;
      } else {
        //ע��˴���++�ǿ��ǵ�4��������Ϊ5��5��������Ϊ6����4�ĸ��ڵ�Ϊ7����6��++֮��Ľ��Ϊ7
        t = current->parent;
        while (t&&t->data<current->data) {
          t = t->parent;
        }
        current = t;
      }
      return *this;
    }
    //����++,���صĲ�������.
    const_iterator operator++(int) { 
      const_iterator old = *this;
      ++(*this);
      return old;
    }
    bool operator==(const const_iterator &rhs) const { return *this == rhs; }
    bool operator!=(const const_iterator &rhs) const { return !(*this == rhs); }
   protected:
    BinaryNode *current;
    T &retrive() const { return current->data; }
    const_iterator(BinaryNode *p) : current(p) {}
  }; 
  class iterator:public const_iterator {
   friend class Set;
   public:
    iterator() : const_iterator() {}
    T &operator*() const { return const_iterator::retrive(); }
    const T &operator*() const { return const_iterator::operator *(); }
    //ǰ��++
    iterator & operator++() { 
      if (current->right) {
        BinaryNode<T> *t = current->right;
        while (t->left!=nullptr) {
          t = t->left;
        }
        current = t;
      } else {
        //ע��˴���++�ǿ��ǵ�4��������Ϊ5��5��������Ϊ6����4�ĸ��ڵ�Ϊ7����6��++֮��Ľ��Ϊ7
        t = current->parent;
        while (t&&t->data<current->data) {
          t = t->parent;
        }
        current = t;
      }
      return *this;
    }
    //����++,���صĲ�������.
    iterator operator++(int) { 
      iterator old = *this;
      ++(*this);
      return old;
    }
   private:
    iterator(BinaryNode * t) : const_iterator(t) {}
  };
  Set() : root(nullptr), Size(0) {}
  //�������캯��
  Set(const Set &rhs);
  ~Set();
  iterator insert(const T &x) { 
    Size++;
    return insert(x, root, root);
  }
  //ʣ�µĽӿں��������������
 protected:
  struct BinaryNode {
    T data;
    BinaryNode *left;
    BinaryNode *right;
    BinaryNode *parent;  //ָ�򸸽���ָ��

    BinaryNode() { left = right = parent = nullptr; }
    BinaryNode(const T &element)
        : left(nullptr), right(nullptr), parent(nullptr), data(element) {}
    BinaryNode(const T &element, BinaryNode *l, BinaryNode *r, BinaryNode *p)
        : data(element), left(l), right(s), parent(r) {}
  };
  BinaryNode *root;
  int Size;
  iterator insert(const T &x, BinaryNode *t, BinaryNode *p) {
    if (t==nullptr) {
      t = new BinaryNode(x, nullptr, nullptr, p);
      return iterator(t);
    } else if (x < t->data) {
      insert(x, t->left, t);
    } else if (x > t->data) {
      insert(x, t->right, t);
    } else {
      return iterator(t);  //Ҫ�����Ԫ���Ѿ���set����
    }
  }
};

//4.12 Map��ײ�洢ΪSet<pair<KeyType,ValueType>>,ֻ��ʵ��Map��һЩ���ýӿڼ��ɡ�

//4.13 ��

//4.14 ��̫����

//4.15
//û����ʵ�顣Ӧ�������ѡ��

//4.16
//��MyTree.h,����lazy�汾��remove insert findMin findMax

//4.34
