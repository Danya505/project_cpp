#include "std_lib_facilities.h"
#pragma once

struct Variable
{
  string name;
  double value;

  Variable(string n, double v) : name{n}, value{v} {}
};
 
extern vector<Variable> var_table;