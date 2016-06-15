#pragma once
#include<iostream>
using namespace std;
#include<assert.h>
#include<stack>

void Print(int *a, size_t len)
{
	for (size_t i = 0; i < len; ++i)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}


//ֱ�Ӳ�������
void InsertSort(int *a, size_t len)
{
	assert(a);
	size_t end = 1;
	while (end<len)
	{
		//��������
		int tmp = a[end];
		int i = end-1;
		for (i; i >= 0; i--)
		{
			if (a[i] > tmp)
				a[i + 1] = a[i];
			else
				break;
		}
		//����ѭ��Ҫô����������tem��Ԫ��  Ҫôi�ҵ���ͷ   ��ʱi = -1
		//����ʱ��i�����λ�� ��Ϊtmp
		a[i + 1] = tmp;
		end++;
	}
}
void TestInsertSort()
{
	//int a[] = { 1, 3, 2, 4, 6, 7, 5, 9, 8, 0 };
	int a[] = { 1,0,2,6,8 , 3, 2, 4, 6, 7, 5, 9, 8, 0 };
	InsertSort(a, sizeof(a) / sizeof(a[0]));
	Print(a, sizeof(a) / sizeof(a[0]));
}

//ϣ������
void ShellSort(int *a, size_t len)
{
	assert(a);
	size_t gap = len / 2;
	while (gap >= 1)
	{
		for (int i = 0; i < len; i++)
		{
			for (int j = i; j < len; j += gap)
			{
				if (a[i]>a[j])
					swap(a[i], a[j]);
			}
		}
		gap /= 2;
	}
}

void TestShellSort()
{
	//int a[] = { 1, 3, 2, 4, 6, 7, 5, 9, 8, 0 };
	int a[] = { 1, 0, 2, 6, 8, 3, 2, 4, 6, 7, 5, 9, 8, 0 };
	ShellSort(a, sizeof(a) / sizeof(a[0]));
	Print(a, sizeof(a) / sizeof(a[0]));
}

//ѡ������
void SelectSort(int *a, size_t len)
{
	assert(a);
	int Max = 0;
	int j = 0;
	while (j < len)
	{
		Max = 0;
		//ÿ��ѡ���������е����ֵ
		for (int i = 0; i < len - j; i++)
		{
			if (a[i]>a[Max])
				Max = i;
		}
		swap(a[Max], a[len - 1 - j]);
		j++;
	}
}

void TestSelectSort()
{
	//int a[] = { 1, 3, 2, 4, 6, 7, 5, 9, 8, 0 };
	int a[] = { 1, 0, 2, 6, 8, 3, 2, 4, 6, 7, 5, 9, 8, 0 };
	SelectSort(a, sizeof(a) / sizeof(a[0]));
	Print(a, sizeof(a) / sizeof(a[0]));
}


//������
//���µ���
void AdjustDown(int *a, size_t len, size_t parent)
{
	while (parent < len)
	{
		size_t child = parent * 2 + 1;
		if (child + 1 < len&&a[child] <= a[child + 1])
			child++;
		if (child < len&&a[parent] <= a[child])
			swap(a[child], a[parent]);
		parent = child;
	}
}
void HeapSort(int *a, size_t len)
{
	assert(a);
	//����
	for (int i = (len - 2) / 2; i >= 0; --i)
	{
		AdjustDown(a, len, i);
	}
	for (int j = 1; j < len; j++)
	{
		swap(a[0], a[len - j ]);
		AdjustDown(a, len - j, 0);
	}
}

void TestHeapSort()
{
	//int a[] = { 1, 3, 2, 4, 6, 7, 5, 9, 8, 0 };
	int a[] = { 1, 0, 2, 6, 8, 3, 2, 4, 6, 7, 5, 9, 8, 0 };
	HeapSort(a, sizeof(a) / sizeof(a[0]));
	Print(a, sizeof(a) / sizeof(a[0]));
}


//ð������
void BubbleSort(int *a, size_t len)
{
	assert(a);
	for (int i = 0; i < len; ++i)
	{
		//ÿ������ѡ�����������е����ֵ
		for (int j = 0; j < len - i - 1; ++j)
		{
			if (a[j]>a[j + 1])
				swap(a[j], a[j + 1]);
		}
	}
}

void TestBubbleSort()
{
	//int a[] = { 1, 3, 2, 4, 6, 7, 5, 9, 8, 0 };
	int a[] = { 1, 0, 2, 6, 8, 3, 2, 4, 6, 7, 5, 9, 8, 0 };
	BubbleSort(a, sizeof(a) / sizeof(a[0]));
	Print(a, sizeof(a) / sizeof(a[0]));
}

