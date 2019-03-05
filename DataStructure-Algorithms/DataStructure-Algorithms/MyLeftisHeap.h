#pragma once
//左式堆,解决二叉堆无法合并的问题
#include <iostream>
#include <queue>
#include <stack>
#include <stdexcept>
#include <vector>
template <typename T>
class MyLeftistHeap {
 public:
  MyLeftistHeap() : root(nullptr) {}
  MyLeftistHeap(const MyLeftistHeap &rhs) { *this = rhs; }
  ~MyLeftistHeap() { makeEmpty(); }
  bool isEmpty() const;
  const T &findMin() const;

  //插入即 合并一个根节点
  void insert(const T &x);

  //删除即 将root->left root->right合并,将原root删除
  void deleteMin();
  void deleteMin(T &minItem);
  void makeEmpty();

  // void remove(T &minItem) is for 6.23(a).具体操作在Chapter11中
  //删除某一个节点t,将t->left,r->right合并,代替t。同时要注意更新npl,同时可能要交换左右子树。
  //按理说堆的操作不应该去操作堆内部的节点的
  void remove(T &minItem);
  //递归的合并方法
  void merge(MyLeftistHeap &rhs);  //将rhs合并到this堆,rhs置为nullptr

  const MyLeftistHeap &operator=(const MyLeftistHeap &rhs);

  //懒惰删除方案,设立标志,若根节点被设为isDeleted.则lazyFindMin()和lazyDeleteMin()按以下进行。
  const T &lazyFindMin();
  void lazyDeleteMin();

  //练习6.25 更为合适的buildHeap(),斜堆同样也可以这样操作进行buildHeap().
  void buildHeap(const std::vector<T> &tvec);

  void printInfo() const;

 private:
  struct LeftistNode {
    T data;
    LeftistNode *left;
    LeftistNode *right;
    int npl;  //零路径长
    // lazy delete标志
    bool isDeleted;
    LeftistNode(const T &ele = T(), LeftistNode *l = nullptr,
                LeftistNode *r = nullptr, int n = 0, bool f = false)
        : data(ele), left(l), right(r), npl(n), isDeleted(f) {}
    void reset() {
      left = nullptr;
      right = nullptr;
      npl = 0;
      isDeleted = false;
    }
  };

  LeftistNode *root;

  LeftistNode *merge(LeftistNode *h1, LeftistNode *h2) {
    if (h1 == nullptr) return h2;
    if (h2 == nullptr) return h1;
    if (h1->data < h2->data)
      return merge1(h1, h2);
    else
      return merge1(h2, h1);
  }

  // h1为根较小的堆
  LeftistNode *merge1(LeftistNode *h1, LeftistNode *h2) {
    if (h1->left ==
        nullptr)  //此处只需要判断h1->left是否为nullptr
                  //因为左式堆不存在左子树为nullptr,右子树不为nullptr的情况.
      h1->left = h2;  // h1只有一个跟节点,则h2直接为h1的左子树
    else {
      h1->right = merge(h1->right, h2);
      if (h1->left->npl < h1->right->npl) swapChildren(h1);
      h1->npl = h1->right->npl + 1;  //更新合并后的npl
    }
    return h1;
  }

  void swapChildren(LeftistNode *t) {
    LeftistNode *temp = t->left;
    t->left = t->right;
    t->right = temp;
  }

  void reclaimMemory(LeftistNode *t);

  LeftistNode *clone(LeftistNode *t) const {
    if (t == nullptr) return nullptr;
    LeftistNode *newroot =
        new LeftistNode(t->data, clone(t->left), clone(t->right), t->npl);
    return newroot;
  }

  // 6.40 避免递归调用深度过大,导致爆栈,修改递归策略
  LeftistNode *clone2(LeftistNode *t) const {
    if (t == nullptr) return nullptr;
    LeftistNode *newroot =
        new LeftistNode(t->data, nullptr, clone2(t->right), t->npl);
    if (t->left == nullptr)
      newroot->left = nullptr;
    else {
      newroot->left = clone2(t->left);
    }
    return newroot;
  }

  void makeEmpty(LeftistNode *&t);
  void remove(T &minItem, LeftistNode *t) {
    // TODO
  }
  void lazyDelete(LeftistNode *t) { t->isDeleted = true; }
};

template <typename T>
void MyLeftistHeap<T>::merge(MyLeftistHeap<T> &rhs) {
  if (this == &rhs) return;
  root = merge(root, rhs.root);
  rhs.root = nullptr;
}

