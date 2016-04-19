#pragma once
#include <assert.h>
#include <iostream>
#include <queue>
#include <stack>
using namespace std;
//节点的结构
template <class T>
struct BinaryTreeNode
{
	T _value;
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;
	BinaryTreeNode(const T &b=0)
		:_value(b)
		,_left(NULL)
		,_right(NULL)
	{
	}
		
};

//二叉树
template<class T>
class BinaryTree
{
public:
	BinaryTree()
		:_root(NULL)
	{

	}
	BinaryTree(const T *a,size_t size)
	{ 
		size_t index=0;
		_root=_CreateTree(a,size,index);
	}
	~BinaryTree()
	{
		_Detory(_root);
	}
	BinaryTree(const BinaryTree<T> &t)
	{
		_root=_Copy(t._root);
	}
	BinaryTree& operator=(const BinaryTree<T> &t)
	{
		if (t._root!=_root)
		{
			_Detory(_root);
			_root=_Copy(t._root);
		}
		return *this;
	}
	void PrevOrder()
	{
		_PrevOrder(_root);
		cout<<endl;
	}
	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}
	void PostOrder()
	{
		_PostOrder(_root);
		cout<<endl;
	}
	void LevelOrder()
	{
		BinaryTree<T> r=*this;
		queue<BinaryTreeNode<T>> q1;
		q1.push(*r._root);
		while (q1.size())
		{
			*r._root=q1.front();
			q1.pop();
			cout<<r._root->_value<<" ";
			if (r._root->_left)
			{	
				q1.push(*(r._root->_left));
			}
			if (r._root->_right)
			{
				q1.push(*(r._root->_right));
			}
		}
		cout<<endl;
	}
	//非递归前序
	void PrevOrder_NonR()
	{
		if (_root==NULL)
		{
			return;
		}
		stack<BinaryTreeNode<T>*> s1;
		s1.push(_root);
		while (!s1.empty())
		{
			BinaryTreeNode<T> *top=s1.top();
			cout<<top->_value<<" ";
			s1.pop();
			if (top->_right)
			{
				s1.push(top->_right);
			}
			if (top->_left)
			{
				s1.push(top->_left);
			}
		}
		cout<<endl;
	}
	//非递归中序
	void InOrder_NonR()
	{
		stack<BinaryTreeNode<T>*> s1;
		BinaryTreeNode<T>* cur=_root;
		while (cur||!s1.empty())
		{
			while (cur)
			{
				s1.push(cur);
				cur=cur->_left;
			}
			if (!s1.empty())
			{
				BinaryTreeNode<T>* top=s1.top();
				cout<<top->_value<<" ";
				s1.pop();
				cur=top->_right;
			}

		}
		cout<<endl;
	}
	//非递归后序
	void PostOrder_NonR()
	{
		stack<BinaryTreeNode<T>*> s1;
		BinaryTreeNode<T> *cur=_root;
		BinaryTreeNode<T> *prevVisited=NULL;
		while (cur||!s1.empty())
		{
			while (cur)
			{
				s1.push(cur);
				cur=cur->_left;
			}
			BinaryTreeNode<T> *top=s1.top();
			if (top->_right==NULL||top->_right==prevVisited)
			{
				cout<<top->_value<<" ";
				s1.pop();
			}
			else
			{
				cur=top->_right;
				prevVisited=cur;

			}
		}
		cout<<endl;
	}
	int Size()
	{
		//return _Size(_root);
		int index=0;
		_Size1(_root,index);
		return index;
	}
	int Depth()
	{
		return _Depth(_root);
	}
	BinaryTreeNode<T>* Find(const T &x)
	{
		return _Find(x,_root);
	}
	int GetLeafNum()
	{
		//return _GetLeafNum(_root);
		int index=0;
		_GetLeafNum1(_root,index);
		return index;
	}
