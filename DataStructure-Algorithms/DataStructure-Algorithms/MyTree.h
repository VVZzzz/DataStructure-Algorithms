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

	BinaryNode *func1();
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

//template <typename T>
//BinarySearchTree<T>::BinaryNode *BinarySearchTree<T>::func1(){
//	return nullptr;
//}
