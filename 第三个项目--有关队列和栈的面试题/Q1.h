//1��ʵ��һ��ջ��Ҫ��ʵ��Push(��ջ)��Pop(��ջ)��Min(������Сֵ�Ĳ���)
//   ʱ�临�Ӷ�ΪO(1)
//����1������ջ
//����2��ÿ����ջ���߳�ջΪ����Ԫ��
#ifndef Q1_H
#define Q1_H
#include <iostream>
using namespace std;
template<class T>
class Stack
{
private:
	T *_array;
	size_t _size;
	size_t _capacity;
private:
	void IsCapacity()
	{
		if(_size+2>=_capacity)
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
	//��������--��ǳ��������
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
	//��ֵ�����������--����_capacity�Ƿ��㹻
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
	void Push(const T & val)
	{
		IsCapacity();
		_array[_size++]=val;
		_array[_size++]=Min();
		


	}
	void Pop()
	{
		if(_size>0)
		{	
			_size=_size-2;
		}

	}
	T Min()
	{
		if (_size==1)
		{
			return _array[_size-1];
		}
		else
		{
			return _array[_size-1]<_array[_size-2]? _array[_size-1]:_array[_size-2];
		}
	
	}

};
#endif