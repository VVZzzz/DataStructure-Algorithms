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
		Node(const Object &object = Object(),
			Node *p = nullptr, Node *n = nullptr) :
			data(object), prev(p), next(n) { }
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

		bool operator==(const const_iterator &rhs) const 
		{return current == rhs.current;}

		bool operator!=(const const_iterator &rhs) const 
		{return current != rhs.current;}

	protected:  //能允许List类访问
		Node *current;
		Object &retrieve() const
		{ return current->data; } //工具函数
		const_iterator(Node *p) :current(p) { }

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

	const Object &front()  //常量版本由于调用对象为const,传入函数内this指针为const就会调用const版本的begin()
	{
		return *begin();
	}

	Object &back()  //返回最后一个结点（非尾节点）
	{
		return *--end();
	}

	const Object &back()
	{
		return *--end();
	}

	void push_front(const Object &object)
	{
		insert(begin(), x);
	}

	void push_back(const Object &object)
	{
		insert(end(), x);
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
		delete p;
		theSize--;
		return retVal;
	}

	iterator erase(iterator start, iterator to)
	{
		for (iterator i = start; i != to; i = erase(i));
		return to;
	}
private:
	int theSize;
	Node *head;  //表头结点
	Node *tail;  //尾结点

	void init()  //初始化工具函数
	{
		theSize = 0;
		head = new Node;
		tail = new Node;
		head->next = tail;
		tail->prev = head;
	}
};
#endif // !MYLIST_H_

