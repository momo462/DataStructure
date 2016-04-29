#pragma once

//�ڵ�ṹ
template <class K,int M=3>
struct BTreeNode
{
	K _key[M];                 //�ؼ�������
	BTreeNode<K,M>* _sub[M+1]; //����ָ������
	size_t _size;              //�ؼ��ָ���
	BTreeNode<K,M>* _parent;   //�ؼ�������ĸ��ڵ�
	BTreeNode()
		:_parent(NULL)
		,_size(0)
	{
		for(int i=0;i<M;i++)
		{
			_key[i]=K();
		}
		for(int i=0;i<M+1;i++)
		{
			_sub[i]=NULL;
		}
	}
};

//����ֵ�ṹ
template <class K,class V>
struct Pair
{
	K _first;
	V _second;
	Pair(const K &k=K(),const V &v=V())
		:_first(k)
		,_second(v)
	{}
};
//B��
template <class K,int M=3>
class BTree
{
	typedef BTreeNode<K,M> Node;
public:
	//����
	BTree()
		:_root(NULL)
	{}
	//����
	bool Insert(const K &key)
	{
		K k=key;
		if(_root==NULL)
		{
			_root=new Node;
			_root->_key[0]=k;
			_root->_size++;
		    return true;
		}
		else
		{
			//���Һ���λ��
			Pair<Node*,int> pos=Find(key);
			//�ҵ���keyֵ��ͬ��λ�ã�����false
			if(pos._second!=-1)
			{
				return false;
			}
			else
			{
				_InsertKey(key,pos._first);
				Node *cur=pos._first;
				while(cur)
				{
					if(cur->_size==M)
					{
						//����
						//�ֽ��֮��Ľ��
						Node *temp=new Node;
						int boundary=M/2;
						int index=0;
						for(int i=boundary+1;i<M;i++)
						{
							temp->_key[index]=cur->_key[i];
							temp->_sub[index]=cur->_sub[i];
							if(cur->_sub[i]&&cur->_sub[i]->_parent)
							{
								temp->_sub[index]->_parent=temp;
							}
							cur->_sub[i]=NULL;
							temp->_sub[index+1]=cur->_sub[i+1];
							if(cur->_sub[i+1]&&cur->_sub[i+1]->_parent)
							{
								temp->_sub[index+1]->_parent=temp;
							}
							cur->_sub[i+1]=NULL;
							index++;
							temp->_size++;
							cur->_size--;
						}
						//�ֽ�㴦�Ľڵ�
						Node *temp1=new Node;
						temp1->_key[0]=cur->_key[boundary];
						temp1->_size++;
						cur->_size--;
						Node *parent=cur->_parent;
						if(parent==NULL)
						{
							_root=temp1;
							temp1->_sub[0]=cur;
							cur->_parent=temp1;
							temp1->_sub[1]=temp;
							temp->_parent=temp1;

						}
						else
						{
							/*int index=0;
							for(int i=0;i<=parent->_size;i++)
							{
							if(parent->_sub[i]==pos._first)
							{
							index=i;
							break;
							}
							}
							parent->_sub[index]=temp1;*/
							_InsertKey(temp1->_key[0],parent);
							int i=0;
							for(i=0;i<parent->_size;i++)
							{
								if(temp1->_key[0]==parent->_key[i])
								{
									break;
								}
							}
							parent->_sub[i]=cur;
							cur->_parent=parent;
							parent->_sub[i+1]=temp;
							temp->_parent=parent;
							cur=parent;
						}
						
					}
					else
					{
						break;
					}
				}
			}
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
		if (root==NULL)
		{
			return;
		}
		for(int i=0;i<(root->_size);i++)
		{
			_Inorder(root->_sub[i]);
			cout<<root->_key[i]<<" ";
		}
		_Inorder(root->_sub[root->_size]);
	}
	void _InsertKey(const K &key,Node *parent)
	{
		int i=0;
		for(i=parent->_size-1;i>=0;i--)
		{
			if(parent->_key[i]>key)
			{
				parent->_key[i+1]=parent->_key[i];
				parent->_sub[i+2]=parent->_sub[i+1];
			}
			else
			{
				break;
			}
		}
		K k=key;
		parent->_key[i+1]=k;
		parent->_size++;
		return;
	}
	Pair<Node*,int> Find(const K & key)
	{
		Node *cur=_root;
		Node *parent=NULL;
		while(cur)
		{
			int i=0;
			for(i;i<cur->_size;i++)
			{
				if (cur->_key[i]>key)
				{
					break;
				}
				if(cur->_key[i]==key)
				{
					return Pair<Node*,int>(cur,i);
				}
			}
			parent=cur;
			cur=cur->_sub[i];
		}
		return Pair<Node*,int>(parent,-1);
	}

protected:
	Node *_root;
};

void test()
{
	int a[]={53, 75, 139, 49, 145, 36, 101};
	BTree<int> b;
	for(int i=0;i<sizeof(a)/sizeof(int);i++)
	{
		b.Insert(a[i]);
	}
	b.Inorder();
	cout<<endl;
	BTree<int,6> b1;
	for(int i=0;i<100;i++)
	{
		b1.Insert(i);
	}
	b1.Inorder();
}