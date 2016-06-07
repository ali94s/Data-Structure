#include<iostream>
using namespace std;
#include<vector>
#include<assert.h>
//仿函数
template<class T>
struct MAX
{
	//重载()   通过对象的调用来实现仿函数
	bool operator()(T s1, T s2)
	{
		return s1 > s2 ? true : false;
	}
};

template<class T>
struct MIN
{
	bool operator()(T s1, T s2)
	{
		return s1 < s2 ? true : false;
	}
};
//给一个默认的模版参数  用来构建默认的最大堆
//给两个模版参数可以根据传参来构建想要构建的堆的类型
template<class T,class F = MAX<T>>
class Heap
{
public:
	Heap()
	{}
	//用一个匿名的MAX<T>的对象来默认初始化com
	Heap(const T *a, const size_t size, F com = MAX<T>()) :_type(com)
	{
		for (int i = 0; i < size; i++)
		{
			_a.push_back(a[i]);
		}
		for (int i = (size - 2) / 2; i >= 0; i--)
		{
			//找到第一个非叶子节点来向下调整
			_AdjustDown(i,size);
		}
	}

	void Push(T data)
	{
		_a.push_back(data);
		for (int i = _a.size() - 1; i >= 0; i = (i - 1) / 2)
		{
			//每当push一个元素时只需要向上调整即可(只改变一个分支的结构)
			_AdjustUp(i);
		}
	}
	//删除根节点  一般都是删除堆顶元素
	void Pop()
	{
		if (!_a.empty())
			return;
		swap(_a[0], _a[_a.size() - 1]);
		_a.pop_back();
		_AdjustDown(0);
	}
	//堆排序
	void Sort()
	{
		//如果是个最大堆则排序输出的是一个升序
		//若是个最小堆则是个降序
		for (int i = 1; i < _a.size(); i++)
		{
			swap(_a[0], _a[_a.size() - i]);
			_AdjustDown(0, _a.size() - i);
		}
	}
protected:
	//向下调整
	void _AdjustDown(size_t parent,size_t len)
	{
		//调整后可能出现的父亲是小与下面的孩子的所以每次要调整下面
		while (parent < len)
		{
			size_t child = parent * 2 + 1;

			if (child + 1 < len && _type(_a[child+1], _a[child]))
			{
				child++;
			}

			//通过仿函数使程序更加灵活
			if (child < len && _type(_a[child] ,_a[parent]))
			{
				swap(_a[parent], _a[child]);
			}
			parent = child;
		}
	}
	//向上调整
	void _AdjustUp(size_t child)
	{
		int parent = (child - 1) / 2;
		if (_a[child] > _a[parent])
		{
			swap(_a[child], _a[parent]);
		}
	}
	
private:
	vector<T> _a;
	F _type; //构造堆的类型
};