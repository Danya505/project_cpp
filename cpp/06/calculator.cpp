//
// This is example of starting code from Chapter 7.8 "Variables" of
// "Software - Principles and Practice using C++" by Bjarne Stroustrup
//

#include "std_lib_facilities.h"
#include "token.h"
#include "variable.h"





double get_value (const string& s)
{
  for (const auto& var : var_table)
  {
    if (var.name == s)
      return var.value;
  }

  error("get: undefined name ", s);
}

void set_value (const string& s, double d)
{
  for (auto& var : var_table)
  {
    if (var.name == s)
    {
      var.value = d;
      return;
    }
  }

  error("set: undefined name ", s);
}

bool is_declared (const string& s)
{
  for (const auto& var : var_table)
  {
    if (var.name == s)
      return true;
  }

  return false;
}

double define_name (const string& var, double val)
{
  if (is_declared(var))
    error(var, " declared twice");

  var_table.push_back(Variable{var, val});

  return val;
}

// Token_stream ts;

double expression (Token_stream& ts);

double primary (Token_stream& ts)
{
  Token t = ts.get();
  switch (t.kind)
  {
  case '(':
  {
    double d = expression(ts);
    t = ts.get();
    if (t.kind != ')')
      error("'(' expected");
    return d;
  }

  case '-':
    return -primary(ts);
  case '+':
    return +primary(ts);

  case number:
    return t.value;

  case name:
    return get_value(t.name);

  default:
    error("primary expected");
  }
}

double term (Token_stream& ts)
{
  double left = primary(ts);

  while (true)
  {
    Token t = ts.get();

    switch (t.kind)
    {
    case '*':
      left *= primary(ts);
      break;

    case '/':
    {
      double d = primary(ts);
      if (d == 0)
        error("divide by zero");
      left /= d;
      break;
    }

    case '%':
    {
      double d = primary(ts);
      if (d == 0)
        error("'%': divide by zero");
      left = fmod(left, d);
      break;
    }

    default:
      ts.putback(t);
      return left;
    }
  }
}

double expression (Token_stream& ts)
{
  double left = term(ts);

  while (true)
  {
    Token t = ts.get();

    switch (t.kind)
    {
    case '+':
      left += term(ts);
      break;

    case '-':
      left -= term(ts);
      break;

    default:
      ts.putback(t);
      return left;
    }
  }
}

double declaration (Token_stream& ts)
{
  Token t = ts.get();
  if (t.kind != name)
    error("name expected in declaration");

  string var = t.name;
  if (is_declared(var))
    error(var, " declared twice");

  t = ts.get();
  if (t.kind != '=')
    error("'=' missing in declaration of ", var);

  return define_name(var, expression(ts));
}

double statement (Token_stream& ts)
{
  Token t = ts.get();
  switch (t.kind)
  {
  case let:
    return declaration(ts);
  default:
    ts.putback(t);
    return expression(ts);
  }
}

void clean_up_mess (Token_stream& ts) { ts.ignore(print); }

void calculate ()
{ Token_stream ts;
  while (true)
    try
    {
      cout << prompt;
      Token t = ts.get();
      while (t.kind == print)
        t = ts.get();
      if (t.kind == quit)
        return;

      ts.putback(t);
      cout << result << statement(ts) << endl;
    }
    catch (runtime_error& e)
    {
      cerr << e.what() << endl;
      clean_up_mess(ts);
    }
}

int main ()
try
{
  define_name("pi", 3.141592653589793);
  define_name("e", 2.718281828459045);

  calculate();
}
catch (exception& e)
{
  cerr << "exception: " << e.what() << endl;
  return 1;
}
catch (...)
{
  cerr << "Oops, unknown exception" << endl;
  return 2;
}