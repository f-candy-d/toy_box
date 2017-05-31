#ifndef TOY_BOX_CLASSES_CONTAINER_RING_BUFFER_ITERATORS_H
#define TOY_BOX_CLASSES_CONTAINER_RING_BUFFER_ITERATORS_H

#include <iterator>
#include <cassert>
#include "constants.h"

namespace toy_box {

// forward declaration
template <typename T> class ring_buffer;

namespace ring_buffer_bits {

template <typename T> struct const_iterator : public std::iterator<
	std::forward_iterator_tag, T, std::ptrdiff_t, const T*, const T&>
{
	const_iterator(const ring_buffer<T>* p) :parent(p),index(0) { assert(p); }
	const_iterator(const ring_buffer<T>* p, index_t i) :parent(p),index(i) { assert(p); }
	const T& operator*() const { return (*parent)[index]; }
	const T* operator->() const { return &**this; }
	bool operator==(const const_iterator& other) const { return (index == other.index); }
	bool operator!=(const const_iterator& other) const { return !(*this == other); }
	const_iterator& operator++() { ++index; return *this; }
	const_iterator& operator++(int) { auto old = *this; ++*this; return std::move(old); }

private:
	const ring_buffer<T>* parent;
	// index from the front element of the buffer
	index_t index;
};

template <typename T> struct iterator : public const_iterator<T>
{
	iterator(const ring_buffer<T>* p) :const_iterator<T>(p) {}
	iterator(const ring_buffer<T>* p, index_t i) :const_iterator<T>(p, i) {}
	T& operator*() { return const_cast<T&>(const_iterator<T>::operator*()); }
	T* operator->() { return &**this; }
	iterator& operator++() { const_iterator<T>::operator++(); return *this; }
	iterator& operator++(int) { auto old = *this; ++*this; return std::move(old); }
};

template <typename T> struct const_physical_memory_iterator : public std::iterator<
	std::forward_iterator_tag, T, std::ptrdiff_t, const T*, const T&>
{
	const T* value;

	const_physical_memory_iterator() :value(nullptr) {}
	const_physical_memory_iterator(T* p) :value(p) {}
	const T& operator*() const { return *value; }
	const T* operator->() const { return &**this; }
	bool operator==(const const_physical_memory_iterator& other) const { return (value == other.value); }
	bool operator!=(const const_physical_memory_iterator& other) const { return !(*this == other); }
	const_physical_memory_iterator& operator++() { ++value; return *this; }
	const_physical_memory_iterator& operator++(int) { auto old = *this; ++*this; return old; }
};

template <typename T> struct physical_memory_iterator : public const_physical_memory_iterator<T>
{
	physical_memory_iterator() :const_physical_memory_iterator<T>() {}
	physical_memory_iterator(T* p) :const_physical_memory_iterator<T>(p) {}
	T& operator*() { return const_cast<T&>(const_physical_memory_iterator<T>::operator*()); }
	T* operator->() { return &**this; }
	physical_memory_iterator& operator++() { const_physical_memory_iterator<T>::operator++(); return *this; }
	physical_memory_iterator& operator++(int) { auto old = *this; ++*this; return std::move(old); }
};

} /* ring_buffer_bits */
} /* toy_box */

#endif
