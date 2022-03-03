#include"RingBuffer.h"
#include<string>

int main()
{
	int m = 5;
	RingBuffer<std::string> r(m);
	r.add_front("������ ");
	r.add_back("���� ");
	r.add_back("����� ");
	r.add_back("����� ");
	r.add_back("! ");


	for (int i = 0; i < m; i++)
	{
		std::cout << r[i];
	}
	std::cout << std::endl;
	

	r.resize(m - 2);
	r.add_back("��� ");

	for (int i = 0; i < m - 2; i++)
	{
		std::cout << r[i];
	}
	std::cout << std::endl;

	//r.remove_front();

	return 0;
}