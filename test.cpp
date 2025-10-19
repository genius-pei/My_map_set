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
	s.insert(21);
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
void test03()
{
	yiming::map<string, string> dict;
	dict.insert({ "sort", "����" });
	dict.insert({ "left", "���" });
	dict.insert({ "right", "�ұ�" });

	dict["left"] = "��ߣ�ʣ��"; // �޸�
	dict["insert"] = "����";  // ����+�޸�
	dict["string"];          // ����

	yiming::map<string, string>::iterator it = dict.begin();
	while (it != dict.end())
	{
		// �����޸�first�������޸�second
		//it->first += 'x';
		it->second += 'x';
		cout << it->first << ":" << it->second << endl;
		++it;
	}
	cout << endl;
}
int main()
{
	test01();
	test02();
	test03();
	
	return 0;
		 
}