#pragma once
#include <string>

//通用的两个哈希函数
template <typename HashedObj>
int hash(int key) {
	return 0;
}

template <typename HashedObj>
int hash(const std::string & str) {
	return 0;
}
