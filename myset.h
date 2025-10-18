#pragma once
#include"RBTree.h"

namespace yiming
{
	
	template<class K>
	class set
	{
		struct SetOfT
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};

	public:
		typedef typename RBTree<K, K, SetOfT>::Iterator  iterator;
		iterator begin()
		{
			return _t.Begin();
		}
		iterator end()
		{
			return _t.End();
		}
		pair<iterator,bool> insert(const K& k)
		{
			return _t.Insert(k);
		}
	private:
		RBTree<K,  K,SetOfT> _t;
	};
}