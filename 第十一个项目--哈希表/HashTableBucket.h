#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;
template <class K,class V>
struct KVNode
{
	K _key;
	V _value;
	KVNode *_next;
	KVNode()
	{}
	KVNode(const K &key,const V &val)
	{
		_key=key;
		_value=val;
		_next=NULL;
	}
	KVNode(const KVNode<K,V>* &k)
	{
		_key=k->_key;
		_value=k->_value;
		_next=NULL;
	}
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
template<class K>
struct HashFuner
{
	size_t operator()(const K &key)
	{
		return key;
	}
};
template<>
struct HashFuner<string>
{
	size_t operator()(const string &key)
	{
		return BKDRHash(key.c_str());
	}
};
template <class K,class V,class HashFun=HashFuner<K>>
class HashTableBucket
{
public:
	HashTableBucket()
		:_size(0)
	{}
	HashTableBucket(size_t size)
		:_size(0)
	{
		_table.resize(size);
	}
	~HashTableBucket()
	{
		for(size_t i=0;i<_table.size();i++)
		{
			KVNode<K,V> *head=_table[i];
			if(head==NULL)
			{
				continue;
			}
			KVNode<K,V> *cur=head;
			while(cur)
			{
				KVNode<K,V> *del=cur;
				cur=cur->_next;
				delete del;
			}
		}
	}
	HashTableBucket(const HashTableBucket<K,V> &h1)
	{ 
		if(h1._size==0)
		{
			return;
		}
		size_t size=h1._table.size();
		_table.resize(size);
		_size=h1._size;
		for(size_t i=0;i<size;i++)
		{
			if (h1._table[i]!=NULL)
			{
				_table[i]=new KVNode<K,V>(h1._table[i]->_key,h1._table[i]->_value);
				KVNode<K,V> *head=_table[i];
				KVNode<K,V> *hHead=h1._table[i];
				hHead=hHead->_next;
				while (hHead)
				{
					head->_next=new KVNode<K,V>(hHead->_key,hHead->_value);
					hHead=hHead->_next;
					head=head->_next;
				}
			}
			else
			{
				_table[i]=NULL;
			}
		}

	}
	HashTableBucket<K,V>& operator=(const HashTableBucket<K,V> &h1)
	{
		if (&h1==this)
		{
			return *this;
		}
		for(size_t i=0;i<_table.size();i++)
		{
			KVNode<K,V> *head=_table[i];
			if(head==NULL)
			{
				continue;
			}
			KVNode<K,V> *cur=head;
			while(cur)
			{
				KVNode<K,V> *del=cur;
				cur=cur->_next;
				delete del;
			}
		}
		_size=h1._size;
		size_t size=h1._table.size();
		_table.resize(size);
		for (size_t i=0;i<size;i++)
		{
			if (h1._table[i]!=NULL)
			{
				_table[i]=new KVNode<K,V>(h1._table[i]->_key,h1._table[i]->_value);
				KVNode<K,V> *head=_table[i];
				KVNode<K,V> *hHead=h1._table[i];
				hHead=hHead->_next;
				while (hHead)
				{
					head->_next=new KVNode<K,V>(hHead->_key,hHead->_value);
					hHead=hHead->_next;
					head=head->_next;
				}
			}
			else
			{
				_table[i]=NULL;
			}
		}
		return *this;
	}
	void Insert(const K &key,const V &value)
	{
		_CheckCapacity();
		size_t index=HashFunc(key,_table.size());
		KVNode<K,V> *cur=new KVNode<K,V>(key,value);
		cur->_next=_table[index];
		_table[index]=cur;
		_size++;
	}
	bool Remove(const K &key)
	{
		size_t index=HashFunc(key,_table.size());
		KVNode<K,V> *cur=_table[index];
		if(cur==NULL)
		{
			return false;
		}
		//头
		if(cur->_key==key)
		{
			_table[index]=cur->_next;
			delete cur;
			return true;
		}
		KVNode<K,V> *prev=cur;
		cur=cur->_next;
		while(cur)
		{
			if(cur->_key==key)
			{
				prev->_next=cur->_next;
				delete cur;
				return true;
			}
			cur=cur->_next;
		}
		return false;
	}
	bool Find(const K &key)
	{
		size_t index=HashFunc(key,_table.size());
		KVNode<K,V> *cur=_table[index];
		while(cur)
		{
			if(cur->_key==key)
			{
				return true;
			}
			cur=cur->_next;
		}
		return false;
	}
	size_t HashFunc(const K &key,size_t size)
	{
		HashFun h1;
		return h1(key)%size;
	}
	void Print()
	{
		for(size_t i=0;i<_table.size();i++)
		{
			KVNode<K,V> *cur;
			cur=_table[i];
			cout<<"[table"<<i<<"]";
			while(cur)
			{
				cout<<"->";
				cout<<"key:"<<cur->_key;
				cout<<"value:"<<cur->_value;
				cur=cur->_next;
			}
			cout<<"->NULL"<<endl;
		}
	}
protected:

	size_t GetNextPrime(size_t size)
	{
		const int _PrimeSize = 28;
		static const unsigned long _PrimeList [_PrimeSize] =
			{
				53ul,         97ul,         193ul,       389ul,       769ul,
				1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
				49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
				1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
				50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,
				1610612741ul, 3221225473ul, 4294967291ul
			};
			size_t i=0;
			while(size>=_PrimeList[i])
			{
				i++;
			}
			return _PrimeList[i];
	}

	void _CheckCapacity()
	{
		if(_size==_table.size())
		{
			//增容
			vector<KVNode<K,V>*> newTable;
			newTable.resize(GetNextPrime(_size));
			//初始化
			for(size_t i=0;i<newTable.size();i++)
			{
				newTable[i]=NULL;
			}
			//重建
			for(size_t i=0;i<_size;i++)
			{
				KVNode<K,V> * cur=_table[i];
				while(cur)
				{
					KVNode<K,V> *temp=cur;
					cur=cur->_next;
					size_t index=HashFunc(temp->_key,_table.size());
					temp->_next=newTable[index];
					newTable[index]=temp;
				}
			}
			swap(newTable,_table);
		}
	}
protected:
	vector<KVNode<K,V>*> _table;
	size_t _size;
};

void TestHashTableBucket()
{
	HashTableBucket<string,string> h1;
	h1.Insert("水","water");
	h1.Insert("人","human");
	//h1.Print();
	HashTableBucket<int,int> h2;
	h2.Insert(2,2);
	h2.Insert(55,55);
	/*for(size_t i=0;i<10;i++)
	{
		h2.Remove(4*i);
	}*/
	//h2.Print();
	HashTableBucket<string,string> h3(h1);
	//h3.Print();
	HashTableBucket<int,int> h4(h2);
	//h4.Print();
	HashTableBucket<int,int> h5;
	h2=h4;
	h2.Print();
}