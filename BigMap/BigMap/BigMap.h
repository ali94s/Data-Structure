#pragma once 
#include<iostream>

//��������ݵ��������   
//����ֻ�ܷ�����������Ƿ������е��ļ����Ƿ����
class BigMap
{
public:
	BigMap(const int &n) :_n(new int[n / 32 + 1])
	{
		//�������е�ÿ��Ԫ����Ϊ0
		memset(_n, 0, (n / 32 + 1) * 4);
	}
	void Insert(const int &data)
	{
		//��data����/32���������±�
		size_t index = IndexFunc(data);
		//��data����%32��������λ
		size_t bitnumber = BitNumberFunc(data);
		//��Ӧ����λ��Ϊ1��ʾ����
		_n[index] |= 1 << (bitnumber - 1);
	}
	void Remove(const int &data)
	{
		size_t index = IndexFunc(data);
		size_t bitnumber = BitNumberFunc(data);
		//��Ϊ0  ��ʾû�������
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