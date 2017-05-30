/**
 * the implementation file for the template class 'ring_buffer'.
 */
#ifndef TOY_BOX_CLASSES_CONTAINER_RING_BUFFER_IMPL_H
#define TOY_BOX_CLASSES_CONTAINER_RING_BUFFER_IMPL_H

#include "ring_buffer.h"

namespace toy_box {

template <typename T>
ring_buffer<T>::ring_buffer()
{}

template <typename T>
ring_buffer<T>::ring_buffer(capacity_t request_size)
{

}

template <typename T>
ring_buffer<T>::ring_buffer(const ring_buffer& other)
{

}

template <typename T>
ring_buffer<T>::~ring_buffer()
{

}

template <typename T>
ring_buffer<T>& ring_buffer<T>::operator=(const ring_buffer& other)
{

}

template <typename T>
void ring_buffer<T>::resize(capacity_t request_size)
{

}

template <typename T>
void ring_buffer<T>::expand(capacity_t request_size)
{

}

template <typename T>
void ring_buffer<T>::shrink(capacity_t request_size)
{

}

template <typename T>
typename ring_buffer<T>::capacity_t ring_buffer<T>::capacity() const
{

}

template <typename T>
typename ring_buffer<T>::capacity_t ring_buffer<T>::count() const
{

}

template <typename T>
void ring_buffer<T>::push_back(T&& value)
{

}

template <typename T>
void ring_buffer<T>::push_front(const T& value)
{

}

template <typename T>
void ring_buffer<T>::push_front(T&& value)
{

}

template <typename T>
void ring_buffer<T>::pop_back()
{

}

template <typename T>
void ring_buffer<T>::pop_front()
{

}

template <typename T>
void ring_buffer<T>::clear()
{

}

template <typename T>
T& ring_buffer<T>::operator[](index_t index)
{

}

template <typename T>
const T& ring_buffer<T>::operator[](index_t index) const
{

}

template <typename T>
T& ring_buffer<T>::front()
{

}

template <typename T>
const T& ring_buffer<T>::front() const
{

}

template <typename T>
T& ring_buffer<T>::back()
{

}

template <typename T>
const T& ring_buffer<T>::back() const
{

}

template <typename T>
void free_memory()
{

}

template <typename T>
typename ring_buffer<T>::capacity_t ring_buffer<T>::confirm_capacity(capacity_t request_size)
{

}

} /* toy_box */

#endif
