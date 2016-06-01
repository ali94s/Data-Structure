#include"BigMap.h"

int main()
{
	BigMap bm(100);
	bm.Insert(1);
	bm.Insert(14);
	bm.Insert(2);
	bm.Insert(3);
	bm.Insert(100);
	bm.Test(1);
	bm.Remove(1);
	bm.Test(1);
	system("pause");
	return 0;
}