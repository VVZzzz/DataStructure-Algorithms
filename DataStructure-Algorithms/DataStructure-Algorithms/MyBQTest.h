#pragma once
//此文件测试二项队列MyBinomialQueue
#include <random>
#include "MyBinomialQueue.h"
void binomial_queue_test() {
  //测试二项队列默认构造函数
  std::cout << "\n测试构造函数" << std::endl;
  MyBinomialQueue<int> binomial_queue(1);
  binomial_queue.printInfo();

  //测试insert(),merge(MyBinomialQueue &rhs),combine()
  std::cout << "\n测试insert函数" << std::endl;
  MyBinomialQueue<int> binomial_queue2;
  std::random_device rd;
  std::default_random_engine random(rd());
  std::uniform_int_distribution<int> num(1, 100);
  for (int i = 0; i < 50; i++) {
    binomial_queue2.insert(num(random));
    binomial_queue2.printInfo();
  }
}
