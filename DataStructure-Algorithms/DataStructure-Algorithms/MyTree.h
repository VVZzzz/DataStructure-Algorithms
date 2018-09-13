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
	 struct BinaryNode;
  BinarySearchTree();
  BinarySearchTree( const BinarySearchTree &rhs );
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

	
	//得到结点数
	int countNodes(BinaryNode *t) const;
	//得到树叶数
	int countLeaves(BinaryNode *t) const;
	//得到满结点数
	int countFullNodes(BinaryNode *t) const;

	//检查是否为BST
	bool isBST_1(BinaryNode *t) const;
	bool isBST_2(BinaryNode *t) const;
	bool isBST_3(BinaryNode *t) const;
	bool isBST_4(BinaryNode *t) const;

	//4.33 递归删除叶子结点
	void remove_leaves(BinaryNode *&t) const;

	//4.34 生成low~up的随机二叉搜索树,rndInt(low,up)生成low与up之间的随机数
	int rndInt(int low, int up) { return (up + low) / 2; }
	void makeRandomTree(int low,int up);

	//4.37 打印[k1,k2]范围内的结点值
	void printRange(const T &low, const T &up, BinaryNode *t) const;
 private:
  struct BinaryNode {
    T data;
    BinaryNode *left;
    BinaryNode *right;
		bool isDeleted;		//懒惰删除标志
    BinaryNode(const T &t, BinaryNode *l, BinaryNode *r, bool flag=false)
        : data(t), left(l), right(r), isDeleted(flag) { }
  };
  BinaryNode *root;
	int theSize;
	int deletedSize;

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

	//懒惰删除版本的insert remove contains findMin findMax
	void lazy_insert(const T &x, BinaryNode *&t) const;
  bool lazy_contains(const T &x, BinaryNode *&t) const;
  void lazy_remove(const T &x, BinaryNode *&t);
	void lazy_chkrmall();
	void lazy_dormall(BinaryNode *&t);
	BinaryNode *lazy_findMin(BinaryNode *t) const{
		if (t != nullptr){
		BinaryNode *ltemp = lazy_findMin(t->left);
		if (ltemp != nullptr&&ltemp->isDeleted == false)
			return ltemp;
		BinaryNode *rtemp = lazy_findMin(t->right);
		if (rtemp != nullptr&&rtemp->isDeleted == false)
			return rtemp;
		}
	}
	BinaryNode *lazy_findMax(BinaryNode *t) const {
		BinaryNode *ltemp = lazy_findMin(t->right);
		if (ltemp != nullptr&&ltemp->isDeleted == false)
			return ltemp;
		BinaryNode *rtemp = lazy_findMin(t->left);
		if (rtemp != nullptr&&rtemp->isDeleted == false)
			return rtemp;
		//没有找到
		return nullptr;
	}

	//isBST版本1的工具函数
	bool isBSTUtil_1(BinaryNode *t, long long int min, long long int max) const;
	bool isBSTUtil_2(BinaryNode *t, BinaryNode *minNode, BinaryNode *maxNode) const;
	bool isBSTUtil_3(BinaryNode *t, BinaryNode *&prev) const;

};

template <typename T>
inline BinarySearchTree<T>::BinarySearchTree() : root(nullptr), theSize(0), deletedSize(0) {}

template <typename T>
inline BinarySearchTree<T>::BinarySearchTree(
    const BinarySearchTree &rhs) {
	theSize = rhs.theSize;
	deletedSize = rhs.deletedSize;
  root = clone(rhs.root);
}

template <typename T>
inline const T &BinarySearchTree<T>::findMin() const {
  BinaryNode *t = findMin(root);
  if (t!=nullptr) {
    return t->data;
  } else {
    //没找到最小值
    return T();
  }
}

template <typename T>
inline const T &BinarySearchTree<T>::findMax() const {
  // TODO: 在此处插入 return 语句
  BinaryNode *t = findMax(root);
  if (t!=nullptr) {
    return t->data;
  } else {
    //没找到最大值
    return T();
  }

}

