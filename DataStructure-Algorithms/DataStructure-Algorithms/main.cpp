#include <iostream>
#include <list>
#include <vector>
using namespace std;
int main()
{
	int a[5] = { 1,2,3,4,5 };
	int * p = &a[2];
	cout << *p << endl;
	system("pause");
	return 0;
}