//����ȡ��
size_t GetMid(int *a, size_t left, size_t right)
{
	size_t mid = left + (right - left) / 2;
	if (a[left] > a[right])
	{
		if (a[right] > a[mid])
			return mid;
		else
		{
			if (a[left]>a[mid])
				return right;
			else
				return left;
		}
	}
	//a[left]<=a[right]
	else
	{
		if (a[mid] > a[left])
			return mid;
		else
			return left;
	}
}
//��������
//�ڿӷ�
void QuickSort(int *a, int start,int end)
{
	assert(a);
	if (start >= end)
		return;
	size_t mid = GetMid(a, start, end - 1);
	swap(a[mid], a[start]);
	//ѡȡ��һ����Ϊkey
	int key = a[start];
	int left = start;
	int right = end - 1;

	while (left < right)
	{
		//(����)����Ҫ�Ӻ���ǰ�ҵ�һ����keyС����
		while (left < right&&a[right] >= key)
		{
			--right;
		}
		if (a[right] < key)
			swap(a[right], a[left]);
		//��ǰ�����ҵ�һ����key�����
		while (left < right&&a[left]<=key)
		{
			++left;
		}
		if (a[left]>key)
			swap(a[left],a[right]);
	}
	//һ����������б�keyС�ķ���key�����  ��ķ����ұ�
	QuickSort(a, start, left);
	QuickSort(a, left + 1, end);
}
void TestQuickSort()
{
	//int a[] = { 1, 3, 2, 4, 6, 7, 5, 9, 8, 0 };
	int a[] = { 1, 0, 2, 6, 8, 3, 2, 4, 6, 7, 5, 9, 8, 0 };
	QuickSort(a, 0, sizeof(a) / sizeof(a[0]));
	Print(a, sizeof(a) / sizeof(a[0]));
}

//���ڿӷ����Ƶ��㷨
//��������
void QuickSort2(int *a, int start, int end)
{
	assert(a);
	if (start >= end)
		return;
	int key = a[end - 1];
	int left = start;
	int right = end - 2;
	while (left < right)
	{
		//�ҵ�һ����key�����
		while (left < right&&a[left] <= key)
		{
			left++;
		}
		//�ҵ�һ����keyС����
		while (left<right&&a[right]>=key)
		{
			right--;
		}
		if (left == right)
			break;
		swap(a[left], a[right]);
	}
	//����������ֻ������  �ҵ�һ��С�ڵڶ���
	if (a[left] < a[end - 1])
	{
		swap(a[left], a[end - 1]);
	}
	swap(a[left], a[end-1]);
	QuickSort2(a, start, left);
	QuickSort2(a, left+1, end);
}

void TestQuickSort2()
{
	int a[] = { 1, 3, 2, 4, 6, 7, 0, 9, 8, 5 };
	//int a[] = { 1, 0, 2, 6, 8, 3, 2, 4, 6, 7, 5, 9, 8, 0 };
	QuickSort2(a, 0,sizeof(a) / sizeof(a[0]));
	Print(a, sizeof(a) / sizeof(a[0]));
}
//�ǵݹ��������
void QuickSort1(int *a, int len)
{
	if (a == NULL || len <= 0)
		return;
	stack<int> s;
	s.push(len);
	s.push(0);
	while (!s.empty())
	{
		int start = s.top();
		s.pop();
		int end = s.top();
		s.pop();
		size_t mid = GetMid(a, start, end - 1);
		swap(a[mid], a[start]);
		//ѡȡ��һ����Ϊkey
		int key = a[start];
		int left = start;
		int right = end - 1;

		while (left < right)
		{
			//(����)����Ҫ�Ӻ���ǰ�ҵ�һ����keyС����
			while (left < right&&a[right] >= key)
			{
				--right;
			}
			if (a[right] < key)
				swap(a[right], a[left]);
			//��ǰ�����ҵ�һ����key�����
			while (left < right&&a[left] <= key)
			{
				++left;
			}
			if (a[left]>key)
				swap(a[left], a[right]);
		}
		if (start<left)
		{ 
			s.push(left);
			s.push(start);
	    }
		if (left+1<end)
		{
			s.push(end);
			s.push(left+1);
		}

	}

}
void TestQuickSort1()
{
	//int a[] = { 1, 3, 2, 4, 6, 7, 5, 9, 8, 0 };
	int a[] = { 1, 0, 2, 6, 8, 3, 2, 4, 6, 7, 5, 9, 8, 0 };
	QuickSort1(a, sizeof(a) / sizeof(a[0]));
	Print(a, sizeof(a) / sizeof(a[0]));
}
//�鲢����
//��������
//��������

