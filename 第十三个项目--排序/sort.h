#pragma once
#include <iostream>
#include <stack>
#include <queue>
#include <assert.h>
using namespace std;
//都是升序
//插入排序---直接插入排序
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
		a[end+1]=temp; //temp在while循环完之后放在end+1（比他小的后面）
	}
}
//插入排序---希尔排序
//分段进行插入排序
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
//选择排序--选择排序
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
	//1/2数列的长度
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
			//最大值在左边要先移走
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
//选择排序--堆排序(升序--大堆)
void HeapSort(int *a,size_t size)
{
	assert(a);
	int i=(size-2)/2;// 第一个非叶子结点的下标
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
//单趟排序
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
//快速排序--递归思想
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
//快速排序---三数取中
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
//快速排序中个数少时用插入排序
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
//快速排序非递归实现
//	手动利用栈来存储每次分块快排的起始点，栈非空时循环获取中轴入栈。
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
//合并
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
//分解
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
//归并排序
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
//归并排序的非递归写法
void MergeSortNor(int *a1,size_t size)
{
	//先分成一个一个的然后两两排序合并
	int temp[10];
	size_t begin=0;
	size_t gap=0;
	size_t end=begin+gap+1;
	for (gap;gap<size;gap+=begin-end)
	{
		for(begin=0;begin<size;begin+=gap*2+2)//如果有个是单着的？？？
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
						//[8，9][9，9]----数组越界
						//[8，9][10，9]
						GetMerge(a,begin,begin+gap,size,size-1,temp+begin);
				}
				else
				{
					//[8，9][9，9]
					//[8，9][10，9]
					GetMerge(a,begin,size-1,size,size-1,temp+begin);
				}
			}

		}
		memcpy(a,temp,sizeof(int)*size);

	}
	
}
//单链表应用快排
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
//计数排序---数据集中的时候应用，且数据多有重复
//时间复杂度O（n+range） 空间复杂度 O(range)
void CountSort(int *a1,size_t size)
{
	//求最大值和最小值
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
	//****记得要将temp中的随机值都置为空
	memset(temp,0,sizeof(int)*(max-min+1));
	//向temp中填数
	for (size_t i=0;i<size;i++)
	{
		temp[b[i]-min]++;
	}
	//遍历temp转入a;
	for(size_t j=0,i=0;i<max-min+1;i++)
	{
		while (temp[i]--)
		{
			b[j++]=i+min;
		}
	}
}
//基数排序---LSD
int GetMaxBit(int *c1,size_t size)
{
	int bit=1;
	int max=10;
	for (size_t i=0;i<size;i++)
	{
		//等于号，当c[i]=100，max=100，这个时候如果没有=,那么就少一位
		//尽量将除法化简为乘，加减
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
	//按照低位向高位一层一层排序
	/*求出最大的位数*/
	int maxBit=GetMaxBit(c,size);
	//直接定址在一个数组中放数据
	//一个数据放在什么位置有他前一个数据决定
	int *temp=new int[size];

	int count[10];  //方便观察调试 下标0-9表示每个位上有几个数 eg：22 42 则各位为2的位上有2个数
	int start[10];  //每个位上的第一个数的起始位置
	//*********count,start清空
	memset(temp,0,size*sizeof(int));
	for (int digit=0,max=1;digit<maxBit;digit++)
	{

		memset(count,0,10*sizeof(int));
		memset(start,0,10*sizeof(int));
		for(size_t i=0;i<size;i++)
		{
			int num=c[i]/max%10; //是哪位上
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
//冒泡排序
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