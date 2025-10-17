#pragma once
#include<iostream>
using namespace std;

enum Colour
{
	RED, BLACK
};

template<class T>
struct RBTreeNode
{
	T _data;
	RBTreeNode<T>* _left;
	RBTreeNode<T>* _right;
	RBTreeNode<T>* _parent;
	Colour _col;
	RBTreeNode(const T& data)
		:_data(data)
		, _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
	{

	}

};
template<class T,class Ref,class Ptr>
struct TreeIterator
{
	typedef	RBTreeNode<T> Node;
	typedef TreeIterator<T, Ref, Ptr> Self;
	Node* _node;

	TreeIterator(Node* node)
		:_node(node)
	{

	}
	Ref operator*()
	{
		return _node->_data;
	}
	Ptr operator->()
	{
		return  &_node->_data;
	}

	Self& operator++()
	{
		//当前右孩子不为空，下一个为柚子树中序最左节点
		if (_node->_right)
		{
			Node* min = _node->_right;
				while(min->_left)
				{
					min = min->_left;
				}
			_node = min;
		}
		else	// 当前节点右为空，下一个孩子是父亲左的那个祖先节点
		{
			Node* cur = _node;
			Node* parent = cur->_parent;
			while (parent && cur == parent->_right)
			{
				cur = parent;
				parent = parent->_parent;
			}
			_node = parent;
		}
		return *this;
	}
	bool operator!=(const Self& s)const
	{
		return _node != s._node;
	}
	bool operator==(const Self& s)const
	{
		return _node == s._node;
	}

};


template<class K, class T,class KeyOfT>
class RBTree
{
	typedef RBTreeNode<T> Node;
public:
	typedef TreeIterator<T,T&,T*> Iterator;
	Iterator Begin()
	{
		Node* min = _root;
		while (min && min->_left)
		{
			min = min->_left;
		}
		return Iterator(min);
	}
	Iterator End()
	{
		return Iterator(nullptr);
	}

	bool Insert(const T& data)
	{

		if (_root == nullptr)//将根节点初始化成为黑色
		{
			_root = new Node(data);
			_root->_col = BLACK;

			return true;
		}
		KeyOfT kot;
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)//遍历到最下方
		{
			if (kot(cur->_data) < kot(data))
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (kot(cur->_data) >kot(data))
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}

		cur = new Node(data);
		cur->_col = RED;
		if (kot(parent->_data) < kot(data))
		{
			parent->_right = cur;
		}
		if (kot(parent->_data) > kot(data))
		{
			parent->_left = cur;
		}
		cur->_parent = parent;
		while (parent && parent->_col == RED)
		{
			Node* grandfather = parent->_parent;
			if (!grandfather) break; // 如果grandfather为空，退出循环
			if (grandfather->_left == parent)
			{
				Node* uncle = grandfather->_right;
				//叔叔存在且为红
				if (uncle && uncle->_col == RED)
				{
					parent->_col = BLACK;
					uncle->_col = BLACK;
					grandfather->_col = RED;

					//继续向上处理
					cur = grandfather;
					parent = cur->_parent;
				}

				else//叔叔不存在或叔叔为黑,旋转+变色
				{
					if (cur == parent->_left)
					{
						//     g
						//  p    u
						//c 
					//右单旋
						RotateR(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;

					}
					else
					{
						//     g
						//  p     u
						//    c 
						// 左右单旋
						RotateL(parent);
						RotateR(grandfather);
						cur->_col = BLACK;
						grandfather->_col = RED;
					}
					break;
				}
			}
			else//grandfather->_right==parent
			{
				//   g
				// u   p
				Node* uncle = grandfather->_left;
				// 叔叔存在且为红,变色即可
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					// 继续往上处理
					cur = grandfather;
					parent = cur->_parent;
				}
				else // 叔叔不存在，或者存在且为黑
				{
					// 情况二：叔叔不存在或者存在且为黑
					// 旋转+变色
					//   g
					// u   p
					//       c
					if (cur == parent->_right)
					{
						RotateL(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else//双旋+变色
					{	//    g
						// u     p
						//     c
						RotateR(parent);
						RotateL(grandfather);
						cur->_col = BLACK;
						grandfather->_col = RED;
					}

					break;
				}
			}

		}

		_root->_col = BLACK;
		return true;
	}
	void InOrder()
	{
		_InOrder(_root);

	}
	//bool IsBalance() {
	   // if (_root == nullptr) return true;
	   // if (_root->_col == RED) return false;

	   // // 计算参考值（最左路径黑节点数）
	   // Node* leftMost = _root;
	   // int blackRef = 0;
	   // while (leftMost) {
	   //	 if (leftMost->_col == BLACK) ++blackRef;
	   //	 leftMost = leftMost->_left;
	   // }
	   // return Check(_root, 0, blackRef);
	//}
	bool IsBalance()
	{
		if (_root == nullptr)
			return true;

		if (_root->_col == RED)
			return false;

		// 黑色节点数量参考值
		Node* leftMost = _root;
		int blackRef = 0;
		while (leftMost)
		{
			if (leftMost->_col == BLACK)
				++blackRef;

			leftMost = leftMost->_left;
		}

		return Check(_root, 0, blackRef);
	}

	int Height()
	{
		return _Height(_root);
	}

	int Size()
	{
		return _Size(_root);
	}

	Node* Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (kot(cur->_data) < key)
			{
				cur = cur->_right;
			}
			else if (kot(cur->_data) > key)
			{
				cur = cur->_left;
			}
			else
			{
				return cur;
			}
		}
		return nullptr;
	}


