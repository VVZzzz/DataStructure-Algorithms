#include <iostream>
#include <list>
#include <vector>
#include "MyList.h"
#include "ch3practice.hpp"
#include "ch4practice.hpp"
#include "MyTree.h"
#include "MyHashSeparateChain.h"
#include "MyHashProbing.h"
int main()
{
	std::vector<int> ivec = { 4371,1323,6173,4199,4344,9679,1989 };
	for (auto c : ivec) {
		std::cout << 7 - c % 7 << std::endl;
	}
	system("pause");
	return 0;
}