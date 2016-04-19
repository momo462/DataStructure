#include <iostream>
#include <stack>
#include <queue>
#include <assert.h>
using namespace std;
//��ȡ�Թ��ĵ�
void GetMazeMap(int *a,int row,int col)
{
	FILE *fout=fopen("MazeMap.txt","r");
	assert(fout);
	for (int i=0;i<row;i++)
	{
		for(int j=0;j<col;)
		{
			//ֻ�ж���1��0��ʱ������뵽a��������һֱ������
			char ch=fgetc(fout);
			if (ch=='0'||ch=='1')
			{
				a[i*10+j]=ch-'0';
				j++;
			}
		}
	}

}
//��ӡ�Թ�
void PrintMazeMap(int *a,int row,int col)
{
	for (int i=0;i<row;i++)
	{
		for (int j=0;j<col;j++)
		{
			cout<<a[i*10+j]<<" ";
		}
		cout<<endl;
	}
}

//���Թ��е�λ�ñ�ʾ
struct pos
{
	int row;
	int col;
};
//��������Ƿ���Խ���
bool checkIsAccess(int *a,pos p,int rowsize,int colsize)
{
	if (p.row>=0&&p.col>=0&&p.row<rowsize&&p.col<colsize
		&&a[p.row*10+p.col]==0)
	{
		return true;
	}
	return false;

}
bool checkIsCrash(int *a,pos p,int rowsize,int colsize)
{
	if (p.row>=0&&p.col>=0&&p.row<rowsize&&p.col<colsize
		&&a[p.row*10+p.col]==2)
	{
		return true;
	}
	return false;
}
//�����ַ���--����
//queue<pos> MazePath(int *a,int rowsize,int colsize,pos entry)
//{
//	//ÿ��һ���������У�ֱ��crash��������ÿһ��Ԫ�س����У�ͬʱ�ж��ǲ��ǻ�����������
//	//�����ߣ�������ԣ��ͽ����У�ֱ������Ԫ��Ϊ3�ĳ����У�Ȼ��2���ڳ�ȥ
//	assert(a);
//	pos cur=entry;
//	pos next=cur;
//	a[entry.row*10+entry.col]=2;
//	queue<pos> q;
//	q.push(entry);
//	while (true)
//	{
//		//��
//		next=cur;
//		next.col=cur.col-1;
//		if (checkIsAccess(a,next,rowsize,colsize))
//		{
//			a[next.row*10+next.col]=2;
//			q.push(next);
//			cur=next;
//			continue;
//		}
//		//��
//		next=cur;
//		next.col=cur.col+1;
//		if (checkIsAccess(a,next,rowsize,colsize))
//		{
//			a[next.row*10+next.col]=2;
//			q.push(next);
//			cur=next;
//			continue;
//		}
//		//��
//		next=cur;
//		next.row=cur.row+1;
//		if (checkIsAccess(a,next,rowsize,colsize))
//		{
//			a[next.row*10+next.col]=2;
//			q.push(next);
//			cur=next;
//			continue;
//		}
//		//��
//		next=cur;
//		next.row=cur.row-1;
//		if (checkIsAccess(a,next,rowsize,colsize))
//		{
//			a[next.row*10+next.col]=2;
//			q.push(next);
//			cur=next;
//			continue;
//		}
//		a[cur.row*10+cur.col]=3;
//		cur=q.front();
//		
//	}
//	return q;
//}
////���Ž�
stack<pos> MazePath(int *a,int rowsize,int colsize,pos entry)
{
	assert(a);
	stack<pos> s;
	a[entry.row*10+entry.col]=2;
	s.push(entry);
	while(!s.empty())
	{
		pos cur=s.top();
		pos next=cur;
		//���λ���Ѿ�������β
		if(cur.row==rowsize-1)
		{
			return s;
		}

		//����
		next=cur;
		next.col=cur.col-1;
		if (checkIsAccess(a,next,rowsize,colsize))
		{
			s.push(next);
			a[next.row*10+next.col]=2;
			continue;
		}
		//����
		next=cur;
		next.col=cur.col+1;
		if (checkIsAccess(a,next,rowsize,colsize))
		{
			s.push(next);
			a[next.row*10+next.col]=2;
			continue;
		}
		//����
		next=cur;
		next.row=cur.row-1;
		if (checkIsAccess(a,next,rowsize,colsize))
		{
			s.push(next);
			a[next.row*10+next.col]=2;
			continue;
		}
		//����
		next=cur;
		next.row=cur.row+1;
		if (checkIsAccess(a,next,rowsize,colsize))
		{	
			s.push(next);
			a[next.row*10+next.col]=2;
			continue;
		}
		pos top = s.top();
		a[top.row* colsize + top.col] = 3;
		s.pop();
	}
	return s;
}
//�ڶ��ַ���--�ݹ�
//?��μ�¼�ֲ��
bool crash=true;
pos MazePath(int *a,int rowsize,int colsize,pos entry)
{
	assert(a);
	pos left=entry;
	left.col=entry.col-1;
	pos right=entry;
	right.col=entry.col+1;
	pos up=entry;
	up.row=entry.row-1;
	pos down=entry;
	down.row=entry.row+1;
	if (crash)
	{
		a[entry.row*10+entry.col]=2;
	}
	if (entry.col==colsize-1||entry.row==rowsize-1)
	{
		pos final=entry;
		return final;
	}
	if (crash)
	{
		a[entry.row*10+entry.col]=2;
	}
	if (checkIsAccess(a,left,rowsize,colsize))
	{
		crash=true;
		MazePath(a,rowsize,colsize,left);
		//a[left.row*10+left.col]=2;
		//return left;
	}
	else if(checkIsAccess(a,right,rowsize,colsize))
	{
		crash=true;
		MazePath(a,rowsize,colsize,right);
		//a[right.row*10+right.col]=2;
		//return right;
	}
	else if(checkIsAccess(a,up,rowsize,colsize))
	{
		crash=true;
		MazePath(a,rowsize,colsize,up);
		//a[up.row*10+up.col]=2;
		//return up;
	}
	else if(checkIsAccess(a,down,rowsize,colsize))
	{
		crash=true;
		MazePath(a,rowsize,colsize,down);
		//a[down.row*10+down.col]=2;
		//return down;
	}
	else 
	{
		if (checkIsCrash(a,left,rowsize,colsize))
		{
			crash=false;
			a[entry.row*10+entry.col]=3;
			MazePath(a,rowsize,colsize,left);
			
			//return left;
		}
		else if(checkIsCrash(a,right,rowsize,colsize))
		{
			crash=false;
			a[entry.row*10+entry.col]=3;
			MazePath(a,rowsize,colsize,right);
			
			//return right;
		}
		else if(checkIsCrash(a,up,rowsize,colsize))
		{
			crash=false;
			a[entry.row*10+entry.col]=3;
			MazePath(a,rowsize,colsize,up);
			
			//return up;
		}
		else if(checkIsCrash(a,down,rowsize,colsize))
		{
			crash=false;
			a[entry.row*10+entry.col]=3;
			MazePath(a,rowsize,colsize,down);
			//return down;
		}
	}

}

