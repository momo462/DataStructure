#pragma once

enum Color
{
	RED,
	BLACK,
};
template <class K,class V>
struct RBTreeNode
{
	K _key;
	V _value;
	RBTreeNode<K,V> *_left;
	RBTreeNode<K,V> *_right;
	RBTreeNode<K,V> *_parent;
	Color _col;
	RBTreeNode(const K & key,const V & value,const Color col=BLACK)
		:_key(key)
		,_value(value)
		,_col(col)
		,_left(NULL)
		,_right(NULL)
		,_parent(NULL)
	{}
};

template<class K,class V>
class RBTree
{
	typedef RBTreeNode<K,V> Node;
public:
	RBTree()
		:_root(NULL)
	{}
	bool Insert(const K &key,const V &value)
	{
		//1������
		if(_root==NULL)
		{
			_root=new Node(key,value,BLACK);
		}
		else
		{
			//1�����뵽����λ��
			Node *cur=_root;
			Node *parent=NULL;
			while(cur)
			{
				if(cur->_key>key)
				{
					parent=cur;
					cur=cur->_left;
				}
				else if(cur->_key<key)
				{
					parent=cur;
					cur=cur->_right;
				}
				else
				{
					//�������ظ�
					return false;
				}
			}
			cur=new Node(key,value,RED);
			cur->_parent=parent;
			if(parent->_key>key)
			{
				parent->_left=cur;
			}
			else
			{
				parent->_right=cur;
			}
			//�жϸ�λ���Ƿ���ʣ���Ҫ���Ƿ����ڲ����ʵ������
			//�����ʽ��е���
			while(cur!=_root&&parent->_col==RED)
			{

				Node *grandpa=parent->_parent;
				Node *uncle=NULL;
				if(parent->_key<grandpa->_key)
				{
					uncle=grandpa->_right;
				}
				else
				{
					uncle=grandpa->_left;
				}
				//1��cur��red  parent��red grandpa��black uncle��red
					if(uncle&&uncle->_col==RED)
					{
						parent->_col=BLACK;
						uncle->_col=BLACK;
						grandpa->_col=RED;
						cur=grandpa;
						parent=cur->_parent;
					}
					else
					{
						//1�����ж��ǲ��Ƿ������3
						if(parent->_key<grandpa->_key&&cur->_key>parent->_key)
						{
							_RotateL(parent);
							cur=parent->_left;
						}
						if(parent->_key>grandpa->_key&&cur->_key<parent->_key)
						{
							_RotateR(parent);
							cur=parent->_right;
						}
						//curΪp�����ӣ�pΪg������---�ҵ���ת
						if (parent->_key<grandpa->_key&&cur->_key<parent->_key)
						{
							parent->_col=BLACK;
							grandpa->_col=RED;
							_RotateR(grandpa);

						}
						if(parent->_key>grandpa->_key&&cur->_key>parent->_key)
						{
							parent->_col=BLACK;
							grandpa->_col=RED;
							_RotateL(grandpa);
						}
						break;
					}
			}
			_root->_col=BLACK;
		}
	}
	bool IsBalance()
	{
		  /*

			4.���к�ڵ���ӽڵ㶼Ϊ��ɫ��

			5.����һ�ڵ㵽��Ҷ�ӽڵ������·���϶�������ͬ��Ŀ�ĺڽڵ㡣*/
		if(_root==NULL)
		{
			return true;
		}
		//2
		if(_root->_col!=BLACK)
		{
			return false;
		}
		//4
		if(!ResultRed(_root))
		{
			return false;
		}
		//5
		if(!_ResultBlack(_root))
		{
			return false;
		}
		return true;
	}
	void Inorder()
	{
		_Inorder(_root);
	}
protected:
	void _Inorder(Node *root)
	{
		if(root==NULL)
		{
			return;
		}
		_Inorder(root->_left);
		cout<<root->_key<<" ";
		_Inorder(root->_right);
	}
	bool ResultRed(Node *root)
	{
		if(root==NULL)
		{
			return true;
		}
		if(root->_col==RED)
		{
			if(root->_parent->_col==RED)
			{
				return false;
			}
		}
		bool left=ResultRed(root->_left);
		bool right=ResultRed(root->_right);
		return left&&right;
	}
    int  _Black(Node *root)
	{
		if(root==NULL)
		{
			return 0;
		}
		int count=0;
		if(root->_col!=RED)
		{
			count=1;
		}
		int left=_Black(root->_left)+count;
		int right=_Black(root->_right)+count;
		if(left==right)
		{
			return left;
		}
		else 
			return -1;

	}
	bool _ResultBlack(Node *root)
	{
		if(root==NULL)
		{
			return true;
		}
		int leftB=_Black(root->_left);
		int rightB=_Black(root->_right);
		if(leftB==rightB&&(leftB!=-1||rightB!=-1))
		{
			return true;
		}
		else
			return false;
	}
	void _RotateR(Node *&parent)
	{
		Node *subL=parent->_left;
		Node *subLR=subL->_right;
		parent->_left=subLR;
		if (subLR)
		{
			subLR->_parent=parent;
		}
		subL->_right=parent;
		subL->_parent=parent->_parent;
		parent->_parent=subL;
		if(subL->_parent==NULL)
		{
			_root=subL;
		}
		if(subL->_parent&&subL->_parent->_key>subL->_key)
		{
			subL->_parent->_left=subL;
		}
		else if(subL->_parent)
		{
			subL->_parent->_right=subL;
		}
		parent=subL;

	}
	void _RotateL(Node *&parent)
	{
		Node *subR=parent->_right;
		Node *subRL=subR->_left;
		parent->_right=subRL;
		if (subRL)
		{
			subRL->_parent=parent;
		}
		subR->_left=parent;
		subR->_parent=parent->_parent;
		parent->_parent=subR;
		if(subR->_parent==NULL)
		{
			_root=subR;
		}
		if(subR->_parent&&subR->_parent->_key>subR->_key)
		{
			subR->_parent->_left=subR;
		}
		else if(subR->_parent)
		{
			subR->_parent->_right=subR;
		}
		parent=subR;
	}
protected:
	Node *_root;
};

void test()
{
	int a[]={16, 3, 7, 11, 9, 26, 18, 14, 15};
	RBTree<int,int> rb1;
	for(int i=0;i<9;i++)
	{
		rb1.Insert(a[i],i);
	}
	rb1.Inorder();
	cout<<endl;
	cout<<rb1.IsBalance()<<endl;
}