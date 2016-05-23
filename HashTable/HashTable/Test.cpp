#include"HashTable.h"

int main()
{

	HashTable<string,string> ht;

	//HashTableNode<int, int>h1(89, 2);
	//HashTableNode<int, int>h2(18, 3);
	//HashTableNode<int, int>h3(49, 4);
	//HashTableNode<int, int>h4(58, 5);
	//HashTableNode<int, int>h5(9, 6);
	//HashTableNode<int, int>h6(38, 7);
	//HashTableNode<int, int>h7(39, 8);
	//HashTableNode<int, int>h8(48, 9);
	//HashTable<int, int>ht1;
	//HashTable<int, int>ht2;
	HashTableNode<string, string>h1("adc", "sdqd");
	HashTableNode<string, string>h2("afdc", "sdid");
	HashTableNode<string, string>h3("agdc", "sdud");
	HashTableNode<string, string>h4("addc", "sdyd");
	HashTableNode<string, string>h5("adhc", "sdtd");
	ht.Insert(h1);
	ht.Insert(h2);
	ht.Insert(h3);
	ht.Insert(h4);
	ht.Insert(h5);
	//ht.Delete(h1);
	//ht.Insert(h7);
	//ht.Insert(h6);
	//ht.Insert(h7);
	//ht.Insert(h8);
	HashTable<string, string> ht1(ht);
	ht.Print();
	cout << "---------------------------------" << endl;
	ht1.Print();
	//HashTableNode<string, string> *ret = ht.Seek("abc");
	//if (ret != NULL)
	//	cout << ret->_key << ":" << ret->_value << endl;
	//else
	//	cout << "no!" << endl;
	system("pause");
	return 0;
}