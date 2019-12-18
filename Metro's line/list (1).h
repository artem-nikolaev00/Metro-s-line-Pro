#pragma once
#ifndef _LIST_H_
#define _LIST_H_

#include <memory>
#include <initializer_list>

template <class _Ty, class _Allocator = std::allocator<_Ty>>
class list;

template <class _Ty>
struct List_node
{
	_Ty* _value = nullptr;
	List_node* _prev = nullptr;
	List_node* _next = nullptr;
	~List_node() {
		if (_value)	delete _value;
		if (_prev)	_prev ->_next = _next;
		if (_next)	_next->_prev = _prev;
	}
};

template <class _Category, class _Ty, class _Diff = ptrdiff_t, class _Pointer = _Ty * , class _Reference = _Ty & >
struct iterator { // base type for iterator classes
	using iterator_category = _Category;
	using value_type = _Ty;
	using difference_type = _Diff;
	using pointer = _Pointer;
	using reference = _Reference;
};

template <class _Ty>
class List_const_iterator : public iterator<std::bidirectional_iterator_tag, List_node<_Ty>>
{
protected:
	typename List_const_iterator::pointer _node;
private:
	friend class list<_Ty>;
public:
	List_const_iterator() : _node(nullptr) {}
	List_const_iterator(typename List_const_iterator::pointer node) : _node(node) {}
	List_const_iterator(const List_const_iterator& other) : _node(other._node) {}
	List_const_iterator(List_const_iterator&& other) noexcept : _node(other._node) { other._node = nullptr; }

	List_const_iterator& operator = (typename List_const_iterator::pointer node) { this->_node = node; return *this; }
	List_const_iterator& operator = (const List_const_iterator& other) { this->_node = other._node; return *this; }
	List_const_iterator& operator = (List_const_iterator&& other) noexcept { this->_node = other._node; other._node = nullptr; return *this; }

	const _Ty& operator *() const { return *(this->_node->_value); }

	_Ty* operator ->() const { return this->_node->_value; }
	bool operator !=(const List_const_iterator &it) const { return this->_node != it._node; }
	bool operator ==(const List_const_iterator &it) const { return this->_node == it._node; }
	List_const_iterator & operator ++ () {
		this->_node = this->_node->_next;
		return *this;
	}
	List_const_iterator operator ++ (int) {
		List_const_iterator res(*this);
		this->_node = this->_node->_next;
		return res;
	}
	List_const_iterator & operator -- () {
		this->_node = this->_node->_prev;
		return *this;
	}
	List_const_iterator operator -- (int) {
		List_const_iterator res(*this);
		this->_node = this->_node->_prev;
		return res;
	}

	operator _Ty&() { return *(this->_node->_value); }
};

template<class _Ty>
class List_iterator : public List_const_iterator<_Ty>
{
private:
	friend class list<_Ty>;
public:
	List_iterator() : List_const_iterator<_Ty>() {}
	List_iterator(typename List_iterator::pointer node) : List_const_iterator<_Ty>(node) {}
	List_iterator(const List_iterator& other) : List_const_iterator<_Ty>(other) {}
	List_iterator(List_iterator&& other) noexcept : List_const_iterator<_Ty> (std::move(other)) {}

	List_iterator& operator = (typename List_iterator::pointer node) { this->_node = node; return *this; }
	List_iterator& operator = (const List_iterator& other) { this->_node = other._node; return *this; }
	List_iterator& operator = (List_iterator&& other) noexcept { this->_node = other._node; other._node = nullptr; return *this; }

	_Ty& operator *() { return *(this->_node->_value); }
	const _Ty& operator *() const { return *(this->_node->_value); }
	_Ty* operator ->() const { return this->_node->_value; }

	bool operator !=(const List_iterator &it) const { return this->_node != it._node; };
	bool operator ==(const List_iterator &it) const { return this->_node == it._node; };
	List_iterator & operator ++ () {
		this->_node = this->_node->_next;
		return *this;
	}
	List_iterator operator ++ (int) {
		List_const_iterator res(*this);
		this->_node = this->_node->_next;
		return res;
	}
	List_iterator & operator -- () {
		this->_node = this->_node->_prev;
		return *this;
	}
	List_iterator operator -- (int) {
		List_iterator res(*this);
		this->_node = this->_node->_prev;
		return res;
	}

	operator _Ty&() { return *(this->_node->_value); }

};

template <class _Ty, class _Allocator = std::allocator<_Ty>>
class list
{
private:
	using List_node = List_node<_Ty>;
	size_t _size = 0;
	List_node* _begin = nullptr;
	List_node* _end = nullptr;
public:
	using const_iterator = List_const_iterator<_Ty>;
	using iterator = List_iterator<_Ty>;

	using const_reverse_iterator = std::reverse_iterator<const_iterator>;
	using reverse_iterator = std::reverse_iterator<iterator>;

	list() {
		_begin = new List_node;
		_end = new List_node;
		_begin->_next = _end;
		_end->_prev = _begin;
	}; // Пустой конструктор

	
	iterator insert(const_iterator pos, const _Ty& value) {
		const_iterator right = pos;
		const_iterator left = --pos;
		List_node* newel = new List_node;
		newel->_next = right._node;
		newel->_prev = left._node;
		newel->_value = new _Ty(value);
		right._node->_prev = newel;
		left._node->_next = newel;
		return iterator(newel);
	}
	void push_back(const _Ty& value) {
		insert(end(), value);
	}

	list(const list& other) {
		typename List_const_iterator<_Ty>::pointer p;
		for (p = other._begin; p != other._end; ++p) {
			this->push_back(*p);//////////////
		}
			
	} // Копирующий

	//list(list&& other) noexcept : // Перемещающий 
	//	_size(other._size),
	//	_begin(other._begin),
	//	_end(other._end)
	//{other._nodes = nullptr; }


	list& operator = (const list& other) {
		if (this == &other) {
			return *this;
		}
		typename List_const_iterator<_Ty>::pointer p;
		if (this != &other) {
			this->clear();
			for (p = other._begin; p != other._end; ++p)
				this->push_back(*p);
		}
		// Копирование (здесь)
		return *this;
	}

	//list& operator = (list&& other) noexcept {
	//	if (this == &other) {
	//		return *this;
	//	}
	//	// Перемещение (здесь) // Перемещение делать обязательно с использованием std::move()
	//	return *this;
	//}

	// Дальше методы
	void clear() {
		for (iterator p = begin(); p != end(); ++p) {
			delete(p._node);
		}
	}

	
	
	bool empty() const {
		if (begin() == end())
			return true;
		else
			return false;
	};
	
	size_t size() const {
		return _size;
	};
	
	iterator begin() { return iterator(_begin->_next); }
	const_iterator begin() const { return const_iterator(_begin->_next); }
	const_iterator cbegin() const { return const_iterator(_begin->_next); }


	iterator end() { return iterator(_end); }
	const_iterator end() const { return const_iterator(_end); }
	const_iterator cend() const { return const_iterator(_end); }
};
#endif