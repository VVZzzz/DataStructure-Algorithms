#pragma once

//���ڵ�Ķ��壬������ӽ����ֵܽ��
template <typename T>
struct TreeNode {
  T data;
  TreeNode *firstchild;   //�ӽ��
  TreeNode *nextSibling;  //�ֵܽ��
};


//�������������
template <typename T>
class BinarySearchTree{
 public:
  BinarySearchTree();
  BinarySearchTree( const BinarySearchTree &rhs ) const ;
  ~BinarySearchTree() { makeEmpty(); }

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
  void remove(const T &x, BinaryNode *&t);
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
  BinaryNode *clone(BinaryNode *t) const {
    if (t==nullptr) {
      return nullptr;
    }
    return new BinaryNode(t->data, clone(t->left), clone(t->right));
  }
};

template <typename T>
inline bool BinarySearchTree<T>::contains(const T &x) const {
  return contains(x, root);
}

template <typename T>
inline void BinarySearchTree<T>::makeEmpty() {
  makeEmpty(root);
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
inline const BinarySearchTree<T> &BinarySearchTree<T>::operator=(
    const BinarySearchTree &rhs) {
  if (this!=rhs) {
    makeEmpty();
    root = clone(rhs.root);
  }
  return *this;
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
    //�Ѵ��ڣ�do nothing;
}

//���remove������������������Ч�ʲ���
template <typename T>
inline void BinarySearchTree<T>::remove(const T &x, BinaryNode *&t) {
  if (t==nullptr) {
    return;
  } else if (x < t->data) {
    remove(x, t->left);
  } else if (x > t->data) {
    remove(x, t->right);
  } else if (t->left!=nullptr && t->right!=nullptr) {
    t->data = findMin(t->right)->data;  //�ҵ��������������ӽڵ�
    remove (t->data,t->right);  //���ŵݹ�ɾ������������������ӽ��
  } else {
    BinaryNode *oldNode = t;
    t = (t->left != nullptr) ? t->left : t->right;
    delete oldNode;
  }
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

template <typename T>
inline void BinarySearchTree<T>::makeEmpty(BinaryNode *&t) {
  if (t!=nullptr) {
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
  }
  t = nullptr;
}

