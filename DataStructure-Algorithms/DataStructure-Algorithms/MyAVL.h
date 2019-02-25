#pragma once
#include <queue>
#include <stack>
// AVL��,ÿ���ڵ���height��Ա
template <typename T = int>
class AVLTree {
  struct AvlNode;

 public:
  AVLTree() : root(nullptr) {}
  AVLTree(const AVLTree &rhs) { root = clone(rhs.root); }
  ~AVLTree() { makeEmpty(); }
  void insert(const T &x) { insert(x, root); }
  // remove��BST����,��Ҫ����ƽ�����
  void remove(const T &x) { remove(x, root); }
  int getHeight() { return getHeight(root); }

  //�ǵݹ��insert,����ջ.ԭ����ͬ
  void insert_iteration(const T &x) { insert_iteration(x, root); }
  //�ж��Ƿ�����ƽ������
  bool isBalanced();

  // 4.35 �������ٽ��ĸ߶�Ϊh��AVL��,���ߺ���generate_min_H_utils()
  void generate_min_H(int h);

  // print_tree������
  void print_tree() const;

  void makeEmpty() { return makeEmpty(root); }

 private:
  struct AvlNode {
    T data;
    AvlNode *left;
    AvlNode *right;
    int height;
    AvlNode(const T &d, AvlNode *l, AvlNode *r, int h = 0)
        : data(d), left(l), right(r), height(h) {}
    AvlNode() : data(T()), left(nullptr), right(nullptr), height(0) {}
  };
  AvlNode *root;

  int getHeight(AvlNode *&t) const { return t == nullptr ? -1 : t->height; }
  void insert(const T &x, AvlNode *&t);
  void remove(const T &x, AvlNode *&t);
  void insert_iteration(const T &x, AvlNode *&t);

  //����ת
  void singleRotateWithLeft(AvlNode *&t);
  //��˫��ת
  void doubleRotateWithLeft(AvlNode *&t);
  //�ҵ���ת
  void singleRotateWithRight(AvlNode *&t);
  //��˫��ת
  void doubleRotateWithRight(AvlNode *&t);
  // LeetCode110ʵ�ֵĵõ��߶ȹ��ߺ���(ʹ��DFS),���������ƽ���������ص���-1
  int getWholeHeight(AvlNode *t);

  //��������ʱ�ĵ�������
  void rightBalance(AvlNode *&t);
  //��������ʱ�ĵ�������
  void leftBalance(AvlNode *&t);

  AvlNode *generate_min_H_util(int h, T lastVal) {
    AvlNode *t = nullptr;
    if (h >= 2) {
      t = new AvlNode();
      t->left = generate_min_H_util(h - 1, lastVal);
      t->data = ++lastVal;
      t->right = generate_min_H_util(h - 2, lastVal);
      //�������Ǳ�����ĸ߶���Ϣ,�˾�ɲ�Ҫ
      t->height = std::max(getHeight(t->left), getHeight(t->right)) + 1;
      return t;
    }
    // return t;
    if (h == 0) {
      return new AvlNode(T(), nullptr, nullptr);
    }
    if (h == 1) {
      return new AvlNode(T(), nullptr, generate_min_H_util(0, lastVal));
    }
    return new AvlNode(T(), generate_min_H_util(h - 1, lastVal),
                       generate_min_H_util(h - 2, lastVal));
  }

  void makeEmpty(AvlNode *&t) {
    if (t != nullptr) {
      makeEmpty(t->left);
      makeEmpty(t->right);
      delete t;
    }
    t = nullptr;
  }

  AvlNode *clone(AvlNode *t) const {
    if (t == nullptr) return nullptr;
    return AvlNode(t->data, clone(t->left), clone(t->right), t->height);
  }
};

