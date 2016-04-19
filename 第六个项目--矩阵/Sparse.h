#pragma once
#include <iostream>
#include <vector>
using namespace std;
//��Ԫ��
template <class T>
struct Trituple
{
	int _row;
	int _col;
	T _value;
};
template<class T>
class SparseMatrix
{
public:
	SparseMatrix(T *a,size_t m,size_t n,const T& invalid)
		:_rowSize(m)
		,_colSize(n)
		,_invalid(invalid)
	{
		//�����ȴ洢??????????????????WHY
		for (size_t i=0;i<m;++i)
		{
			for (size_t j=0;j<n;++j)
			{
				if (a[i*n+j]!=_invalid)
				{
					Trituple<T> t;
					t._row=i;
					t._col=j;
					t._value=a[i*n+j];
					_array.push_back(t);
				}
				else
				{
					break;
				}
			}
		}
	}

	void Display()
	{
		size_t index=0;
		for(size_t i=0;i<_rowSize;i++)
		{
			for(size_t j=0;j<_colSize;j++)
			{
				if (index<_array.size()&&_array[index]._row==i&&_array[index]._col==j)
				{
					cout<<_array[index++]._value<<" ";
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

	SparseMatrix<T> Transpose()
	{
		SparseMatrix<T> s;
		s._rowSize=_colSize;
		s._colSize=_rowSize;
		s._invalid=_invalid;
		//O(��Ч���ݵĸ���)--->
		for (int i=0;i<_colSize;i++)
		{
			size_t index=0;
			while (index<_array.size())
			{
				if (_array[index]._col==i)
				{
					Trituple<T> t;
					t._row=_array[index]._col;
					t._col=_array[index]._row;
					s._array.push_back(t);
				}
				index++;

			}
		}
	}
	//O(��Ч���ݵĸ���*2+colsize)---��O(��Ч���ݵĸ���+colsize)---ʱ�临�Ӷ�
	//O(colsize)---�ռ�
	//ת�ú�ľ���ĵ�x�еĵ�һ��Ԫ�ص���ǰһ�е�λ�üӸ��е�Ԫ�ظ���---����������
	SparseMatrix<T> FastTranspose()
	{
		SparseMatrix<T> s;
		s._rowSize=_colSize;
		s._colSize=_rowSize;
		s._invalid=_invalid;
		int *rowCounts=new int[_colSize];
		int *rowStart=new int[_colSize];
		memset(rowCounts,0,sizeof(int *)_colSize);
		memset(rowStart,0,sizeof(int *)_colSize);
		//ͳ��
		size_t index=0;
		while(index<_array.size())
		{
			//ÿ����Ԫ�������Ϊ������±�
			rowCounts[_array[index]._col]++;
		}
		rowStart[0]=0;
		for (int i=1;i<_colSize)
		{
			rowStart[i]=rowStart[i]+rowCounts[i-1];
		}
		//����rowstart��λת�ú�ѹ���洢��λ��
		index=0;
		sm._array.Resize(_array.size());
		while (index<_array.size())
		{
			size_t begin=rowCounts[_array[index]._col];
			Trituple<T> t;
			t._col=_array[index]._row;
			t._row=_array[index]._col;
			t._value=_array[index]._value;
			
			sm._array[begin]=t;
			++rowStart[_array[index]._col];
			++index;
		}
		return s;
	}
	//����ļӷ�&�˷�----�Ѳ���������
private:
	//Trituple<T> *_array;//ѹ���洢---->��֪��Ҫ�����
	vector<Trituple<T>> _array;
	size_t _size;//��Ч���ݵĸ���
	size_t _rowSize;
	size_t _colSize;
	T _invalid;
};

void test2()
{
	int b[6][5]=
	{
		{1,0,3,0,5},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{1,0,3,0,5},
		{0,0,0,0,0},
		{0,0,0,0,0},
	};
	SparseMatrix<int> s1((int *)b,6,5,0);
	s1.Display();
}