//��һ�ַ���-ջ
//stack<pos> MazePath(int *a,int rowsize,int colsize,pos entry)
//{
//	assert(a);
//	stack<pos> s;
//	a[entry.row*10+entry.col]=2;
//	s.push(entry);
//	while(!s.empty())
//	{
//		pos cur=s.top();
//		pos next=cur;
//		//���λ���Ѿ�������β
//		if(cur.row==rowsize-1)
//		{
//			return s;
//		}
//
//		//����
//		next=cur;
//		next.col=cur.col-1;
//		if (checkIsAccess(a,next,rowsize,colsize))
//		{
//			s.push(next);
//			a[next.row*10+next.col]=2;
//			continue;
//		}
//		//����
//		next=cur;
//		next.col=cur.col+1;
//		if (checkIsAccess(a,next,rowsize,colsize))
//		{
//			s.push(next);
//			a[next.row*10+next.col]=2;
//			continue;
//		}
//		//����
//		next=cur;
//		next.row=cur.row-1;
//		if (checkIsAccess(a,next,rowsize,colsize))
//		{
//			s.push(next);
//			a[next.row*10+next.col]=2;
//			continue;
//		}
//		//����
//		next=cur;
//		next.row=cur.row+1;
//		if (checkIsAccess(a,next,rowsize,colsize))
//		{	
//			s.push(next);
//			a[next.row*10+next.col]=2;
//			continue;
//		}
//		//����
//		next=cur;
//		next.col=cur.col-1;
//		if (checkIsAccess(a,next,rowsize,colsize))
//		{
//			s.push(next);
//			a[next.row*10+next.col]=2;
//			continue;
//		}
//		//����
//		next=cur;
//		next.col=cur.col+1;
//		if (checkIsAccess(a,next,rowsize,colsize))
//		{
//			s.push(next);
//			a[next.row*10+next.col]=2;
//			continue;
//		}
//		
//		pos top = s.top();
//		a[top.row* colsize + top.col] = 3;
//		s.pop();
//	}
//	return s;
//}
//����
void TestMaze()
{
	int a[10][10];
	GetMazeMap((int *)a,10,10);
	/*PrintMazeMap((int *)a,10,10);*/
	pos entry={2,0};
	MazePath((int *)a,10,10,entry);
	PrintMazeMap((int *)a,10,10);

}
int main()
{
	TestMaze();
	return 0;
}