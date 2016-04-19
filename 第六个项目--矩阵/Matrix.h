#pragma once

//�Գƾ���---ѹ���洢----->��ʡ�ռ�
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
				//��
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
	T *_array;//�Գƾ����ѹ���洢��һά����
	size_t _n;//������
};

void test()
{
	//�βζ�ά��ǿת��һά
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