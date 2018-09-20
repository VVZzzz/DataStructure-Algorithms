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
	MyProbingHash<std::string> ihash;
	std::vector<std::string> svec{ "hello", "world", "hash" };
	for (auto &s:svec) {
		ihash.insert(s);
	}
	if (ihash.contains("hello"))
		std::cout << "found!" << std::endl;
	system("pause");
	return 0;
}