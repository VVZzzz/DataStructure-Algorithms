#pragma once
#include <string>
#include "MyPair.h"

//通用的两个哈希函数
int hash(int key) {
	return key;
}

int hash(const std::string & str) {
	int hashVal = 0;
	for (int i = 0; i < str.length();i++) {
		hashVal = 37 * hashVal + str[i];
	}
	return hashVal;
}

template <typename HashedObj,typename Object>
int hash(const MyPair<HashedObj, Object> &pr)
{
	return 0;
}