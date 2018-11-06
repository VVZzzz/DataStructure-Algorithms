#pragma once
/**
 * 简单的随机数生成器
 * 线性同余数生成器:X(i+1)=A*X(i)%M;
 * M一般为较大的素数 取:2^31-1
 * 为解决乘法溢出,改为:X(i+1)=A(X(i)%Q)-R((int)X(i)/Q)+M(σ(x(i));
 * 最后一项为若余项小于0则加上M
 */
static const int A = 48271;
static const int M = 2147483647;
static const int Q = M / A;
static const int R = M % R;
class Random {
 public:
  explicit Random(int initialValue = 1);
  int randomInt();
  double random0_1();
  int randomInt(int low, int high);

 private:
  int state;  //种子
};

Random::Random(int initialValue) {
  if (initialValue < 0) initialValue += M;
  state = initialValue;
  if (state == 0) state = 1;  //种子禁止为0
}

int Random::randomInt() {
  int tmpState = A * (state % Q) - R * (state / R);
  if (tmpState >= 0)
    state = tmpState;
  else
    state = tmpState + M;
}

double Random::random0_1() { return (double)randomInt() / M; }

int Random::randomInt(int low, int high) {
  return low + (high - low) * random0_1();
}
