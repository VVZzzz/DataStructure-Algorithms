#pragma once
//AVL树,每个节点有height成员
template <typename T>
class AVLTree {
 public:
	 AVLTree() :root(nullptr) { }
	 int getHeight(AvlNode *&t) const {
		 return t == nullptr ? -1 : t->height;
	 }
	 void insert(const T &x, AvlNode *t);
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
};

//插入节点时,先插入再旋转调整
template <typename T>
void AVLTree<T>::insert(const T &x, AvlNode *t) { 
	if (t == nullptr)
		t = new AvlNode(x, nullptr, nullptr);
	else if (x < t->data) { 
		insert(t->left);
		if (getHeight(t->left) - getHeight(t->right) == 2)
			//TODO:左单旋转
			ldanxuan(t);
		else
			//TODO:左双旋转
			lshuangxuan(t);
	} else if (x > t->data) {
		insert(t->right);
		if (getHeight(t->right) - getHeight(t->left) == 2)
			//TODO:右单旋转
			rdanxuan(t);
		else
			//TODO:右双旋转
			rshuangxuan(t);
	} 
	else ; //do noting,已有该元素
	t->height = max(getHeight(t->right), getHeight(t->left)) + 1;
}