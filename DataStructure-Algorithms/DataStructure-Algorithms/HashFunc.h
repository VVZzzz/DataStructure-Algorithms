#pragma once
#include <string>

//ͨ�õ�������ϣ����
template <typename HashedObj>
int hash(int key) {
	return 0;
}

template <typename HashedObj>
int hash(const std::string & str) {
	return 0;
}