//����ڵ�ʱ,�Ȳ�������ת����
template <typename T>
void AVLTree<T>::insert(const T &x, AvlNode *&t) {
  if (t == nullptr)
    t = new AvlNode(x, nullptr, nullptr);
  else if (x < t->data) {
    //��ʱ���뵽��������
    insert(x, t->left);
    if (getHeight(t->left) - getHeight(t->right) == 2)
      if (x < t->left->data)
        //��ʱ���뵽�����������ӽڵ�,����
        singleRotateWithLeft(t);
      else
        //��ʱ���뵽�����������ӽڵ�,��˫��
        doubleRotateWithLeft(t);
  } else if (x > t->data) {
    //��ʱ���뵽��������
    insert(x, t->right);
    if (getHeight(t->right) - getHeight(t->left) == 2)
      if (x > t->right->data)
        //��ʱ���뵽�����������ӽڵ�,�ҵ���
        singleRotateWithRight(t);
      else
        //��ʱ���뵽�����������ӽڵ�,��˫��
        doubleRotateWithRight(t);
  } else
    ;  // do noting,���и�Ԫ��
  //�����޸ĸ����ĸ߶�
  t->height = std::max(getHeight(t->right), getHeight(t->left)) + 1;
}

template <typename T>
void AVLTree<T>::singleRotateWithLeft(AvlNode *&t) {
  AvlNode *temp = t->left;
  t->left = temp->right;
  temp->right = t;
  t->height = std::max(getHeight(t->left), getHeight(t->right)) + 1;
  temp->height = std::max(getHeight(temp->left), t->height) + 1;
  t = temp;
}

template <typename T>
void AVLTree<T>::doubleRotateWithLeft(AvlNode *&t) {
  /*ֱ��˼·,Ч�ʳ�����������ת*/
  //	AvlNode *l = t->left, *r = t->left->right;
  //	l->right = r->left;
  //	t->left = r->right;
  //	r->left = l;
  //	r->right = t;
  //	l->height = max(getHeight(l->left), getHeight(l->right)) + 1;
  //	t->height = max(getHeight(t->left), getHeight(t->right)) + 1;
  //	r->height = max(l->height, t->height) + 1;
  //	t = r;
  //    ����˫��,ʵ���������ε���,�ȶ�t->left���ҵ���,�ٶ�t������.
  singleRotateWithRight(t->left);
  singleRotateWithLeft(t);
}

template <typename T>
void AVLTree<T>::singleRotateWithRight(AvlNode *&t) {
  AvlNode *temp = t->right;
  t->right = temp->left;
  temp->left = t;
  t->height = std::max(getHeight(t->left), getHeight(t->right)) + 1;
  temp->height = std::max(getHeight(temp->right), t->height) + 1;
  t = temp;
}

template <typename T>
void AVLTree<T>::doubleRotateWithRight(AvlNode *&t) {
  //����˫��,ʵ���������ε���,�ȶ�t->right������,�ٶ�t���ҵ���.
  singleRotateWithLeft(t->right);
  singleRotateWithRight(t);
}

template <typename T>
int AVLTree<T>::getWholeHeight(AvlNode *t) {
  if (t == nullptr) return 0;
  int leftheight = getWholeHeight(t->left);
  if (leftheight == -1) return -1;
  int rightheight = getWholeHeight(t->right);
  if (rightheight == -1) return -1;
  if (abs(leftheight - rightheight) > 1) return -1;
  return std::max(leftheight, rightheight) + 1;
}

template <typename T>
void AVLTree<T>::rightBalance(AvlNode *&t) {
  auto temp = t->right;
  if (getHeight(temp->right) - getHeight(temp->left) == 1)
    //�����������ӽڵ�
    singleRotateWithRight(t);
  else
    //�����������ӽڵ�
    doubleRotateWithRight(t);
}

template <typename T>
void AVLTree<T>::leftBalance(AvlNode *&t) {
  auto temp = t->left;
  if (getHeight(temp->left) - getHeight(temp->right) == 1)
    //�����������ӽڵ�
    singleRotateWithLeft(t);
  else
    //�����������ӽڵ�
    doubleRotateWithLeft(t);
}

/*
template<typename T>
inline AvlNode * AVLTree<T>::generate_min_H_util(int h) {
}
*/

template <typename T>
bool AVLTree<T>::isBalanced() {
  return getWholeHeight(root) != -1;
}

