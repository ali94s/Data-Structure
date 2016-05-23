#pragma once 
#include<iostream>
#include<string>
using namespace std;

//枚举状态
enum State
{
	EMPTY,
	DELETE,
	EXIST
};

//原生类
template<class T>
struct __HashFunc
{
	size_t operator()(const string &key)
	{
		return key;
	}
		
};

//特化类
template<>
struct __HashFunc<string>
{
	size_t operator()(const string &key)
	{
		size_t sum = 0;
		for (size_t i = 0; i < key.size(); ++i)
		{
			sum += key[i];
		}
		return sum;
	}
};


//KEY/VALUE 形式
template<class T,class K>
struct HashTableNode
{
	T _key;
	K _value;
	HashTableNode()
	{}
	HashTableNode(const T &key, const K &value) :_key(key), _value(value)
	{}
};

//模板参数将仿函数传进去
template<class T, class K, class _HashFunc = __HashFunc<T>>
class HashTable
{
	typedef HashTableNode<T, K> Node;
public:
	//构造函数
	HashTable(size_t capacity=10) :_capacity(capacity),_size(0), _table(NULL), _state(NULL)
	{
		_table = new Node[_capacity];
		_state = new State[_capacity];
		//Hash表中的状态都初始化为空
		for (size_t i = 0; i < _capacity; i++)
		{
			_state[i] = EMPTY;
		}
		//不能使用memset  因为memste是按字节进行初始化的
	}
	//拷贝构造
	HashTable(const HashTable<T, K> &ht) :_capacity(0), _size(0), _table(NULL), _state(NULL)
	{
		//有问题?
		_capacity = ht._capacity;
		_size = ht._size;
		_table = new Node[_capacity];
		_state = new State[_capacity];
		//这里也不能使用memcpy  会出现浅拷贝
		for (int i = 0; i < _capacity; ++i)
		{
			_table[i] = ht._table[i];
			_state[i] = ht._state[i];
		}
	}

	//赋值运算符
	HashTable<T,K>& operator=(HashTable<T,K> ht)
	{
		Swap(ht);
		return *this;
	}


	//析构函数
	~HashTable()
	{
		if (_table != NULL)
		{
			delete[] _table;
			delete[] _state;
			_table = NULL;
			_state = NULL;
		}
	}

public:
	//插入
	bool Insert(const Node &node)
	{
		CheckCapacity();
		size_t index = HashFunc(node._key);
		size_t i = 1;
		size_t tmp = index;
		while (_state[tmp] == EXIST)
		{
			if (_table[tmp]._key == node._key)
				return false;
			tmp = index;
			tmp += i*i;
			if (tmp >= _capacity)
				tmp %= _capacity;
			i++;
		}
		index = tmp;
		_table[index] = node;
		_state[index] = EXIST;
		_size++;
	}
	

	//删除
	bool Delete(const Node &node)
	{
		size_t index = HashFunc(node._key);
		size_t i = 1;
		size_t tmp = index;
		while (_state[tmp] != EMPTY)
		{
			if (_table[tmp]._key == node._key)
			{
				_state[tmp] = DELETE;
				_size--;
				return true;
			}
			tmp = index;
			tmp += i*i;
			if (tmp >= _capacity)
				tmp %= _capacity;
			i++;
		}
		return false;
	}
	void Print()
	{
		for (size_t i = 0; i < _capacity; i++)
		{
			cout << (_table[i])._key << ":" << (_table[i])._value << ":" << _state[i] << endl;
		}
	}
	Node* Seek(const T &key)
	{
		size_t index = HashFunc(key);
		size_t tmp = index;
		int i = 0;
		while (_state[tmp] != EMPTY)
		{
			if (_table[tmp]._key == key)
				return &_table[tmp];
			tmp = index;
			tmp += i*i;
			if (tmp >= _capacity)
				tmp %= _capacity;
			i++;
		}
		return NULL;
	}
protected:
	void Swap(HashTable<T, K> &ht)
	{
		swap(_table, ht._table);
		swap(_state, ht._state);
		swap(_size, ht._size);
		swap(_capacity, ht._capacity);
	}
	void CheckCapacity()
	{
		//当载荷因子到达0.7的时候进行扩容
		if (_size * 10 / _capacity == 7)
		{
			HashTable<T, K> tmp(2 * _capacity);
			for (size_t i = 0; i < _capacity; ++i)
			{
				if (_state[i] == EXIST)
				{
					tmp.Insert(_table[i]);
				}
			}
			Swap(tmp);
		}
	}
	      
	size_t HashFunc(const T &key)
	{
		return _HashFunc()(key) % _capacity;
	}

private:
	Node* _table;   //哈希表
	State* _state;   //状态表
	size_t _capacity;  //容量
	size_t _size;     //有效元素个数
};