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


//直接插入排序
void InsertSort(int *a, size_t len)
{
	assert(a);
	size_t end = 1;
	while (end<len)
	{
		//单趟排序
		int tmp = a[end];
		int i = end-1;
		for (i; i >= 0; i--)
		{
			if (a[i] > tmp)
				a[i + 1] = a[i];
			else
				break;
		}
		//跳出循环要么遇到不大于tem的元素  要么i找到了头   此时i = -1
		//将此时的i后面的位置 置为tmp
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

//希尔排序
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

//选择排序
void SelectSort(int *a, size_t len)
{
	assert(a);
	int Max = 0;
	int j = 0;
	while (j < len)
	{
		Max = 0;
		//每次选出所给序列的最大值
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


//堆排序
//向下调整
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
	//建堆
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


//冒泡排序
void BubbleSort(int *a, size_t len)
{
	assert(a);
	for (int i = 0; i < len; ++i)
	{
		//每趟排序选出所给序列中的最大值
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

//三数取中
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
//快速排序
//挖坑法
void QuickSort(int *a, int start,int end)
{
	assert(a);
	if (start >= end)
		return;
	size_t mid = GetMid(a, start, end - 1);
	swap(a[mid], a[start]);
	//选取第一个数为key
	int key = a[start];
	int left = start;
	int right = end - 1;

	while (left < right)
	{
		//(必须)首先要从后往前找第一个比key小的数
		while (left < right&&a[right] >= key)
		{
			--right;
		}
		if (a[right] < key)
			swap(a[right], a[left]);
		//从前往后找第一个比key大的数
		while (left < right&&a[left]<=key)
		{
			++left;
		}
		if (a[left]>key)
			swap(a[left],a[right]);
	}
	//一次排序后将所有比key小的放在key的左边  大的放在右边
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

//与挖坑法相似的算法
//快速排序
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
		//找第一个比key大的数
		while (left < right&&a[left] <= key)
		{
			left++;
		}
		//找第一个比key小的数
		while (left<right&&a[right]>=key)
		{
			right--;
		}
		if (left == right)
			break;
		swap(a[left], a[right]);
	}
	//如果区间的数只有两个  且第一个小于第二个
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
//非递归快速排序
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
		//选取第一个数为key
		int key = a[start];
		int left = start;
		int right = end - 1;

		while (left < right)
		{
			//(必须)首先要从后往前找第一个比key小的数
			while (left < right&&a[right] >= key)
			{
				--right;
			}
			if (a[right] < key)
				swap(a[right], a[left]);
			//从前往后找第一个比key大的数
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
//归并排序
//计数排序
//基数排序

