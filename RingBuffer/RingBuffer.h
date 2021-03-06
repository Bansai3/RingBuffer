#pragma once
#include <cmath>
#include <iostream>
#include <string>

template<class T2>
class iterator
{
private:
	T2* current;
public:
	iterator()
	{
		current = nullptr;
	}
	T2& operator*();
	void operator++();
	void operator--();
	bool operator==(const iterator& it);
	bool operator!=(const iterator& it);
	void operator=(T2* object);
	iterator<T2> operator+(int offset);
	iterator<T2> operator-(int offset);
	void operator+=(int offset);
	void operator-=(int offset);
	int operator-(const iterator<T2>& it);
	~iterator()
	{
		delete[] current;
	}
};



template<class T>
class RingBuffer
{
	struct BufferElement
	{
		T data;
		std::string state;
	};
	BufferElement* buffer;
	int start_iterator;
	int end_iterator;
	int capacity;
	int size;
public:
	RingBuffer(int size = 10);
	void add_back(T new_elem);
	void add_front(T new_elem);
	void remove_front();
	void remove_back();
	void resize(int new_capacity);
	T access_to_start();
	T acces_to_end();
	bool is_empty();
	T operator[](int index);

};



template<class T>
RingBuffer<T>::RingBuffer(int size)
{
	capacity = size;
	this->size = 0;
	buffer = new BufferElement[capacity];
	start_iterator = 0;
	end_iterator = 0;
	for (int i = 0; i < capacity; ++i)
	{
		buffer[i].state = "empty";
	}
}

template<class T>
void RingBuffer<T>::add_back(T new_elem)
{
	if (start_iterator == end_iterator && buffer[end_iterator].state == "empty")
	{
		buffer[end_iterator].data = new_elem;
		buffer[end_iterator].state = "full";
		size++;
	}
	else if (buffer[end_iterator].state == "empty")
	{
		buffer[end_iterator].data = new_elem;
		buffer[end_iterator].state = "full";
		size++;
	}
	else
	{
		if (end_iterator == capacity - 1)
		{
			end_iterator = 0;
			if (buffer[end_iterator].state == "empty")
				size++;
			if (end_iterator == start_iterator)
				start_iterator++;
			buffer[end_iterator].data = new_elem;
			buffer[end_iterator].state = "full";
		}
		else
		{
			if (buffer[end_iterator + 1].state == "empty")
				size++;
			if (end_iterator + 1 == start_iterator)
			{
				if (start_iterator == capacity - 1)
					start_iterator = 0;
				else
					start_iterator++;
			}
			buffer[++end_iterator].data = new_elem;
			buffer[end_iterator].state = "full";
		}
	}
}

template<class T>
void RingBuffer<T>::add_front(T new_elem)
{
	if (start_iterator == end_iterator && buffer[start_iterator].state == "empty")
	{
		buffer[start_iterator].data = new_elem;
		buffer[start_iterator].state = "full";
		size++;
	}
	else
	{
		if (buffer[start_iterator].state == "empty")
			size++;
		buffer[start_iterator].data = new_elem;
		buffer[start_iterator].state = "full";
		end_iterator = start_iterator;
		do
		{
			if (start_iterator == capacity - 1)
			{
				start_iterator = 0;
			}
			else
				start_iterator++;
		} while (buffer[start_iterator].state != "empty");
	}
}

template<class T>
void RingBuffer<T>::remove_front()
{
	if (buffer[start_iterator].state != "empty")
	{
		size--;
		buffer[start_iterator].state = "empty";
		if (start_iterator == capacity - 1)
		{
			start_iterator = 0;
		}
		else
			start_iterator++;
	}
	else
	{
		throw "?????? ????? ???????? ??????????!";
	}
}

template<class T>
void RingBuffer<T>::remove_back()
{
	if (buffer[end_iterator].state != "empty")
	{
		size--;
		buffer[end_iterator].state = "empty";
		if (end_iterator == 0)
		{
			end_iterator = capacity - 1;
		}
		else
		{
			end_iterator--;
		}
		if (size != 0)
		{
			while (buffer[end_iterator].state == "empty");
			{
				if (end_iterator == 0)
				{
					end_iterator = capacity - 1;
				}
				else
				{
					end_iterator--;
				}
			}

		}
	}
	else
	{
		throw "?????? ????? ???????? ?? ????????!";
	}
}

