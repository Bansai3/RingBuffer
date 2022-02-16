#include "RingBuffer.h"

template<class T>
RingBuffer<T>::RingBuffer(int size)
{
	capacity = 0;
	this->size = size;
	data = new T[size];
}

template<class T>
void RingBuffer<T>::add_back(T new_elem)
{
	
}

template<class T>
void RingBuffer<T>::add_front(T new_elem)
{
	int count = 0;
	T* pointer = data;
	resize();
	data = new T[size + 1];
	for (auto i : data + 1)
	{
		i = pointer[count];
		count++;
	}
	data[0] = new_elem;
	size++;
	delete[pointer];
}

template<class T>
void RingBuffer<T>::remove_front()
{
	int count = 0;
	T* pointer = data;
	resize();
	data = new T[size - 1];
	for (auto i : data)
	{
		i = pointer[count + 1];
		count++;
	}
	size--;
	delete[] pointer;
}

template<class T>
void RingBuffer<T>::remove_back()
{
	int count = 0;
	T* pointer = data;
	resize();
	data = new T[size - 1];
	for (auto i : data)
	{
		i = pointer[count + 1];
		count++;
	}
	size--;
	delete[] pointer;
}

template<class T>
void RingBuffer<T>::resize()
{
	if (size + 1 >= capacity)
		capacity *= 2;
	if (size <= capacity / 2)
		capacity /= 2;
}
