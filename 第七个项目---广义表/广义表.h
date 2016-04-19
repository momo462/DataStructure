#pragma once
#include <iostream>
#include<assert.h>
using namespace std;
//���������ͽڵ�
enum Type
{
	HEAD,  //ͷ�ڵ�
	VALUE, //ֵ�ڵ�
	SUB   //�ֱ�ڵ�
};

//�ڵ�Ķ���
struct Node
{
	Type _type;
	Node* _next;
	union
	{
		char _value;
		Node *_subLink;
	};
	Node(Type type=VALUE,char value=0)
	{
		_type=type;
		_next=NULL;
		if (_type==VALUE)
		{
			_value=value;
		}
		else if(_type==SUB)
		{
			_subLink=NULL;
		}
	}
	
};


class GList
{
private:
	Node *_head;
	bool IsNum(char a)
	{
		if ((a>='0'&&a<='9')||(a>='a'&&a<='z')||(a>='A'&&a<='Z'))
		{
			return true;
		}
		else 
			return false;
	}
	Node* _creatGList(char *& c)
	{
		Node *head=new Node(HEAD);
		Node *cur=head;
		c++;
		Node *subhead=NULL;
		Node *valuehead=NULL;
		while (*c)
		{
			if (*c=='(')
			{

				subhead=new Node(SUB);
				cur->_next=subhead;
				subhead->_subLink=_creatGList(c);
				cur=cur->_next;
			}
			else if (IsNum(*c))
			{
				valuehead=new Node(VALUE,*c);
				cur->_next=valuehead;
				cur=cur->_next;
				c++;
			}
			else if (*c==',')
			{
				c++;
			}
			else if (*c==')')
			{
				c++;
				break;
			}
		}
		return head;
	}
	void _Destory(Node* head)
	{
		Node *del=head;
		Node *cur=del;
		while (cur)
		{
			//������
			del=cur;
			cur=cur->_next;
			if (cur->_type==SUB)
			{
				_Destory(del->_subLink);
			}
			delete del;
		}
	}
	void _Print(Node* head)
	{
		assert(head);
		cout<<"(";
		Node *cur=head->_next;
		while (cur)
		{
			if (cur->_type==SUB)
			{
				_Print(cur->_subLink);
				if (cur->_next!=NULL)
				{
					cout<<",";
				}
			}
			else if (cur->_type==VALUE)
			{
				cout<<cur->_value;
				if (cur->_next!=NULL)
				{
					cout<<",";
				}
			}
			cur=cur->_next;
		}
		cout<<")";

	}
	int _Size(Node* head)
	{
		int count=0;
		assert(head);
		Node *cur=head->_next;
		while (cur)
		{
			if (cur->_type==VALUE)
			{
				count++;
			}
			else if (cur->_type==SUB)
			{
				count+=_Size(cur->_subLink);
			}
			cur=cur->_next;
		}
		return count;
	}
	int _Depth(Node* head)
	{
		int count=0;
		head=head->_next;
		while (head)
		{
			if (head->_type==VALUE)
			{
				count=1;
			}
			if (head->_type==SUB)
			{
				count+=_Depth(head->_subLink);
			}
			head=head->_next;
		}
		return count;
	}
	Node* _Copy(Node *head)
	{
		Node *newHead=new Node(HEAD);
		head=head->_next;
		Node *cur=newHead;
		while(head)
		{
			if (head->_type==VALUE)
			{
				Node *valuenode=new Node(VALUE,head->_value);
				cur->_next=valuenode;
				cur=cur->_next;
				head=head->_next;
			}
			else if (head->_type==SUB)
			{
				Node *subnode=new Node(SUB);
				cur->_next=subnode;
				subnode->_subLink=_Copy(head->_subLink);
				cur=cur->_next;
				head=head->_next;
			}
		}
		return newHead;
	}
public:
	//����
	GList(char *head=NULL)
	{
		_head=_creatGList(head);
	}
	//����
	~GList()
	{
		_Destory(_head);
	}
	//��������
	GList(const GList & g)
	{
		_head=_Copy(g._head);
	}
	GList& operator=(GList g)
	{
		swap(g._head,_head);
		return *this;
	}
	//��ӡ��ʾ
	void Print()
	{
		_Print(_head);
		cout<<endl;
	}
	//����
	int Size()
	{
		return _Size(_head);
	}
	//���
	int Depth()
	{
		return _Depth(_head);
	}
};

void test()
{
		GList g1("()");
		GList g2("(a,b)");
		GList g3("(a,b,(c,d)");
		GList g4("(a,b,(c,d),(e,(f),g))");
		g1.Print();
		g2.Print();
		g3.Print();
		g4.Print();
		cout<<g1.Size()<<endl;
		cout<<g2.Size()<<endl;
		cout<<g3.Size()<<endl;
		cout<<g4.Size()<<endl;
		cout<<g1.Depth()<<endl;
		cout<<g2.Depth()<<endl;
		cout<<g3.Depth()<<endl;
		cout<<g4.Depth()<<endl;
		GList g5(g4);
		g5.Print();
		GList g6(g2);
		g6.Print();
		g6=g5;
		g6.Print();
}