#ifndef MYLIST_H_
#define MYLIST_H_
template <typename Object>
class MyList
{
private:
	struct Node
	{
		Object data;
		Node *prev;
		Node *next;
		bool isactive;
		bool istodel;
		Node(const Object &object = Object(),
			Node *p = nullptr, Node *n = nullptr) :
			data(object), prev(p), next(n), isactive(true), istodel(false) { }
	};

public:
	class const_iterator
	{
	friend class MyList<Object>;
	public:
		const_iterator() :current(nullptr) { }

		const Object & operator*() const
		{return retrieve();}
		
		/*前置运算符返回引用,后置运算符返回的是复制值*/
		/*前置运算符需要检查有效性(此处没查),而后置运算符不需要*/
		/*3.18中实现废物为NULL,则在应在每个方法中检测current->isactive
		是否为false,一旦为false则就将this设为nullptr即可。（该代码中没写）*/
		const_iterator & operator++ ()
		{
			current = current->next;
			return *this;
		}

		const_iterator & operator-- ()
		{
			current = current->prev;
			return *this;
		}

		const_iterator operator++(int)
		{
			const_iterator old_p(*this);
			++(*this);
			//或者current = current->next;
			return old_p;
		}

		const_iterator operator--(int)
		{
			const_iterator old_p(*this);
			--(*this);
			return old_p;
		}

		const_iterator & operator+ (int k) const {
			const_iterator advanced = *this;
			for (size_t i = 0; i < k; i++) {
				//++advanced;
				advanced.current = advanced.current->next;
			}
			return advanced;
		}

		bool operator==(const const_iterator &rhs) const 
		{return current == rhs.current;}

		bool operator!=(const const_iterator &rhs) const 
		{return current != rhs.current;}

	protected:  //能允许List类访问
		Node *current;
		Object &retrieve() const
		{ return current->data; } //工具函数
		const_iterator(Node *p) :current(p->isactive ? p:nullptr) { }

	};

	class iterator :public const_iterator
	{
	friend class MyList<Object>;
	public:
		iterator() { }
		Object &operator*()
		{
			return retrieve();
		}

		iterator & operator++ ()
		{
			current = current->next;
			return *this;
		}

		iterator & operator-- ()
		{
			current = current->prev;
			return *this;
		}

		iterator operator++(int)
		{
			iterator old_p(*this);
			++(*this);
			//或者current = current->next;
			return old_p;
		}

		iterator operator--(int)
		{
			iterator old_p(*this);
			--(*this);
			return old_p;
		}

	protected:
		iterator(Node *p) :const_iterator(p) { }
	};

	class const_reverse_iterator {
		friend class MyList<Object>;
	public:
		const_reverse_iterator() :current(nullptr) { }

		const Object & operator*() const
		{return retrieve();}
		
		/*前置运算符返回引用,后置运算符返回的是复制值*/
		/*前置运算符需要检查有效性(此处没查),而后置运算符不需要*/
		const_reverse_iterator & operator++ ()
		{
			current = current->prev;
			return *this;
		}

		const_reverse_iterator & operator-- ()
		{
			current = current->next;
			return *this;
		}

		const_reverse_iterator operator++(int)
		{
			const_reverse_iterator old_p(*this);
			++(*this);
			//或者current = current->next;
			return old_p;
		}

		const_reverse_iterator operator--(int)
		{
			const_reverse_iterator old_p(*this);
			--(*this);
			return old_p;
		}

		const_reverse_iterator & operator+ (int k) const {
			const_reverse_iterator advanced = *this;
			for (size_t i = 0; i < k; i++) {
				//++advanced;
				advanced.current = advanced.current->prev;
			}
			return advanced;
		}

		bool operator==(const const_reverse_iterator &rhs) const 
		{return current == rhs.current;}

		bool operator!=(const const_reverse_iterator &rhs) const 
		{return current != rhs.current;}

	protected:
		Node *current;
		Object &retrieve() const
		{ return current->data; } //工具函数
		const_reverse_iterator(Node *p) :current(p->isactive ? p:nullptr) { }

	};

	class reverse_iterator :public const_reverse_iterator {
		friend class MyList<Object>;
	public:
		reverse_iterator() { }
		Object &operator*()
		{
			return retrieve();
		}

		reverse_iterator & operator++ ()
		{
			current = current->prev;
			return *this;
		}

