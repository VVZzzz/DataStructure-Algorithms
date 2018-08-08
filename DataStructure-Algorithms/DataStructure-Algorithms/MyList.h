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
		
		/*ǰ���������������,������������ص��Ǹ���ֵ*/
		/*ǰ���������Ҫ�����Ч��(�˴�û��),���������������Ҫ*/
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
			//����current = current->next;
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

	protected:  //������List�����
		Node *current;
		Object &retrieve() const
		{ return current->data; } //���ߺ���
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
			//����current = current->next;
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

	iterator begin()  //���ص�һ����㣨�Ǳ�ͷ��㣩
	{
		return iterator(head->next);
	}

	const_iterator begin() const 
	{
		return const_iterator(head->next);
	}

	iterator end()  //����β���
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

	void clear()  //ֻɾ������ͷ β�����������
	{
		while (!empty())
			pop_front();
	}

	Object &front()  //�����汾��Object,�ǳ����汾���ڵ��ö���Ϊ��const,���뺯����thisָ��Ϊ��const�ͻ���÷�const�汾��begin()
	{
		return *begin();
	}

	const Object &front()  //�����汾���ڵ��ö���Ϊconst,���뺯����thisָ��Ϊconst�ͻ����const�汾��begin()
	{
		return *begin();
	}

	Object &back()  //�������һ����㣨��β�ڵ㣩
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

	iterator insert(iterator itr, const Object &x)  //��itr֮ǰ��λ�ò���,���ز���֮���itr
	{
		Node *p = itr.current;
		theSize++;  //ע���ȸ�ֵ,���޸�
		return iterator(p->prev = p->prev->next = new Node(x, p->prev, p));
		
	}

	iterator erase(iterator itr)  //ɾ��itrλ�õĽ��,����itr֮��ĵ�����
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
	Node *head;  //��ͷ���
	Node *tail;  //β���

	void init()  //��ʼ�����ߺ���
	{
		theSize = 0;
		head = new Node;
		tail = new Node;
		head->next = tail;
		tail->prev = head;
	}
};
#endif // !MYLIST_H_

