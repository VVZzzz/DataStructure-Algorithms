# Chapter3练习
--------------------------------------
### 3.6 约瑟夫问题

- 问题描述：  
>编号为1,2,3...n的人一词围成一圈，从第k个人开始报数（从1开始），数到m的人退出。接着下一个人又从1开>始报数，数到m的人退出，以此类推。问：剩下的人的编号是多少？

>如：n=6,m=3,k=1
 原始序列： 1  2  3  4  5  6 ； 从编号1开始报数
 第一轮数完后的序列为：  1  2  4  5  ； 3、6出列——从编号1开始报数
 第二轮数完后的序列为：  1  2  5   ； 4出列——从编号5开始报数
 第三轮数完后的序列为：   1  5   ；   2 出列——从5开始报数
 第四轮数完后的序列为：   1  ；5 出列

> 所以，最后出列的编号为1.

- 求解思路：
	- 朴素思路：  
	将这n个人编为双向链表(c++中为list),我们知道n个人中只有一个人存活。故外部循环为n次。每循环1次，就有一个人出局。而对于内部循环，便是找到第m个那一个。找到后，将他erase掉，重新进入外部循环。在此注意，如果遇到list.end()，那么下一个应该是list.begin()。
	故：

			// 朴素算法时间复杂度为O(nm)
			void josephus_base(int n, int m) {
				int i, j, mPrime, numLeft;
				list<int> L;
				list<int>::iterator iter;
				cin >> n >> m;
				numLeft = n;
				mPrime = m % n;
				for (i =1 ; i <= n; i++)
					L.push_back(i);
				iter = L.begin();
				// Pass the potato
				for (i = 0; i < n; i++)
				{
					mPrime = mPrime % numLeft;
					for (j = 0; j < mPrime; j++)
					{
						iter++;
						if (iter == L.end())
							iter = L.begin();
					}
					cout<<*iter<<" ";
					iter= L.erase(iter);
					if (iter == L.end())
						iter = L.begin();
				}
				cout<<endl;
			}
 
	- 数学推导解法    
	这里有一个公式记住即可，如下(编号从0开始)   
```f(n,m)=(f(n-1,m) + m) mod n,f(1,m) = 0```    
	```f(n,k)```为n个人，编号为m的出局的最终结果。
	公式的证明推导，见[约瑟夫问题](https://zh.wikipedia.org/wiki/%E7%BA%A6%E7%91%9F%E5%A4%AB%E6%96%AF%E9%97%AE%E9%A2%98)  

			//时间复杂度为O(n)
			//編號從0開始，也就是說如果編號從1開始結果要加1
			int josephus(int n, int k) { //非遞回版本
				int s = 0;
				for (int i = 2; i <= n; i++)
					s = (s + k) % i;
				return s;
			}

			int josephus_recur(int n, int k) { //递归版本
				return n > 1 ? (josephus_recur(n - 1, k) + k) % n : 0;
			}

	- 从上一方法推广    
	时间复杂度为O(klogn)，详见[约瑟夫问题](https://zh.wikipedia.org/wiki/%E7%BA%A6%E7%91%9F%E5%A4%AB%E6%96%AF%E9%97%AE%E9%A2%98)

### 3.9 
对于vector,按照C++标准,对push_back,pop_back,insert或erase的调用将使所有的指向vector的迭代器失效(潜在生成废物的可能)。为什么？

答：对于C++的各个容器，在其添加和删除元素之后，其迭代器有的会失效。详细描述见```<<C++Primer>> P315```

