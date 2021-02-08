#include <iostream>
#include <stdexcept>
#include <cassert>
#include <initializer_list>

template <class T>
class LList
{
	struct Node
	{
		Node(const T& val = T(), Node* next = nullptr);
		T data;
		Node* next;
	};

public:
	LList();
	LList(const std::initializer_list<T>& values);
	LList(const LList& other);
	LList(LList&& other);
	LList& operator=(const LList& rhs);
	LList& operator=(LList&& other);
	~LList();

	const T& front() const;
	const T& back() const;
	const T& at(size_t pos) const;

	bool is_empty() const;
	size_t size() const;

	void push_front(const T& val);
	void push_end(const T& val);
	void push_atPos(size_t pos, const T& val);

	void pop_front();
	void pop_end();
	T pop_atPos(size_t pos);
private:
	Node* head, * tail;
	size_t sz;

	void copy(const LList& other);
	void freeHeap();
};

template<class T>
inline LList<T>::Node::Node(const T& val, Node* next)
	:data(val), next(next)
{}

template<class T>
inline void LList<T>::copy(const LList<T>& other)
{
	Node dummy;
	Node* iter = &dummy;
	Node* curr = other.head;
	while (curr) {
		iter->next = new Node(curr->data);
		iter = iter->next;
		curr = curr->next;
	}
	head = dummy.next;
	tail = head ? iter : nullptr;
	sz = other.sz;
}

template<class T>
inline void LList<T>::freeHeap()
{
	Node* iter = head;
	Node* detach = head;

	for (size_t i = 0; i < sz; ++i) {
		detach = iter;
		iter = iter->next;
		delete detach;
	}

	tail = head = nullptr;
	sz = 0;
}

template<class T>
inline LList<T>::LList()
	:head(nullptr), tail(nullptr), sz(0) {}

template<class T>
inline LList<T>::LList(const std::initializer_list<T>& values)
	: head(nullptr), tail(nullptr), sz(0)
{
	for (const T& val : values) {
		push_end(val);
	}
}

template<class T>
inline LList<T>::LList(const LList& other)
	:LList()
{
	copy(other);
}

template<class T>
inline LList<T>::LList(LList&& other)
	:LList()
{
	std::swap(head, other.head);
	std::swap(tail, other.tail);
	std::swap(sz, other.sz);
}

template<class T>
inline LList<T>& LList<T>::operator=(const LList<T>& rhs)
{
	if (this != &rhs) {
		freeHeap();
		copy(rhs);
	}

	return *this;
}

template<class T>
inline LList<T>& LList<T>::operator=(LList<T>&& rhs)
{
	if (this != &rhs) {
		std::swap(head, rhs.head);
		std::swap(tail, rhs.tail);
		std::swap(sz, rhs.sz);
	}
	return *this;
}

template<class T>
inline LList<T>::~LList()
{
	freeHeap();
}

template<class T>
inline const T& LList<T>::at(size_t pos) const
{
	if (is_empty() || pos >= sz) {
		throw std::invalid_argument("Index out of bounds\n");
	}

	if (pos == sz - 1) {
		return tail->data;
	}

	const Node* iter = head;
	for (size_t i = 0; i < pos; ++i, iter = iter->next)
		;
	return iter->data;
}

template<class T>
inline const T& LList<T>::front() const
{
	return at(0);
}

template< class T>
inline const T& LList<T>::back() const
{
	return at(sz - 1);
}

template<class T>
inline size_t LList<T>::size() const
{
	return sz;
}

template<class T>
inline void LList<T>::push_atPos(size_t pos, const T& val)
{
	if (pos > sz) {
		throw std::invalid_argument("Index out of bounds\n");
	}

	if (pos == 0) {
		head = new Node(val, head);
		if (!sz) tail = head;
	}
	else if (pos == sz) {
		tail->next = new Node(val);
		tail = tail->next;
	}
	else {
		Node* iter = head;
		for (size_t i = 0; i < pos - 1; ++i, iter = iter->next)
			;

		iter->next = new Node(val, iter->next);
	}

	++sz;
}

template<class T>
inline void LList<T>::push_front(const T& val)
{
	push_atPos(0, val);
}

template<class T>
inline void LList<T>::push_end(const T& val)
{
	push_atPos(sz, val);
}

template<class T>
inline T LList<T>::pop_atPos(size_t pos)
{
	if (is_empty() || pos > sz - 1) {
		throw std::invalid_argument("Index out of bounds\n");
	}

	Node* detach = head;

	if (pos == 0) {
		head = head->next;
		if (head == nullptr) {
			tail = nullptr;
		}
	}
	else {
		Node* iter = head;
		for (size_t i = 0; i < pos - 1; ++i, iter = iter->next)
			;

		detach = iter->next;
		iter->next = detach->next;

		if (detach == tail) {
			tail = iter;
		}
	}
	--sz;
	T store = detach->data;
	delete detach;
	return store;
}

template<class T>
inline void LList<T>::pop_front()
{
	pop_atPos(0);
}

template<class T>
inline void LList<T>::pop_end()
{
	pop_atPos(sz - 1);
}

template<class T>
inline bool LList<T>::is_empty() const
{
	return sz == 0;
}
