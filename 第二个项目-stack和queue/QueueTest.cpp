#include "Queue.h"
void test1()
{
	Queue<int>q1;
	q1.Push(1);
	q1.Push(2);
	q1.Push(3);
	q1.Push(4);
	Queue<int>q2(q1);
	Queue<int>q3;
	q3=q2;
	q1.Pop();
}
int main()
{
	test1();
	return 0;
}