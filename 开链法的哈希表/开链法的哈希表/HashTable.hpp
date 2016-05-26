#pragma once 

#include<iostream>
#include<vector>
#include<string>
using namespace std;

//素数表
const int _PrimeSize = 28;
static const unsigned long _PrimeList[_PrimeSize] =
{
	53ul, 97ul, 193ul, 389ul, 769ul,
	1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
	49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
	1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
	50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
	1610612741ul, 3221225473ul, 4294967291ul
};
//使用开链法实现哈希表数据结构
template<class T>
struct HASHFUNC
{

	size_t operator()(const T &key)
	{
		return key;
	}
};
template<>
struct HASHFUNC<string>
{
	size_t operator()(const string &key)
	{
		size_t sum = 0;
		for (size_t i = 0; i < key.size(); i++)
		{
			sum += key[i];
		}
		return sum;
	}
};
//key/value形式
template<class K,class V> 
struct HashTableNode
{
	K _key;
	V _value;
	HashTableNode<K,V> *_next;
	HashTableNode()
	{}
	HashTableNode(const K &key, const V &value) :_key(key), _value(value), _next(NULL)
	{}
};

template<class K, class V, class T = HASHFUNC<K> >
class  HashTable
{
	typedef HashTableNode<K, V> Node;
	typedef HashTable<K, V> Table;
public:
	HashTable() :_size(0)
	{
		_table.resize(53);
	}
	//拷贝构造
	HashTable(const Table &ht)
	{
		HashTable tmp;
		tmp._table.resize(ht._table.size());
		for (size_t i = 0; i < tmp._table.size(); ++i)
		{
			Node *cur = ht._table[i];
			while (cur)
			{
				tmp.Insert(cur->_key, cur->_value);
				cur = cur->_next;
			}
		}
		//swap(_table, tmp._table);
		//swap(_size, tmp._size);
		Swap(tmp);
	}
	Table& operator=(Table ht)
	{
		Swap(ht);
		return *this;
	}
	~HashTable()
	{
		size_t i = 0;
		//size_t i = _size;
		while (_size>0)
		{
			if (_table[i] == NULL)
				i++;
			else
			{
				Node *del = _table[i];
				_table[i] = del->_next;
				delete del;
			}
			_size--;
		}
	}
public:
	//插入key/value元素
	bool Insert(const K &key,const V &value)
	{
		ExpandCapacity();
		Node *NewNode = new Node(key, value);
		size_t index = HashFunc(key);
		if (_table[index] == NULL)
		{
			_size++;
		}
		if (_table[index] != NULL)
		{
			Node *IfRepeat = _table[index];
			while (IfRepeat)
			{
				if (IfRepeat->_key == key)
					return false;
				IfRepeat = IfRepeat->_next;
			}
		}
		Node *tmp = _table[index];
		_table[index] = NewNode;
		NewNode->_next = tmp;
		return true;
	}

	//寻找节点
	Node* Find(const K &key)
	{
		size_t index = HashFunc(key);
		if (_table[index] == NULL)
			return NULL;
		Node *cur = _table[index];
		while (cur->_key != key&&cur)
		{
			cur = cur->_next;
		}
		if (cur == NULL)
			return NULL;
		else
			return cur;
	}


	bool Remove(const K &key)
	{
		size_t index = HashFunc(key);
		//没有节点
		if (_table[index] == NULL)
			return false;
		Node *prev = NULL;
		Node *cur = _table[index];

		while (cur&&cur->_key != key)
		{
			prev = cur;
			cur = cur->_next;
		}
		if (cur == NULL)
			return false;

		//如果是头节点
		if (prev == NULL)
		{
			delete cur;
			_table[index] = NULL;
			return true;
		}
		//中间节点或者尾节点
		prev->_next = cur->_next;
		delete cur;
		return true;
	}


	//打印哈希表
	void PrintHashTable()
	{
		for (size_t i = 0; i < _table.size(); ++i)
		{
			if (_table[i] == NULL)
				cout << "NULL" << endl;
			else
			{
				Node *cur = _table[i];
				while (cur)
				{
					cout << cur->_key << ":" << cur->_value << "->";
					cur = cur->_next;
				}
				cout << "NULL" << endl;
			}
		}
	}
protected:
	void Swap(Table &ht)
	{
		swap(_table, ht._table);
		swap(_size, ht._size);
	}
	//哈希函数
	size_t HashFunc(const K &key)
	{
		return T()(key) % _table.size();
	}
	//增大顺序表的容量
	void ExpandCapacity()
	{
		HashTable<K, V> tmp;
		if (_size == _table.size())
		{
			size_t i = 0;
			while (i<_PrimeSize)
			{
				if (_table.size() >= _PrimeList[i])
					i++;
				else
				{
					tmp._table.resize(_PrimeList[i]);
					break;
				}
			}
			for (size_t i = 0; i < _table.size(); ++i)
			{
				Node *cur = _table[i];
				while (cur)
				{
					tmp.Insert(cur->_key, cur->_value);
					cur = cur->_next;
				}
			}
			//swap(_table, tmp._table);
			//swap(_size, tmp._size);
			Swap(tmp);
		}
	}
private:
	size_t _size;   //有效元素
	vector<Node*> _table;  //哈希表
};

void TestInt()
{
	HashTable<int, int>ht;
	ht.Insert(1, 2);
	ht.Insert(54, 2);
	ht.Insert(107, 2);
	//HashTable<int, int>ht2(ht);
	//HashTable<int, int>ht1;
	//ht1 = ht;
	cout << ht.Find(1)->_key << ":" << ht.Find(1)->_value << endl;
	//ht.PrintHashTable();
	//ht.Remove(1);
	//ht.PrintHashTable();
}
void TestStr()
{
	HashTable<string, string>ht;
	ht.Insert("asd", "sda");
	ht.Insert("asssd", "sdda");
	ht.Insert("assd", "sdfa");
}