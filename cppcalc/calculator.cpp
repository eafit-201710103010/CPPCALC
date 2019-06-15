#include "calculator.h"
#include "parser.h"
#include "ast.h"
#include <string>
#include <iostream>
#include <sstream>
#include <map>

Calculator::Calculator():
   memory(0)
{}

int Calculator::eval(string expr) {

   Parser* parser = new Parser(new istringstream(expr));
   
   AST* tree = parser->parse();
      
   int result = tree->evaluate();
   
   delete tree;
   
   delete parser;
   
   return result;
   
}

void Calculator::store(int val) {
  
   memory = val;
}

int Calculator::recall() {
  
   return memory;
}

int Calculator::plus(int factor){
  memory= memory +factor;
}

int Calculator::minus(int factor){
  memory = memory - factor;
}

void Calculator::clear(){
  memory=0;
}

int Calculator::set(string var, int val){
  variables[var]=val;
  return val;
}

int Calculator::getNum(string var){
  return variables[var]; 
}
