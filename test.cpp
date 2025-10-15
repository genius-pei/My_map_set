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
int main()
{
	test01();
	return 0;
}