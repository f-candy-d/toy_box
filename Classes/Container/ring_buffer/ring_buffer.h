#ifndef TOY_BOX_CLASSES_CONTAINER_RING_BUFFER_RING_BUFFER_H
#define TOY_BOX_CLASSES_CONTAINER_RING_BUFFER_RING_BUFFER_H

#include <cstdlib>
#include <memory>
#include "constants.h"
#include "iterators.h"

namespace toy_box {

template <typename T> class ring_buffer
{
	using index_t = ring_buffer_bits::index_t;
	using capacity_t = ring_buffer_bits::capacity_t;
	using iterator = ring_buffer_bits::iterator<T>;
	using const_iterator = ring_buffer_bits::const_iterator<T>;
	using physical_memory_iterator = ring_buffer_bits::physical_memory_iterator<T>;
	using const_physical_memory_iterator = ring_buffer_bits::const_physical_memory_iterator<T>;

public:
	ring_buffer();
	ring_buffer(capacity_t request_size);
	ring_buffer(const ring_buffer& other);
	~ring_buffer();
	ring_buffer& operator=(const ring_buffer& other);
	// capacity
	void resize(capacity_t request_size);
	void expand(capacity_t request_size);
	void shrink(capacity_t request_size);
	capacity_t capacity() const;
	capacity_t count() const;
	bool empty() const;
	bool full() const;
	// modifiers
	void push_back(const T& value);
	void push_back(T&& value);
	void push_front(const T& value);
	void push_front(T&& value);
	void pop_back();
	void pop_front();
	void clear();
	void clean_up();
	// element access
	T& operator[](index_t index);
	const T& operator[](index_t index) const;
	T& front();
	const T& front() const;
	T& back();
	const T& back() const;
	// iterators
	iterator begin() { return (count_ == 0) ? end() : iterator(this, 0); }
	const_iterator begin() const { return (count_ == 0) ? end() : const_iterator(this, 0); }
	const_iterator cbegin() const { return (count_ == 0) ? cend() : const_iterator(this, 0); }
	iterator end() { return iterator(this, count_); }
	const_iterator end() const { return const_iterator(this, count_); }
	const_iterator cend() const { return const_iterator(this, count_); }
	physical_memory_iterator pmbegin() { return physical_memory_iterator(data_); }
	const_physical_memory_iterator pmbegin() const { return const_physical_memory_iterator(data_); }
	const_physical_memory_iterator cpmbegin() const { return const_physical_memory_iterator(data_); }
	physical_memory_iterator pmend() { return physical_memory_iterator(data_ + capacity_); }
	const_physical_memory_iterator pmend() const { return physical_memory_iterator(data_ + capacity_); }
	const_physical_memory_iterator cpmend() const { return physical_memory_iterator(data_ + capacity_); }

private:
	std::allocator<T> alc_;
	T* data_;
	capacity_t capacity_;
	capacity_t count_;
	index_t front_;
	index_t back_;

	void free_memory();
	void init(capacity_t request_size);
	capacity_t confirm_capacity(capacity_t request_size);
};

} /* toy_box */

// include the implementation file
#include "impl.h"

#endif
