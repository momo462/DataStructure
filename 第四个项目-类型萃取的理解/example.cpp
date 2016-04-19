#include <iostream>
using namespace std;
/*Example 1:
�ٶ�������ҪΪĳ�������һ�����Զ���������
(������ͨ��int/long...,�ṩ��clone�����ĸ�������CComplexObject,���ɸ�����������)
���в����ĺ���clone,����,����OO�ķ���������һ�½������.
����ǰ�������,����������������Ŀ϶���Interface,pure virtual function�ȵ�.
���������Լ���Ƶ���CComplexObject����,�ⲻ������,
����,���ڻ�������������?������Щû���ṩclone�����ĸ���������?
(��ʱ������ܻ���,Ҫ��Java�ö�easy,�����඼Ĭ�ϴ�Object����,
��Object���ṩ��һ��Ĭ�ϵ�clone����,����,Ҫʹ������֧��clone,
������implements Cloneable,����,ͬ��Ҳ���ܱ��������������鷳).
������һ�����ܵĽ������:*/
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
//			//ʵ�ֲ���¡�ĵķ���
//		}
//	}
//};
//Ϊ��ʵ����һ��,���ǿ��������ǵ�ģ��������enum����һ��trait,
//�Ա�ʾ���Ƿ�ΪClonable��,Ȼ����ԭģ�����ڲ�����һ��traits��ȡ��Traits,
//ͨ���Ը������specilizing,�Ը��ݲ�ͬ��trait�ṩ��ͬ��ʵ��.

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

//1����Ƕ�ͱ�
//template <class T>
//struct Type
//{
//	//������һ����Ƕ����
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
////ģ�庯��
//template <class I>
////foo����������β���I���͵����ã�I�ɵ�����Type���������Է���ֵ��I���͵ļ���������type
////��ʲô����
//typename I::valuetype foo(const I &x)
//{
//	return *x;
//};
//
//void Test()
//{
//	int num=10;
//	//x��Type���͵ģ���num�ĵ�ַ��ʼ��
//	//���ù��죬_ptrָ��num
//	Type<int> x(&num);
//	//I����int��
//	cout<<foo(x);
//}
//int main()
//{
//	Test();
//	return 0;
//}
////trait��
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
//ģ�庯��
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