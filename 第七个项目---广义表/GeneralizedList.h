//#pragma once
//#include <assert.h>
////---��������
//enum Type
//{
//	HEAD,   //ͷ�ڵ�
//	VALUE,  //ֵ�ڵ�
//	SUB     //�ӱ�ڵ�
//};  
//struct GeneralListNode     //
//{
//	Type _type;        //����        
//	GeneralListNode *_next;      //�����Ƿ��У���˭  
//	union  //ֵ�ڵ��sub�ڵ㹫�ÿռ�---��ʡ�ռ�
//	{
//		char _value;            //�����ֵ�ڵ㣬��ôֵ
//		GeneralListNode *_subLink; //������ֱ�ڵ㣬��ô��ָ����ӱ�
//	};
//	GeneralListNode(Type type=VALUE,char value=0)
//		:_type(type)
//		,_next(NULL)
//	{
//		if (_type==VALUE)
//		{
//			_value=value;
//		}
//		else if (_type==SUB)
//		{
//		     _subLink=NULL;
//		}
//	}
//	
//};
//
//class GeneralList
//{
//public:
//	GeneralList()
//		:_head(NULL)
//	{
//
//	}
//	GeneralList(char *s)
//		:_head(NULL)
//	{
//		_head=_CreatGeneralList(s);
//	}
//	//�ݹ�ɾ��
//	~GeneralList()
//	{
//		Destroy(_head);
//	}
//	//�ݹ鿽��
//	GeneralList(const GeneralList &g)
//	{
//		Copy(g._head);
//	}
//	//1��destroy--copy
//	//2��swap
//	GeneralList& operator=(const GeneralList &g)
//	{
//
//	}
//	size_t size()
//	{
//		return _Size(_head);
//	}
//	void Print()
//	{
//		 _Print(_head);
//		 cout<<endl;
//	}
//	int Depth()
//	{
//		return _Depth(_head);
//	}
//protected:
//	GeneralListNode* Copy(GeneralListNode *head)
//	{
//		assert(head);
//		GeneralListNode *newhead=new GeneralListNode(HEAD);
//		GeneralListNode *newcur=newhead;
//		GeneralListNode *cur=head->_next;
//		while (cur)
//		{
//			if (cur->_type==VALUE)
//			{
//				newcur->_next=new GeneralListNode(VALUE,cur->_value);
//				newcur=newcur->_next;
//			}
//			else if(cur->_type==SUB)
//			{
//				newcur->_next=new GeneralListNode(SUB);
//				newcur=newcur->_next;
//				newcur->_subLink=Copy(cur->_subLink);
//
//			}
//			cur=cur->_next;
//		}
//		return newhead;
//
//	}
//	void Destroy(GeneralListNode *head)
//	{
//		GeneralListNode *cur=head;
//
//		while (cur)
//		{
//			GeneralListNode *del=cur;
//			cur=cur->_next;
//			if (del->_type==SUB)
//			{
//				Destroy(del->_subLink);
//			}
//			delete del;
//		}
//
//	}
//	int _Depth(GeneralListNode *head)
//	{
//
//	}
//	void _Print(GeneralListNode *head)
//	{
//		GeneralListNode *cur=head;
//		
//		while (cur)
//		{
//			if (cur->_type==HEAD)
//			{
//				cout<<"(";
//			}
//			else if (cur->_type==VALUE)
//			{
//				cout<<cur->_value;
//				if (cur->_next)
//				{
//					cout<<",";
//				}
//			}
//			else
//			{
//				_Print(cur->_subLink);
//				if (cur->_next)
//				{
//					cout<<",";
//				}
//			}
//		}
//		cout<<")";
//	}
//	size_t _Size(GeneralListNode *head)
//	{
//		GeneralListNode *cur=head;
//		size_t size=0;
//		while(cur)
//		{
//			if (cur->_type==VALUE)
//			{
//				++size;
//			}
//			else if (cur->_type==SUB)
//			{
//				size+=_Size(cur->_subLink);
//			}
//			cur=cur->_next;
//		}
//		return size;
//	}
//	bool IsValue(char ch)
//	{
//		if ((ch>='0'&&ch<='9')||(ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))
//		{
//			return true;
//		}
//		else 
//		{
//			return false;
//		}
//	}
//	GeneralListNode* _CreatGeneralList(char * &s)
//	{
//		assert(*s=='(');
//
//		GeneralListNode *head=new GeneralListNode(HEAD);
//		GeneralListNode *cur=head;
//		++s;
//		while (*s)
//		{
//			//�п����Ǹ��ӱ�
//			if (*s=='(')   //Ҫ�ݹ�
//			{
//				GeneralListNode *subnode=new GeneralListNode(SUB);
//				cur->_next=subnode;
//				subnode->_subLink=_CreatGeneralList(s);
//			}
//			else if (*s==')')
//			{
//				++s;
//				break;
//			}
//			else if(IsValue(*s))
//			{
//				GeneralListNode *valuenode=new GeneralListNode(VALUE,*s);
//				cur->_next=valuenode;
//				cur=cur->_next;
//				s++;
//			}
//			else 
//			{
//				++s;
//			}
//		}
//		return head;
//
//	}
//protected:
//	GeneralListNode *_head;
//
//};
////( ---ͷ  a --- ֵ  b---ֵ
//void Test1()
//{
//	GeneralList g1("()");
//	GeneralList g2("(a,b)");
//	GeneralList g3("(a,b,(c,d)��");
//	GeneralList g4("(a,b,(c,d),(e,(f),h))");
//}