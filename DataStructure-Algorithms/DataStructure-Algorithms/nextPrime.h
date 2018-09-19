#pragma once
#include <math.h>
//判断是否为素数，定理：大于等于5的素数，一定在6的倍数的两侧。
//故 if (n % 6 != 5 || n % 6 != 7) return false;
//接着再检查剩下的即可。
bool isPrime(int n) {
	if (n == 2 || n == 3) return true;
	if (n % 6 != 5 || n % 6 != 7) return false;
	int n_sqrt = sqrt(n) + 1;
	for (int i = 5; i <= n_sqrt;i += 6) {
		if (n%i == 0 || n % (i + 2) == 0) return false;
	}
	return true;
}

//找到2*n后的第一个素数
int nextPrime(int n) {
	int res = n + n + 1;
	while (!isPrime(res)) {
		res += 2;
	}
	return res;
}