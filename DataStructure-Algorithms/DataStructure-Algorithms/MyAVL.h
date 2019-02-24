#pragma once
#include <queue>
#include <stack>
// AVL树,每个节点有height成员
template <typename T = int>
class AVLTree {
  struct AvlNode;

 public:
  AVLTree() : root(nullptr) {}
  void insert(const T &x) { insert(x, root); }
  // remove和BST类似,但要进行平衡调整
  void remove(const T &x) { remove(x, root); }
  int getHeight() { return getHeight(root); }

  //非递归的insert,借助栈.原理相同
  void insert_iteration(const T &x) { insert_iteration(x, root); }
  //判断是否满足平衡条件
  bool isBalanced();

  // 4.35 生成最少结点的高度为h的AVL树,工具函数generate_min_H_utils()
  void generate_min_H(int h);

  // print_tree测试用
  void print_tree() const;

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
  void insert_iteration(const T &x, AvlNode *t);

  //左单旋转
  void singleRotateWithLeft(AvlNode *&t);
  //左双旋转
  void doubleRotateWithLeft(AvlNode *&t);
  //右单旋转
  void singleRotateWithRight(AvlNode *&t);
  //右双旋转
  void doubleRotateWithRight(AvlNode *&t);
  // LeetCode110实现的得到高度工具函数(使用DFS),如果不满足平衡条件返回的是-1
  int getWholeHeight(AvlNode *t);

  //右子树高时的调整函数
  void rightBalance(AvlNode *&t);
  //左子树高时的调整函数
  void leftBalance(AvlNode *&t);

  AvlNode *generate_min_H_util(int h, T &lastVal) {
    AvlNode *t = nullptr;
    if (h >= 0) {
      t = new AvlNode();
      t->left = generate_min_H_util(h - 1, lastVal);
      t->data = ++lastVal;
      t->right = generate_min_H_util(h - 2, lastVal);
      //若不考虑保存结点的高度信息,此句可不要
      t->height = max(getHeight(t->left), getHeight(t->right)) + 1;
    }
    return t;
    if (h == 0) {
      return new AvlNode(T(), nullptr, nullptr);
    }
    if (h == 1) {
      return new AvlNode(T(), nullptr, generate_min_H_util(0));
    }
    return new AvlNode(T(), generate_min_H_util(h - 1),
                       generate_min_H_util(h - 2));
  }
};

//插入节点时,先插入再旋转调整
template <typename T>
void AVLTree<T>::insert(const T &x, AvlNode *&t) {
  if (t == nullptr)
    t = new AvlNode(x, nullptr, nullptr);
  else if (x < t->data) {
    //此时插入到左子树上
    insert(x, t->left);
    if (getHeight(t->left) - getHeight(t->right) == 2)
      if (x < t->left->data)
        //此时插入到左子树的左子节点,左单旋
        singleRotateWithLeft(t);
      else
        //此时插入到左子树的右子节点,左双旋
        doubleRotateWithLeft(t);
  } else if (x > t->data) {
    //此时插入到右子树上
    insert(x, t->right);
    if (getHeight(t->right) - getHeight(t->left) == 2)
      if (x > t->right->data)
        //此时插入到右子树的右子节点,右单旋
        singleRotateWithRight(t);
      else
        //此时插入到右子树的左子节点,右双旋
        doubleRotateWithRight(t);
  } else
    ;  // do noting,已有该元素
  //重新修改该树的高度
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
  /*直白思路,效率超过两个单旋转*/
  //	AvlNode *l = t->left, *r = t->left->right;
  //	l->right = r->left;
  //	t->left = r->right;
  //	r->left = l;
  //	r->right = t;
  //	l->height = max(getHeight(l->left), getHeight(l->right)) + 1;
  //	t->height = max(getHeight(t->left), getHeight(t->right)) + 1;
  //	r->height = max(l->height, t->height) + 1;
  //	t = r;
  //    做左双旋,实际上是两次单旋,先对t->left做右单旋,再对t做左单旋.
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
  //做右双旋,实际上是两次单旋,先对t->right做左单旋,再对t做右单旋.
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
  return max(leftheight, rightheight) + 1;
}

