#ifndef MYVECTOR_H_
#define MYVECTOR_H_

//没有适配范围for
template <typename Object>
class const_iterator {
	friend class MyVector<Object>;
public:
	const Object &operator*() const {
		return retrieve();
	}
	const_iterator & operator++() {
		current++;
		return *this;
	}
	const_iterator &operator++(int) {
		const_iterator old = *this;
		++(*this);
		return old;
	}
	bool operator==(const const_iterator & rhs) const {
		return current == rhs.current;
	}
	bool operator!=(const const_iterator & rhs) const {
		return !(current == rhs.current);
	}

protected:
	Object *current;
	const MyVector<Object> *theVect;
	Object & retrieve() const {
		assertIsValid();
		return *current;
	}
	//protect保护构造函数
	const_iterator(const MyVector<Object> &vect,Object *p)
		:theVect(vect),current(p){}
	
	void assertIsValid() const {
		if (theVect==nullptr||current==nullptr) {
			throw IteratorOutOfBoundsException();
		}
	}
};
template <typename Object>
class iterator :public const_iterator {
	friend class MyVector<Object>;
public:
	Object & operator *()
	{
		return retrieve();
	}
	const Object & operator*() const {
		return const_iterator::retrieve();
	}
	iterator & operator++() {
		cout << "old " << *current << " ";
		current++;
		return *this;
	}
	iterator operator++(int) {
		iterator old = *this;
		++(*this);
		return old;
	}
protected:
	iterator(const MyVector<Object>& vect,Object *p)
		:const_iterator(vect,p){ } 

};
template <typename Object>
class MyVector
{
	//typedef Object * iterator;
	//typedef const Object * const_iterator;
public:
	explicit MyVector(int initsize = 0)
		: m_Size(initsize),
		m_Capacity(initsize + SPARE_CAPACITY),
		m_pobjects(new Object[m_Capacity]) { }

	MyVector(const MyVector &rhs)
		: m_pobjects(NULL)
	{
		operator=(rhs);
	}

	MyVector & operator=(const MyVector &rhs)
	{
		if (rhs != this)
		{
			delete[] objects;
			m_Size = rhs.m_Size;
			m_Capacity = rhs.m_Capacity;
			m_pobjects = new Object[m_Capacity];
			auto temp = m_pobjects;
			auto temp_rhs = rhs.m_pobjects;
			for (int i = 0; i != m_Size; i++)
			{
				*temp++ = *temp_rhs++;
			}
		}
		return *this;
	}

	void resize(int resz)
	{
		if (resz > m_Size)
			reserve(2*resz+1);
		m_Size = resz;
	}

	void reserve(int recapacity)
	{
		if (recapacity < m_Capacity) //不允许保留空间小于旧的空间
			return;
		Object *newpobjects = new Object[recapacity];
		auto temp_new = newpobjects;
		auto temp = m_pobjects;
		for (int i = 0; i != m_Size; i++)
		{
			*temp_new++ = *temp++;
		}
		delete[] m_pobjects;
		m_pobjects = newpobjects;
		m_Capacity = recapacity;
	}

	Object & operator[](unsigned int i)
	{
		if (i < m_Size)
			return *(m_pobjects + i);
	}

	const Object &operator[](unsigned int i) const
	{
		if (i < m_Size)
			return *(m_pobjects + i);
		else
			throw out_of_range("out of range!");
	}

	bool empty() const
	{
		return m_Size == 0;
	}
	int size() const   //无需返回const,只需后置const即可
	{
		return m_Size;
	}
	int capacity() const
	{
		return m_Capacity;
	}

	void push_back(Object obj)
	{
		if (m_Size+1>m_Capacity)
			reserve(2 * m_Size + 1);
		m_pobjects[m_Size++] = obj;
	}
	void pop_back()  
	{
		--m_Size;
	}
	iterator insert(iterator pos, const Object& x) {
		Object * iter = &m_pobjects[0];
		Object *oldArray = m_pobjects;
		m_Size++;
		int i = 0;
		if (m_Capacity<m_Size) {
			m_Capacity = m_Size;
		}
		m_pobjects = new Object[m_Capacity];
		while (iter!= pos) {
			m_pobjects[i] = oldArray[i];
			iter += sizeof(Object);
			//pos += sizeof(Object);
			i++;
		}
		m_pobjects[i] = x;
		for (int k = i + 1; k < m_Size;k++) {
			m_pobjects[k] = oldArray[k - 1];
		}
		delete[] oldArray;
		return &m_pobjects[i];
	}
	iterator erase(iterator pos) {
		if (begin()==end()||pos==end()) {
			return end();
		}
		Object * iter = pos, *niter = pos+1;
		Object * res = pos;
		while (niter!=end()) {
			*iter = *niter;
			iter++;
			niter++;
		}
		//delete	niter;
		//erase和clear不回收内存
		m_Size--;
		return res;

	}
	const Object &back() const 
	{
		return m_pobjects[m_Size - 1];
	}

	/*
	iterator begin()
	{
		return &m_pobjects[0];
	}
	

	const const_iterator begin() const 
	{
		return const &m_pobjects[0];
	}

	iterator end()
	{
		return &m_pobjects[m_Size-1];
	}

	const const_iterator end() const //此处无需前置的const，只需后置const是this指针为const即可
	{
		return &m_pobjects[m_Size-1];
	}
	*/
	iterator begin() {
		return iterator(*this, &m_pobjects[0]);
	}
	const_iterator begin() const {
		return const_iterator(*this, &m_pobjects[0]);
	}
	iterator end() {
		return iterator(*this, &m_pobjects[size()]);
	}
	const_iterator begin() const {
		return const_iterator(*this, &m_pobjects[size()]);
	}

	const 
		enum { SPARE_CAPACITY = 16 };
private:
	int m_Size;
	int m_Capacity;
	Object *m_pobjects;
};
#endif // !MYVECTOR_H_
