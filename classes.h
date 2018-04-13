#pragma once

// forward declare learner
template<class T, class E> struct learner;

// base_learner templatized on example
using base_learner = learner<char, char>;

using generic_learn_fn = void (*)(void* data, void* ex);
// function pointers for learn/predict etc
struct learn_data
{
  void* data;
  generic_learn_fn learn_f;
};

// example holds features and labels
struct example {};

// multiline example
using multi_ex = std::vector<example>;

// learner with learn funciton delegated to learn_data
template <class T, class E>
struct learner
{
  inline void learn(E& ec) 
  { 
    learn_fd.learn_f(learn_fd.data, &ec);
  }

  bool is_multiline;
  learn_data learn_fd;
};

// passed into setup funcitons for reductions
struct arguments {};

// make_base casts to learner<char,E>
template<class T, class E> base_learner* make_base(learner<T, E>* base) { return (base_learner*)(base); }