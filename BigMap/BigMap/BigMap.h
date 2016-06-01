#pragma once 
#include<iostream>

//解决大数据的相关问题   
//但是只能返回这个数据是否在已有的文件中是否存在
class BigMap
{
public:
	BigMap(const int &n) :_n(new int[n / 32 + 1])
	{
		//将数组中的每个元素置为0
		memset(_n, 0, (n / 32 + 1) * 4);
	}
	void Insert(const int &data)
	{
		//对data进行/32锁定数组下标
		size_t index = IndexFunc(data);
		//对data进行%32锁定比特位
		size_t bitnumber = BitNumberFunc(data);
		//相应比特位置为1表示存在
		_n[index] |= 1 << (bitnumber - 1);
	}
	void Remove(const int &data)
	{
		size_t index = IndexFunc(data);
		size_t bitnumber = BitNumberFunc(data);
		//置为0  表示没有这个数
		_n[index] &= ~(1 << (bitnumber - 1));
	}
	void Test(const int &data)
	{
		size_t index = IndexFunc(data);
		size_t bitnumber = BitNumberFunc(data);
		int tmp = _n[index] & (1 << (bitnumber - 1));
		if (!tmp)
			printf("this number is not here!\n");
		else
			printf( "yes!it is here!\n" );
	}
protected:
	size_t IndexFunc(const int &key)
	{
		return key / 32;
	}
	size_t BitNumberFunc(const int &key)
	{
		return key % 32;
	}
private:
	int *_n;
};