#include<iostream>
using namespace std;
#include<vector>
#include<assert.h>
//�º���
template<class T>
struct MAX
{
	//����()   ͨ������ĵ�����ʵ�ַº���
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
//��һ��Ĭ�ϵ�ģ�����  ��������Ĭ�ϵ�����
//������ģ��������Ը��ݴ�����������Ҫ�����Ķѵ�����
template<class T,class F = MAX<T>>
class Heap
{
public:
	Heap()
	{}
	//��һ��������MAX<T>�Ķ�����Ĭ�ϳ�ʼ��com
	Heap(const T *a, const size_t size, F com = MAX<T>()) :_type(com)
	{
		for (int i = 0; i < size; i++)
		{
			_a.push_back(a[i]);
		}
		for (int i = (size - 2) / 2; i >= 0; i--)
		{
			//�ҵ���һ����Ҷ�ӽڵ������µ���
			_AdjustDown(i,size);
		}
	}

	void Push(T data)
	{
		_a.push_back(data);
		for (int i = _a.size() - 1; i >= 0; i = (i - 1) / 2)
		{
			//ÿ��pushһ��Ԫ��ʱֻ��Ҫ���ϵ�������(ֻ�ı�һ����֧�Ľṹ)
			_AdjustUp(i);
		}
	}
	//ɾ�����ڵ�  һ�㶼��ɾ���Ѷ�Ԫ��
	void Pop()
	{
		if (!_a.empty())
			return;
		swap(_a[0], _a[_a.size() - 1]);
		_a.pop_back();
		_AdjustDown(0);
	}
	//������
	void Sort()
	{
		//����Ǹ������������������һ������
		//���Ǹ���С�����Ǹ�����
		for (int i = 1; i < _a.size(); i++)
		{
			swap(_a[0], _a[_a.size() - i]);
			_AdjustDown(0, _a.size() - i);
		}
	}
protected:
	//���µ���
	void _AdjustDown(size_t parent,size_t len)
	{
		//��������ܳ��ֵĸ�����С������ĺ��ӵ�����ÿ��Ҫ��������
		while (parent < len)
		{
			size_t child = parent * 2 + 1;

			if (child + 1 < len && _type(_a[child+1], _a[child]))
			{
				child++;
			}

			//ͨ���º���ʹ����������
			if (child < len && _type(_a[child] ,_a[parent]))
			{
				swap(_a[parent], _a[child]);
			}
			parent = child;
		}
	}
	//���ϵ���
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
	F _type; //����ѵ�����
};