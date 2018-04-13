#pragma once
#include "classes.h"
#include <ostream>
#include <iostream>

// example of struct that holds state for multi-line reduction
struct ldf {};

inline void ldf_learn(ldf& dat, multi_ex& ex)
{
  cout << __FUNCTION__ << endl;
}

inline base_learner* ldf_setup(const arguments& args)
{
  std::cout << __FUNCTION__ << std::endl;
  ldf* pldf = new ldf();
  learner<ldf, multi_ex>* plearner = init_learner(pldf, ldf_learn);
  return make_base(plearner);
}

