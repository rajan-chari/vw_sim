#pragma once
#include "classes.h"

template<class T, class E>
learner<T, E>* init_learner(T* dat, void(*learnfn)(T&, E&))
{
  auto l = new learner<T, E>();
  l->is_multiline = std::is_same<multi_ex,E>::value;
  l->learn_fd.data = dat;
  l->learn_fd.learn_f = (generic_learn_fn)learnfn;
  
  return l;
}
