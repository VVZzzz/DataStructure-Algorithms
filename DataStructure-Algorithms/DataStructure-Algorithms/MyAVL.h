#pragma once
//AVL��,ÿ���ڵ���height��Ա
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
	//����ת
	void singleRotateWithLeft(AvlNode *&t);
	//��˫��ת
};

//����ڵ�ʱ,�Ȳ�������ת����
template <typename T>
void AVLTree<T>::insert(const T &x, AvlNode *t) { 
	if (t == nullptr)
		t = new AvlNode(x, nullptr, nullptr);
	else if (x < t->data) { 
		insert(t->left);
		if (getHeight(t->left) - getHeight(t->right) == 2)
			//TODO:����ת
			ldanxuan(t);
		else
			//TODO:��˫��ת
			lshuangxuan(t);
	} else if (x > t->data) {
		insert(t->right);
		if (getHeight(t->right) - getHeight(t->left) == 2)
			//TODO:�ҵ���ת
			rdanxuan(t);
		else
			//TODO:��˫��ת
			rshuangxuan(t);
	} 
	else ; //do noting,���и�Ԫ��
	t->height = max(getHeight(t->right), getHeight(t->left)) + 1;
}