template<class T>
void RingBuffer<T>::resize(int new_capacity)
{
	if (new_capacity > capacity)
	{
		BufferElement* point = buffer;
		buffer = new BufferElement[new_capacity];
		int count = 0;
		while (start_iterator != end_iterator)
		{
			if (point[start_iterator].state == "empty")
			{
				if (start_iterator == capacity - 1)
					start_iterator = 0;
				else
					start_iterator++;
			}
			else
			{
				buffer[count].data = point[start_iterator].data;
				buffer[count].state = "full";
				count++;
			}
		}
		if (point[end_iterator].state != "empty")
		{
			buffer[count].data = point[end_iterator].data;
			buffer[count].state = "full";
		}
		start_iterator = 0;
		end_iterator = size - 1;
		delete[] point;
	}
	else if (new_capacity < capacity)
	{
		if (new_capacity < size)
		{
			BufferElement* point = buffer;
			buffer = new BufferElement[new_capacity];
			int count = 0;
			while (count != new_capacity)
			{
				if (point[start_iterator].state == "empty")
				{
					if (start_iterator == capacity - 1)
					{
						start_iterator = 0;
					}
					else
					{
						start_iterator++;
					}
					continue;
				}
				buffer[count] = point[start_iterator];
				if (start_iterator == capacity - 1)
				{
					start_iterator = 0;
				}
				else
				{
					start_iterator++;
				}
				count++;
			}
			start_iterator = 0;
			end_iterator = new_capacity - 1;
			capacity = new_capacity;
			size = new_capacity;
			delete[] point;
		}
		else
		{
			BufferElement* point = buffer;
			buffer = new BufferElement[new_capacity];
			int count = 0;
			while (start_iterator != end_iterator)
			{
				if (point[start_iterator].state == "empty")
				{
					if (start_iterator == capacity - 1)
					{
						start_iterator = 0;
					}
					else
					{
						start_iterator++;
					}
					continue;
				}
				buffer[count] = point[start_iterator];
				if (start_iterator == capacity - 1)
				{
					start_iterator = 0;
				}
				else
				{
					start_iterator++;
				}
				count++;
			}

			buffer[count] = point[start_iterator];

			start_iterator = 0;
			end_iterator = count - 1;
			capacity = new_capacity;
			delete[] point;
		}
	}
}

template<class T>
inline T RingBuffer<T>::access_to_start()
{
	return buffer[start_iterator].data;
}

template<class T>
inline T RingBuffer<T>::acces_to_end()
{
	return buffer[end_iterator].data;
}

template<class T>
inline bool RingBuffer<T>::is_empty()
{
	if (size > 0)
		return false;
	else return true;
}

template<class T>
inline T RingBuffer<T>::operator[](int index)
{
	setlocale(LC_ALL, "Russian");
	if (index >= 0 && index < capacity)
	{
		if (buffer[index].state == "empty")
		{
			T data;
			std::cout << std::endl;
			std::cout << "?????? ?????! " << std::endl;
			return data;
		}
		else
			return buffer[index].data;
	}
	else
	{
		throw "????? ?? ??????? ???????!";
	}
}


template<class T2>
inline T2& iterator<T2>::operator*()
{
	return *(this->current);
}

template<class T2>
inline void iterator<T2>::operator++()
{
	++current;
}

template<class T2>
inline void iterator<T2>::operator--()
{
	--current;
}

template<class T2>
inline bool iterator<T2>::operator==(const iterator& it)
{
	if (it == current)
		return true;
	else
		return false;
}

template<class T2>
inline bool iterator<T2>::operator!=(const iterator& it)
{
	if (it == current)
		return false;
	else
		return true;
}

template<class T2>
inline void iterator<T2>::operator=(T2* object)
{
	current = object;
}

template<class T2>
inline iterator<T2> iterator<T2>::operator+(int offset)
{
	iterator<T2> it;
	it.current = this->current + offset;
	return it;
}

template<class T2>
inline iterator<T2> iterator<T2>::operator-(int offset)
{
	iterator<T2> it;
	it.current = this->current - offset;
	return it;
}

template<class T2>
inline void iterator<T2>::operator+=(int offset)
{
	current += offset;
}

template<class T2>
inline void iterator<T2>::operator-=(int offset)
{
	current -= offset;
}

template<class T2>
inline int iterator<T2>::operator-(const iterator<T2>& it)
{
	return abs(int(current - it.current));
}
