#pragma once
#include <time.h>
#include <iostream>
#include <random>
#include "MyDisjSets.h"
#define ABS(a) a < 0 ? 0 - a : a
struct MazeNode {
  MazeNode() : up(false), down(false), left(false), right(false) {}
  bool up, down, left, right;
};
void generateMaze(int N, int M) {
  int sum = N * M;
  MyDisjSets disjsets(sum);
  static std::default_random_engine num_e, dirc_e;
  num_e.seed(time(0));
  dirc_e.seed(time(0));
  std::uniform_int_distribution<unsigned> u1(0, sum - 1), u2(0, 1);
  while (!disjsets.isSingleTree()) {
    int a = u1(num_e), b = u1(num_e);
    if (disjsets.find_pathcompress(a) == disjsets.find_pathcompress(b))
      continue;
    /* while (disjsets.find_pathcompress(a) != disjsets.find_pathcompress(b)) */
    else {
      if (a > b) std::swap(a, b);
      int a_y = a / N, a_x = a % N;
      int b_y = b / N, b_x = b % N;
      int dis_x = b_x - a_x;
      int dis_y = b_y - a_y;
      int temp = a;
      while (dis_x && dis_y) {
        if (dis_x > 0) {
          if (u2(dirc_e) == 0) {
            disjsets.unionSets_size(disjsets.find_pathcompress(temp),
                                    disjsets.find_pathcompress(temp + 1));
            std::cout << temp << "¡ú" << temp + 1 << std::endl;
            temp++;
            dis_x--;
          } else {
            disjsets.unionSets_size(disjsets.find_pathcompress(temp),
                                    disjsets.find_pathcompress(temp + N));
            std::cout << temp << "¡ý" << temp + N << std::endl;
            temp += N;
            dis_y--;
          }
        } else {
          if (u2(dirc_e) == 0) {
            disjsets.unionSets_size(disjsets.find_pathcompress(temp),
                                    disjsets.find_pathcompress(temp - 1));
            std::cout << temp << "¡ú" << temp + 1 << std::endl;
            temp--;
            dis_x++;
          } else {
            disjsets.unionSets_size(disjsets.find_pathcompress(temp),
                                    disjsets.find_pathcompress(temp + N));
            std::cout << temp << "¡ý" << temp + N << std::endl;
            temp += N;
            dis_y--;
          }
        }
      }
      if (dis_x > 0) {
        for (; dis_x > 0; dis_x--) {
          disjsets.unionSets_size(disjsets.find_pathcompress(temp),
                                  disjsets.find_pathcompress(temp + 1));
          std::cout << temp << "¡ú" << temp + 1 << std::endl;
          temp++;
        }
      } else if (dis_x < 0) {
        for (; dis_x < 0; dis_x++) {
          disjsets.unionSets_size(disjsets.find_pathcompress(temp),
                                  disjsets.find_pathcompress(temp - 1));
          std::cout << temp << "¡û" << temp - 1 << std::endl;
          temp--;
        }
      }
      for (; dis_y > 0; dis_y--) {
        disjsets.unionSets_size(disjsets.find_pathcompress(temp),
                                disjsets.find_pathcompress(temp + N));
        std::cout << temp << "¡ý" << temp + N << std::endl;
        temp += N;
      }
    }
  }
}

void generateMaze2(int N, int M) {
  int sum = N * M;
  MyDisjSets disjsets(sum);
  static std::default_random_engine num_e, dirc_e;
  num_e.seed(time(0));
  dirc_e.seed(time(0));
  std::uniform_int_distribution<unsigned> u1(0, sum - 1), u2(0, 3);
  while (!disjsets.isSingleTree()) {
    int a = u1(num_e), b = a;
    while (1) {
      int direc = u2(dirc_e);
      switch (direc) {
        case 0:
          b = a - N;
          break;
        case 1:
          b = a + 1;
          break;
        case 2:
          b = a + N;
          break;
        case 3:
          b = a - 1;
          break;
      }
      if (b >= 0 && b < sum) {
        if (!((b%N==N-1)&&(a%N==0)||(a%N==N-1)&&(b%N==0)))
          break;
      }
    }
    if (disjsets.find_pathcompress(a) == disjsets.find_pathcompress(b))
      continue;
    else {
      disjsets.unionSets_size(disjsets.find_pathcompress(a),
                                disjsets.find_pathcompress(b));
      std::cout << "(" << a << "," << b << ")" << std::endl;
    }
  }
}
