//#include "Q1.h"
//void TestQ1()
//{
//	Stack<int>s1;
//	s1.Push(10);
//	s1.Push(11);
//	s1.Push(14);
//	s1.Push(8);
//	s1.Push(13);
//	s1.Push(12);
//	s1.Push(2);
//	cout<<s1.Min()<<endl;
//
//}
#include "Q2.h"
void TestQ2()
{
	Queue<int>q1;
	q1.Push(1);
	q1.Push(2);
	q1.Push(3);
	q1.Push(4);
	q1.Pop();
	q1.Push(5);
	q1.Pop();
	q1.Push(6);
	q1.Pop();
	q1.Pop();
	q1.Push(7);
	q1.Pop();

}
#include "Q3.h"
void TestQ3()
{
	Stack<int>s1;
	s1.Push(1);
	s1.Push(2);
	s1.Pop();
	s1.Pop();
	s1.Push(3);
	s1.Pop();
	s1.Push(4);
	
	
	s1.Pop();
	s1.Pop();


}

//#include <stack>
//#include <iostream>
//using namespace std;
////������ջ˳���е�Ԫ�أ����������
////A�����Ԫ����ջ����Ԫ�أ���pop������
////B���������ջ��Ԫ�أ��������ջ˳��û��ջ��Ԫ��push��ջ��
////ֱ������Ԫ��pushջ�У�Ȼ�󽫸�Ԫ��pop���������push������Ԫ�ض�û���ҵ���Ԫ�أ�
////��ô�����ջ˳���Ǵ���ġ�
//bool IsTrueStack(int n,int* In,int *Out)
//{
//	//ջ�ǿյ�
//	stack<int> s1;
//	int i=0;
//	int m=n;
//	int y=0;
//	for (int j=0;j<n;j++)
//	{
//		for(i;In[i]!=Out[j];i++)
//		{
//			if(i==s1.size()-1)
//			{
//				break;
//			}
//			s1.push(In[i]);
//		}
//		if(In[i]==Out[j])
//		{
//			
//			if (In[i]==In[m-1])
//			{
//				
//				if(y==0)
//				{
//					s1.push(In[i]);
//					s1.pop();
//				}
//				else
//				{
//					s1.pop();
//				}
//				y++;
//				i=s1.size()-1;
//				m=s1.size();
//			}
//			else
//			{
//				s1.push(In[i]);
//				s1.pop();
//				i++;
//			}
//			continue;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	return true;
//	
//}
//void TestQ4()
//{
//	int In[5]={1,2,3,4,5};
//	int Out[5]={4,5,3,2,1};
//	int Out1[5]={4,5,1,2,3};
//	cout<<IsTrueStack(5,In,Out)<<endl;
//	cout<<IsTrueStack(5,In,Out1)<<endl;
//	
//}
#include "Q5.h"
void TestQ5()
{
	//int _a[4];
	//TwoStack<int> ts1(_a,4);
	TwoStack<int> ts1(4);
	ts1.push(2,1);
	ts1.push(2,2);
	ts1.push(2,3);
	ts1.push(2,4);
}
int main()
{
	//TestQ1();
	//TestQ2();
	TestQ3();
	//TestQ4();
	//Test5();
	return 0;
}
