//1、一个数组实现两个栈
#ifndef	Q5_H
#define Q5_H
#include <iostream>
using namespace std;
template <class T>
class TwoStack
{
private:
	int _size1;
	int _size2;
	int _size;
	T*_array;
public:
	TwoStack(int size)
	{
		_size=size;
		_array=new T[_size];
		_size1=0;
		_size2=0;
		
	}
	void push(int i,const T & val)
	{	
		//_bottom1中插入
		if (i==1)
		{
			if (!check(_size1+1,_size2))
			{
				return;
			}
			_array[_size1++]=val;
		}
		else
		{
			if (!check(_size1,_size2+1))
			{
				return;
			}
			_array[_size-(++_size2)]=val;
		}
	}
	~TwoStack()
	{
		delete []_array;
	}
private:
	bool check(int size1,int size2)
	{
		if (size1+size2<=(int)_size)
		{
			return true;
		}
		return false;
	}
};
#endif