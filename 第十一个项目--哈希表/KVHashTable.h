#pragma once
#include<iostream>
#include <string>
using namespace std;

enum Status
{
	EMPTY,
	EXITS,
	DELETE,
};
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
template<class K,class V>
struct KVNode
{
	K _key;
	V _value;
	KVNode()
	{
	}
	KVNode(const K &key,const V & value)
	{
		_key=key;
		_value=value;
	}
};
//防函数+特化
template<class K>
struct GetFuner
{
	size_t operator()(const K &key)
	{
		return key;
	}
};
template<>
struct GetFuner<string>
{
	size_t operator()(const string &key)
	{
		return BKDRHash(key.c_str());
	}
};

template<class K,class V,class KVHashFun=GetFuner<K>>
class KVHashTable
{
public:
	KVHashTable()
		:_array(NULL)
		,_size(0)
		,_capacity(0)
		,_status(NULL)
	{

	}
	KVHashTable(const size_t &_capacity)
		:_table(new KVNode<K,V>[_capacity])
		,_size(0)
		,_capacity(_capacity)
		,_status(new Status[_capacity])
	{
		for(size_t i=0;i<_capacity;i++)
		{
			_status[i]=EMPTY;
		}
	}
	void Insert(const K & key,const V & value)
	{
		//增容问题
		if (_size*10/_capacity>8)
		{
			_capacity=_capacity*2;
			KVHashTable<K,V> newTable(_capacity);
			for(size_t i=0;i<_capacity;i++)
			{
				if (_status[i]==EXITS)
				{
					newTable.Insert(_table[i]._key,_table[i]._value);
				}
			}
			Swap(newTable);
		}
		size_t index=GetFunc(key);
		size_t i=1;
		while(_status[index]==EXITS)
		{
			index=(index+2*i-1)%_capacity;
			i++;
		}
		_table[index]._key=key;
		_table[index]._value=value;
		_status[index]=EXITS;
		_size++;
	}
	bool Remove(const K &key)
	{
		size_t index=GetFunc(key);
		size_t i=1;
		while(_status[index]==EXITS)
		{
			if(_table[index]._key==key)
			{
				_status[index]=DELETE;
				return true;
			}
			index=(index+2*i-1)%_capacity;
			i++;
		}
		return false;
	}
	KVNode<K,V>* Find(const K &key)
	{
		size_t index=GetFunc(key);
		size_t i=1;
		KVNode<K,V>* cur=NULL;
		while(_status[index]!=EMPTY)
		{
			if(_table[index]._key==key)
			{
				 cur=_table+index;
				
			}
			index=(index+2*i-1)%_capacity;
			i++;
		}
		return cur;

	}
	void Swap(KVHashTable<K,V> & newTable)
	{
		swap(_table,newTable._table);
		swap(_size,newTable._size);
		swap(_capacity,newTable._capacity);
		swap(_status,newTable._status);
	}
	size_t GetFunc(const K &key)
	{
		KVHashFun k;
		return k(key)%_capacity;
	}
	void Print()
	{
		for(size_t i=0;i<_capacity;i++)
		{
			cout<<"key:"<<_table[i]._key<<" ";
			cout<<"val:"<<_table[i]._value<<" ";
			cout<<"status:"<<_status[i]<<" ";
			cout<<endl;
		}
	}
protected:
	KVNode<K,V> *_table;
	size_t _size;
	size_t _capacity;
	Status *_status;
};

void TestKVHashTable()
{
	KVHashTable<int,int> kv1(7);
	kv1.Insert(1,1);
	kv1.Insert(2,2);
	kv1.Insert(3,3);
	kv1.Insert(4,4);
	kv1.Insert(5,5);
    kv1.Insert(6,9);
	kv1.Insert(7,8);
	kv1.Insert(8,8);
	kv1.Insert(18,8);
	kv1.Print();
	kv1.Remove(8);
	kv1.Print();
	KVNode<int,int> *k1=kv1.Find(18);
	cout<<k1->_key<<" "<<k1->_value<<" "<<endl;
}
