#ifndef MY_LOCAL_VECTOR_H
#define MY_LOCAL_VECTOR_H

#include <assert.h>

#define PRINT_MY_VECTOR_ELEMENT
#ifdef PRINT_MY_VECTOR_ELEMENT
#include <iostream>
#endif

#define LOCAL_VECTOR_BUFFER_SIZE 16

template <class T>
class MyVector
{
	T buffer_[LOCAL_VECTOR_BUFFER_SIZE];
	T* ptr_;
	size_t size_;
	size_t capacity_;

	void _init()
	{
		ptr_ = buffer_;
		size_ = 0;
		capacity_ = LOCAL_VECTOR_BUFFER_SIZE;
	}
public:
	typedef const T* const_iterator;
	typedef T value_type;
	typedef size_t size_type;
	MyVector()
	{
		_init();
	}

	MyVector(const MyVector<T>& vec)
	{
		_init();
		*this = vec;
	}

	MyVector(const_iterator begin, const_iterator end)
	{
		_init();
		while (begin != end)
			push_back(*begin++);
	}

	MyVector(size_t size, const T& t)
	{
		_init();
		while (size--)
			push_back(t);
	}

	MyVector(const std::initializer_list<value_type>& list)
	{
		_init();
		reserve(list.size());
		for (const auto& value : list)
			push_back(value);
	}

	~MyVector()
	{
		if (ptr_ != buffer_)
			free(ptr_);
	}

public:
	MyVector<T>& operator=(const MyVector<T>& vec)
	{
		clear();
		size_ = vec.size();
		capacity_ = vec.capacity();

		if (vec.buffer_ == vec.ptr_) {
			memcpy(static_cast<void*>(buffer_), vec.buffer_, sizeof(T) * size_);
			ptr_ = buffer_;
		}
		else {
			ptr_ = (T*)malloc(vec.capacity() * sizeof(T));
			assert(ptr_);
			memcpy(static_cast<void*>(ptr_), vec.ptr_, vec.size() * sizeof(T));
		}

		return *this;
	}

public:
	T& operator[](size_t i)
	{
		return ptr_[i];
	}
	const T& operator[](size_t i) const
	{
		return ptr_[i];
	}

	void push_back(const T& t)
	{
		if (size_ == capacity_) {
			assert(capacity_);
			reserve(capacity_ * 2);
		}

		ptr_[size_++] = t;
	}

	void reserve(size_t size)
	{
		if (size <= capacity_)
			return;

		T* next = (T*)malloc(sizeof(T) * size);
		assert(next);

		T* old = ptr_;
		ptr_ = next;

		memcpy(static_cast<void*>(ptr_), old, sizeof(T) * capacity_);
		capacity_ = size;

		if (old != buffer_)
			free(old);
	}

	bool empty() const
	{
		return 0 == size();
	}

	size_t size() const
	{
		return size_;
	}

	size_t capacity() const
	{
		return capacity_;
	}

	const_iterator begin() const
	{
		return ptr_;
	}

	const_iterator end() const
	{
		return ptr_ + size_;
	}

	void clear()
	{
		if (ptr_ != buffer_) {
			free(ptr_);
		}

		_init();
	}
};

#ifdef PRINT_MY_VECTOR_ELEMENT
template <class T>
std::ostream& operator<<(std::ostream& os, const MyVector<T>& vec)
{
	if (vec.empty())
		return os << "[]";

	os << "[\"" << vec[0];
	for (size_t i = 1; i < vec.size(); i++) {
		os << "\", \"" << vec[i];
	}

	os << "\"]";
	return os;
}
#endif // !PRINT_MY_VECTOR_ELEMENT

#endif // !MY_LOCAL_VECTOR_H