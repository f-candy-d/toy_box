#ifndef TOY_BOX_CLASSES_CONTAINER_RING_BUFFER_RING_BUFFER_H
#define TOY_BOX_CLASSES_CONTAINER_RING_BUFFER_RING_BUFFER_H

#include <cstdlib>
#include <memory>

namespace toy_box {

template <typename T> class ring_buffer
{
	using index_t = size_t;
	using capacity_t = size_t;

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
	// modifiers
	void push_back(const T& value);
	void push_back(T&& value);
	void push_front(const T& value);
	void push_front(T&& value);
	void pop_back();
	void pop_front();
	void clear();
	// element access
	T& operator[](index_t index);
	const T& operator[](index_t index) const;
	T& front();
	const T& front() const;
	T& back();
	const T& back() const;

private:
	std::allocator<T> alc_;
	T* data_;
	capacity_t capacity_;
	capacity_t count_;
	index_t front_;
	index_t back_;

	void free_memory();
	capacity_t confirm_capacity(capacity_t request_size);
};

} /* toy_box */

#endif