template <typename T>
void AVLTree<T>::generate_min_H(int h) {
  T lastVal = T();
  auto temp = root;
  root = generate_min_H_util(h, lastVal);
  print_tree();
  root = temp;
}

template <typename T>
void AVLTree<T>::print_tree() const {
  if (root == nullptr) {
    std::cout << "This tree is null." << std::endl;
    return;
  }
  AvlNode *sep_node = new AvlNode();
  std::queue<AvlNode *> node_queue;
  AvlNode *opnode;
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
void AVLTree<T>::insert_iteration(const T &x, AvlNode *&t) {
  std::stack<AvlNode *> nodeptr_stack;
  //��һ��ѭ�����ҵ�����·��,�������ջ��
  auto p = t;
  while (1) {
    if (p == nullptr) {
      p = new AvlNode(x, nullptr, nullptr);
      nodeptr_stack.push(p);
      if (t == nullptr) t = p;  //Ϊ�������ڵ�Ϊnullptrʱ�����
      break;
    } else if (x < p->data) {
      nodeptr_stack.push(p);
      p = p->left;
    } else if (x > p->data) {
      nodeptr_stack.push(p);
      p = p->right;
    } else
      ;  //���ҵ�
  }

  //��ѭ�����в��벢����ƽ�����
  while (1) {
    if (nodeptr_stack.empty()) return;
    AvlNode *child = nodeptr_stack.top();
    nodeptr_stack.pop();
    if (nodeptr_stack.empty()) {
      t = child;
      return;
    }
    AvlNode *parent = nodeptr_stack.top();
    nodeptr_stack.pop();

    if (parent->data < child->data)
      parent->right = child;
    else
      parent->left = child;

    if (getHeight(parent->left) - getHeight(parent->right) == 2)
      leftBalance(parent);
    else if (getHeight(parent->left) - getHeight(parent->right) == -2)
      rightBalance(parent);

    parent->height =
        std::max(getHeight(parent->left), getHeight(parent->right)) + 1;
    nodeptr_stack.push(parent);
  }
  /*
  if (nodeptr_stack.empty()) return;
  AvlNode *child = nodeptr_stack.top();
  nodeptr_stack.pop();
  if (nodeptr_stack.empty()) return;
  AvlNode *parent = nodeptr_stack.top();

  if (parent->data < child->data)
    parent->right = child;
  else
    parent->left = child;

  parent->height =
      std::max(getHeight(parent->left), getHeight(parent->right)) + 1;
  if (!nodeptr_stack.empty()) {
    auto pparent = nodeptr_stack.top();
    nodeptr_stack.pop();
    if (getHeight(pparent->left) - getHeight(pparent->right) == 2)
      leftBalance(pparent);
    else if (getHeight(pparent->left) - getHeight(pparent->right) == -2)
      rightBalance(pparent);
  }
  */
}

template <typename T>
void AVLTree<T>::remove(const T &x, AvlNode *&t) {
  if (t == nullptr)
    return;
  else if (x < t->data) {
    remove(x, t->left);
    //����������,����
    if (getHeight(t->right) - getHeight(t->left) == 2) {
      rightBalance(t);
    }
  } else if (x > t->data) {
    remove(x, t->right);
    //����������,����
    if (getHeight(t->left) - getHeight(t->right) == 2) {
      leftBalance(t);
    }
  } else {
    if (t->left == nullptr) {
      auto temp = t;
      t = t->right;
      delete temp;
    } else if (t->right == nullptr) {
      auto temp = t;
      t = t->left;
      delete temp;
    } else {
      //������������Ϊ��,ɾ������Ϊ�������������ҽڵ����������������ڵ���档
      //��BST����ɾ������, ����ѡ���ߡ�
      auto temp = t->right;
      while (temp->left != nullptr) {
        temp = temp->left;
      }
      t->data = temp->data;
      remove(x, temp);  //�ݹ�ɾ���˽ڵ�
    }
  }
  //���½ڵ�߶�
  if (t != nullptr)
    t->height = std::max(getHeight(t->left), getHeight(t->right)) + 1;
}