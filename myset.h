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
		bool insert(const K& k)
		{
			return _t.Insert(k);
		}
	private:
		RBTree<K, K,SetOfT> _t;
	};
}