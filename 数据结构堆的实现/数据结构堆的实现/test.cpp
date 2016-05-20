#include"Heap.hpp"


int main()
{

	int a[] = { 1, 2, 3, 4, 6, 7, 5, 4, 9, 12, 23, 43, 11 };
	int len = sizeof(a) / sizeof(a[0]);
	MAX<int> com;
	MIN<int> com1;
	//使用了两个模板参数 
	//Heap<int> h(a, len,com);
	Heap<int, MIN<int>> h(a, len, com1);
	//默认构造的是大堆
	Heap<int> h2(a, len);

	h.Sort();
	system("pause");
	return 0;
}