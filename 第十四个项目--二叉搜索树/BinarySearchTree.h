#pragma once

//过滤
template<class k,class v>
struct BSTNode
{
	BSTNode<k,v> *_left;
	BSTNode<k,v> *_right;
	k _key;
	v _value;
	//construcor
	BSTNode(const k & key,const v & value)
		:_key(key)
		,_value(value)
		,_left(NULL)
		,_right(NULL)
	{}
};

template <class k,class v>
class BinarySearchTree
{
	typedef BSTNode<k,v> Node;
public:
	//constructor
	BinarySearchTree()
		:_root(NULL)
	{}
	//destructor---递归删除每个节点
	~BinarySearchTree()
	{}
	//pair<bool,Node *>
	bool Insert(const k & key,const v & value)
	{
		
		if (_root==NULL)
		{
			_root=new Node(key,value);
			return true;
		}
		else
		{
			Node *cur=_root;
			Node *prev=NULL;
			while(cur)
			{
				if(cur->_key>key)
				{
					prev=cur;
					cur=cur->_left;
				}
				else if(cur->_key<key)
				{
					prev=cur;
					cur=cur->_right;
				}
				else
					break;
			}
			if(prev->_key>key)
			{
				prev->_left=new Node(key,value);
				return true;
			}
			else if (prev->_key<key)
			{
				prev->_right=new Node(key,value);
				return true;
			}
			else
				return false;
			 
		}
	}
	bool Insert_R(const k & key,const v & value)
	{
		Node *temp=new Node(key,value);
		return _Insert_R(temp,_root);
	}
	//删除
	bool Remove(const k &key)
	{
		//叶子结点
		if (_root==NULL)
		{
			return false;
		}
		Node *cur=_root;
		Node *prev=NULL;
		while (cur)
		{
			if (cur->_key>key)
			{
				prev=cur;
				cur=cur->_left;
			}
			else if (cur->_key<key)
			{
				prev=cur;
				cur=cur->_right;
			}
			else
				break;
		}
		//是叶子结点
		if (cur->_left==NULL&&cur->_right==NULL)
		{
			if (cur->_key!=_root->_key)
			{
				if(prev->_key>key)
				{
					prev->_left=NULL;
				}
				else
				{
					prev->_right=NULL;
				}
			}
			Node *del=cur;
			delete del;
			return true;
		}
		//非叶子结点但是左孩子为空
		else if (cur->_left==NULL)
		{
			if (prev->_key<key)
				prev->_right=cur->_right;
			else
				prev->_left=cur->_right;
			Node *del=cur;
			delete del;
		}
		//非叶子结点但是右孩子为空
		else if (cur->_right==NULL)
		{
			if (prev->_key<key)
				prev->_right=cur->_left;
			else
				prev->_left=cur->_left;
			Node *del=cur;
			delete del;
		}
		//非叶子结点左右均不为空
		else
		{
			//找到其右子树中key值最小的结点---中序遍历最左值
			Node *newcur=cur->_right;
			Node *newprev=cur;
			while (newcur->_left)
			{
				newprev=newcur;
				newcur=newcur->_left;
			}
			if (newprev->_key>key)
			{
				newprev->_left=NULL;
			}
			else
			{
				newprev->_right=NULL;
			}
			swap(newcur->_key,cur->_key);
			swap(newcur->_value,cur->_value);
			Node *del=newcur;
			delete del;
			
		}

	}
	//删除的非递归形式
	bool Remove_R(const k & key)
	{
		return _Remove_R(key,_root);
	}
	//查找
	Node* Find(const k & key)
	{
		if (_root==NULL)
		{
			return NULL;
		}
		Node *cur=_root;
		while(cur)
		{
			if (cur->_key>key)
			{
				cur=cur->_left;
			}
			else if(cur->_key<key)
			{
				cur=cur->_right;
			}
			else
				 break;
		}
		if(cur&&cur->_key==key)
		{
			return cur;
		}
		else
			return NULL;
	}
	Node*  Find_R(const k &key)
	{
		return _Find_R(key,_root);
	}

protected:
	Node*  _Find_R(const k & key,Node *& root)
	{
		if(root==NULL)
		{
			return NULL;
		}
		if(root->_key>key)
		{
			return _Find_R(key,root->_left);
		}
		else if(root->_key<key)
		{
			return _Find_R(key,root->_right);
		}
		else
		{
			return root;
		}

	}
	bool _Remove_R(const k & key,Node * &root)
	{
		if (root==NULL)
		{
			return false;
		}
		if(root->_key>key)
		{
			return _Remove_R(key,root->_left);
		}
		else if(root->_key<key)
		{
			return _Remove_R(key,root->_right);
		}
		else
		{
			if (root->_left==NULL&&root->_right==NULL)
			{
				delete root;
				root=NULL;
				return true;
			}
			else if(root->_left==NULL)
			{
				Node *del=root;
				root=root->_right;
				delete del;
				return true;
			}
			else if(root->_right==NULL)
			{
				Node *del=root;
				root=root->_left;
				delete del;
				return true;
			}
			else
			{
				
					Node *cur=root->_right;
					Node *prev=root;
					while (cur->_left)
					{
						prev=cur;
						cur=cur->_left;
					}
					if (prev->_key>key)
					{
						prev->_left=NULL;
					}
					else
					{
						prev->_right=NULL;
					}
					swap(root->_key,cur->_key);
					swap(root->_value,cur->_value);
					Node *del=cur;
					delete cur;
					return true;
			
			}
		}
		//if (root->_key>key)
		//{
		//	_Remove_R(key,root->_left);
		//	//非叶子结点且左孩子为空
		//	if (root->_left->_key==key&&root->_left->_left==NULL)
		//	{
		//		Node *del=root->_left;
		//		root->_left=del->_right;
		//		delete del;
		//	}
		//	//非叶子结点且右孩子为空
		//	else if (root->_left->_key==key&&root->_left->_right==NULL)
		//	{
		//		Node *del=root->_left;
		//		root->_left=del->_left;
		//		delete del;
		//	}
		//	else
		//	{
		//		Node *cur=root->_left->_right;
		//		Node *prev=root->_left;
		//		while (cur->_left)
		//		{
		//			prev=cur;
		//			cur=cur->_left;
		//		}
		//		swap(root->_right->_key,cur->_key);
		//		swap(root->_right->_value,cur->_value);
		//		if (prev->_key>key)
		//		{
		//			prev->_left=NULL;
		//		}
		//		else
		//		{
		//			prev->_right=NULL;
		//		}
		//		Node *del=cur;
		//		delete cur;
		//	}
		//	
		//}
		//else if (root->_key<key)
		//{
		//	_Remove_R(key,root->_right);
		//	//非叶子结点且左孩子为空
		//	if (root->_right->_key==key&&root->_right->_left==NULL)
		//	{
		//		Node *del=root->_right;
		//		root->_right=del->_right;
		//		delete del;
		//	}
		//	//非叶子结点且右孩子为空
		//	else if (root->_right->_key==key&&root->_right->_right==NULL)
		//	{
		//		Node *del=root->_right;
		//		root->_right=del->_left;
		//		delete del;
		//	}
		//	else
		//	{
		//		Node *cur=root->_right->_right;
		//		Node *prev=root->_right;
		//		while (cur->_left)
		//		{
		//			prev=cur;
		//			cur=cur->_left;
		//		}
		//		swap(root->_right->_key,cur->_key);
		//		swap(root->_right->_value,cur->_value);
		//		if (prev->_key>key)
		//		{
		//			prev->_left=NULL;
		//		}
		//		else
		//		{
		//			prev->_right=NULL;
		//		}
		//		Node *del=cur;
		//		delete cur;
		//	}
		//	
		//}
		//else
		//{
		//	//root就是要找的结点
		//	if (root->_left!=NULL&&root->_right!=NULL)
		//	{
		//		Node *cur=root->_right;
		//		Node *prev=root;
		//		while (cur->_left)
		//		{
		//			prev=cur;
		//			cur=cur->_left;
		//		}
		//		swap(root->_key,cur->_key);
		//		swap(root->_value,cur->_value);
		//		if (prev->_key>key)
		//		{
		//			prev->_left=NULL;
		//		}
		//		else
		//		{
		//			prev->_right=NULL;
		//		}
		//		Node *del=cur;
		//		delete cur;
		//		return true;
		//	}
		//	else
		//	{
		//		return true;
		//	}
		//}
	}
	bool _Insert_R(Node *temp,Node * &root)
	{
		if (root==NULL)
		{
			root=temp;
			return true;
		}
		if (root->_key>temp->_key)
		{
			return _Insert_R(temp,root->_left);
		}
		else if(root->_key<temp->_key)
		{
			return _Insert_R(temp,root->_right);
		}
		else
		{
			return false;
		}
	}

protected:
	Node* _root;
};

void test()
{
	BinarySearchTree<int,int> b1;
	int a[10]={5,3,4,1,7,8,2,6,0,9};
	for(int i=0;i<10;i++)
	{
		b1.Insert_R(a[i],a[i]);
	}
	/*for (int i=0;i<10;i++)
	{
		b1.Remove_R(a[i]);
	}*/
	for(int i=0;i<10;i++)
	{
		//BSTNode<int ,int> *temp=b1.Find(a[i]);
		BSTNode<int ,int> *temp=b1.Find_R(a[i]);
		cout<<temp->_key<<endl;
	}
	BSTNode<int,int> *temp=b1.Find_R(11);
	if(temp==NULL)
	{
		cout<<"*_*"<<endl;
	}
}