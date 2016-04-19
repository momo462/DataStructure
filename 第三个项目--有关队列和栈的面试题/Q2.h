//使用两个栈实现一个队列
//如1，2，3，4，5顺序入S1栈————————〉（顶）5，4，3，2，1
//由LIFO决定顺序出S1栈然后进入S2栈——————〉（顶）1，2，3，4，5
//此时出栈即为符合队列的特点（FIFO）
//方法1
//方法2
//方法3:入栈：都在s1，
//      出栈：如果s2为空就将s1的数据都弹到s2中，之后弹出栈顶不空的话，就一直弹出战顶

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