private:
	BinaryTreeNode<T>* _CreateTree(const T *a,size_t size,size_t& index)
	{
		assert(a);
		BinaryTreeNode<T> *head=new BinaryTreeNode<T>(a[index]);
		if (a[index]!='#'&&index<size)
		{
			head->_left=_CreateTree(a,size,++index);
			head->_right=_CreateTree(a,size,++index);
		}
		else
		{
			return NULL;
		}
		return head;
	}
	void _Detory(BinaryTreeNode<T> *root)
	{
		BinaryTreeNode<T> *del=root;
		if(root->_left)
		{

			_Detory(root->_left);
			//delete del;
			
		}
		if (root->_right)
		{
			_Detory(root->_right);
			//delete del;
		}
		delete del;
		del=NULL;
		return;
	}
	BinaryTreeNode<T>* _Copy(const BinaryTreeNode<T>* croot)
	{
		BinaryTreeNode<T> *root;
		if (!croot)
		{
			return NULL;
		}
		else
		{
			root=new BinaryTreeNode<T>(croot->_value);
			root->_left=_Copy(croot->_left);
			root->_right=_Copy(croot->_right);
		}
		return root;
	}
	void _PrevOrder(BinaryTreeNode<T>* root)
	{
		if (root)
		{
			cout<<root->_value<<" ";
			_PrevOrder(root->_left);
			_PrevOrder(root->_right);
		}
		else
		{
			return;
		}
	}
	void _InOrder(BinaryTreeNode<T>* root)
	{
		if (root)
		{
			_InOrder(root->_left);
			cout<<root->_value<<" ";
			_InOrder(root->_right);
		}
		else
		{
			return;
		}
	}
	void _PostOrder(BinaryTreeNode<T>* root)
	{
		if (root)
		{
			_PostOrder(root->_left);
			_PostOrder(root->_right);
			cout<<root->_value<<" ";
		}
		else
		{
			return;
		}
	}
	int _Size(BinaryTreeNode<T>* root)
	{
		if (root)
		{
			return _Size(root->_left)+_Size(root->_right)+1;
		}
		return  0;
	}
	void _Size1(BinaryTreeNode<T>* root,int & index)
	{
		if (root==NULL)
		{
			return;
		}
		++index;
		_Size1(root->_left,index);
		_Size1(root->_right,index);	
	}
	int _Depth(BinaryTreeNode<T> *root)
	{
		if (root)
		{
			int depth1=_Depth(root->_left)+1;
			int depth2=_Depth(root->_right)+1;
			if (depth1>depth2)
			{
				return depth1;
			}
			else
			{
				return depth2;
			}
		}
		else
		{
			return 0;
		}
	}
	BinaryTreeNode<T>* _Find(const T &x,BinaryTreeNode<T>* root)
	{
		
		if(root)
		{
			if(root->_value==x)
				return root;
			BinaryTreeNode<T>* findz=_Find(x,root->_left);
			BinaryTreeNode<T>* findy=_Find(x,root->_right);
			return findz==NULL? findy:findz;
		}
		return NULL;
	}
	int _GetLeafNum(BinaryTreeNode<T>* root)
	{
		if (root==NULL)
		{
			return 0;
		}
		if (root->_left==NULL&&root->_right==NULL)
		{
			return 1;
		}
		return _GetLeafNum(root->_left)+_GetLeafNum(root->_right);
	}
	void _GetLeafNum1(BinaryTreeNode<T>* root,int & index)
	{
		if (root==NULL)
		{
			return;
		}
		if (root->_left==NULL&&root->_right==NULL)
		{
			index++;
		}
		_GetLeafNum1(root->_left,index);
		_GetLeafNum1(root->_right,index);
	}
private:
	BinaryTreeNode<T> *_root;
};
void test()
{
	int a[10]={1,2,3,'#','#',4,'#','#',5,6};
	BinaryTree<int> b1(a,10);
	BinaryTree<int> b2(b1);
	b1.PrevOrder();
	b1.PrevOrder_NonR();
	b1.InOrder();
	b1.InOrder_NonR();
	b1.PostOrder();
	b1.PostOrder_NonR();
	b1.LevelOrder();
	cout<<b1.Size()<<endl;
	cout<<b1.Depth()<<endl;
	BinaryTreeNode<int> *b=b1.Find(6);
	cout<<b1.GetLeafNum();
}