template <typename T>
void AVLTree<T>::rightBalance(AvlNode *&t) {
  auto temp = t->right;
  if (getHeight(temp->right) - getHeight(temp->left) == 1)
    //右子树的右子节点
    singleRotateWithRight(t);
  else
    //右子树的左子节点
    doubleRotateWithRight(t);
}

template <typename T>
void AVLTree<T>::leftBalance(AvlNode *&t) {
  auto temp = t->left;
  if (getHeight(temp->left) - getHeight(temp->right) == 1)
    //左子树的左子节点
    singleRotateWithLeft(t);
  else
    //右子树的左子节点
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
inline void AVLTree<T>::generate_min_H(int h) {
  T lastVal();
  return generate_min_H_util(h, lastVal);
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
    //对opnode进行操作
    node_queue.pop();
  }
  delete sep_node;
  return;
}

template <typename T>
void AVLTree<T>::insert_iteration(const T &x, AvlNode *t) {
  std::stack<AvlNode *> nodeptr_stack;
  while (1) {
    if (t == nullptr) {
      t = new AvlNode(x, nullptr, nullptr);
      nodeptr_stack.push(t);
      break;
    } else if (x < t->data) {
      nodeptr_stack.push(t);
      t = t->left;
    } else if (x > t->data) {
      nodeptr_stack.push(t);
      t = t->right;
    } else
      ;  //已找到
  }

    if (nodeptr_stack.empty()) return;
    AvlNode *child = nodeptr_stack.top();
    nodeptr_stack.pop();
    if (nodeptr_stack.empty()) return;
    AvlNode *parent = nodeptr_stack.top();
    /*
    if (parent->data < child->data) {
      parent->right = child;
      if (getHeight(parent->right) - getHeight(parent->left) == 2) {
        if (x > t->right->data)
          singleRotateWithRight(t);
        else
          doubleRotateWithRight(t);
      }
    } else if (parent->data > child->data) {
      parent->left = child;
      if (getHeight(parent->left) - getHeight(parent->right) == 2) {
        if (x < t->left->data)
          singleRotateWithLeft(t);
        else
          doubleRotateWithLeft(t);
      }
    }
	*/

	if (parent->data < child->data)
      parent->right = child;
    else
      parent->left = child;
    
    parent->height = std::max(getHeight(parent->left), getHeight(parent->right)) + 1;
    if (!nodeptr_stack.empty()) {
      auto pparent = nodeptr_stack.top();
      nodeptr_stack.pop();
      if (getHeight(pparent->left) - getHeight(pparent->right) == 2)
        leftBalance(pparent);
      else if (getHeight(pparent->left) - getHeight(pparent->right) == -2)
        rightBalance(pparent);
    }

}

template <typename T>
void AVLTree<T>::remove(const T &x, AvlNode *&t) {
  if (t == nullptr)
    return;
  else if (x < t->data) {
    remove(x, t->left);
    //右子树更高,调整
    if (getHeight(t->right) - getHeight(t->left) == 2) {
      rightBalance(t);
    }
  } else if (x > t->data) {
    remove(x, t->right);
    //左子树更高,调整
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
      //左右子树都不为空,删除策略为找左子树的最右节点或者右子树的最左节点代替。
      //即BST树的删除策略, 这里选后者。
      auto temp = t->right;
      while (temp->left != nullptr) {
        temp = temp->left;
      }
      t->data = temp->data;
      remove(x, temp);  //递归删除此节点
    }
  }
  //更新节点高度
  if (t != nullptr)
    t->height = std::max(getHeight(t->left), getHeight(t->right)) + 1;
}