#pragma once
#include <stack>
//AVL树,每个节点有height成员
template <typename T = int>
class AVLTree {
 struct AvlNode;
 public:
	 AVLTree() :root(nullptr) { }
	 int getHeight(AvlNode *&t) const {
		 return t == nullptr ? -1 : t->height;
	 }
	 void insert(const T &x, AvlNode *t);
	 void remove(const T &x, AvlNode *t);

	 //非递归的insert,借助栈.原理相同
	 void insert_iteration(const T &x, AvlNode *t);
	 //判断是否满足平衡条件
	 bool isBalanced();

	 //4.35 生成最少结点的高度为h的AVL树,工具函数generate_min_H_utils()
	 void generate_min_H(int h);
 private:
	struct AvlNode {
		T data;
		AvlNode *left;
		AvlNode *right;
		int height;
		AvlNode(const T &d, AvlNode *l, AvlNode *r, int h = 0) 
			:data(d), left(l), right(r), height(h) { }
    AvlNode() 
			:data(T()), left(nullptr), right(nullptr), height(0) { }
	};
	AvlNode *root;
	//左单旋转
	void singleRotateWithLeft(AvlNode *&t);
	//左双旋转
	void doubleRotateWithLeft(AvlNode *&t);
  //右单旋转
	void singleRotateWithRight(AvlNode *&t);
	//右双旋转
	void doubleRotateWithRight(AvlNode *&t);
	//LeetCode110实现的得到高度工具函数(使用DFS),如果不满足平衡条件返回的是-1
	int getWholeHeight(AvlNode *t);

	AvlNode *generate_min_H_util(int h, T & lastVal) {
		AvlNode *t = nullptr;
		if (h>=0) {
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
		return new AvlNode(T(), generate_min_H_util(h-1), generate_min_H_util(h-2));
	}
};

//插入节点时,先插入再旋转调整
template <typename T>
void AVLTree<T>::insert(const T &x, AvlNode *t) { 
	if (t == nullptr)
		t = new AvlNode(x, nullptr, nullptr);
	else if (x < t->data) { 
		insert(t->left);
		if (getHeight(t->left) - getHeight(t->right) == 2)
			if (x < t->left->data)
				singleRotateWithLeft(t);
			else
				doubleRotateWithLeft(t);
	} 
	else if (x > t->data) {
		insert(t->right);
		if (getHeight(t->right) - getHeight(t->left) == 2)
			if (x > t->right->data)
				singleRotateWithRight(t);
			else
				doubleRotateWithRight(t);
	} 
	else ; //do noting,已有该元素
	t->height = max(getHeight(t->right), getHeight(t->left)) + 1;
}

template <typename T>
void AVLTree<T>::singleRotateWithLeft(AvlNode *&t) {
	AvlNode *temp = t->left;
	t->left = temp->right;
	temp->right = t;
	t->height = max(getHeight(t->left), getHeight(t->right)) + 1;
	temp->height = max(getHeight(temp->left), t->height) + 1;
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
	singleRotateWithRight(t->left);
	singleRotateWithLeft(t);
}

template <typename T>
void AVLTree<T>::singleRotateWithRight(AvlNode *&t) {
	AvlNode *temp = t->right;
	t->right = temp->left;
	temp->left = t;
	t->height = max(getHeight(t->left), getHeight(t->right)) + 1;
	temp->height = max(getHeight(temp->right), t->height) + 1;
	t = temp;
}

template <typename T>
void AVLTree<T>::doubleRotateWithRight(AvlNode *&t) {
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

template<typename T>
inline AvlNode * AVLTree<T>::generate_min_H_util(int h) {
}

template <typename T>
bool AVLTree<T>::isBalanced() {
	return getWholeHeight(root) != -1;
}

template<typename T>
inline void AVLTree<T>::generate_min_H(int h) {
	T lastVal();
	return generate_min_H_util(h, lastVal);
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
		}
		else
			;  //已找到
	}

	while (1) {
		AvlNode *child = nodeptr_stack.top();
		if (nodeptr_stack.empty()) return;
		nodeptr_stack.pop();
		AvlNode *parent = nodeptr_stack.top();
		if (parent->data < child->data) {
			parent->right = child;
			if (getHeight(parent->right) - getHeight((parent->left) == 2)) {
				if (x > t->right->data)
					singleRotateWithRight(t);
				else
					doubleRotateWithRight(t);
			}
		} else if (parent->data > child->data) {
			parent->left = child;
			if (getHeight(parent->left) - getHeight((parent->right) == 2)) {
				if (x < t->left->data)
					singleRotateWithLeft(t);
				else
					doubleRotateWithLeft(t);
			}
		}
		nodeptr_stack.push(parent);
		parent->height = max(getHeight(parent->left), getHeight(parent->right)) + 1;
	}
}

template <typename T>
void AVLTree<T>::remove(const T &x, AvlNode *t) { 
	if (t == nullptr)
		return;
	else if (x < t->data) {
		remove(t->left);
		if (getHeight(t->right) - getHeight(t->left) == 2) {
			
		}
	}
	else if (x > t->data) { 
		remove(t->right);
	}
	else {
		if (t->left == nullptr&&t->right==nullptr) {
			delete t;
		}
	}
	t->height = max(getHeight(t->left), getHeight(t->right)) + 1;
}