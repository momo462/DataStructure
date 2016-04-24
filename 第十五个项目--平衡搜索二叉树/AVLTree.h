#pragma once

template <class K,class V>
struct AVLTreeNode
{
	K _key;
	V _value;
	AVLTreeNode *_left;
	AVLTreeNode *_right;
	AVLTreeNode *_parent;
	int _bf;//balance factor
	AVLTreeNode(const K &key,const V &value)
		:_key(key)
		,_value(value)
		,_left(NULL)
		,_right(NULL)
		,_parent(NULL)
		,_bf(0)
	{}
};

template<class K,class V>
class AVLTree
{
	typedef AVLTreeNode<K,V> Node;
public:
	AVLTree()
		:_root(NULL)
	{}
	bool Insert(const K &key,const V &value)
	{
		//1、空
		if (_root==NULL)
		{
			_root=new Node(key,value);
		}
		else
		{
			//找位置
			//插入
			//改变_bf--->找父节点（栈，三叉链，递归）
			//看_bf的值是不是有到2/-2
			//调整
			Node *cur=_root;
			Node *parent=NULL;
			while(cur)
			{
				if (cur->_key>key)
				{
					parent=cur;
					cur=cur->_left;
				}
				else if (cur->_key<key)
				{
					parent=cur;
					cur=cur->_right;
				}
				else
					return false;
			}
			cur=new Node(key,value);
			cur->_parent=parent;
			if(parent->_key>key)
			{
				parent->_left=cur;
			}
			else
			{
				parent->_right=cur;
			}
			while(parent)
			{
				if (parent->_left==cur)
				{
					parent->_bf--;
				}
				else
				{
					parent->_bf++;
				}
				if (parent->_bf==-1||parent->_bf==1)
				{
					cur=parent;
					parent=parent->_parent;
				}
				else if(parent->_bf==0)
				{
					break;
				}
				else
				{
					//进行旋转
					if (parent->_bf==2)
					{
						if (cur->_bf==-1)
						{
							//右左双旋
							_RotateRL(parent);
							return true;
						}
						else
						{
							//左单旋
							_RotateL(parent);
							return true;
						}
					}
					else
					{
						if (cur->_bf==1)
						{
							//左右双旋
							_RotateLR(parent);
							return true;
						}
						else
						{
							//右单旋
							_RotateR(parent);
							return true;
						}
					}
				}
			}
		}
	}
	bool Remove(const K &key)
	{
	}
	Node *Find(const K &key)
	{

	}
	void Inorder()
	{
		_Inorder(_root);
	}
	bool IsBalanceTree()
	{
		return _IsBalance(_root);
	}
protected:
	bool _IsBalance(Node *root)
	{
		if(root==NULL)
		{
			return true;
		}
		int height=_Height(root->_right)-_Height(root->_left);
		if(abs(height)>1)
		{
			cout<<root->_key<<":这个节点不平衡"<<endl;
			return false;
		}
		if(height!=root->_bf)
		{
			cout<<root->_key<<"这个节点的平衡因子有问题"<<endl;
			cout<<"高度差："<<height<<endl;
			cout<<"平衡因子："<<_root->_bf<<endl;
			return false;
		}
		return _IsBalance(root->_left)&&_IsBalance(root->_right);
	}
	int _Height(Node *root)
	{
		if(root==NULL)
		{
			return 0;
		}
		int left= _Height(root->_left)+1;
		int right=_Height(root->_right)+1;
		return left>right? left:right;
	}
	void _Inorder(Node *root)
	{
		if (root==NULL)
		{
			return;
		}
		_Inorder(root->_left);
		cout<<root->_key<<" ";
		_Inorder(root->_right);
	}
	//左单
	void _RotateL(Node *&parent)
	{
		assert(parent);
		Node *subR=parent->_right;
		Node *subRL=subR->_left;
		parent->_right=subRL;
		if (subRL)
		{
			subRL->_parent=parent;
		}
		subR->_parent=parent->_parent;
		parent->_parent=subR;
		subR->_left=parent;
		parent->_bf=subR->_bf=0;
		parent=subR;
		if(parent->_parent==NULL&&_root!=parent)
		{
			_root=parent;
		}
		if(parent->_parent!=NULL)
		{
			if(parent->_parent->_key>parent->_key)
			{
				parent->_parent->_left=parent;
			}
			else
			{
				parent->_parent->_right=parent;
			}
		}
	}
	void _RotateR(Node *&parent)
	{
		assert(parent);
		Node *subL=parent->_left;
		Node *subLR=subL->_right;
		parent->_left=subLR;
		if(subLR)
		{
			subLR->_parent=parent;
		}
		subL->_parent=parent->_parent;
		parent->_parent=subL;
		subL->_right=parent;
		parent->_bf=subL->_bf=0;
		parent=subL;
		if(parent->_parent==NULL&&_root!=parent)
		{
			_root=parent;
		}
		if(parent->_parent!=NULL)
		{
			if(parent->_parent->_key>parent->_key)
			{
				parent->_parent->_left=parent;
			}
			else
			{
				parent->_parent->_right=parent;
			}
		}
	}
	void _RotateLR(Node *&parent)
	{
		//-2 1
		//_RotateL(parent->_left);
		//_RotateR(parent);
		Node *subL=parent->_left;
		Node *subLR=subL->_right;
		Node *subLRL=subLR->_left;
		subL->_right=subLRL;
		if(subLRL)
		{
			subLRL->_parent=subL;
		}
		subLR->_left=subL;
		subLR->_parent=subL->_parent;
		subL->_parent=subLR;
		if(subLR->_bf==0||subLR->_bf==-1)
		{
			subL->_bf=0;
		}
		else
		{
			subL->_bf=1;
		}
		Node *subLRR=subLR->_right;
		parent->_left=subLRR;
		if(subLRR)
		{
			subLRR->_parent=parent;
		}
		subLR->_right=parent;
		subLR->_parent=parent->_parent;
		parent->_parent=subLR;
		if(subLR->_parent->_key>subLR->_key)
		{
			subLR->_parent->_left=subLR;
		}
		else
		{
			subLR->_parent->_right=subLR;
		}
		if(subLR->_bf==0||subLR->_bf==-1)
		{
			parent->_bf=0;
		}
		else
		{
			parent->_bf=-1;
		}
		subLR->_bf=0;
		parent=subLR;

	}
	void _RotateRL(Node *&parent)
	{
        //2  -1
		//_RotateR(parent->_right);
		//_RotateL(parent);
		//先右单旋
		Node *subR=parent->_right;
		Node *subRL=subR->_left;
		Node *subRLR=subRL->_right;
	    subR->_left=subRLR;
		if(subRLR)
		{
			subRLR->_parent=subR;
		}
		subRL->_right=subR;
		subRL->_parent=subR->_parent;
	    subR->_parent=subRL;
		if(subRL->_bf==0||subRL->_bf==1)
		{
			subR->_bf=0;
		}
		else
		{
			subR->_bf=1;
		}
		Node *subRLL=subRL->_left;
		parent->_right=subRLL;
		if(subRLL)
		{
			subRLL->_parent=parent;
		}
		subRL->_left=parent;
		subRL->_parent=parent->_parent;
		parent->_parent=subRL;
		if(subRL->_parent->_key>subRL->_key)
		{
			subRL->_parent->_left=subRL;
		}
		else
		{
			subRL->_parent->_right=subRL;
		}
		if(subRL->_bf==0||subRL->_bf==-1)
		{
			parent->_bf=0;
		}
		else
		{
			parent->_bf=-1;
		}
		subRL->_bf=0;
		parent=subRL;
	}
protected:
	Node *_root;
};


void TestAVL()
{
	/*int a[]={16, 3, 7, 11, 9, 26, 18, 14, 15};
	AVLTree<int,int> avl;
   for (int i=0;i<9;i++)
   {
	   avl.Insert(a[i],i);
   }
   avl.Inorder();
   cout<<endl;
   avl.IsBalanceTree();*/

   int b[]={4, 2, 6, 1, 3, 5, 15, 7, 16, 14};
   AVLTree<int,int> avl1;
   for(int i=0;i<10;i++)
   {
		avl1.Insert(b[i],i);
   }
   avl1.Inorder();
   cout<<endl;
   avl1.IsBalanceTree();

}