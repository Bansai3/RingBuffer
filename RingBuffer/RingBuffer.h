#pragma once
template<class T>
class RingBuffer
{
	T* data;
	T* current;
	int start_iterator;
	int end_iterator;
	int capacity;
	int size;
public:
	RingBuffer(int size);
	void add_back(T new_elem);
	void add_front(T new_elem);
	void remove_front();
	void remove_back();
	void resize();
};

