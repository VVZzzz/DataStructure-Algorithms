#include <iostream>
#include <list>
#include <vector>
#include <string>
#include "MyList.h"
#include "ch3practice.hpp"
#include "ch4practice.hpp"
#include "MyTree.h"
#include "MyHashSeparateChain.h"
#include "MyHashProbing.h"
#include "Dictionary.h"
int main()
{
	MyProbingHash<std::string> ihash(3);
	std::cout << ihash.getElementSize() << std::endl;
	std::cout << ihash.getTableSize() << std::endl;
	std::vector<std::string> svec{ "hello", "world", "nihao","shijie","ads","add","sda","sds" };
	for (auto &s:svec) {
		ihash.insert(s);
	}
	std::cout << ihash.getElementSize() << std::endl;
	std::cout << ihash.getTableSize() << std::endl;
	ihash.remove("world");
	std::cout << ihash.getElementSize() << std::endl;
	std::cout << ihash.getTableSize() << std::endl;
	if (ihash.contains("world"))
		std::cout << "found!" << std::endl;
	system("pause");
	return 0;
}