private:
	//bool Check(Node* cur, int blackNum, const int blackRef) {
	//	if (cur == nullptr)
	//		return blackNum == blackRef;  // 修正1：正确判断路径终点

	//	// 修正2：避免根节点访问_parent
	//	if (cur != _root && cur->_col == RED && cur->_parent->_col == RED) {
	//		cout << "连续红节点：" << cur->_kv.first << endl;
	//		return false;
	//	}

	//	// 更新黑节点计数
	//	int newBlackNum = (cur->_col == BLACK) ? blackNum + 1 : blackNum;

	//	// 修正3：独立传递左右子树计数
	//	int leftCount = newBlackNum;
	//	int rightCount = newBlackNum;
	//	bool leftValid = Check(cur->_left, leftCount, blackRef);
	//	bool rightValid = Check(cur->_right, rightCount, blackRef);

	//	return leftValid && rightValid;
	//}
	//	 void _InOrder(Node* root)
	//	 {
	//		 if (root == nullptr)
	//			 return;
	//		 _InOrder(root->_left);
	//		 cout << root->_kv.first<<" ";
	//		 _InOrder(root->_right);
	//	 }


	int _Size(Node* root)
	{
		return root == nullptr ? 0 : _Size(root->_left) + _Size(root->_right) + 1;
	}

	int _Height(Node* root)
	{
		if (root == nullptr)
			return 0;
		int leftHeight = _Height(root->_left);
		int rightHeight = _Height(root->_right);
		return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
	}

	bool Check(Node* cur, int blackNum, const int blackNumRef)
	{
		if (cur == nullptr)
		{
			if (blackNum != blackNumRef)
			{
				cout << "黑色节点的数量不相等" << endl;
				return false;
			}

			return true;
		}

		if (cur->_col == RED && cur->_parent && cur->_parent->_col == RED)
		{
			cout << cur->_kv.first << "->" << "连续的红色节点" << endl;
			return false;
		}

		if (cur->_col == BLACK)
			++blackNum;

		return Check(cur->_left, blackNum, blackNumRef)
			&& Check(cur->_right, blackNum, blackNumRef);
	}
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;

		Node* parentParent = parent->_parent;

		subL->_right = parent;
		parent->_parent = subL;

		if (parent == _root)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		else
		{
			if (parentParent->_left == parent)
			{
				parentParent->_left = subL;
			}
			else
			{
				parentParent->_right = subL;
			}

			subL->_parent = parentParent;
		}
	}

	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;

		Node* parentParent = parent->_parent;

		subR->_left = parent;
		parent->_parent = subR;

		if (parent == _root)
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		else
		{
			if (parentParent->_left == parent)
			{
				parentParent->_left = subR;
			}
			else
			{
				parentParent->_right = subR;
			}

			subR->_parent = parentParent;
		}
	}

	Node* _root = nullptr;

};