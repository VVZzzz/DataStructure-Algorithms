#include <iostream>
#include <list>
#include <vector>
#include "MyList.h"
int main()
{
	MyList<int> mylist;
	for (int  i = 0; i < 5; i++) {
		mylist.push_back(i);
	}
	auto itr = mylist.rbegin();
	while (itr!=mylist.rend()) {
		std::cout << *itr++ << std::endl;
	}
	system("pause");
	return 0;
}