#pragma once
#include <iostream>
#include <stack>
#include <queue>
#include <assert.h>
using namespace std;
//��������
//��������---ֱ�Ӳ�������
//int a[10]={2,0,4,9,5,6,5,7,5,5};
//int a[9]={4,1,3,6,8,2,7,9,9};
int a[10]={2,5,4,9,3,6,8,7,1,0};
int b[10]={20,20,100,3,55,54,87,99,19,23};
int c[10]={73,22,93,43,55,14,28,65,39,81};
void InsertSort(int *a,size_t size)
{
	assert(a);
	for (size_t i=1;i<size;i++)
	{
		int end=i-1;
		int temp=a[i];
		while (end>=0&&temp<a[end])
		{
			a[end+1]=a[end];
			end--;
		}
		a[end+1]=temp; //temp��whileѭ����֮�����end+1������С�ĺ��棩
	}
}
//��������---ϣ������
//�ֶν��в�������
void ShellSort(int *a1,size_t size)
{
	assert(a);
	int gap=size;
	while (gap>1)
	{
		gap=gap/3+1;
		for (size_t i=gap;i<size;i++)
		{
			int index=i;
			int end=index-gap;
			int temp=a[index];
			while (end>=0&&temp<a[end])
			{
				a[end+gap]=a[end];
				end-=gap;
			}
			a[end+gap]=temp;
		}
	}
	

}
//ѡ������--ѡ������
//void SelectSort(int *a,size_t size)
//{
//	assert(a);
//	for (size_t i=0;i<size;i++)
//	{
//		int min=a[i];
//		//int max=a[i];
//		for (size_t j=i+1;j<size;j++)
//		{
//			/*if (max<a[j])
//			{
//				max=a[j];
//			}*/
//			if (min>a[j])
//			{
//				swap(a[j],min);
//			}
//		}
//		//a[size-1-i]=max;
//
//		a[i]=min;
//	}
//}
void SelectSort(int *a1,size_t size)
{
	//1/2���еĳ���
	for(size_t left=0,right=size-1;left<=right;left++,right--)
	{
		int min=left;
		int max=right;
		for(size_t j=left;j<=right;j++)
		{
			if(a[min]>a[j])
			{
				min=j;
			}
			else if(a[max]<a[j])
			{
				max=j;
			}
		}
		if(min!=left)
		{
			if(min==right&&max==left)
			{
				swap(a[min],a[left]);
			}
			//���ֵ�����Ҫ������
			else if(min!=right&&max==left)
			{
				swap(a[max],a[right]);
				swap(a[min],a[left]);
			}
			else
			{
				swap(a[min],a[left]);
			}
		}
		if(max!=right)
		{
			swap(a[max],a[right]);
		}
	}
}
void AdjustDown(int *a,size_t size,size_t root)
{
	assert(a);
	size_t child=root*2+1;
	while(child<size)
	{
		if(child+1<size&&a[child]<a[child+1])
		{
			child++;
		}
		if (a[child]>a[root])
		{
			swap(a[child],a[root]);
			root=child;
			child=root*2+1;
		}
		else
		{
			break;
		}

	}
}
//ѡ������--������(����--���)
void HeapSort(int *a,size_t size)
{
	assert(a);
	int i=(size-2)/2;// ��һ����Ҷ�ӽ����±�
	for (int i=(size-2)/2;i>=0;i--)
	{
		AdjustDown(a,size,i);
	}
	for (size_t i=0;i<size;i++)
	{
		swap(a[0],a[size-i-1]);
		AdjustDown(a,size-i-1,0);
	}

}
//��������
int PartionSort(int *a1,int left,int right)
{
	int begin=left;
	int end=right-1;
	int key=a[right];
	while(begin<end)
	{
		while(begin<end&&a[begin]<key)
		{
			begin++;
		}
		while(end>begin&&a[end]>key)
		{
			end--;
		}
		if (end!=begin)
		{
			swap(a[end],a[begin]);
			end--;
			begin++;
		}
	}
	if (a[begin]>key)
	{
		swap(a[begin],a[right]);
		return begin;
	}
	else
	{
		return begin;
	}
}
//��������--�ݹ�˼��
void QuickSort(int *a1,int left,int right)
{
	assert(a);
	if (left<right)
	{
		int boundary=PartionSort(a,left,right);
		QuickSort(a,left,boundary-1);
		QuickSort(a,boundary+1,right);
	}
}
//��������---����ȡ��
//void QuickSort(int *a1,int left,int right)
//{
//	assert(a);
//	int mid=left+(right-left)/2;
//	if (left<right)
//	{
//		if (a[left]<a[right])
//		{
//			if (a[right]<a[mid])
//			{
//				swap(a[mid],a[right]);
//			}
//			if (a[left]>a[mid])
//			{
//				swap(a[mid],a[left]);
//			}
//
//		}
//		else
//		{
//			if (a[left]<a[mid])
//			{
//				swap(a[mid],a[left]);
//			}
//			if (a[right]>a[mid])
//			{
//				swap(a[mid],a[right]);
//			}
//		}
//		swap(a[mid],a[right]);
//
//		int boundary=PartionSort(a,left,right);
//		QuickSort(a,left,boundary-1);
//		QuickSort(a,boundary+1,right);
//	}
//
//}
//���������и�����ʱ�ò�������
void QuickSort(int *a1,int left,int right)
{
	assert(a);
	if(right-left<13)
	{
		InsertSort(a,right-left+1);
	}
	if (left<right)
	{
		int boundary=PartionSort(a,left,right);
		QuickSort(a,left,boundary-1);
		QuickSort(a,boundary+1,right);
	}
}
//��������ǵݹ�ʵ��
//	�ֶ�����ջ���洢ÿ�ηֿ���ŵ���ʼ�㣬ջ�ǿ�ʱѭ����ȡ������ջ��
//	void QuickSort(int *a1,int left,int right)
//{
//	stack<int> s1;
//
//	if(left<right)
//	{
//		int boundary=PartionSort(a,left,right);
//		if (boundary-1-left>1)
//		{
//			s1.push(left);
//			s1.push(boundary-1);
//		}
//		if (right-(boundary+1)>1)
//		{
//			s1.push(boundary+1);
//			s1.push(right);
//		}
//		while (!s1.empty())
//		{
//			int r=s1.top();
//			s1.pop();
//			int l=s1.top();
//			s1.pop();
//			boundary=PartionSort(a,l,r);
//			if (boundary-1-l>1)
//			{
//				s1.push(l);
//				s1.push(boundary-1);
//			}
//			if (r-(boundary+1)>1)
//			{
//				s1.push(boundary+1);
//				s1.push(r);
//			}
//		}
//	}
//
//}
//�ϲ�
void GetMerge(int *a,int begin1,int end1,int begin2,int end2,int *temp)
{
	int i=0;
	while(begin1<=end1&&begin2<=end2)
	{
		if (a[begin1]<a[begin2])
		{
			temp[i++]=a[begin1];
			begin1++;
		}
		else
		{
			temp[i++]=a[begin2];
			begin2++;
		}
	}
	while(begin1<=end1)
	{
		temp[i++]=a[begin1++];
	}
	while(begin2<=end2)
	{
		temp[i++]=a[begin2++];
	}
}
//�ֽ�
void _MergeSort(int *a,int left,int right)
{
	if (right-left<1)
	{
		return;
	}
	int mid=left+(right-left)/2;
	_MergeSort(a,left,mid);
	_MergeSort(a,mid+1,right);
	int *temp=new int[right-left+1];
	GetMerge(a,left,mid,mid+1,right,temp);
	memcpy(a+left,temp,(right-left+1)*sizeof(int));

}
//�鲢����
void MergeSort(int *a,size_t size)
{
	_MergeSort(a,0,size-1);
}
void Print(int *a,size_t size)
{
	for (size_t i=0;i<size;i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;

}
//�鲢����ķǵݹ�д��
void MergeSortNor(int *a1,size_t size)
{
	//�ȷֳ�һ��һ����Ȼ����������ϲ�
	int temp[10];
	size_t begin=0;
	size_t gap=0;
	size_t end=begin+gap+1;
	for (gap;gap<size;gap+=begin-end)
	{
		for(begin=0;begin<size;begin+=gap*2+2)//����и��ǵ��ŵģ�����
		{
			end=begin+gap+1;
			if(begin+gap<size&&end<size&&end+gap<size)
			{
				GetMerge(a,begin,begin+gap,end,end+gap,temp+begin);
			}
			else
			{
				if(begin+gap<size)
				{
					if (end<size)
					{
						GetMerge(a,begin,begin+gap,end,size-1,temp+begin);
					}
					else
						//[8��9][9��9]----����Խ��
						//[8��9][10��9]
						GetMerge(a,begin,begin+gap,size,size-1,temp+begin);
				}
				else
				{
					//[8��9][9��9]
					//[8��9][10��9]
					GetMerge(a,begin,size-1,size,size-1,temp+begin);
				}
			}

		}
		memcpy(a,temp,sizeof(int)*size);

	}
	
}
//������Ӧ�ÿ���
int PartionSortLink(int *a1,int left,int right)
{
	int prev=left-1;
	int cur=left;
	int key=a[right];
	while(cur<right)
	{
		if (a[cur]<key)
		{

			prev++;
			if (prev!=cur)
			{
				swap(a[prev],a[cur]);
			}
		}
		if (cur==right-1)
		{
			prev++;
			swap(a[prev],a[right]);

		}
		cur++;
	}
	return prev;
}
void QuickSortLink(int *a1,int left,int right)
{
	assert(a);
	if (left<right)
	{
		int boundary=PartionSortLink(a,left,right);
		QuickSortLink(a,left,boundary-1);
		QuickSortLink(a,boundary+1,right);
	}
}
//��������---���ݼ��е�ʱ��Ӧ�ã������ݶ����ظ�
//ʱ�临�Ӷ�O��n+range�� �ռ临�Ӷ� O(range)
void CountSort(int *a1,size_t size)
{
	//�����ֵ����Сֵ
	int max=b[0];
	int min=b[0];
	for(size_t i=1;i<size;i++)
	{
		if (b[i]>max)
		{
			max=b[i];
		}
		if (b[i]<min)
		{
			min=b[i];
		}
	}
	int temp[98];
	//****�ǵ�Ҫ��temp�е����ֵ����Ϊ��
	memset(temp,0,sizeof(int)*(max-min+1));
	//��temp������
	for (size_t i=0;i<size;i++)
	{
		temp[b[i]-min]++;
	}
	//����tempת��a;
	for(size_t j=0,i=0;i<max-min+1;i++)
	{
		while (temp[i]--)
		{
			b[j++]=i+min;
		}
	}
}
//��������---LSD
int GetMaxBit(int *c1,size_t size)
{
	int bit=1;
	int max=10;
	for (size_t i=0;i<size;i++)
	{
		//���ںţ���c[i]=100��max=100�����ʱ�����û��=,��ô����һλ
		//��������������Ϊ�ˣ��Ӽ�
		if (c[i]>=max) 
		{
			bit++;
			max*=10;
		}
	}
	return bit;
}
void DigitSortLSD(int *c1,size_t size)
{
	//���յ�λ���λһ��һ������
	/*�������λ��*/
	int maxBit=GetMaxBit(c,size);
	//ֱ�Ӷ�ַ��һ�������з�����
	//һ�����ݷ���ʲôλ������ǰһ�����ݾ���
	int *temp=new int[size];

	int count[10];  //����۲���� �±�0-9��ʾÿ��λ���м����� eg��22 42 ���λΪ2��λ����2����
	int start[10];  //ÿ��λ�ϵĵ�һ��������ʼλ��
	//*********count,start���
	memset(temp,0,size*sizeof(int));
	for (int digit=0,max=1;digit<maxBit;digit++)
	{

		memset(count,0,10*sizeof(int));
		memset(start,0,10*sizeof(int));
		for(size_t i=0;i<size;i++)
		{
			int num=c[i]/max%10; //����λ��
			count[num]++;
		}
		start[0]=0;
		for (size_t j=1;j<10;j++)
		{
			start[j]=count[j-1]+start[j-1];
		}
		for (size_t i=0;i<size;i++)
		{
			int num=c[i]/max%10;
			temp[start[num]++]=c[i];
		}
		memcpy(c,temp,size*sizeof(int));
		max=max*10;
	}
}
//ð������
void BubbleSort(int *a1,size_t size)
{
	for (size_t i=0;i<size;i++)
	{
		for (size_t j=0;j<size-i-1;j++)
		{
			if (a[j]>a[j+1])
			{
				swap(a[j],a[j+1]);
			}
		}
	}
}
void test()
{
	//int a[10]={2,5,4,9,3,6,8,7,1,0};
	//InsertSort(a,10);
	//Print(a,10);
	//ShellSort(a,10);
	BubbleSort(a,10);
	Print(a,10);
	//SelectSort(a,10);
	/*Print(a,10);*/
	/*HeapSort(a,10);
	Print(a,10);*/
	//QuickSort(a,0,9);
	//QuickSort(a,10);
	/*MergeSortNor(a,10);
	Print(a,10);*/
	//QuickSortLink(a,0,9);
	//CountSort(b,10);
	//DigitSortLSD(c,10);
	//Print(c,10);
	//Print(b,10);
	/*MergeSort(a,10);
	Print(a,10);*/
	//int d[9]={9,5,4,1,3,6,8,7,9};
	//SelectSort(a,9);
	// Print(a,9);
}