# pragma once
//左式堆,解决二叉堆无法合并的问题
#include <stdexcept>
#include <iostream>
template <typename T>
class MyLeftistHeap{
 public:
	 MyLeftistHeap() :root(nullptr) {}
	 MyLeftistHeap(const MyLeftistHeap &rhs) {
		 *this = rhs;
	 }
	 ~MyLeftistHeap() {
		 makeEmpty();
	 }
	 bool isEmpty() const;
	 const T &findMin() const;

	 //插入即 合并一个根节点
	 void insert(const T & x);

	 //删除即 将root->left root->right合并,将原root删除
	 void deleteMin();
	 void deleteMin(T &minItem);
	 void makeEmpty();
	 //递归的合并方法
	 void merge(MyLeftistHeap & rhs);	 //将rhs合并到this堆,rhs置为nullptr

	 const MyLeftistHeap & operator=(const MyLeftistHeap & rhs);
 private:
	 struct LeftistNode {
		 T data;
		 LeftistNode *left;
		 LeftistNode *right;
		 int npl;	 //零路径长
		 LeftistNode(const T &ele,LeftistNode *l=nullptr,LeftistNode *r=nullptr,int n=0)
			 : data(ele), left(l), right(r), npl(n) {}
	 };

	 LeftistNode *root;

	 LeftistNode *merge(LeftistNode *h1, LeftistNode *h2) {
		 if (h1 == nullptr) return h2;
		 if (h2 == nullptr) return h1;
		 if (h1->data < h2->data) return merge1(h1, h2);
		 else return merge1(h2, h1);
	 }

	 //h1为根较小的堆
	 LeftistNode *merge1(LeftistNode *h1, LeftistNode *h2) {
		 if (h1->left == nullptr) h1->left = h2;  //h1只有一个跟节点,则h2直接为h1的左子树
		 else{
			 h1->right = merge(h1->right, h2);
			 if (h1->left->npl < h1->right->npl) swapChildren(h1);
			 h1->npl = h1->right->npl + 1;  //更新合并后的npl
		 }
		 return h1;
	 }

	 void swapChildren(LeftistNode *t){
		 LeftistNode *temp = t->left;
		 t->left = t->right;
		 t->right = t->left;
	 }

	 void reclaimMemory(LeftistNode *t);
	 LeftistNode *clone(LeftistNode *t) const {
		 LeftistNode *newroot = new LeftistNode(t->data, clone(t->left), clone(t->right),t->npl);
		 return newroot;
	 }

	 void makeEmpty(LeftistNode *t);
};

template <typename T>
void MyLeftistHeap<T>::merge(MyLeftistHeap<T> &rhs){
	if (this == &rhs) return;
	root = merge(root, rhs.root);
	rhs.root = nullptr;
}

template <typename T>
void MyLeftistHeap<T>::insert(const T & x){
	root = merge(new LeftistNode<T>(x), root);
}

template <typename T>
bool MyLeftistHeap<T>::isEmpty() const {
	return root == nullptr;
}

template <typename T>
const T & MyLeftistHeap<T>::findMin() const{
	try{
		if (isEmpty())
			throw std::underflow_error("root is nullptr!");
	}
	catch (std::underflow_error &e){
		std::cout << e.what() << std::endl;
	}
	return root->data;
}

template <typename T>
void MyLeftistHeap<T>::deleteMin() {
	try{
		if (isEmpty())
			throw std::underflow_error("root is nullptr!");
	}
	catch (std::underflow_error &e){
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
void MyLeftistHeap<T>::makeEmpty(LeftistNode *t) {
	if (t == nullptr) return;
	if (t->left == nullptr&&t->right == nullptr) {
		delete t;
		t = nullptr;
	}
	makeEmpty(t->left);
	makeEmpty(t->right);
}

template <typename T>
const MyLeftistHeap<T> & MyLeftistHeap<T>::operator=(const MyLeftistHeap & rhs) {
	if (this == &rhs) return *this;
	this->root = clone(rhs.root);
	return *this;
}
