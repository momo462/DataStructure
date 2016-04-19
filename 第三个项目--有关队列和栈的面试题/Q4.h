//4、元素出栈、入栈顺序的合法性。如入栈的序列（1，2，3，4，5）
//5、出栈序列为（4，5，3，2，1）
//当size第一次为4时，出一个元素；当size第二次为4时，清空所有的栈中元素
#ifndef Q4_H
#define Q4_H
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
		if (_size==4)
		{
			Pop();
		}
		
	}
	void Pop()
	{
		if (_size>0)
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
		for (int i=0;i<(int)_size;i++)
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