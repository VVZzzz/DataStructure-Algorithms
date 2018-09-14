#pragma once
// 4.11
//此处Set类使用简单的二叉查找树实现
//即Set即二叉查找树，更新了insert和添加了iterator和const_iterator
template <typename T>
class Set {
 public:
	struct BinaryNode;
  class const_iterator {
   friend class Set<T>;
   public: 
    const_iterator() : current(nullptr) {}
    const T & operator*() const { return retrive(); }
    //前置++
    const_iterator & operator++() const { 
      if (current->right) {
        BinaryNode<T> *t = current->right;
        while (t->left!=nullptr) {
          t = t->left;
        }
        current = t;
      } else {
        //注意此处的++是考虑到4的右子树为5，5的右子树为6，而4的父节点为7，则6的++之后的结点为7
        t = current->parent;
        while (t&&t->data<current->data) {
          t = t->parent;
        }
        current = t;
      }
      return *this;
    }
    //后置++,返回的不是引用.
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
    //前置++
    iterator & operator++() { 
      if (current->right) {
        BinaryNode<T> *t = current->right;
        while (t->left!=nullptr) {
          t = t->left;
        }
        current = t;
      } else {
        //注意此处的++是考虑到4的右子树为5，5的右子树为6，而4的父节点为7，则6的++之后的结点为7
        t = current->parent;
        while (t&&t->data<current->data) {
          t = t->parent;
        }
        current = t;
      }
      return *this;
    }
    //后置++,返回的不是引用.
    iterator operator++(int) { 
      iterator old = *this;
      ++(*this);
      return old;
    }
   private:
    iterator(BinaryNode * t) : const_iterator(t) {}
  };
  Set() : root(nullptr), Size(0) {}
  //拷贝构造函数
  Set(const Set &rhs);
  ~Set();
  iterator insert(const T &x) { 
    Size++;
    return insert(x, root, root);
  }
  //剩下的接口函数即二叉查找树
 protected:
  struct BinaryNode {
    T data;
    BinaryNode *left;
    BinaryNode *right;
    BinaryNode *parent;  //指向父结点的指针

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
      return iterator(t);  //要插入的元素已经在set中了
    }
  }
};

//4.12 Map类底层存储为Set<pair<KeyType,ValueType>>,只用实现Map的一些常用接口即可。

//4.13 略

//4.14 不太明白

//4.15
//没有做实验。应该是随机选用

//4.16
//见MyTree.h,定义lazy版本的remove insert findMin findMax
template <typename T=int>
struct BTNode {
	T data;
	BTNode *left;
	BTNode *right;
	BTNode(const T& t,BTNode *l,BTNode *r):
		data(t), left(t), right(r) {}
	BTNode():data(T()),left(nullptr),right(nullptr) {}
};
//4.45 判断两棵树是否相似
template <typename T=int>
bool isSimilar(BTNode<T> *t1, BTNode<T> *t2) {
	if (t1 == nullptr || t2 == nullptr)
		return t1 == nullptr&&t2 == nullptr;
	return isSimilar(t1->left, t2->left) && isSimilar(t1->right, t2->right);
}

//4.46 判断两树是否同构
template <typename T=int>
bool isOmorphic(BTNode<T> *t1, BTNode<T> *t2) {
	if (t1 == nullptr&&t2 == nullptr) return true;
	if (t1 == nullptr&&t2 != nullptr || t2 == nullptr&&t1 != nullptr)
		return false;
	if (t1->data != t2->data) return false;
	//同一侧的树都为空(即没有发生交换),则检查另一侧的
	if (t1->left == nullptr&&t2->left == nullptr)return isOmorphic(t1->right, t2->right);

	//没有发生交换
	if ((t1->left != nullptr&&t2->left != nullptr) && (t1->left->data == t2->left->data))
		return isOmorphic(t1->left, t1->left) && isOmorphic(t1->right, t2->right);
	else //否则
		return isOmorphic(t1->right, t1->left) && isOmorphic(t1->left, t2->right);
}
