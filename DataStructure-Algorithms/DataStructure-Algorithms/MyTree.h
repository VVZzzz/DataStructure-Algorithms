#pragma once

//树节点的定义，存放左子结点和兄弟结点
template <typename T>
struct TreeNode {
  T data;
  TreeNode *firstchild;   //子结点
  TreeNode *nextSibling;  //兄弟结点
};


//二叉查找树的类
template <typename T>
class BinarySearchTree{
 public:
  BinarySearchTree();
  BinarySearchTree( const BinarySearchTree &rhs ) const ;
  ~BinarySearchTree();

  const T &findMin() const;
  const T &findMax() const;
  bool contains(const T &x) const;
  bool isEmpty() const;
  void printTree() const;

  void makeEmpty();
  void insert(const T &x);
  void remove(const T &x);

  const BinarySearchTree &operator=(const BinarySearchTree &rhs);

 private:
  struct BinaryNode {
    T data;
    BinaryNode *left;
    BinaryNode *right;
    BinarySearchTree(const T &t, BinaryNode *l, BinaryNode *r)
        : data(t), left(l), right(r) { }
  };
  BinaryNode *root;

  void insert(const T &x, BinaryNode *&t) const;
  void remove(const T &x, BinaryNode *&t) const;
  BinaryNode *findMin(BinaryNode *t) const{
    if (t == nullptr) {
    return nullptr;
    }
    if (t->left == nullptr) {
      return t;
    }
    return t->left;
  }
  BinaryNode *findMax(BinaryNode *t) const {
    if (t!=nullptr) 
      while (t->right != nullptr) t = t->right;
    return t;
  }
  bool contains(const T &x, BinaryNode *&t) const;
  void makeEmpty(BinaryNode *&t);
  void printTree(BinaryNode *t) const;
  BinaryNode *clone(BinaryNode *t) const;
};

template <typename T>
inline bool BinarySearchTree<T>::contains(const T &x) const {
  return contains(x, root);
}

template <typename T>
inline void BinarySearchTree<T>::insert(const T &x) {
  insert(x, root);
}

template <typename T>
inline void BinarySearchTree<T>::remove(const T &x) {
  remove(x, root);
}

template <typename T>
void BinarySearchTree<T>::insert(const T &x, BinaryNode *&t) const {
  if (t == nullptr)
    t = new BinaryNode(x, nullptr, nullptr);
  else if (t->data < x)
    insert(x, t->right);
  else if (x < t->data)
    insert(x, t->left);
  else
    //已存在，do nothing;
}

template <typename T>
bool BinarySearchTree<T>::contains(const T &x, BinaryNode *&t) const {
  if (t==nullptr) {
    return false;
  } else if (x < t->data) {
    return contains(x, t->left);
  } else if (t->data < x) {
    return contains(x, t->right);
  } else {
    return true;
  }
}

