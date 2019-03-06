#pragma once
//���ļ����Զ������MyBinomialQueue
#include <random>
#include "MyBinomialQueue.h"
void binomial_queue_test() {
  //���Զ������Ĭ�Ϲ��캯��
  std::cout << "\n���Թ��캯��" << std::endl;
  MyBinomialQueue<int> binomial_queue(1);
  binomial_queue.printInfo();

  //����insert(),merge(MyBinomialQueue &rhs),combine()
  std::cout << "\n����insert����" << std::endl;
  MyBinomialQueue<int> binomial_queue2;
  std::random_device rd;
  std::default_random_engine random(rd());
  std::uniform_int_distribution<int> num(1, 100);
  for (int i = 0; i < 50; i++) {
    binomial_queue2.insert(num(random));
    binomial_queue2.printInfo();
  }
}
