#include <vector>
#include "classes.h"
#include "gd.h"
#include "ldf.h"

using namespace std;

// Typedefs
using setup_fptr = base_learner* (*) (const arguments&);
using single_lrn_fptr = void (*) (const arguments&);

// Forward declatations
vector<setup_fptr> get_reduction_stack();
base_learner* setup_base(arguments& args, vector<setup_fptr>& reduction_stack);
learner<char,multi_ex>* as_multiline(base_learner* l);
learner<char, example>* as_singleline(base_learner* l);
void single_line_proc(base_learner* l);
void multi_line_proc(base_learner* l);
template<void(*)(base_learner*)> void generic_driver(base_learner* l);

// Start here
int main()
{
  // Get reduction stack made up of setup functions
  auto reduction_stack = get_reduction_stack();
  arguments args;
  
  // go through the stack and find a reduction that matches
  base_learner* l = setup_base(args, reduction_stack);

  // start the right driver (multiline or singleline)
  if (l->is_multiline)
    generic_driver<multi_line_proc>(l);
  else
    generic_driver<single_line_proc>(l);
}

// Driver template
template<void(*F)(base_learner*)>
void generic_driver(base_learner* l)
{
  F(l);
}

void single_line_proc(base_learner* l)
{
  example ec;
  as_singleline(l)->learn(ec);
}

void multi_line_proc(base_learner* l)
{
  vector<example> ec_col;
  as_multiline(l)->learn(ec_col);
}

base_learner* setup_base(arguments& args, vector<setup_fptr>& reduction_stack)
{
  const auto fptr = reduction_stack.back();
  reduction_stack.pop_back();
  base_learner* ret = fptr(args);

  if (ret == nullptr)
    return setup_base(args,reduction_stack);
  else
    return ret;
}

learner<char, multi_ex>* as_multiline(base_learner* l)
{
  if (!l->is_multiline) throw logic_error("Tried to use a singleline reduction as a multiline reduction");
  return (learner<char, multi_ex>*) (l);
}

learner<char, example>* as_singleline(base_learner* l)
{
  if (l->is_multiline) throw logic_error("Tried to use a multiline reduction as a singleline reduction");
  return (learner<char, example>*) (l);
}

vector<setup_fptr> get_reduction_stack()
{
  vector<base_learner* (*)(const arguments&)> reduction_stack;
  reduction_stack.push_back(gd_setup);
  reduction_stack.push_back(ldf_setup);
  return reduction_stack;
}


