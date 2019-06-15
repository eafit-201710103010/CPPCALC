#pragma once
#include "ast.h"
#include "scanner.h"

class Parser {
 public:
   Parser(istream* in);
   ~Parser();

   AST* parse();

 private:
   AST* prog();
   AST* BitExpr();
   AST* RestBitExpr(AST* e);
   AST* expr();
   AST* restExpr(AST* e);
   AST* term();
   AST* restTerm(AST* t);
   AST* storable();
   AST* factor();

   Scanner* scan;
};



