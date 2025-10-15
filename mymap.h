#pragma once
#include"RBTree.h"
namespace yiming
{
	template<class K,class V>
	class map
	{
		struct MapKeyOfT
		{
			const K& operator()(const pair<K,V>& kv)
			{
				return kv.first;
			}
		};
	public:
		template<class K, class V>
		bool insert(const pair<K, V>& kv)
		{
			return _t.Insert(kv);
		}
	private:
		RBTree<K, pair<K, V>,MapKeyOfT>_t;
	};
}
