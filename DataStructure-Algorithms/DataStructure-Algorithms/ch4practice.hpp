#pragma once
// 4.11
//此处Set类使用简单的二叉查找树实现
template <typename T>
class Set {
 public:
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
    BinaryNode<T> *current;
    T &retrive() const { return current->data; }
    const_iterator(BinaryNode<T> *p) : current(p) {}
  }; 
  class iterator:public const_iterator {
   friend class BinaryNode<T>;
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
    iterator(BinaryNode<T> * t) : const_iterator(t) {}
  };
 private:
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
};