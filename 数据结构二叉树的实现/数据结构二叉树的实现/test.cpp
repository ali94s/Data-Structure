#include"BinaryTree.hpp"

int main()
{
	char *a = "123##4##56";
	BinaryTree<char> b(a, '#');
	b.PostOrder();
	cout << endl;
	b.LevelOrder();
	cout << endl;
	cout << b.Depth() << endl;
	cout << b.LeafSize() << endl;
	system("pause");
	return 0;
}