template <typename T>
void MyLeftistHeap<T>::insert(const T &x) {
  root = merge(new LeftistNode(x), root);
}

template <typename T>
bool MyLeftistHeap<T>::isEmpty() const {
  return root == nullptr;
}

template <typename T>
const T &MyLeftistHeap<T>::findMin() const {
  try {
    if (isEmpty()) throw std::underflow_error("root is nullptr!");
  } catch (std::underflow_error &e) {
    std::cout << e.what() << std::endl;
  }
  return root->data;
}

template <typename T>
void MyLeftistHeap<T>::deleteMin() {
  try {
    if (isEmpty()) throw std::underflow_error("root is nullptr!");
  } catch (std::underflow_error &e) {
    std::cout << e.what() << std::endl;
  }
  LeftistNode *oldRoot = root;
  root = merge(root->left, root->right);
  delete oldRoot;
}

template <typename T>
void MyLeftistHeap<T>::deleteMin(T &minItem) {
  minItem = findMin();
  deleteMin();
}

template <typename T>
void MyLeftistHeap<T>::makeEmpty() {
  makeEmpty(root);
}

template <typename T>
void MyLeftistHeap<T>::makeEmpty(LeftistNode *&t) {
  if (t == nullptr) return;
  if (t->left == nullptr && t->right == nullptr) {
    delete t;
    t = nullptr;
    return;
  }
  makeEmpty(t->right);
  makeEmpty(t->left);
}

template <typename T>
const MyLeftistHeap<T> &MyLeftistHeap<T>::operator=(const MyLeftistHeap &rhs) {
  if (this == &rhs) return *this;
  this->root = clone(rhs.root);
  return *this;
}

template <typename T>
const T &MyLeftistHeap<T>::lazyFindMin() {
  if (root->isDeleted) lazyDeleteMin();
  return root->data;
}

template <typename T>
void MyLeftistHeap<T>::lazyDeleteMin() {
  root->isDeleted = true;
  std::vector<LeftistNode *> nodeVec;
  std::stack<LeftistNode *> nodeStack;
  //借用stack进行前序遍历,将遍历的节点放入nodeVec中
  nodeStack.push(root);
  while (!nodeStack.empty()) {
    LeftistNode *temp = nodeStack.top();
    nodeVec.push_back(temp);
    nodeStack.pop();
    if (temp->right != nullptr) nodeStack.push(temp->right);
    if (temp->left != nullptr) nodeStack.push(temp->left);
  }
  //从nodeVec中进行两两合并,将每次合并的结果
  auto i = nodeVec.begin(), j = i;
  for (; i != nodeVec.end(); i++) {
    if ((*i)->isDeleted) {
      delete *i;
      continue;
    } else {
      if ((i != j) && (!((*j)->isDeleted))) {
        (*i)->reset();
        (*j)->reset();
        nodeVec.push_back(merge(*i, *j));
        j = i + 1;
        continue;
      }
      j = i;
    }
  }
  root = nodeVec.back();
  //此处注意,不用clone。直接赋值给root,因为vector中保存的是指针,函数结束后不进行对指针所指向的元素的delete.
  //故其节点实体仍在,除非我们使用makeEmpty.
}

//此建堆方式:两两合并,比insert效率高.
template <typename T>
void MyLeftistHeap<T>::buildHeap(const std::vector<T> &tvec) {
  makeEmpty();
  std::queue<LeftistNode *> nodeQueue;
  for (int i = 0; i < tvec.size(); i += 2) {
    if (i == (tvec.size() - 1)) {
      nodeQueue.push(new LeftistNode(tvec[i]));
      break;
    }
    nodeQueue.push(
        merge(new LeftistNode(tvec[i]), new LeftistNode(tvec[i + 1])));
  }
  while (!nodeQueue.empty()) {
    root = nodeQueue.front();
    nodeQueue.pop();
    if (nodeQueue.empty()) {
      break;
    } else {
      root = merge(root, nodeQueue.front());
      nodeQueue.pop();
    }
    nodeQueue.push(root);
  }
}

template <typename T>
void MyLeftistHeap<T>::printInfo() const {
  if (root == nullptr) {
    std::cout << "This tree is null." << std::endl;
    return;
  }
  LeftistNode *sep_node = new LeftistNode();
  std::queue<LeftistNode *> node_queue;
  LeftistNode *opnode;
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
}
