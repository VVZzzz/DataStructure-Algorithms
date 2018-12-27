#pragma once
#include <iostream>
#include <queue>
#include <stack>
//���ڵ�Ķ��壬������ӽ����ֵܽ��
template <typename T>
struct TreeNode {
  T data;
  TreeNode *firstchild;   //�ӽ��
  TreeNode *nextSibling;  //�ֵܽ��
};

//�������������
template <typename T = int>
class BinarySearchTree {
 public:
  struct BinaryNode;
  BinarySearchTree();
  BinarySearchTree(const BinarySearchTree &rhs);
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

  //�õ������
  int countNodes() const { return countNodes(root); }
  //�õ���Ҷ��
  int countLeaves() const { return countLeaves(root); }
  //�õ��������
  int countFullNodes() const { return countFullNodes(root); }

  //����Ƿ�ΪBST
  bool isBST_1(BinaryNode *t) const;
  bool isBST_2(BinaryNode *t) const;
  bool isBST_3(BinaryNode *t) const;
  bool isBST_4(BinaryNode *t) const;

  // 4.33 �ݹ�ɾ��Ҷ�ӽ��
  void remove_leaves() { return remove_leaves(root); }

  // 4.34 ����low~up���������������,rndInt(low,up)����low��up֮��������
  int rndInt(int low, int up) { return (up + low) / 2; }
  void makeRandomTree(int low, int up);

  // 4.37 ��ӡ[k1,k2]��Χ�ڵĽ��ֵ
  void printRange(const T &low, const T &up, BinaryNode *t) const;

  // 4.40 �������������
  void levelOrder(BinaryNode *t) const;

 private:
  struct BinaryNode {
    T data;
    BinaryNode *left;
    BinaryNode *right;
    bool isDeleted;  //����ɾ����־
    BinaryNode(const T &t, BinaryNode *l, BinaryNode *r, bool flag = false)
        : data(t), left(l), right(r), isDeleted(flag) {}
    BinaryNode() : data(T()), left(nullptr), right(nullptr), isDeleted(false) {}
  };
  BinaryNode *root;
  int theSize;
  int deletedSize;

  void insert(const T &x, BinaryNode *&t) const;
  void remove(const T &x, BinaryNode *&t);

  BinaryNode *findMin(BinaryNode *t) const {
    if (t == nullptr) {
      return nullptr;
    }
    if (t->left == nullptr) {
      return t;
    }
    return findMin(t->left);
  }
  BinaryNode *findMax(BinaryNode *t) const {
    if (t != nullptr)
      while (t->right != nullptr) t = t->right;
    return t;
  }
  bool contains(const T &x, BinaryNode *t) const;
  void makeEmpty(BinaryNode *&t);
  BinaryNode *clone(BinaryNode *t) const {
    if (t == nullptr) {
      return nullptr;
    }
    return new BinaryNode(t->data, clone(t->left), clone(t->right));
  }

  //����ɾ���汾��insert remove contains findMin findMax
  void lazy_insert(const T &x, BinaryNode *&t) const;
  bool lazy_contains(const T &x, BinaryNode *&t) const;
  void lazy_remove(const T &x, BinaryNode *&t);
  void lazy_chkrmall();
  void lazy_dormall(BinaryNode *&t);
  BinaryNode *lazy_findMin(BinaryNode *t) const {
    if (t != nullptr) {
      BinaryNode *ltemp = lazy_findMin(t->left);
      if (ltemp != nullptr && ltemp->isDeleted == false) return ltemp;
      BinaryNode *rtemp = lazy_findMin(t->right);
      if (rtemp != nullptr && rtemp->isDeleted == false) return rtemp;
    }
  }
  BinaryNode *lazy_findMax(BinaryNode *t) const {
    BinaryNode *ltemp = lazy_findMin(t->right);
    if (ltemp != nullptr && ltemp->isDeleted == false) return ltemp;
    BinaryNode *rtemp = lazy_findMin(t->left);
    if (rtemp != nullptr && rtemp->isDeleted == false) return rtemp;
    //û���ҵ�
    return nullptr;
  }

