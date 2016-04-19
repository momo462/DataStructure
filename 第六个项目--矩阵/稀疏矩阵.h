#pragma once
#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

template <class T>
struct trituple
{
	int _row;
	int _col;
	T _value;
};
template <class T>
class SparseMatrix
{
private:
	vector<trituple<T>> _array;
	int rowsize;
	int colsize;
	int _invalid;  
public:
	SparseMatrix(T *a,int row,int col,int invalid)
		:rowsize(row)
		,colsize(col)
		,_invalid(invalid)
	{
		assert(a);
		//行优先存储？？？？？？？？？？？？？？？？？？？
		for (int i=0;i<row;i++)
		{
			for (int j=0;j<col;j++)
			{
				if (a[i*col+j]!=_invalid)
				{
					trituple<T> t1;
					t1._col=j;
					t1._row=i;
					t1._value=a[i*col+j];
					_array.push_back(t1);
				}
				
			}
		}
	}
	SparseMatrix()
		:_array(NULL)
		,rowsize(0)
		,colsize(0)
		,_invalid(0)
	{

	}
	~SparseMatrix()
	{
	}
	void Display()
	{
			int index=0;
			for (int i=0;i<rowsize;i++)
			{
				for (int j=0;j<colsize;j++)
				{
					//index越界----所以要加index<_array.size()这个条件
					if (index<_array.size()
						&&i==_array[index]._row&&j==_array[index]._col)
					{
						cout<<_array[index]._value<<" ";
						index++;
					}
					else
					{
						cout<<_invalid<<" ";
					}	
				}
				cout<<endl;
			}
			cout<<endl;
	}
	//转置
	void Transpose()
	{
		SparseMatrix<T> s1;
		int index=0;
		for(int i=0;i<colsize;i++)
		{
			index=0;
			while (_array.size()>index)
			{
				if(_array[index]._col==i)
				{
					trituple<T> t1;
					t1._col=_array[index]._row;
					t1._row=_array[index]._col;
					t1._value=_array[index]._value;
					s1._array.push_back(t1);
				}
				index++;
			}
			
		}
		s1.colsize=rowsize;
		s1.rowsize=colsize;
		s1._invalid=_invalid;
		s1.Display();
	}
	void FastTranspose1()
	{
		SparseMatrix<T> s1;
		s1.rowsize=colsize;
		s1.colsize=rowsize;
		s1._invalid=_invalid;
		s1._array.resize(_array.size());
		int *RowCount=new int[colsize];
		int *RowStart=new int[colsize];
		memset(RowCount,0,sizeof(int)*colsize);
		memset(RowStart,0,sizeof(int)*colsize);
		for (int i=0;i<colsize;i++)
		{
			int index=0;
			while (_array.size()>index)
			{
				if(_array[index]._col==i)
				{
					RowCount[i]++;
				}
				index++;
			}
		}
		RowStart[0]=0;
		for (int i=1;i<colsize;i++)
		{
			RowStart[i]=RowStart[i-1]+RowCount[i-1];
		}
		int index=0;
		while(_array.size()>index)
		{
			trituple<T> t1;
			t1._col=_array[index]._row;
			t1._row=_array[index]._col;
			t1._value=_array[index]._value;
			s1._array[RowStart[t1._row]++]=t1;
			index++;
			
		}
		s1.Display();
	}
};
void testS1()
{
	int a[6][5]=
	{
		{1,0,3,0,5},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{2,0,4,0,6},
		{0,0,0,0,0},
		{0,0,0,0,0}
	};
	SparseMatrix<int> s1((int*)a,6,5,0);
	s1.Display();
	s1.Transpose();
	s1.FastTranspose1();
}
