//#include "Stack.h"
//void Test1()
//{
//	Stack<int>s1;
//	Stack<int>s2(3,3);
//	Stack<int>s3(s2);
//	Stack<int>s4;
//	s4=s3;
//	s1.Push(1);
//	s1.Push(2);
//	s1.Push(3);
//	s1.Push(4);
//	cout<<s1.Top()<<endl;
//	cout<<s1.empty()<<endl;
//	cout<<s1.size()<<endl;
//	s1.Pop();
//	cout<<s1.size()<<endl;
//	s1.Pop();
//	cout<<s1.size()<<endl;
//	s1.Pop();
//	cout<<s1.size()<<endl;
//	s1.Pop();
//	cout<<s1.empty()<<endl;
//	s1.Pop();
//	cout<<s1.empty()<<endl;
//}
//void Test2()
//{
//	Stack<string>s1;
//	Stack<string>s2("abcd",3);
//	Stack<string>s3(s2);
//	Stack<string>s4;
//	s4=s3;
//	//因为插入的是字符串常量所以如果在pop中出栈不能改变原先的字符串
//	s1.Push("123");
//	s1.Push("456");
//	s1.Push("789");
//	s1.Push("101112");
//	string s=s1.Top();
//	cout<<s1.empty()<<endl;
//	cout<<s1.size()<<endl;
//	s1.Pop();
//	cout<<s1.size()<<endl;
//	s1.Pop();
//	cout<<s1.size()<<endl;
//	s1.Pop();
//	cout<<s1.size()<<endl;
//	s1.Pop();
//	cout<<s1.empty()<<endl;
//	s1.Pop();
//	cout<<s1.empty()<<endl;
//	
//}
//int main()
//{
//	//Test1();
//	Test2();
//	return 0;
//}