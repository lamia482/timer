/***************************
 > File: main.cc
 > Date: 2018/09/22
 > Author: lamia
 > Question: 推到并实现数学上常见的排列组合
 > Method: 
***************************/
#include <bits/stdc++.h>
// #include "common.h"
#include "lamia_timer.h"

auto timer = new lamia::LamiaTimer();
typedef size_t DTYPE;
static const DTYPE MAX_MOD_SIZE = 10000000007;
static const DTYPE MAX_SAVED_FACTORY_SIZE = 0;

DTYPE factory(DTYPE x, DTYPE MOD = MAX_MOD_SIZE) {
  if(x < 0) return 0;
  static std::map<DTYPE, DTYPE> factory_map;
  factory_map[0] = 1; factory_map[1] = 1;
  if(x < MAX_SAVED_FACTORY_SIZE) return factory_map[x];
  for(DTYPE i = MAX_SAVED_FACTORY_SIZE > 1? MAX_SAVED_FACTORY_SIZE: 1; i <= x; ++i) {
    factory_map[i] = i * factory_map[i - 1] & MAX_MOD_SIZE;
  }
  return factory_map[x];
}

/* 实现数学组合公式 A_d^u
return d! / (d - u)!
*/
DTYPE A(DTYPE down, DTYPE up) {
  return factory(down) / factory(down - up);
}

int main(int argc, char **argv) {
  timer->start();
  std::cout << A(2, 1) << "\n";
  timer->stop();
  std::cout << "timer size: " << timer->timerSize() 
            << ", time cost: " << timer->seconds() << "\n";
  delete timer;
  return 0;
}
