#pragma once
#include <stack>
//AVL��,ÿ���ڵ���height��Ա
template <typename T>
class AVLTree {
 struct AvlNode;
 public:
	 AVLTree() :root(nullptr) { }
	 int getHeight(AvlNode *&t) const {
		 return t == nullptr ? -1 : t->height;
	 }
	 void insert(const T &x, AvlNode *t);
	 void remove(const T &x, AvlNode *t);

	 //�ǵݹ��insert,����ջ.ԭ����ͬ
	 void insert_iteration(const T &x, AvlNode *t);
	 //�ж��Ƿ�����ƽ������
	 bool isBalanced();
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
	//����ת
	void singleRotateWithLeft(AvlNode *&t);
	//��˫��ת
	void doubleRotateWithLeft(AvlNode *&t);
  //�ҵ���ת
	void singleRotateWithRight(AvlNode *&t);
	//��˫��ת
	void doubleRotateWithRight(AvlNode *&t);
	//LeetCode110ʵ�ֵĵõ��߶ȹ��ߺ���(ʹ��DFS),���������ƽ���������ص���-1
	int getWholeHeight(AvlNode *t);
};

//����ڵ�ʱ,�Ȳ�������ת����
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
	else ; //do noting,���и�Ԫ��
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

template <typename T>
bool AVLTree<T>::isBalanced() {
	return getWholeHeight(root) != -1;
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
			;  //���ҵ�
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