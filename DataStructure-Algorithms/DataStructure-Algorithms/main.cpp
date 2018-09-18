#include <iostream>
#include <list>
#include <vector>
#include "MyList.h"
#include "ch3practice.hpp"
#include "ch4practice.hpp"
#include "MyTree.h"
#include "MyHashSeparateChain.h"
int main()
{
	std::string res = postToinFix();
	std::cout << res << std::endl;
	system("pause");
	return 0;
}