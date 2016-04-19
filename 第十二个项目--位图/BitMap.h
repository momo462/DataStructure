#pragma once
#include <iostream>
#include <vector>
using namespace std;

class BitMap
{
public:
	BitMap()
		:_size(0)
	{
	
	}
	BitMap(size_t  size)
		:_size(0)
	{
		_array.resize(size/32+1);
	}
	bool Set(size_t num)
	{
		size_t index=num>>5;
		size_t n=num%32;
		if ((_array[index]&(1<<n)))
		{
			return false;
		}
		_array[index]|=(1<<n);
		++_size;
		return true;
	}
	bool Reset(size_t num)
	{
		size_t index=num>>5;
		size_t n=num%32;
		if (!(_array[index]&(1<<n)))
		{
			return false;
		}
		_array[index]&=(~(1<<n));
		--_size;
		return true;
	}
	bool Test(size_t num)
	{
		size_t index=num>>5;
		size_t n=num%32;
		return (_array[index]&(1<<n));
	}
protected:
	size_t _size;
	vector<size_t> _array;
};

void Test()
{
	BitMap b1(33);
	b1.Set(1);
	b1.Set(4);
	b1.Set(32);
	b1.Reset(32);
	b1.Reset(4);
	b1.Reset(4);
	cout<<b1.Test(4);
	cout<<b1.Test(32);
	cout<<b1.Test(1);

}
void Test1()
{
	//40ÒÚÊı
	BitMap b2(-1);
	b2.Set(42354623);

}