#include <iostream>
using namespace std;
/*Example 1:
假定我们需要为某个类设计一个可以对所有类型
(包括普通的int/long...,提供了clone方法的复杂类型CComplexObject,及由该类派生的类)
进行操作的函数clone,下面,先用OO的方法来考虑一下解决方案.
看到前面的条件,最先跳进你脑子里的肯定是Interface,pure virtual function等等.
对于我们自己设计的类CComplexObject而言,这不是问题,
但是,对于基本数据类型呢?还有那些没有提供clone方法的复杂类型呢?
(这时候你可能会想,要是Java该多easy,所有类都默认从Object派生,
而Object已提供了一个默认的clone方法,但是,要使类真正支持clone,
还必须implements Cloneable,所以,同样也不能避免这里遇到的麻烦).
下面是一个可能的解决方案:*/
//template <class T,bool IsClonable>
//class XContainer
//{
//	void clone(T *pObj)
//	{
//		if (IsClonable)
//		{
//			pObj->clone();
//		}
//		else
//		{
//			//实现不克隆的的方法
//		}
//	}
//};
//为了实现这一点,我们可以在我们的模板类中用enum定义一个trait,
//以标示类是否为Clonable类,然后在原模板类内部引入一个traits提取类Traits,
//通过对该类进行specilizing,以根据不同的trait提供不同的实现.

class CComplexObject
{
public:
	void clone()
	{
		cout<<"is clone"<<endl;
	}
};
template<class T,bool IsClonable>
class XContainer
{	
public:
	enum
	{
		Clonable=IsClonable
	};
	void clone(T* pObj)
	{
		Traits<Clonable>().clone(pObj);
	}
	template<bool flag>
	class Traits
	{

	};
	template<>
	class Traits<true>
	{
	public:
		void clone(T *pObj)
		{
			cout<<"before"<<endl;
			pObj->clone();
			cout<<"after"<<endl;
		}

	};
	template<>
	class Traits<false>
	{
	public:
		void clone(T *pObj)
		{
			cout<<"non"<<endl;
		}
	};
};
void test1()
{
	int *p1=0;
	CComplexObject *p2=0;
	XContainer<int,false> n1;
	XContainer<CComplexObject,true> n2;
	n1.clone(p1);
	n2.clone(p2);
}
int main()
{
	test1();
	return 0;
}


struct __xtrue_type { }; // define two mark-type
struct __xfalse_type { };

class CComplexObject // a demo class
{
public:
	virtual void clone() { cout << "in clone" << endl; }
};

class CDerivedComplexObject : public CComplexObject // a demo derived class
{
public:
	virtual void clone() { cout << "in derived clone" << endl; }
};

// A general edtion of Traits
template <typename T>
struct Traits
{
	typedef __xfalse_type has_clone_method; // trait 1: has clone method or not? All types defaultly has no clone method.
};

// Specialized edtion for ComplexObject
template <>
struct Traits<CComplexObject>
{
	typedef __xtrue_type has_clone_method;
};

template <typename T>
class XContainer
{
	template <typename flag>
	class Impl
	{
	};
	template <>
	class Impl <__xtrue_type>
	{
	public:
		void clone(T* pObj)
		{
			pObj->clone();
		}
	};
	template <>
	class Impl <__xfalse_type>
	{
	public:
		void clone(T* pObj)
		{
		}
	};
public:
	void clone(T* pObj)
	{
		Impl<Traits<T>::has_clone_method>().clone(pObj);
	}
};

void main()
{
	int* p1 = 0;
	CComplexObject c2;
	CComplexObject* p2 = &c2;
	CDerivedComplexObject c3;
	CComplexObject* p3 = &c3; 

	XContainer<int> n1;
	XContainer<CComplexObject> n2;
	XContainer<CComplexObject> n3;

	n1.clone(p1);
	n2.clone(p2);
	n3.clone(p3);
}

