#pragma once
#include <string>
#include <iostream>
using namespace std;
//构造哈希函数--直接定址法/数字分析法/平方取中法/折叠法/除留余数法/随机数法
//处理哈希冲突--线性检测/二次检测/伪随机数检测/再哈希法/链地址法/公共溢出区
//增容问题--负荷因子
enum Status
{
	EMPTY,
	EXITS,
	DELETE,
};
//为了处理不同数据--数字/字符串--防函数--特化
static size_t BKDRHash(const char * str)
{
	unsigned int seed = 131; // 31 131 1313 13131 131313
	unsigned int hash = 0;
	while (*str )
	{
		hash = hash * seed + (* str++);
	}
	return (hash & 0x7FFFFFFF);
}
template <class K>
struct GetFuner
{
	size_t operator()(const K& key)
	{
		return key;
	}
};
template <>
struct GetFuner<string>
{
	size_t operator()(const string& key)
	{
		return BKDRHash(key.c_str());
	}
};

template<class K,class GetFun=GetFuner<K>>
class HashTable
{
public:
	HashTable()
		:_table(NULL)
		,_size(0)
		,_capacity(0)
		,_status(NULL)
	{
	
	}
	HashTable(const size_t capacity)
		:_table(new K[capacity])
		,_size(0)
		,_capacity(capacity)
		,_status(new Status[capacity])
	{
	
		for (size_t i=0;i<_capacity;i++)
		{
			_status[i]=EMPTY;
		}
	}
	~HashTable()
	{
		if (_table)
		{
			delete[]_table;
			delete[]_status;
			_size=0;
			_capacity=0;
		
		}
	}
	//造表
	void Insert(const K& key)
	{
		//判断是否需要增容
		if(_size*10/_capacity>=8)
		{
			//增容
			_capacity*=2;
			//建新表
			HashTable newTable(_capacity);
			for(size_t i=0;i<_capacity;i++)
			{
				if (_status[i]==EXITS)
				{
					newTable.Insert(_table[i]);
				}
			}
			Swap(newTable);
		}
		//除留余数
		size_t index=GetFunc(key);
		if(_status[index]==EXITS)
		{
			//发生冲突----线性检测
			while(_status[index]==EXITS)
			{
				index++;
				if (index==_capacity)
				{
					index=0;
				}
			}
			
		}
		_table[index]=key;
		_status[index]=EXITS;
	}
	//查表
	size_t Find(const K &key)
	{
		size_t index=GetFunc(key);
		/*if (_table[index]==key&&_status[index]==EXITS)
		{
			return index;
		}
		else if (_table[index]==key&&_status[index]==DELETE)
		{
			return _capacity+1;
		}
		else if(_table[index]!=key)
		{
			size_t temp=index;
			while (_status[index]==EXITS)
			{
				index++;
				if (_table[index]==key)
				{
					return index;
				}
				if (index==_capacity)
				{
					index=0;
				}
				if (temp==index)
				{
				return _capacity+1;
				}
				}
				}*/
		while(_status[index]==EXITS)
		{
			if (_table[index]==key)
			{
				return index;
			}
			else
			{
				index++;
				//因为_capacity永远大于等于_size*0.8---所以一定会遇到不是exits的状态
				//不会死循环
				if (index==_capacity)
				{
					index=0;
				}
			}
		}
		return _capacity+1;
	
	}
	//删除表中元素
	void Remove(const K& key)
	{
		size_t index=Find(key);
		if (index>=0||index<=_capacity)
		{
			_status[index]=DELETE;
		}
	}
	size_t GetFunc(const K& key)
	{
		GetFun g1;
		return g1(key)%_capacity;
	}
	/*size_t GetFunc2(const size_t prev,const K &key)
	{
		return  (prev+2*key-1)%_capacity;
	}*/
	void Print()
	{
		for(size_t i=0;i<_capacity;i++)
		{
			cout<<"status:"<<_status[i]<<" ";
			cout<<"key:"<<_table[i]<<" ";
			if (i%5==0&&i!=0)
			{
				cout<<endl;
			}
		}
		cout<<endl;
	}
	void Swap(HashTable<K>& newTable)
	{
		swap(_size,newTable._size);
		swap(_capacity,newTable._capacity);
	}
protected:
	K *_table;
	size_t _size;     //关键字个数
	size_t _capacity; //表长
	Status *_status;  //关键字状态

};
void TestHash()
{
	HashTable<int> h1(10);
	h1.Insert(1);
	h1.Insert(11);
	h1.Insert(13);
	h1.Insert(14);
	h1.Insert(17);
	h1.Insert(10);
	h1.Insert(21);
	h1.Print();
	cout<<h1.Find(21)<<endl;
	cout<<h1.Find(22)<<endl;
	

	HashTable<string> h2(10);
	h2.Insert("momo");
	h2.Insert("mumu");
	h2.Insert("manifestation");
	h2.Print();
}

