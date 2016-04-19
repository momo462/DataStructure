#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include <string>
using namespace std;
template<class T>
struct ListNode
{
	ListNode<T>(const T& t)
	{
		_data=t;
		_next=NULL;
	}
	T _data;
	ListNode<T>* _next;

};
template<class T>
class Queue
{
private:

public:
		Queue()
			:_head(NULL)
			,_tail(NULL)
			,_size(0)
		{

		}
		Queue(const Queue &q)
		{
			if(q._size==0)
			{
				return;
			}
			else if(q._size==1)
			{
				_tail=_head=new ListNode<T>(q._head->_data);
				_head->_next=_tail->_next=NULL;
				_size=1;

			}
			else
			{
				ListNode<T> *tmp=q._head;
				ListNode<T> *temp=new ListNode<T>(tmp->_data);
				ListNode<T> *newHead=temp;
				_head=temp;
				_size=q._size;
				for(int i=1;i<(int)q._size;i++)
				{ 
					
					tmp=tmp->_next;
					temp=new ListNode<T>(tmp->_data);
					newHead->_next=temp;
					newHead=temp;
					if(i==q._size-1)
					{
						_tail=temp;
						_tail->_next=NULL;
					}
				}
			}
		}
		Queue& operator=(const Queue &q)
		{
			if(&q==this)
			{
				return *this;
			}
			if(_size>0)
			{
				for(int i=0;i<(int)_size;i++)
				{
					ListNode<T> *cur=_head;
					cur=cur->_next;
					delete _head;
				}
			}
			else
			{
				delete _head;
			}
			if(q._size==0)
			{
				return *this;
			}
			else if(q._size==1)
			{
				_tail=_head=new ListNode<T>(q._head->_data);
				_size=1;
			}
			else
			{
				ListNode<T> *tmp=q._head;
				ListNode<T> *temp=new ListNode<T>(tmp->_data);
				ListNode<T> *newHead=temp;
				_head=temp;
				_size=q._size;
				for(int i=1;i<(int)q._size;i++)
				{ 
					
					tmp=tmp->_next;
					temp=new ListNode<T>(tmp->_data);
					newHead->_next=temp;
					newHead=temp;
					if(i==q._size-1)
					{
						_tail=temp;
						_tail->_next=NULL;

					}
				}
			}
			return *this;
		}
		~Queue()
		{
			if(_size==0)
			{
				return;
			}
			else if(_size==1)
			{
				delete _head;
				_head=_tail=NULL;
				_size=0;
			}
			else
			{
				ListNode<T> *del=_head;
				ListNode<T> *cur=del->_next;
				for(int i=1;i<(int)_size;i++)
				{
					delete del;
					del=cur;
					cur=cur->_next;
				}
				_head=_tail=NULL;
				_size=0;
			}
		}
public:
	bool Empty()const
	{
		if(_size==0)
			return true;
		else
			return false;
	}
	size_t Size()const
	{
		return _size;
	}
	T& Front()
	{
		assert(_head);
		return _head->_data;
	}
	const T& Front()const
	{
		assert(_head);
		return _head->_data;
	}
	T& Back()
	{
		assert(_head);
		return _tail->_data;
	}
	const T& Back()const
	{
		assert(_head);
		return _head->_data;
	}
	void Push(const T& val)
	{
		ListNode<T> *cur=new ListNode<T>(val);
		if(_head==NULL)
		{
			_tail=_head=cur;

		} 
		else 
		{
			_tail->_next=cur;
			_tail=_tail->_next;
		}
		_size++;
		
	}
	void Pop()
	{
		if(_head==NULL)
			return;
		else if(_head==_tail)
		{
			delete _head;
			_head=_tail=NULL;
		}
		else
		{
			ListNode<T> *del=_head;
			_head=_head->_next;
			delete del;
		}
		_size--;

	}
private:
	ListNode<T> *_head;
	ListNode<T> *_tail;
	size_t _size;
};
#endif	