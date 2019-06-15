#pragma once
#include <string>
#include <map>
 
using namespace std;


class Calculator {
 public:
   Calculator();

   int eval(string expr);
   void store(int val);
   int recall();
   int plus(int factor);
   int minus(int factor);
   int set(string iden, int numero);
   void clear();
   int getNum(string var);

 private:
   int memory;
   map <string, int> variables;
};

extern Calculator* calc;