  // isBST�汾1�Ĺ��ߺ���
  bool isBSTUtil_1(BinaryNode *t, long long int min, long long int max) const;
  bool isBSTUtil_2(BinaryNode *t, BinaryNode *minNode,
                   BinaryNode *maxNode) const;
  bool isBSTUtil_3(BinaryNode *t, BinaryNode *&prev) const;
  int countNodes(BinaryNode *t) const;
  int countLeaves(BinaryNode *t) const;
  int countFullNodes(BinaryNode *t) const;
  void remove_leaves(BinaryNode *&t) ;
};

template <typename T>
inline BinarySearchTree<T>::BinarySearchTree()
    : root(nullptr), theSize(0), deletedSize(0) {}

template <typename T>
inline BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree &rhs) {
  theSize = rhs.theSize;
  deletedSize = rhs.deletedSize;
  root = clone(rhs.root);
}

template <typename T>
inline const T &BinarySearchTree<T>::findMin() const {
  BinaryNode *t = findMin(root);
  if (t != nullptr) {
    return t->data;
  } else {
    //û�ҵ���Сֵ
    return T();
  }
}

template <typename T>
inline const T &BinarySearchTree<T>::findMax() const {
  // TODO: �ڴ˴����� return ���
  BinaryNode *t = findMax(root);
  if (t != nullptr) {
    return t->data;
  } else {
    //û�ҵ����ֵ
    return T();
  }
}

template <typename T>
inline bool BinarySearchTree<T>::contains(const T &x) const {
  return contains(x, root);
}

template <typename T>
inline bool BinarySearchTree<T>::isEmpty() const {
  return root == nullptr;
}