		reverse_iterator & operator-- ()
		{
			current = current->next;
			return *this;
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator old_p(*this);
			++(*this);
			//或者current = current->next;
			return old_p;
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator old_p(*this);
			--(*this);
			return old_p;
		}

	protected:
		reverse_iterator(Node *p) :const_reverse_iterator(p) { }

	};

	MyList() { init(); }
	~MyList() 
	{
		clear();
		delete head;
		delete tail;
	}

	const MyList operator= (const MyList &rhs)
	{
		if (this != rhs)
		{
			clear();
			for (const_iterator i=rhs.begin();i!=rhs.end();++i)
			{
				push_back(*i);
			}
		}
		return *this;
	}

	iterator begin()  //返回第一个结点（非表头结点）
	{
		return iterator(head->next);
	}

	const_iterator begin() const 
	{
		return const_iterator(head->next);
	}

	iterator end()  //返回尾结点
	{
		return iterator(tail);
	}

	const_iterator end() const
	{
		return const_iterator(tail);
	}

	reverse_iterator rbegin() {
		return reverse_iterator(tail->prev);
	}

	const_reverse_iterator rbegin() const {
		return const_reverse_iterator(tail->prev);
	}

	reverse_iterator rend() {
		return reverse_iterator(head);
	}

	const_reverse_iterator rend() const {
		return const_reverse_iterator(head);
	}

	int size() const
	{
		return theSize;
	}

	bool empty() const
	{
		return theSize == 0;
	}

	void clear()  //只删除除表头 尾结点的其他结点
	{
		while (!empty())
			pop_front();
	}

	Object &front()  //两个版本的Object,非常量版本由于调用对象为非const,传入函数内this指针为非const就会调用非const版本的begin()
	{
		return *begin();
	}

	const Object &front() const  //常量版本由于调用对象为const,传入函数内this指针为const就会调用const版本的begin()
	{
		return *begin();
	}

	Object &back()  //返回最后一个结点（非尾节点）
	{
		return *--end();
	}

	const Object &back() const 
	{
		return *--end();
	}

	void push_front(const Object &object)
	{
		insert(begin(), x);
	}

	void push_back(const Object &object)
	{
		insert(end(), object);
	}

	void pop_front()
	{
		erase(begin());
	}

	void pop_back()
	{
		erase(--end());
	}

	iterator insert(iterator itr, const Object &x)  //在itr之前的位置插入,返回插入之后的itr
	{
		Node *p = itr.current;
		theSize++;  //注意先赋值,再修改
		return iterator(p->prev = p->prev->next = new Node(x, p->prev, p));
		
	}

	iterator erase(iterator itr)  //删除itr位置的结点,返回itr之后的迭代器
	{
		Node *p = itr.current;
		iterator retVal = p->next;
		p->prev->next = p->next;
		p->next->prev = p->prev;
		p->isactive = false;
		delete p;
		theSize--;
		return retVal;
	}

	iterator erase(iterator start, iterator to)
	{
		for (iterator i = start; i != to; i = erase(i));
		return to;
	}

	void lazy_full_erase() {
		auto itr = begin();
		while (itr != end()) {
			if (itr.current->istodel) {
				itr = erase(itr);
				del_num--;
			}
			else
				itr++;
		}
	}

	iterator lazy_erase(iterator itr) {
		iterator retitr = itr.current->next;
		//这里注意要跳过istodel为true的结点
		while (retitr&&retitr.current->istodel)
			retitr++;
		itr.current->istodel = true;
		if (++del_num >= size()/2) {
			//清空
			lazy_full_erase();
		}
		return retitr;
	}

	iterator lazy_erase(iterator start, iterator to)
	{
		for (iterator i = start; i != to; i = lazy_erase(i));
		return to;
	}

	void splice(iterator itr, MyList<Object>& lst) {
		Node *p = itr.current;
		theSize += lst.size();
		lst.head->next->prev = p->prev;
		p->prev->next = lst.head->next;
		lst.tail->prev->next = p;
		p->prev = lst.tail->prev;
		lst.head->next = nullptr;
		lst.init();
	}
private:
	int theSize;
	Node *head;   //表头结点
	Node *tail;   //尾结点
	int del_num;  //要删除的结点个数

	void init()  //初始化工具函数
	{
		theSize = 0;
		head = new Node;
		tail = new Node;
		head->next = tail;
		tail->prev = head;
		del_num = 0;
	}
};
#endif // !MYLIST_H_

