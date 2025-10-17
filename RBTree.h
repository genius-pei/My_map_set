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
		//��ǰ�Һ��Ӳ�Ϊ�գ���һ��Ϊ��������������ڵ�
		if (_node->_right)
		{
			Node* min = _node->_right;
				while(min->_left)
				{
					min = min->_left;
				}
			_node = min;
		}
		else	// ��ǰ�ڵ���Ϊ�գ���һ�������Ǹ�������Ǹ����Ƚڵ�
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

		if (_root == nullptr)//�����ڵ��ʼ����Ϊ��ɫ
		{
			_root = new Node(data);
			_root->_col = BLACK;

			return true;
		}
		KeyOfT kot;
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)//���������·�
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
			if (!grandfather) break; // ���grandfatherΪ�գ��˳�ѭ��
			if (grandfather->_left == parent)
			{
				Node* uncle = grandfather->_right;
				//���������Ϊ��
				if (uncle && uncle->_col == RED)
				{
					parent->_col = BLACK;
					uncle->_col = BLACK;
					grandfather->_col = RED;

					//�������ϴ���
					cur = grandfather;
					parent = cur->_parent;
				}

				else//���岻���ڻ�����Ϊ��,��ת+��ɫ
				{
					if (cur == parent->_left)
					{
						//     g
						//  p    u
						//c 
					//�ҵ���
						RotateR(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;

					}
					else
					{
						//     g
						//  p     u
						//    c 
						// ���ҵ���
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
				// ���������Ϊ��,��ɫ����
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					// �������ϴ���
					cur = grandfather;
					parent = cur->_parent;
				}
				else // ���岻���ڣ����ߴ�����Ϊ��
				{
					// ����������岻���ڻ��ߴ�����Ϊ��
					// ��ת+��ɫ
					//   g
					// u   p
					//       c
					if (cur == parent->_right)
					{
						RotateL(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else//˫��+��ɫ
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

	   // // ����ο�ֵ������·���ڽڵ�����
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

		// ��ɫ�ڵ������ο�ֵ
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
	//		return blackNum == blackRef;  // ����1����ȷ�ж�·���յ�

	//	// ����2��������ڵ����_parent
	//	if (cur != _root && cur->_col == RED && cur->_parent->_col == RED) {
	//		cout << "������ڵ㣺" << cur->_kv.first << endl;
	//		return false;
	//	}

	//	// ���ºڽڵ����
	//	int newBlackNum = (cur->_col == BLACK) ? blackNum + 1 : blackNum;

	//	// ����3����������������������
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
				cout << "��ɫ�ڵ�����������" << endl;
				return false;
			}

			return true;
		}

		if (cur->_col == RED && cur->_parent && cur->_parent->_col == RED)
		{
			cout << cur->_kv.first << "->" << "�����ĺ�ɫ�ڵ�" << endl;
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