template <typename T>
inline void BinarySearchTree<T>::printTree() const {
  if (root == nullptr) {
    std::cout << "This tree is null." << std::endl;
    return;
  }
  BinaryNode *sep_node = new BinaryNode();
  std::queue<BinaryNode *> node_queue;
  BinaryNode *opnode;
  node_queue.push(root);
  node_queue.push(sep_node);
  while (!node_queue.empty()) {
    opnode = node_queue.front();
    if (opnode == nullptr)
      std::cout << "nullptr ";
    else if (opnode == sep_node) {
      if (node_queue.size() == 1) break;
      std::cout << std::endl;
      node_queue.push(sep_node);
    } else {
      std::cout << opnode->data << " ";
      node_queue.push(opnode->left);
      node_queue.push(opnode->right);
    }
    //��opnode���в���
    node_queue.pop();
  }
  delete sep_node;
  return;
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
  if (this != rhs) {
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
    ;
  //�Ѵ��ڣ�do nothing;
}

//���remove������������������Ч�ʲ���
template <typename T>
inline void BinarySearchTree<T>::remove(const T &x, BinaryNode *&t) {
  if (t == nullptr) {
    return;
  } else if (x < t->data) {
    remove(x, t->left);
  } else if (x > t->data) {
    remove(x, t->right);
  } else if (t->left != nullptr && t->right != nullptr) {
    t->data = findMin(t->right)->data;  //�ҵ��������������ӽڵ�
    remove(t->data, t->right);  //���ŵݹ�ɾ������������������ӽ��
  } else {
    BinaryNode *oldNode = t;
    t = (t->left != nullptr) ? t->left : t->right;
    delete oldNode;
  }
}

template <typename T>
bool BinarySearchTree<T>::contains(const T &x, BinaryNode *t) const {
  if (t == nullptr) {
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
  if (t != nullptr) {
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
  }
  t = nullptr;
}

//����ɾ���汾��insert remove contains makeEmpty
template <typename T>
void BinarySearchTree<T>::lazy_insert(const T &x, BinaryNode *&t) const {
  if (t == nullptr) {
    theSize++;
    t = new BinaryNode(x, nullptr, nullptr, false);
  } else if (t->data < x)
    insert(x, t->right);
  else if (x < t->data)
    insert(x, t->left);
  else {
    if (t->isDeleted)
      t->isDeleted = false;
    else
    //�Ѵ��ڣ�do nothing;
  }
}

template <typename T>
bool BinarySearchTree<T>::lazy_contains(const T &x, BinaryNode *&t) const {
  if (t == nullptr) {
    return false;
  } else if (x < t->data) {
    return contains(x, t->left);
  } else if (t->data < x) {
    return contains(x, t->right);
  } else {
    if (t->isDeleted)
      return false;
    else
      return true;
  }
}

template <typename T>
void BinarySearchTree<T>::lazy_remove(const T &x, BinaryNode *&t) {
  if (t == nullptr) {
    return;
  } else if (x < t->data) {
    lazy_remove(x, t->left);
  } else if (x > t->data) {
    lazy_remove(x, t->right);
  } else {
    if (t->isDeleted == false) {
      t->isDeleted = true;
      theSize--;
      deletedSize++;
      //����Ƿ�Ҫִ��һ���׼ɾ��
      lazy_chkrmall();
    }
  }
}

template <typename T>
void BinarySearchTree<T>::lazy_chkrmall() {
  if (theSize <= deletedSize) {
    lazy_dormall(root);
    deletedSize = 0;
  }
}

template <typename T>
void BinarySearchTree<T>::lazy_dormall(BinaryNode *&t) {
  if (t == nullptr) {
    return;
  }
  if (t->isDeleted) {
    lazy_dormall(t->left);
    lazy_dormall(t->right);
  } else {
    if (t->left != nullptr && t->right != nullptr) {
      // t->data = findMin(t->right)->data;  //�ҵ��������������ӽڵ�
      // remove(t->data, t->right);  //���ŵݹ�ɾ������������������ӽ��
      BinaryNode *temp = lazy_findMin(t->right);
      if (temp == nullptr)
        ;  //˵��t��������������ɾ����־��,ɾ�����м���.;
      else {
        t->data = temp->data;
        temp->isDeleted = true;
        lazy_dormall(t->right);
      }
    } else {
      BinaryNode *oldNode = t;
      t = (t->left != nullptr) ? t->left : t->right;
      lazy_dormall(t);
      delete oldNode;
    }
  }
}

template <typename T>
inline bool BinarySearchTree<T>::isBSTUtil_1(BinaryNode *t, long long int min,
                                             long long int max) const {
  if (t == nullptr) return true;
  if (t->data <= min || t->data >= max) return false;
  return isBSTUtil_1(root->left, min, t->data) &&
         isBSTUtil_1(root->right, t->data, max);
}

template <typename T>
inline bool BinarySearchTree<T>::isBSTUtil_2(BinaryNode *t, BinaryNode *minNode,
                                             BinaryNode *maxNode) const {
  if (t == nullptr) return true;
  if (minNode != nullptr && t->data <= minNode->data ||
      maxNode != nullptr && t->data >= maxNode->data)
    return false;
  return isBSTUtil_2(t->left, minNode, t) && isBSTUtil_2(t->right, t, maxNode);
}

template <typename T>
inline bool BinarySearchTree<T>::isBSTUtil_3(BinaryNode *t,
                                             BinaryNode *&prev) const {
  if (t == nullptr) return true;
  //���������
  if (!isBSTUtil_3(t->left, prev)) return false;
  //��鵱ǰ
  if (prev != nullptr && prev->data >= t->data) return false;
  prev = t;
  //���������
  return isBSTUtil_3(t->right, prev);
}

template <typename T>
int BinarySearchTree<T>::countNodes(BinaryNode *t) const {
  if (t == nullptr) return 0;
  return 1 + countNodes(t->left) + countNodes(t->right);
}

template <typename T>
int BinarySearchTree<T>::countLeaves(BinaryNode *t) const {
  if (t == nullptr)
    return 0;
  else if (t->left == nullptr && t->right == nullptr)
    return 1;
  return countLeaves(t->left) + countLeaves(t->right);
}

template <typename T>
int BinarySearchTree<T>::countFullNodes(BinaryNode *t) const {
  if (t == nullptr) return 0;
  return ((t->left != nullptr && t->right != nullptr) ? 1 : 0) +
         countFullNodes(t->left) + countFullNodes(t->right);
}

// isBST��Ϊleetcode98.��֤����������
//���º�������,û�п���[10,5,15,null,null,6,20]
/*
template<typename T>
inline bool BinarySearchTree<T>::isBST(BinaryNode * t) const {
        if (t==nullptr||(t->left==nullptr&&t->right==nullptr)) {
                return true;
        }
        if (t->left!=nullptr&&t->right!=nullptr) {
                if (t->left->data<t->data&&t->right->data>t->data) {
                        return isBST(t->left) && isBST(t->right);
                }
                else return false;
        } else if (t->left==nullptr) {
                if (t->right->data > t->data)
                        return isBST(t->right);
                else
                        return false;
        }	else {
                if (t->left->data < t->data)
                        return isBST(t->left);
                else
                        return false;
        }
}
*/

//Ĭ��ģ��Ϊint����,���º���ʹ��LONG_MAX
// LONG_MIN,����[INT_MIN]��[INT_MIN,INT_MIN]��
//�˷�������ʹ���ض����͵���Сֵ�����ֵ,���п������,��ʼ״̬��Ҫʹ�ø���һ�������͡������й㷺��
template <typename T>
bool BinarySearchTree<T>::isBST_1(BinaryNode *t) const {
  return isBSTUtil_1(t, LONG_MIN, LONG_MAX);
}

//Ϊ�����������ʹ���������,��LONG_MIN,LONG_MAX��Щ��Сֵ���ֵ����nullptr��ʾ
template <typename T>
inline bool BinarySearchTree<T>::isBST_2(BinaryNode *t) const {
  return isBSTUtil_2(t, nullptr, nullptr);
}

//�ݹ��������,��Ҫһ��preǰ��ָ��
template <typename T>
inline bool BinarySearchTree<T>::isBST_3(BinaryNode *t) const {
  BinaryNode *&pre = nullptr;
}

//�ǵݹ��������,���Ʒǵݹ�ɾ��.����һ��ջ
template <typename T>
inline bool BinarySearchTree<T>::isBST_4(BinaryNode *t) const {
  if (t == nullptr) return true;
  std::stack<BinaryNode *> BSTNode_stack;
  BinaryNode *prev = nullptr;
  while (t != nullptr || !BSTNode_stack.empty()) {
    while (t != nullptr) {
      //������
      BSTNode_stack.push(t);
      t = t->left;
    }
    //�жϵ�ǰ���
    t = BSTNode_stack.pop();
    if (prev != nullptr && prev->data >= t->data) return false;
    //������
    prev = t;
    t = t->right;
  }
}

template <typename T>
inline void BinarySearchTree<T>::remove_leaves(BinaryNode *&t) {
  if (t == nullptr) return;
  if (t->left == nullptr && t->right == nullptr) {
    delete t;
    t = nullptr;
    return;
  }
  remove_leaves(t->left);
  remove_leaves(t->right);
}

template <typename T>
inline void BinarySearchTree<T>::makeRandomTree(int low, int up) {
  int rndVal;
  if (low <= up) {
    root = new BinaryNode(rndVal = rndInt(low, up),
                          makeRandomTree(low, rndVal - 1),
                          makeRandomTree(rndVal + 1, up));
  }
  return root;
}

template <typename T>
inline void BinarySearchTree<T>::printRange(const T &low, const T &up,
                                            BinaryNode *t) const {
  if (t != nullptr) {
    //ʵ���ϻ��ǵݹ��������,�ȱ���������,�ٸ��ڵ�,��������
    if (t->data >= low) printRange(low, up, t->left);
    if (t->data >= low && t->data <= up) std::cout << t->data << std::endl;
    if (t->data <= up) printRange(low, up, t->right);
  }
}

template <typename T>
inline void BinarySearchTree<T>::levelOrder(BinaryNode *t) const {
  if (t == nullptr) return;
  queue<BinaryNode *> node_queue;
  BinaryNode *opnode;
  node_queue.push(t);
  while (!node_queue.empty()) {
    opnode = node_queue.front();
    //��opnode���в���
    node_queue.pop();
    if (opnode->left != nullptr) node_queue.push(opnode->left);
    if (opnode->right != nullptr) node_queue.push(opnode->right);
  }
  return;
}
