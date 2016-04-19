#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <assert.h>
using namespace std;
template <class T>
class Stack
{
public:
	Stack()
		:_array(NULL)
		,_size(0)
		,_capacity(0)
	{
	
	}
	Stack(const T& val,size_t s)
	{
		_array=new T[s];
		for(int i=0;i<(int)s;i++)
		{
			_array[i]=val;
		}
		_size=s;
		_capacity=s;

	}	
	//拷贝构造--深浅拷贝问题
	Stack(const Stack &s)
	{
		_size=s._size;
		_capacity=s._capacity;
		_array=new T[_capacity];
		for (int i=0;i<(int)_size;i++)
		{
			_array[i]=s._array[i];
		}
	}
	//赋值运算符的重载--检验_capacity是否足够
	Stack& operator=(const Stack &s)
	{
		if(this!=&s)
		{
			delete []_array;
			_array=new T[s._capacity];
			_size=s._size;
			_capacity=s._capacity;
			for(int i=0;i<(int)s._size;i++)
			{
				_array[i]=s._array[i];
			}

		}
		
		return *this;

	}
	~Stack()
	{
		if(_array!=NULL)
		{
			delete []_array;
			_array=NULL;
			_size=0;
			_capacity=0;
		}
	}
public:
	bool empty()const
	{
		if(_size<=0)
		{
			return true;
		}
		return false;
	}
	size_t size()const
	{
		return _size;
	}
	T& Top()
	{
		return _array[_size-1];
	}
	const T& Top()const
	{
		return _array[_size-1];
	}
	void Push(const T & val)
	{
		IsCapacity();
		_array[_size++]=val;

	}
	void Pop()
	{
		if(_size>0)
		{	
			_size--;
		}

	}
private:
	void IsCapacity()
	{
	     if(_size>=_capacity)
		 {
			 _capacity=_capacity*2+3;
		 }
		 T *tmp=new T[_capacity];
		 for (int i=0;i<_size;i++)
		 {
			 tmp[i]=_array[i];
		 }
		 delete []_array;
		 _array=tmp;
		 
	}
private:
	T * _array;
	size_t _size;
	size_t _capacity;

};
#endif