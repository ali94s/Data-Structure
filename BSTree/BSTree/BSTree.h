#pragma once 
#include<iostream>
using namespace std;

//K V形式的搜索二叉树
template <class K,class V>
struct BSTreeNode
{
	K _key;
	V _value;
	BSTreeNode *_left;
	BSTreeNode *_right;

	BSTreeNode(K key, V value) :_key(key), _value(value), _left(NULL), _right(NULL)
	{}
};

template<class K,class V>
class BSTree
{
	typedef BSTreeNode<K,V> Node;
public:
	BSTree() :_root(NULL)
	{}
	~BSTree()
	{
		_Destroy(_root);
		_root == NULL;
	}
//非递归实现
	bool Insert(const K &key, const V &value)
	{
		if (_root == NULL)
			_root = new Node(key, value);
		else
		{
			Node *cur = _root;
			Node *parent = NULL;
			//找到要插入的位置
			while (cur)
			{
				parent = cur;
				if (cur->_key > key)
				{
					cur = cur->_left;
					if (cur == NULL)
					{
						parent->_left = new Node(key, value);
						return true;
					}
				}
				else if (cur->_key < key)
				{
					cur = cur->_right;
					if (cur == NULL)
					{
						parent->_right = new Node(key, value);
						return true;
					}
				}
				else
					return false;
			}
		}
		return true;
	}
	bool Remove(const K &key)
	{
		return _Remove(_root, key);
	}
	Node* Find(const K &key)
	{
		Node *cur = _root;
		while (cur)
		{
			if (cur->_key > key)
				cur = cur->_left;
			else if (cur->_key < key)
				cur = cur->_right;
			else
				return cur;
		}
		return NULL;
	}

	//中序遍历
	void InOrder()
	{
		_InOrder(_root);
	}

	//递归实现
	bool InsertR(const K &key, const V &value)
	{
		return _InsertR(_root, key, value);
	}
	bool RemoveR(const K &key)
	{
		return _RemoveR(_root,key);
	}
	Node* FindR(const K &key)
	{
		return _FindR(_root,key);
	}

protected:
	bool _InsertR(Node*& root, const K &key, const V &value)
	{
		if (root == NULL)
		{
			root = new Node(key, value);
			return true;
		}
		if (root->_key > key)
			_InsertR(root->_left, key, value);
		else if (root->_key < key)
			_InsertR(root->_right, key, value);
		else
			return false;
	}
	bool _RemoveR(Node*& root, const K &key)
	{
		if (root == NULL)
			return false;
		if (root->_key>key)
			_RemoveR(root->_left, key);
		else if (root->_key < key)
			_RemoveR(root->_right, key);
		else
		{
			if (root->_left == NULL)
				root = root->_right;
			else if (root->_right==NULL)
				root = root->_left;
			else
			{
				Node *leftNode = root->_right;
				while (leftNode->_left)
					leftNode = leftNode->_left;
				root->_key = leftNode->_key;
				root->_value = leftNode->_value;
				_Remove(root->_right, root->_value);
			}
		}
		return true;
	}
	Node* _FindR(Node*& root, const K &key)
	{
		if (root == NULL)
			return NULL;
		if (root->_key > key)
			_FindR(root->_left, key);
		else if (root->_key < key)
			_FindR(root->_right, key);
		else
			return root;
	}
		//只需要递归一次  所以参数必须传引用
	bool _Remove(Node*& root, const K &key)
	{
		Node *cur = root;
		Node *parent = NULL;
		while (cur)
		{
			if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
				
			else if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;

			}	
			else
				break;
		}
		if (cur == NULL)
			return false;
		//左子树是空
		if (cur->_left == NULL)
		{
			if (cur == root)
			{
				root = cur->_right;
			}
			else if (cur == parent->_left)
				parent->_left = cur->_right;
			else
				parent->_right = cur->_right;
			delete cur;
			return true;
		}
		//右子树是空
		else if (cur->_right == NULL)
		{
			if (cur == root)
				root = cur->_left;
			else if (cur == parent->_left)
				parent->_left = cur->_left;
			else
				parent->_right = cur->_left;
			delete cur;
			return true;
		}
		//左右子树都不是空
		else
		{
			Node *leftNode = cur->_right;
			while (leftNode->_left)
			{
				leftNode = leftNode->_left;
			}
			cur->_key = leftNode->_key;
			cur->_value = leftNode->_value;
			_Remove(cur->_right, leftNode->_key);
		}
		return true;
	}
	void _InOrder(Node *root)
	{
		if (root == NULL)
			return;
		_InOrder(root->_left);
		cout << root->_key<<" ";
		_InOrder(root->_right);
	}
	void _Destroy(Node*& root)
	{
		if (root == NULL)
			return;
		_Destroy(root->_left);
		_Destroy(root->_right);
		delete root;
	}
private:
	Node *_root;
};




void test()
{
	int a[] = { 5, 6, 7, 1, 2, 3, 4, 8, 9, 0 };
	BSTree<int, int> b;
	for (int i = 0; i < 10; ++i)
	{
		b.InsertR(a[i], i);
	}
	b.InOrder();
	cout << endl;
	b.RemoveR(1);
	b.InOrder();
	cout << endl;
	//b.Remove(2);
	//b.InOrder();
	//cout << endl;
	//b.Remove(3);
	//b.InOrder();
	//cout << endl;
	//b.Remove(4);
	//b.InOrder();
	//cout << endl;
	//b.Remove(5);
	//b.InOrder();
	//cout << endl;
	//b.Remove(6);
	//b.InOrder();
	//cout << endl;
	//b.Remove(7);
	//b.InOrder();
	//cout << endl;
	//b.Remove(8);
	//b.InOrder();
	//cout << endl;
	//b.Remove(9);
	//b.InOrder();
	//cout << endl;
	//b.Remove(0);
	//b.InOrder();
	//cout << endl;
	BSTreeNode<int,int> *ret = b.FindR(2);
	if (ret == NULL)
		cout << "NULL" << endl;
	else
		cout << ret->_key << endl;
}