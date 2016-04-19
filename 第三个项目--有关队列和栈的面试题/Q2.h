//ʹ������ջʵ��һ������
//��1��2��3��4��5˳����S1ջ������������������������5��4��3��2��1
//��LIFO����˳���S1ջȻ�����S2ջ��������������������1��2��3��4��5
//��ʱ��ջ��Ϊ���϶��е��ص㣨FIFO��
//����1
//����2
//����3:��ջ������s1��
//      ��ջ�����s2Ϊ�վͽ�s1�����ݶ�����s2�У�֮�󵯳�ջ�����յĻ�����һֱ����ս��

#ifndef Q2_H
#define Q2_H
#include <stack>
#include <iostream>
using namespace std;
template <class T>
class Queue
{
private:
	stack<T> s1;
	stack<T> s2;
	size_t _size;
public:
	Queue(){}
	~Queue(){}
	void Push(const T & val)
	{
		s1.push(val);
	}
	T& Pop()
	{
		
		if(s2.empty())
		{
			while(!s1.empty())
			{
				T temp=s1.top();
				s2.push(temp);
				s1.pop();
			}
		}
		T tmp=s2.top();
		s2.pop();
		return tmp;
		
	}
};
#endif

