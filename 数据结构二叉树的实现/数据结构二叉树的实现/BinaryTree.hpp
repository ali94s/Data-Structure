#ifndef _BINARYTREE_HPP
#define _BINARYTREE_HPP
#include<iostream>
#include<queue>
using namespace std;

template<class T>
struct BinaryTreeNode
{
	T _value;
	BinaryTreeNode<T> *_left;
	BinaryTreeNode<T> *_right;
	BinaryTreeNode(const T &value = 0) :_value(value), _left(NULL), _right(NULL)
	{}
};
template<class T>
class BinaryTree
{
public:
	//默认构造
	BinaryTree() :_root(NULL)
	{}
	//构造函数	参数为常量应该用const修饰
	BinaryTree(const T *a, const T &invalid)
	{
		_root = _CreateBinaryTree(a,invalid);
	}
	//拷贝构造
	BinaryTree(const BinaryTree<T> &b)
	{
		_root = _CopyBinaryTree(b._root);
	}
	//赋值运算符(采用现代式写法)
	BinaryTree<T>& operator=(BinaryTree<T> b)
	{
		swap(_root, b._root);
		return _root;
	}
	//析构函数
	~BinaryTree()
	{
		_Destroy(_root);
		_root = NULL;
	}





public:
	//二叉树的遍历
	//前序遍历
	void PrevOrder()
	{
		_PrevOrder(_root);
	}
	//中序遍历
	void InOrder()
	{
		_InOrder(_root);
	}
	//后序遍历
	void PostOrder()
	{
		_PostOrder(_root);
	}
	//层序遍历
	void LevelOrder()
	{
		_LevelOrder(_root);
	}
	//二叉树节点个数
	size_t Size()
	{
		return _Size(_root);
	}
	//二叉树的深度
	size_t Depth()
	{
		return _Depth(_root);
	}
	//二叉树叶子节点的个数
	size_t LeafSize()
	{
		return _LeafSize(_root);
	}
protected:

	//谦虚遍历递归写法
	void _PrevOrder(BinaryTreeNode<T> *root)
	{
		if (root != NULL)
		{
			_Visit(root);
			_PrevOrder(root->_left);
			_PrevOrder(root->_right);
		}
	}
	//中序遍历递归写法
	void _InOrder(BinaryTreeNode<T> *root)
	{
		if (root != NULL)
		{
			_InOrder(root->_left);
			_Visit(root);
			_InOrder(root->_right);
		}
	}
	//后序遍历递归写法
	void _PostOrder(BinaryTreeNode<T> *root)
	{
		if (root != NULL)
		{
			BinaryTreeNode<T> *cur = root;
			_PostOrder(root->_left);
			if (cur->_right!=NULL)
				_PostOrder(root->_right);
			_Visit(root);
		}
	}
	//用一个队列来辅助完成层序遍历
	void _LevelOrder(BinaryTreeNode<T> *root)
	{
		if (root != NULL)
		{
			queue<BinaryTreeNode<T> *>q;
			q.push(root);
			while (!q.empty())
			{
				BinaryTreeNode<T> *tmp = q.front();
				_Visit(tmp);
				q.pop();
				if (tmp->_left != NULL)
					q.push(tmp->_left);
				if (tmp->_right != NULL)
					q.push(tmp->_right);
			}
		}
	}

	size_t _Size(BinaryTreeNode<T> *root)
	{
		if (root == NULL)
			return 0;
		//返回左右子树节点的个数再加上根节点
		return _Size(root->_left) + _Size(root->_right) + 1;
	}

	size_t _Depth(BinaryTreeNode<T> *root)
	{
		if (root == NULL)
			return 0;
		size_t ld;
		size_t rd;
		ld = _Depth(root->_left);
		rd = _Depth(root->_right);
		//返回左右深度之和再加根节点
		return (ld > rd ? ld : rd) + 1;
	}

	size_t _LeafSize(BinaryTreeNode<T> *root)
	{
		//空树返回0
		if (root == NULL)
			return 0;
		//左右没有子节点返回1
		if (root->_left == NULL&&root->_right == NULL)
			return 1;
		return _LeafSize(root->_left) + _LeafSize(root->_right);
	}


	void _Visit(BinaryTreeNode<T> *node)
	{
		cout << node->_value << " ";
	}
protected:
	//用字符串来构造二叉树
	BinaryTreeNode<T> *_CreateBinaryTree(const T* &s,const T &invalid)
	{
		BinaryTreeNode<T> *NewNode = NULL;
		if ((*s) != '\0' && (*s) != invalid)
		{
			NewNode = new BinaryTreeNode<T>(*s);
			NewNode->_left = _CreateBinaryTree(++s,invalid);
			NewNode->_right = _CreateBinaryTree(++s,invalid);
		}
		return NewNode;
	}


	//拷贝构造
	BinaryTreeNode<T> *_CopyBinaryTree(BinaryTreeNode<T> *s)
	{
		BinaryTreeNode<T> *NewNode = NULL;
		if (s != NULL)
		{
			NewNode = new BinaryTreeNode<T>(s->_value);
			NewNode->_left = _CopyBinaryTree(s->_left);
			NewNode->_right = _CopyBinaryTree(s->_right);
		}
		return NewNode;
	}
	//析构函数销毁二叉树
	void _Destroy(BinaryTreeNode<T>* &root)
	{
		if (root != NULL)
		{
			_Destroy(root->_left);
			_Destroy(root->_right);
		}
		delete root;
	}
private:
	BinaryTreeNode<T> *_root;
};
#endif  //_BINARYTREE_HPP