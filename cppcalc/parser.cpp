#include "parser.h"
#include "calcex.h"
#include <string>
#include <sstream>

Parser::Parser(istream* in) {
   scan = new Scanner(in);
}

Parser::~Parser() {
   try {
      delete scan;
   } catch (...) {}
}

AST* Parser::parse() {
   return prog();
}

AST* Parser::prog() {
 
 AST* result = BitExpr();
 Token* t = scan->getToken();
 
  if (t->getType() != eof) {
    cout << "*parse Error" << endl;
    throw ParseError;
  }
  
  return result;
 
}

AST* Parser::expr() {
   return restExpr(term());
}

AST* Parser::restExpr(AST* e) {
   Token* t = scan->getToken();

   if (t->getType() == add) {
      return restExpr(new AddNode(e,term()));
   }

   if (t->getType() == sub)
      return restExpr(new SubNode(e,term()));

   scan->putBackToken();

   return e;
}

AST* Parser::BitExpr() {
  return RestBitExpr(expr());
}

AST* Parser::RestBitExpr(AST* e) {
  Token* t = scan->getToken();

  if(t->getType() == bitIz){
    return RestBitExpr(new BitIz(e,expr()));
  }
  if(t->getType() == bitDer){
    return RestBitExpr(new BitDer(e, expr()));
  }

  scan->putBackToken();
  return e;
}

AST* Parser::term() {

  return restTerm(storable());
}

AST* Parser::restTerm(AST* e) {
  Token* t = scan->getToken();

   if (t->getType() == times) {
      return restTerm(new TimesNode(e,storable()));
   }

   if (t->getType() == divide)
      return restTerm(new DivideNode(e,storable()));

    if (t->getType() == modulo)
      return restTerm(new ModuloNode(e,storable()));

   scan->putBackToken();

   return e; 
}

AST* Parser::storable() {
  AST* result = factor();

  Token *t = scan->getToken();

  if(t->getType() == keyword)
    {
      if(t->getLex() == "S")
	{
	  return new StoreNode(result);
	}else if(t->getLex() == "P")
	{
	  return new PlusNode(result);
	}else if(t->getLex() == "M")
	{
	  return new MinusNode(result);
	}else 
	{
	  cout << "parse error" << endl;
	  throw ParseError;
	}

    }
  scan->putBackToken();
  return result;
}

AST* Parser::factor() {
  Token* t = scan->getToken();
     
  if (t->getType() == number) {
    istringstream in(t->getLex());
    int val;
    in >> val;
    return new NumNode(val);
  }

  if(t->getType() == keyword)
    {
      if(t->getLex() == "R")
	{
	   
	  return new RecallNode();
	  
	}else if(t->getLex() == "C")
	{
	  return new ClearNode();
	  
	}else if(t->getLex() =="set") {
	
	t=scan->getToken();
	
	if(t->getType() != identifier){
	  cout << "*parse error"<< endl;
	  throw ParseError;
	}
	istringstream in(t->getLex());
	string id;
	in >> id;
	t=scan->getToken();
	if(t->getType() != equals){
	  cout << "*parse error"<< endl;
	  throw ParseError;
	}

	AST* result = new EqualsNode(BitExpr());
	return new SetNode(result,id);

      }else{
	cout << "*parser error" << endl;
	throw ParseError;
      }
       
    }

  if (t->getType() == identifier) {
    istringstream in(t->getLex());
    string var;
    in >> var;
    return new IdNode(var);
  }
   
  if(t->getType() == lparen) 
    {
      AST* result = BitExpr();
      t = scan->getToken();
      if(t->getType() != rparen)
	{
	  cout << "*parse error"
	       << endl;
	  throw ParseError;
	   
	}
      return result;
    }
  cout << "*parse error" << endl;
  throw ParseError; 
}
   