template <typename T>
inline bool BinarySearchTree<T>::contains(const T &x) const {
  return contains(x, root);
}

template <typename T>
inline bool BinarySearchTree<T>::isEmpty() const {
  return root==nullptr;
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
    //已存在，do nothing;
}

//这个remove遍历了两次右子树，效率不高
template <typename T>
inline void BinarySearchTree<T>::remove(const T &x, BinaryNode *&t) {
  if (t==nullptr) {
    return;
  } else if (x < t->data) {
    remove(x, t->left);
  } else if (x > t->data) {
    remove(x, t->right);
  } else if (t->left!=nullptr && t->right!=nullptr) {
    t->data = findMin(t->right)->data;  //找到右子树的最左子节点
    remove (t->data,t->right);  //接着递归删除这个右子树的最左子结点
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

	//懒惰删除版本的insert remove contains makeEmpty
template <typename T>
void BinarySearchTree<T>::lazy_insert(const T &x, BinaryNode *&t) const{
	if (t == nullptr){
		theSize++;
    t = new BinaryNode(x, nullptr, nullptr, false);
	}
  else if (t->data < x)
    insert(x, t->right);
  else if (x < t->data)
    insert(x, t->left);
	else {
		if (t->isDeleted)
			t->isDeleted = false;
		else
    //已存在，do nothing;
	}
}

template <typename T>
bool BinarySearchTree<T>::lazy_contains(const T &x, BinaryNode *&t) const{
 if (t==nullptr) {
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
void BinarySearchTree<T>::lazy_remove(const T &x, BinaryNode *&t){
	if (t==nullptr) {
    return;
  } else if (x < t->data) {
    lazy_remove(x, t->left);
  } else if (x > t->data) {
    lazy_remove(x, t->right);
	} else {
		if (t->isDeleted == false){
			t->isDeleted = true;
			theSize--;
			deletedSize++;
			//检测是否要执行一遍标准删除
			lazy_chkrmall();
		}
	}
}

template <typename T>
void BinarySearchTree<T>::lazy_chkrmall(){
	if (theSize <= deletedSize){
		lazy_dormall(root);
		deletedSize = 0;
	}
}

template <typename T>
void BinarySearchTree<T>::lazy_dormall(BinaryNode *&t){
  if (t==nullptr) {
    return;
  } 
	if (t->isDeleted) {
		lazy_dormall(t->left);
		lazy_dormall(t->right);
	} else {
		if (t->left != nullptr && t->right != nullptr) {
			//t->data = findMin(t->right)->data;  //找到右子树的最左子节点
			//remove(t->data, t->right);  //接着递归删除这个右子树的最左子结点
			BinaryNode *temp = lazy_findMin(t->right);
			if (temp == nullptr)
				;//说明t的右子树都是有删除标志的,删除所有即可.;
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

template<typename T>
inline bool BinarySearchTree<T>::isBSTUtil_1(BinaryNode * t, 
		long long int min, long long int max) const {
	if (t == nullptr) return true;
	if (t->data <= min || t->data >= max) return false;
	return isBSTUtil_1(root->left, min, t->data) &&
		isBSTUtil_1(root->right, t->data, max);
}

template<typename T>
inline bool BinarySearchTree<T>::isBSTUtil_2(BinaryNode * t, BinaryNode * minNode, BinaryNode * maxNode) const {
	if (t == nullptr) return true;
	if (minNode != nullptr&&t->data <= minNode->data ||
		maxNode != nullptr&&t->data >= maxNode->data) return false;
	return isBSTUtil_2(t->left, minNode, t) && isBSTUtil_2(t->right, t, maxNode);
}

template<typename T>
inline bool BinarySearchTree<T>::isBSTUtil_3(BinaryNode * t, BinaryNode *& prev) const {
	if (t == nullptr) return true;
	//检查左子树
	if (!isBSTUtil_3(t->left, prev)) return false;
	//检查当前
	if (prev != nullptr&&prev->data >= t->data) return false;
	prev = t;
	//检查右子树
	return isBSTUtil_3(t->right, prev);
}

template <typename T>
int BinarySearchTree<T>::countNodes(BinaryNode *t) const{
	if (t == nullptr) return 0;
	return 1 + countNodes(t->left) + countNodes(t->right);
}

template <typename T>
int BinarySearchTree<T>::countLeaves(BinaryNode *t) const{
	if (t == nullptr) return 0;
	else if (t->left == nullptr&&t->right == nullptr)
		return 1;
	return countLeaves(t->left) + countLeaves(t->right);
}

template <typename T>
int BinarySearchTree<T>::countFullNodes(BinaryNode *t) const{
	if (t == nullptr) return 0;
	return (t->left != nullptr&&t->right != nullptr) ? 1 : 0 
		+ countFullNodes(t->left) + countFullNodes(t->right);
}

//isBST即为leetcode98.验证二叉搜索树
//以下函数错误,没有考虑[10,5,15,null,null,6,20]
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

//默认模板为int类型,以下函数使用LONG_MAX LONG_MIN,考虑[INT_MIN]和[INT_MIN,INT_MIN]树
//此方法由于使用特定类型的最小值和最大值,且有可能溢出,初始状态下要使用更高一级的类型。不具有广泛性
template <typename T = int>
bool BinarySearchTree<T>::isBST_1(BinaryNode *t) const {
	return isBSTUtil_1(t, LONG_MIN, LONG_MAX);
}

//为解决上述问题使用这个函数,将LONG_MIN,LONG_MAX这些最小值最大值换成nullptr表示
template<typename T>
inline bool BinarySearchTree<T>::isBST_2(BinaryNode * t) const {
	return isBSTUtil_2(t, nullptr, nullptr);
}

//递归中序遍历,需要一个pre前置指针
template<typename T>
inline bool BinarySearchTree<T>::isBST_3(BinaryNode * t) const {
	BinaryNode *&pre = nullptr;
}

//非递归中序遍历,类似非递归删除.借用一个栈
template<typename T>
inline bool BinarySearchTree<T>::isBST_4(BinaryNode * t) const {
	if (t == nullptr) return true;
	std::stack<BinaryNode *> BSTNode_stack;
	BinaryNode *prev = nullptr;
	while (t!=nullptr||!BSTNode_stack.empty()) {
		while (t!=nullptr) {
			//左子树
			BSTNode_stack.push(t);
			t = t->left;
		}
		//判断当前结点
		t = BSTNode_stack.pop();
		if (prev != nullptr&&prev->data >= t->data) return false;
		//右子树
		prev = t;
		t = t->right;
	}
}

template<typename T>
inline void BinarySearchTree<T>::remove_leaves(BinaryNode *& t) const {
	if (t == nullptr) return;
	if (t->left == nullptr&&t->right == nullptr) {
		delete t;
		t = nullptr;
		return;
	}
	remove_leaves(t->left);
	remove_leaves(t->right);
}

template<typename T>
inline void BinarySearchTree<T>::makeRandomTree(int low, int up) {
	int rndVal;
	if (low <= up) {
		root = new BinaryNode(rndVal = rndInt(low, up), 
			makeRandomTree(low, rndVal - 1), makeRandomTree(rndVal + 1, up));
	}
	return root;
}

template<typename T>
inline void BinarySearchTree<T>::printRange(const T & low, 
	const T & up, BinaryNode * t) const {
	if (t!=nullptr) {
		//实际上还是递归中序遍历,先遍历左子树,再父节点,再右子树
		if (t->data >= low)
			printRange(low, up, t->left);
		if (t->data >= low&&t->data <= up)
			std::cout << t->data << std::endl;
		if (t->data <= up)
			printRange(low, up, t->right);
	}
}