//1、内嵌型别
//template <class T>
//struct Type
//{
//	//定义了一个内嵌类型
//	typedef T valuetype;
//	T* _ptr;
//	Type(T *ptr=0)
//		:_ptr(ptr)
//	{
//
//	}
//	T operator*()const
//	{
//		return *_ptr;
//	}
//};
//
////模板函数
//template <class I>
////foo这个函数的形参是I类型的引用，I由迭代器Type决定，所以返回值是I类型的即迭代器中type
////是什么类型
//typename I::valuetype foo(const I &x)
//{
//	return *x;
//};
//
//void Test()
//{
//	int num=10;
//	//x是Type类型的，由num的地址初始化
//	//调用构造，_ptr指向num
//	Type<int> x(&num);
//	//I就是int的
//	cout<<foo(x);
//}
//int main()
//{
//	Test();
//	return 0;
//}
////trait类
//template <class T>
//class Trait
//{
//
//};

struct TrueType
{
	bool Get()
	{
		return true;
	}
};
struct FalseType
{
	bool Get()
	{
		return false;
	}
};

template <class Type>
struct Trait
{
	typedef FalseType ISPODTYPE;

};
template<>
struct Trait<bool>
{
	typedef TrueType ISPODTYPE;
};
template<>
struct Trait<int>
{
	typedef TrueType ISPODTYPE;
};
template<>
struct Trait<unsigned int>
{
	typedef TrueType ISPODTYPE;
};
template<>
struct Trait<char>
{
	typedef TrueType ISPODTYPE;
};
template<>
struct Trait<unsigned char>
{
	typedef TrueType ISPODTYPE;
};
template<>
struct Trait<short>
{
	typedef TrueType ISPODTYPE;
};
template<>
struct Trait<unsigned short>
{
	typedef TrueType ISPODTYPE;
};
template <>
struct Trait< long>
{
	typedef TrueType     ISPODTYPE;
};

template <>
struct Trait< unsigned long >
{
	typedef TrueType     ISPODTYPE;
};

template <>
struct Trait< long long >
{
	typedef TrueType     ISPODTYPE;
};

template <>
struct Trait< unsigned long long>
{
	typedef TrueType     ISPODTYPE;
};

template <>
struct Trait< float>
{
	typedef TrueType     ISPODTYPE;
};

template <>
struct Trait< double>
{
	typedef TrueType     ISPODTYPE;
};

template <>
struct Trait< long double >
{
	typedef TrueType     ISPODTYPE;
};

template <class _Tp>
struct Trait< _Tp*>
{
	typedef TrueType     ISPODTYPE;
};
//模板函数
template <class T>
void Copy (const T* src , T* dst, size_t size, FalseType )
{
	cout<<"__FalseType:" <<typeid( T).name ()<<endl;
	for (size_t i = 0; i < size ; ++i)
	{
		dst[i ] = src[ i];
	}
}

template <class T>
void Copy (const T* src , T* dst, size_t size, TrueType )
{
	cout<<"__TrueType:" <<typeid( T).name ()<<endl;
	memcpy(dst , src, size*sizeof (T));
}

template <class T>
void Copy (const T* src , T* dst, size_t size)
{
	cout<<"__TrueType:" <<typeid( T).name ()<<endl;

	if (Trait <T>:: ISPODTYPE().Get ())
	{
		memcpy(dst , src, size*sizeof (T));
	}
	else
	{
		for (size_t i = 0; i < size ; ++i)
		{
			dst[i ] = src[ i];
		}
	}
}


void Test1 ()
{
	string s1 [10] = {"1", "2", "3" , "4444444444444444444444444" };
	string s2 [10] ={"11", "22", "33" };
	Copy(s1 , s2, 10, Trait <string>:: ISPODTYPE());
	Copy(s1 , s2, 10);

	int a1 [10] = {1,2,3};
	int a2 [10] = {0};
	Copy(a1 , a2, 10, Trait<int>:: ISPODTYPE());
	Copy(a1 , a2, 10);
}

int main()
{
	Test1();
	return 0;
}