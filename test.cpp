#define _CRT_SECURE_NO_WARNINGS
#include"mymap.h"
#include"myset.h"
void test01()
{
	yiming::set<int> s;
	s.insert(1);
	s.insert(8);
	s.insert(4);
	s.insert(6);
	s.insert(2);
}
void test02()
{
	yiming::set<int> s;
	s.insert(4);
	s.insert(22);
	s.insert(211);
	s.insert(2);
	s.insert(1);
	yiming::set<int>::iterator it = s.begin();
	while (it !=s.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}
int main()
{
	//test01();
	test02();
	return 0;
		 
}