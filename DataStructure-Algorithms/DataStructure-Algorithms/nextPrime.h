#pragma once
#include <math.h>
//�ж��Ƿ�Ϊ�������������ڵ���5��������һ����6�ı��������ࡣ
//�� if (n % 6 != 5 || n % 6 != 7) return false;
//�����ټ��ʣ�µļ��ɡ�
bool isPrime(int n) {
	if (n == 2 || n == 3) return true;
	if (n % 6 != 5 || n % 6 != 7) return false;
	int n_sqrt = sqrt(n) + 1;
	for (int i = 5; i <= n_sqrt;i += 6) {
		if (n%i == 0 || n % (i + 2) == 0) return false;
	}
	return true;
}

//�ҵ�2*n��ĵ�һ������
int nextPrime(int n) {
	int res = n + n + 1;
	while (!isPrime(res)) {
		res += 2;
	}
	return res;
}