#pragma once

//对称矩阵---压缩存储----->节省空间
template<class T>
class SymmetricMatrix
{
public:
	SymmetricMatrix(T* a,size_t n)
		:_array(new T[n*(n+1)/2])
		,_n(n)
	{
		int index=0;
		for (int i=0;i<n;i++)
		{
			for (int j=0;j<n;j++)
			{
				if (i>=j)
				{
					_array[index++]=a[i*n+j];
				}
				else
				{
					break;
				}
			}
		}
	}
	~SymmetricMatrix()
	{
		if (_array)
		{
			delete []_array;
		}
	}
	void Display()
	{
		for (int i=0;i<_n;i++)
		{
			for (int j=0;j<_n;j++)
			{
				//上
				if (i<j)
				{
					cout<<_array[i*(i+1)/2+j];
				}
				else
				{
					cout<<_array[j*(j+1)/2+i];
				}

				
			}
		}
	}
	
	T& AccessNum(size_t i,size_t j)
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
	T *_array;//对称矩阵的压缩存储的一维数据
	size_t _n;//行列数
};

void test()
{
	//形参二维，强转成一维
	int a[5][5]=
	{
		{0,1,2,3,4},
		{1,0,1,2,3},
		{2,1,0,1,2},
		{3,2,1,0,1},
		{4,3,2,1,0},
	};
	SymmetricMatrix <int>s1((int*)a,5);

}