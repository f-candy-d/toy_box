/**
 * the implementation file for the template class 'ring_buffer'.
 */
#ifndef TOY_BOX_CLASSES_CONTAINER_RING_BUFFER_IMPL_H
#define TOY_BOX_CLASSES_CONTAINER_RING_BUFFER_IMPL_H

#include <iostream>
#include <algorithm>
#include <cassert>
#include "ring_buffer.h"

namespace toy_box {

template <typename T>
ring_buffer<T>::ring_buffer()
:alc_()
,data_(nullptr)
,capacity_(0)
,count_(0)
,front_(0)
{
	init(0);
}

template <typename T>
ring_buffer<T>::ring_buffer(capacity_t request_size)
:alc_()
,data_(nullptr)
,capacity_(0)
,count_(0)
,front_(0)
{
	init(request_size);
}

template <typename T>
ring_buffer<T>::ring_buffer(const ring_buffer& other)
{
	free_memory();
	if(other.data_)
	{
		data_ = alc_.allocate(other.capacity_);
		std::uninitialized_copy(other.pmbegin(), other.pmend(), data_);
	}

	capacity_ = other.capacity_;
	count_ = other.count_;
	front_ = other.front_;
	back_ = other.back_;
}

template <typename T>
ring_buffer<T>::~ring_buffer()
{
	free_memory();
}

template <typename T>
ring_buffer<T>& ring_buffer<T>::operator=(const ring_buffer& other)
{
	free_memory();
	if(other.data_)
	{
		data_ = alc_.allocate(other.capacity_);
		std::uninitialized_copy(other.pmbegin(), other.pmend(), data_);
	}

	capacity_ = other.capacity_;
	count_ = other.count_;
	front_ = other.front_;
	back_ = other.back_;
}

template <typename T>
void ring_buffer<T>::resize(capacity_t request_size)
{
	if(capacity_ < request_size)
	{
		expand(request_size);
	}
	else if(request_size < capacity_)
	{
		shrink(request_size);
	}
}

template <typename T>
void ring_buffer<T>::expand(capacity_t request_size)
{
	auto capacity = confirm_capacity(request_size);
	if(capacity_ < capacity)
	{
		if(data_)
		{
			T* data = alc_.allocate(capacity);
			std::uninitialized_copy_n(begin(), count_, data);
			free_memory();
			data_ = data;
		}
		else
		{
			data_ = alc_.allocate(capacity);
		}

		capacity_ = capacity;
		front_ = 0;
		back_ = (count_ == 0) ? 0 : count_ - 1;
	}
}

template <typename T>
void ring_buffer<T>::shrink(capacity_t request_size)
{
	auto capacity = confirm_capacity(request_size);
	if(capacity == 0)
	{
		clean_up();
	}
	else if(capacity < capacity_)
	{
		count_ = (count_ < capacity) ? count_ : capacity;
		T* data = alc_.allocate(capacity);
		std::uninitialized_copy_n(begin(), count_, data);

		free_memory();
		data_ = data;
		capacity_ = capacity;
		front_ = 0;
		back_ = (count_ == 0) ? 0 : count_ - 1;
	}
}

template <typename T>
typename ring_buffer<T>::capacity_t ring_buffer<T>::capacity() const
{
	return capacity_;
}

template <typename T>
typename ring_buffer<T>::capacity_t ring_buffer<T>::count() const
{
	return count_;
}

template <typename T>
bool ring_buffer<T>::empty() const
{
	return (count_ == 0);
}

template <typename T>
bool ring_buffer<T>::full() const
{
	return (count_ == capacity_);
}

template <typename T>
void ring_buffer<T>::push_back(const T& value)
{
	assert(data_);

	if(count_ == 0)
	{
		data_[0] = value;
		++count_;
		front_ = 0;
		back_ = 0;
	}
	else
	{
		back_ = (back_ + 1) & (capacity_ - 1);
		data_[back_] = value;
		front_ = (back_ == front_) ? (front_ + 1) & (capacity_ - 1) : front_;
		count_ = (count_ < capacity_) ? count_ + 1 : count_;

	}
}

template <typename T>
void ring_buffer<T>::push_back(T&& value)
{
	assert(data_);

	if(count_ == 0)
	{
		data_[0] = std::move(value);
		++count_;
		front_ = 0;
		back_ = 0;
	}
	else
	{
		back_ = (back_ + 1) & (capacity_ - 1);
		data_[back_] = std::move(value);
		front_ = (back_ == front_) ? (front_ + 1) & (capacity_ - 1) : front_;
		count_ = (count_ < capacity_) ? count_ + 1 : count_;
	}
}

template <typename T>
void ring_buffer<T>::push_front(const T& value)
{
	assert(data_);

	if(count_ == 0)
	{
		data_[0] = value;
		++count_;
		front_ = 0;
		back_ = 0;
	}
	else
	{
		front_ = (front_ < 1) ? capacity_ - 1 : front_ - 1;
		data_[front_] = value;
		back_ = (front_ == back_)
				? ((back_ < 1) ? capacity_ - 1 : back_ - 1)
				: back_;
		count_ = (count_ < capacity_) ? count_ + 1 : count_;
	}
}

template <typename T>
void ring_buffer<T>::push_front(T&& value)
{
	assert(data_);

	if(count_ == 0)
	{
		data_[0] = std::move(value);
		++count_;
		front_ = 0;
		back_ = 0;
	}
	else
	{
		front_ = (front_ < 1) ? capacity_ - 1 : front_ - 1;
		data_[front_] = std::move(value);
		back_ = (front_ == back_)
				? ((back_ < 1) ? capacity_ - 1 : back_ - 1)
				: back_;
		count_ = (count_ < capacity_) ? count_ + 1 : count_;
	}
}


template <typename T>
void ring_buffer<T>::pop_back()
{
	if(0 < count_)
	{
		alc_.destroy(&data_[back_]);
		back_ = (back_ < 1) ? capacity_ - 1 : back_ - 1;
		--count_;
	}
}

template <typename T>
void ring_buffer<T>::pop_front()
{
	if(0 < count_)
	{
		alc_.destroy(&data_[front_]);
		front_ = (front_ + 1) & (capacity_ - 1);
		--count_;
	}
}

template <typename T>
void ring_buffer<T>::clear()
{
	for(index_t i = 0; i < count_; ++i)
	{
		alc_.destroy(&(*this)[i]);
	}

	count_ = 0;
}

template <typename T>
void ring_buffer<T>::clean_up()
{
	free_memory();
	count_ = capacity_ = 0;
}

template <typename T>
T& ring_buffer<T>::operator[](index_t index)
{
	// NOTE -> (*this)[0] is always returns a reference to the front element in ring_buffer.
	return data_[(front_ + index) & (capacity_ - 1)];
}

template <typename T>
const T& ring_buffer<T>::operator[](index_t index) const
{
	// NOTE -> (*this)[0] is always returns a reference to the front element in ring_buffer.
	return data_[(front_ + index) & (capacity_ - 1)];
}

template <typename T>
T& ring_buffer<T>::front()
{
	return data_[front_];
}

template <typename T>
const T& ring_buffer<T>::front() const
{
	return data_[front_];
}

template <typename T>
T& ring_buffer<T>::back()
{
	return data_[back_];
}

template <typename T>
const T& ring_buffer<T>::back() const
{
	return data_[back_];
}

template <typename T>
void ring_buffer<T>::free_memory()
{
	if(data_ != nullptr)
	{
		for(index_t i = 0; i < count_; ++i)
		{
			alc_.destroy(&(*this)[i]);
		}

		alc_.deallocate(data_, capacity_);
		data_ = nullptr;
	}
}

template <typename T>
void ring_buffer<T>::init(capacity_t request_size)
{
	auto capacity = confirm_capacity(request_size);

	if(!data_ && capacity != 0)
	{
		data_ = alc_.allocate(capacity);
		capacity_ = capacity;
		count_ = 0;
	}
}

template <typename T>
typename ring_buffer<T>::capacity_t ring_buffer<T>::confirm_capacity(capacity_t request_size)
{
	// the capacity must be 2^n or 0 !
	size_t capacity = 0;
	for(; capacity < request_size;
		capacity = (capacity == 0) ? 1 : capacity * ring_buffer_bits::kCapacityBase);

	return capacity;
}

} /* toy_box */

#endif
