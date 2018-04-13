#pragma once
#include "classes.h"
#include <iostream>
#include "learner.h"
#include "gd.h"

using namespace std;

// example of struct that holds state for single-line reduction
struct gd {};

inline void gd_learn(gd& dat, example& ex)
{
  cout << __FUNCTION__ << endl;
}

inline base_learner* gd_setup(const arguments& args)
{
  cout << __FUNCTION__ << endl;
  gd* pgd = new gd();
  learner<gd,example>* plearner = init_learner(pgd, gd_learn);
  return make_base(plearner);
}

