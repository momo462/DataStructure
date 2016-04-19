#pragma once
#include <iostream>
#include <stack>
#include <assert.h>
using namespace std;
enum PointTag
{
	THREAD,
	LINK
};
template <class T>
struct BinaryTreeNode
{
	T _data;
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;
	PointTag _leftTag;
	PointTag _rightTag;
	BinaryTreeNode(const T &data)
		:_data(data)
		,_left(NULL)
		,_right(NULL)
		,_leftTag(LINK)
		,_rightTag(LINK)
	{

	}
};
template<class T>
class BinaryTree
{
public:
	BinaryTree(const T*a,size_t size)
	{
		assert(a);
		int index=0;
		_root=_createBinaryTree(a,index,size);
	}
	//前序线索化
	void PrevOrderThreading()
	{
		BinaryTreeNode<T> *prev=NULL;
		_PrevOrderThreading(_root,prev);
	}
	//前序遍历
	void PrevOrderThread()
	{
		_PrevOrderThread(_root);
	}
	//中序线索化
	void InOrderThreading()
	{
		BinaryTreeNode<T> *prev=NULL;
		_InOrderThreading(_root,prev);
	}
	//中序遍历 
	void InOrderThread()
	{
		_InOrderThread(_root);
	}
	//后续线索化
	void PostOrderThreading()
	{
		BinaryTreeNode<T>*prev=NULL;
		_PostOrderThreading(_root,prev);
	}
	//后续遍历
	void PostOrderThread()
	{
		_PostOrderThread(_root);
	}

private:
	void _PostOrderThreading(BinaryTreeNode<T> *cur,BinaryTreeNode<T> *& prev)
	{
		if (cur==NULL)
		{
			return;
		}
		_PostOrderThreading(cur->_left,prev);
		_PostOrderThreading(cur->_right,prev);
		if (cur->_left==NULL)
		{
			cur->_left=prev;
			cur->_leftTag=THREAD;
		}
		if(prev&&prev->_right==NULL)
		{
			prev->_right=cur;
			prev->_rightTag=THREAD;
		}
	    prev=cur;
		
	}
	void _PostOrderThread(BinaryTreeNode<T> *cur)
	{
		stack<BinaryTreeNode<T>*> s1;
		while (cur)
		{
			while (cur->_rightTag==LINK)
			{
				s1.push(cur);
				cur=cur->_right;
			}
			s1.push(cur);
			cur=cur->_left;
		}
		while (!s1.empty())
		{
			BinaryTreeNode<T>* top=s1.top();
			s1.pop();
			cout<<top->_data<<" ";
		}
	}
	void _InOrderThreading(BinaryTreeNode<T>* cur,BinaryTreeNode<T>*& prev)
	{
		if (cur==NULL)
		{
			return;
		}
		_InOrderThreading(cur->_left,prev);
		if (cur->_left==NULL&&cur->_leftTag==LINK)
		{
			cur->_left=prev;
			cur->_leftTag=THREAD;
		}
		if (prev&&prev->_right==NULL)
		{
			prev->_right=cur;
			prev->_rightTag=THREAD;
		}
		prev=cur;
		_InOrderThreading(cur->_right,prev);
	}
	void _InOrderThread(BinaryTreeNode<T>* cur)
	{
		while(cur)
		{
			while (cur->_leftTag==LINK)
			{
				cur=cur->_left;
			}
			cout<<cur->_data<<" ";
			while (cur->_rightTag==THREAD)
			{
				cur=cur->_right;
				cout<<cur->_data<<" ";
			}
			cur=cur->_right;
		}
	}
	void _PrevOrderThreading(BinaryTreeNode<T>* cur,BinaryTreeNode<T>* &prev)
	{
		if (cur==NULL)
		{
			return;
		}
		if (cur->_left==NULL)
		{
			cur->_left=prev;
			cur->_leftTag=THREAD;
		}
		if (prev&&prev->_right==NULL)
		{
			prev->_right=cur;
			prev->_rightTag=THREAD;
		}
		prev=cur;
		if (cur->_leftTag==LINK)
		{
			_PrevOrderThreading(cur->_left,prev);
		}
		if(cur->_rightTag==LINK)
		{
			_PrevOrderThreading(cur->_right,prev);
		}
	}
	void _PrevOrderThread(BinaryTreeNode<T>*cur)
	{
		while(cur)
		{
			cout<<cur->_data<<" ";
			while(cur->_leftTag==LINK)
			{
				cur=cur->_left;
				cout<<cur->_data<<" ";
			}
			cur=cur->_right;
			/*while(cur&&cur->_rightTag==THREAD)
			{
				cur=cur->_right;
				cout<<cur->_data<<" ";
			}
			if (cur->_right==NULL)
			{
				break;
			}*/
		}
	}
	BinaryTreeNode<T>* _createBinaryTree(const T *a,int& index,int size)
	{
		if (a==NULL)
		{
			return NULL;
		}
		BinaryTreeNode<T>* root=NULL;
		if(index<size&&a[index]!='#')
		{
			root=new BinaryTreeNode<T>(a[index]);
			root->_left=_createBinaryTree(a,++index,size);
			root->_right=_createBinaryTree(a,++index,size);
		}
		return root;

	}
private:
	BinaryTreeNode<T> *_root;
};

void test1()
{
	int a[10]={1,2,3,'#','#',4,'#','#',5,6};
	BinaryTree<int> b1(a,10);
	//b1.PostOrderThreading();
	//b1.PostOrderThread();
	/*b1.InOrderThreading();
	b1.InOrderThread();*/
	b1.PrevOrderThreading();
	b1.PrevOrderThread();
}
