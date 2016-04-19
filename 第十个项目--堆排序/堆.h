pragma once
#include <iostream>
#include <vector>
using namespace std;


template <class T>
class Heap
{
public:
	Heap(T *a,size_t size)
	{
		for (size_t i=0;i<size;i++)
		{
			_array.push_back(a[i]);
		}
		for (size_t i=(size-2)/2;i>0;i--)
		{
			AdjustDown(i);
		}
	}
private:
	void AdjustDown(int root)
	{
		int child=root*2+1;
		while(child<_array.size())
		{
			if (child+1<_array.size()&&_array[child]>_array[child+1])
			{
				child++;
			}
			if (_array[child]<_array[root])
			{
				swap(_array[child],_array[root];
			}
		}
	}
	void AdjustUp()
private:
	vector<T> _array;
};

void test()
{
	int a[10]={10,16,18,12,11,13,15,17,14,19};
	Heap<int> h1(a,10);

}

