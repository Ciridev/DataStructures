#pragma once

#include <utility>

template<typename T>
struct Node
{
	T m_Data;
	Node<T>* m_Next;
	Node<T>* m_Prev;

	Node() :
		m_Next((Node<T>*)nullptr),
		m_Prev((Node<T>*)nullptr),
		m_Data((T)(NULL))
	{
	}

	Node(const T& data, Node<T>* next, Node<T>* prev) :
		m_Next(next), m_Prev(prev), m_Data(data)
	{
	}
};

template<typename T>
class DoublyLinkedList
{
public:
	DoublyLinkedList() : m_Head(nullptr), m_Tail(nullptr)
	{
		m_Size = 0;
	}

	DoublyLinkedList(const std::initializer_list<T>& ilist) : m_Head(nullptr), m_Tail(nullptr)
	{
		for (auto& elem : ilist)
			PushFront(elem);
	}

	~DoublyLinkedList()
	{
		Clear();
	}

	struct iterator
	{
		Node<T>* ptr;
		iterator(Node<T>* p) : ptr(p) {}

		const T& operator*() const
		{
			return ptr->m_Data;
		}

		T& operator*()
		{
			return ptr->m_Data;
		}

		const Node<T>* get() const
		{
			return ptr;
		}
		
		Node<T>* get()
		{
			return ptr;
		}

		iterator& operator++()
		{
			ptr = ptr->m_Next;
			return *this;
		}
		
		iterator& operator++(int)
		{
			iterator& result = *this;
			++(*this);
			return result;
		}

		bool operator == (const iterator& other)
		{
			return ptr == other.ptr;
		}
		
		bool operator != (const iterator& other)
		{
			return ptr != other.ptr;
		}
	};

	void PushFront(const T& data)
	{
		m_Size++;

		m_Head = new Node<T>(
			data,
			m_Head,
			nullptr
		);

		if (m_Head->m_Next)
			m_Head->m_Next->m_Prev = m_Head;

		if (m_Size == 1)
			m_Tail = m_Head;

		return;
	}

	void PopFront()
	{
		if (m_Head)
		{
			m_Size--;

			auto first = m_Head;
			m_Head = m_Head->m_Next;
			delete first;
		}

		// throw empty

		return;
	}

	template<typename... Args>
	void EmplaceFront(Args&&... args)
	{
		m_Size++;

		m_Head = new Node<T>(
			std::move(T(std::forward<Args>(args)...)),
			m_Head,
			nullptr
		);

		if (m_Head->m_Next)
			m_Head->m_Next->m_Prev = m_Head;

		if (m_Size == 1)
			m_Tail = m_Head;

		return;
	}

	void PushBack(const T& data)
	{
		m_Size++;

		m_Tail = new Node<T>(
			data,
			nullptr,
			m_Tail
		);

		if (m_Tail)
			m_Tail->m_Prev->m_Next = m_Tail;

		if (m_Size == 1)
			m_Head = m_Tail;

		return;
	}

	void PopBack()
	{
		if (m_Tail)
		{
			m_Size--;

			auto last = m_Tail;
			m_Tail = m_Tail->m_Prev;
			delete last;
		}

		// throw empty

		return;
	}

	template<typename... Args>
	void EmplaceBack(Args&&... args)
	{
		m_Size++;

		m_Tail = new Node<T>(
			std::move(T(std::forward<Args>(args)...)),
			nullptr,
			m_Tail
			);

		if (m_Tail)
			m_Tail->m_Prev->m_Next = m_Tail;

		if (m_Size == 1)
			m_Head = m_Tail;
	}

	void Insert(iterator __where, const T& data)
	{
		for(auto it = begin(); it != end(); it++)
			if (it == __where)
			{
				m_Size++;

				auto newnode = new Node<T>(
					data,
					__where.get(),
					__where.get()->m_Prev
				);

				__where.get()->m_Prev->m_Next = newnode;
				__where.get()->m_Prev = newnode;
			}
	}

	template<typename... Args>
	void EmplaceInsert(iterator __where, Args&&... args)
	{
		for (auto it = begin(); it != end(); it++)
			if (it == __where)
			{
				m_Size++;

				auto newnode = new Node<T>(
					std::move(T(std::forward<Args>(args)...)),
					__where.get(),
					__where.get()->m_Prev
					);

				__where.get()->m_Prev->m_Next = newnode;
				__where.get()->m_Prev = newnode;
				
				return;
			}
	}
	
	void Replace(iterator __where, const T& data)
	{
		for(auto it = begin(); it != end(); it++)
			if (it == __where)
			{
				__where.get()->m_Data = data;
				return;
			}
	}

	template<typename... Args>
	void EmplaceReplace(iterator __where, Args&&... args)
	{
		for (auto it = begin(); it != end(); it++)
			if (it == __where)
			{
				__where.get()->m_Data = std::move(T(std::forward<Args>(args)...));
				return;
			}
	}

	void Remove(iterator __where)
	{
		for (auto it = begin(); it != end(); it++)
			if (it == __where)
			{
				m_Size--;

				__where.get()->m_Prev->m_Next = __where.get()->m_Next;
				__where.get()->m_Next->m_Prev = __where.get()->m_Prev;

				delete __where.get();

				return;
			}
	}

	void Clear()
	{
		while (!IsEmpty())
			PopFront();
	}

	bool IsEmpty() const { return m_Size == 0; }

	iterator begin() const
	{
		return iterator(m_Head);
	}

	iterator begin() 
	{
		return iterator(m_Head);
	}
	
	iterator end() const
	{
		return iterator(nullptr);
	}

	iterator end() 
	{
		return iterator(nullptr);
	}

	size_t   Size() const { return m_Size; }
	Node<T>* Head() const { return m_Head; }
	Node<T>* Tail() const { return m_Tail; }

private:
	
	using size_t = unsigned int;

	Node<T>* m_Head;
	Node<T>* m_Tail;

	size_t m_Size;
};