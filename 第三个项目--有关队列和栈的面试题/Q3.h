//3、使用两个队列实现一个栈
//入栈：1-2-3-4
//出栈：4-3-2-1
//
#ifndef Q3_H
#define Q3_H
#include <queue>
using namespace std;
template <class T>
class Stack
{
public:
	Stack(){}
	~Stack(){}
	void Push(const T & val)
	{
		q1.push(val);
	}
	T Pop()
	{
		if (q1.size()==0&&q2.size()==0)
		{
			return 0;
		}
		T temp;
		int icount=(int)q1.size()-1;
		if(icount<0)
		{
			icount=(int)q2.size()-1;
			swap(q1,q2);
			
		}
		for(int i=0;i<icount;i++)
		{
			q2.push(q1.front());
			q1.pop();

		}
		temp=q1.front();
		q1.pop();
		
		return temp;
	}
private:
	queue<T> q1;
	queue<T> q2;
};
#endif