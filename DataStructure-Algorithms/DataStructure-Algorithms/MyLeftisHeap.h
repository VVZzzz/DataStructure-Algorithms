# pragma once
//��ʽ��,���������޷��ϲ�������
#include <stdexcept>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
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

	 //���뼴 �ϲ�һ�����ڵ�
	 void insert(const T & x);

	 //ɾ���� ��root->left root->right�ϲ�,��ԭrootɾ��
	 void deleteMin();
	 void deleteMin(T &minItem);
	 void makeEmpty();

	 //void remove(T &minItem) is for 6.23(a).���������Chapter11��
	 //ɾ��ĳһ���ڵ�t,��t->left,r->right�ϲ�,����t��ͬʱҪע�����npl,ͬʱ����Ҫ��������������
	 //����˵�ѵĲ�����Ӧ��ȥ�������ڲ��Ľڵ��
	 void remove(T &minItem);
	 //�ݹ�ĺϲ�����
	 void merge(MyLeftistHeap & rhs);	 //��rhs�ϲ���this��,rhs��Ϊnullptr

	 const MyLeftistHeap & operator=(const MyLeftistHeap & rhs);

	 //����ɾ������,������־,�����ڵ㱻��ΪisDeleted.��lazyFindMin()��lazyDeleteMin()�����½��С�
	 void lazyDelete(LeftistNode *t) { t->isDeleted = true; }
	 const T & lazyFindMin();
	 void lazyDeleteMin();
 private:
	 struct LeftistNode {
		 T data;
		 LeftistNode *left;
		 LeftistNode *right;
		 int npl;	 //��·����
		 //lazy delete��־
		 bool isDeleted;
		 LeftistNode(const T &ele,LeftistNode *l=nullptr,LeftistNode *r=nullptr,int n=0,bool f=false)
			 : data(ele), left(l), right(r), npl(n), isDeleted(f) {}
		 void reset() {
			 left = nullptr;
			 right = nullptr;
			 npl = nullptr;
			 isDeleted = false;
		 }
	 };

	 LeftistNode *root;

	 LeftistNode *merge(LeftistNode *h1, LeftistNode *h2) {
		 if (h1 == nullptr) return h2;
		 if (h2 == nullptr) return h1;
		 if (h1->data < h2->data) return merge1(h1, h2);
		 else return merge1(h2, h1);
	 }

	 //h1Ϊ����С�Ķ�
	 LeftistNode *merge1(LeftistNode *h1, LeftistNode *h2) {
		 if (h1->left == nullptr) h1->left = h2;  //h1ֻ��һ�����ڵ�,��h2ֱ��Ϊh1��������
		 else{
			 h1->right = merge(h1->right, h2);
			 if (h1->left->npl < h1->right->npl) swapChildren(h1);
			 h1->npl = h1->right->npl + 1;  //���ºϲ����npl
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
	 void remove(T &minItem, LeftistNode *t) {
		 //TODO
	 }
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

template <typename T>
const T & MyLeftistHeap<T>::lazyFindMin() {
	if (root->isDeleted)
		lazyDeleteMin();
	return root->data;
}

template <typename T>
void MyLeftistHeap<T>::lazyDeleteMin() {
	root->isDeleted = true;
	std::vector<LeftistNode *> nodeVec;
	std::stack<LeftistNode *> nodeStack;
	//����stack����ǰ�����,�������Ľڵ����nodeVec��
	nodeStack.push(root);
	while (!nodeStack.empty()) {
		LeftistNode *temp = nodeStack.top();
		nodeVec.push_back(temp);
		nodeStack.pop();
		if (temp->right != nullptr)
			nodeStack.push(temp->right);
		if (temp->left != nullptr)
			nodeStack.push(temp->left);
	}
	//��nodeVec�н��������ϲ�,��ÿ�κϲ��Ľ��
	auto i = nodeVec.begin(),j = i;
	for (; i != nodeVec.end(); i++) {
		if (*i->isDeleted) {
			delete *i;
			continue;
		}	else {
			if ((i != j) && (!(*j->isDeleted))) {
				*i->reset();
				*j->reset();
				nodeVec.push_back(merge(*i, *j));
				j = i + 1;
				continue;
			}
			j = i;
		}
	}
	root = nodeVec.back();
	//�˴�ע��,����clone��ֱ�Ӹ�ֵ��root,��Ϊvector�б������ָ��,���������󲻽��ж�ָ����ָ���Ԫ�ص�delete.
	//����ڵ�ʵ������,��������ʹ��makeEmpty.
}
