#pragma once
#include <iostream>
using namespace std;
template <class T>
class SymetricMatrix
{
public:
	SymetricMatrix(T *a,size_t n)
		:_array(new T[n*(n+1)/2])
		,_size(n)
	{
		size_t index=0;
		for (int i=0;i<_size;i++)
		{
			for(int j=0;j<=i;j++)
			{
				_array[index++]=a[i*_size+j];
			}
		}
	}
	~SymetricMatrix()
	{
		if (_array)
		{
			delete []_array;
		}
	}
	void Display()
	{
		for (int i=0;i<_size;i++)
		{
			for (int j=0;j<_size;j++)
			{
				//����
				if (i<=j)
				{
					cout<<_array[j*(j+1)/2+i]<<" ";
				}
				//����
				else
				{
					cout<<_array[i*(i+1)/2+j]<<" ";
				}
			}
			cout<<endl;
		}
		cout<<endl;
	}
	T& ReturnPosNumber(const size_t i,const size_t j)const
	{
		assert(i<_n);
		assert(j<_n);
		if (i<j)
		{
			swap(i,j);
		}
		return _array[i*(i+1)/2+j];
	}
private:
	T *_array;              //�����洢ѹ��������������е�Ԫ��
	size_t _size;           //������¼�Գƾ����������
};

void testM1()
{
	int a[5][5]=
	{
		{0,1,2,3,4},
		{1,0,1,2,3},
		{2,1,0,1,2},
		{3,2,1,0,1},
		{4,3,2,1,0}
	};
	SymetricMatrix <int>s1((int *)a,5);
	s1.Display();
}