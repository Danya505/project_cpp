#include "std_lib_facilities.h"
#pragma once
constexpr char quit = 'q';
constexpr char print = ';';
constexpr char number = '8';
constexpr char name = 'a';
constexpr char let = 'L';

const string prompt = "> ";
const string result = "= ";
const string declkey = "let";
const string quitkey = "quit";

struct Token
{
  char kind;
  double value;
  string name;

  Token(char ch) : kind{ch}, value{0} {}

  Token(char ch, double val) : kind{ch}, value{val} {}

  Token(char ch, string id) : kind{ch}, name{id} {}
};

class Token_stream
{
  bool full{false};
  Token buffer{'\0'};
  istream& in;

public:
  Token_stream() : in{cin} {}
  Token_stream(istream& s) : in{s} {}

  Token get ();
  void putback (Token t);

  void ignore (char);

};