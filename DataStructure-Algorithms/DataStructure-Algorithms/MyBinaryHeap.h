#pragma once
#include <vector>
#include <stdexcept>
#include <iostream>
//�����ʵ�ֵ����ȶ���,�ײ������ü򵥵�����ʵ��
//�ڵ�t������Ϊ2t,�Ҷ���Ϊ2t+1,��Ϊt/2��ȡ��.
//�������һ����ȫ������
template <typename T>
class MyBinaryHeap{
 public:
	explicit MyBinaryHeap(int capacity = 100);
	//�ù��캯�����������ݣ���ȫ���ڵ����ˡ�buildHeap()��Ϊȫ���ڵ����ˡ�
	explicit MyBinaryHeap(const std::vector<T> &items)
		: heap_arry(items.size()+10)
			currentSize(items.size()){
		for (int i = 0; i < items.size(); i++)
			heap_arry[i + 1] = heap_arry[i];
		buildHeap();
	}

	bool isEmpty() const;
	const T &findMin() const;

	void insert(const T &x);
	void deleteMin();
	void deleteMin(const T & minItem);
	void makeEmpty();

	void decreaseKey(int pos, const T &diff);
	void increaseKey(int pos, const T &diff);
	//remove(p)���Ƚ�p�ڵ�decreaseKey(p,�����),��deleteMin();
	void remove(int pos);
 private:
	int currentSize;
	std::vector<T> heap_arry;  //���ݴ��±�1��ʼ����
	void buildHeap();
	void percolateDown(int hole);  //���˲���
	void percolateUp(int hole);  //���˲���
};

//����ΪO(logN)
template <typename T>
void MyBinaryHeap<T>::insert(const T &x){
	if (currentSize == heap_arry.size() - 1)
		heap_arry.resize(heap_arry.size() << 1);
	//ʵ��Ϊ���˲���
	int hole = ++currentSize;
	heap_arry[hole]= x;
	percolateUp(hole);
}

template <typename T>
void MyBinaryHeap<T>::deleteMin() {
	try{
		if (isEmpty())
			throw std::underflow_error("heap_arry is empty!");
	}
	catch (std::underflow_error &e){
		std::cout << e.what() << std::endl;
		return;
	}

	heap_arry[1] = heap_arry[currentSize--];
	percolateDown(1);
}

template <typename T>
void MyBinaryHeap<T>::deleteMin(const T & minItem) {
	try{
		if (isEmpty())
			throw std::underflow_error("heap_arry is empty!");
	}
	catch (std::underflow_error &e){
		std::cout << e.what() << std::endl;
		return;
	}

	minItem = heap_arry[1];
	heap_arry[1] = heap_arry[currentSize--];
	percolateDown(1);
}

template <typename T>
void MyBinaryHeap<T>::percolateDown(int hole){
	T temp = heap_arry[hole];
	int child;
	for (; (hole << 1) <= currentSize; hole = child){
		child = hole << 1;
		if (child != currentSize&&heap_arry[child + 1] < heap_arry[child])
			child++;
		if (heap_arry[child] < temp)
			heap_arry[hole] = heap_arry[child];
		else
			break;
	}
	heap_arry[hole] = temp;
}

template <typename T>
void MyBinaryHeap<T>::percolateUp(int hole){
	T temp = heap_arry[hole];
	for (; hole > 1 && temp < heap_arry[hole >> 1]; hole >>= 1)
		heap_arry[hole] = heap_arry[hole >> 1];	 //��ֵ,���⽻��
	heap_arry[hole] = temp;
}


template<typename T>
void MyBinaryHeap<T>::decreaseKey(int pos, const T &diff){
	try{
		if (pos > currentSize || pos <= 0)
			throw std::out_of_range("pos to decrease is valid!");
	}
	catch (std::out_of_range& e){
		std::cout << e.what() << std::endl;
		return;
	}
	heap_arry[pos] = heap_arry[pos] - diff;
	percolateUp(pos);  //����
}

template <typename T>
void MyBinaryHeap<T>::increaseKey(int pos, const T &diff){
	try{
		if (pos > currentSize || pos <= 0)
			throw std::out_of_range("pos to decrease is valid!");
	}
	catch (std::out_of_range& e){
		std::cout << e.what() << std::endl;
		return;
	}
	heap_arry[pos] = heap_arry[pos] + diff;
	percolateDown(pos);  //����
}

template <typename T = int>
void MyBinaryHeap<T>::remove(int pos){
	//��������������ض�����Ϊint
	decreaseKey(pos, INT_MAX);
	deleteMin();
}

template <typename T>
void MyBinaryHeap<T>::buildHeap(){
	for (int i = currentSize / 2; i > 0; i--)
		percolateDown(i);
}
