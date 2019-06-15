#include "scanner.h"
#include "calcex.h"
#include <iostream>
#include <string>
#include <cctype>
#include <cstdio>

using namespace std;

//Uncomment this to get debug information
//#define debug

const int numberOfKeywords = 6;

const string keywd[numberOfKeywords] = {
  string("S"), string("R"), string("P"), string("M"), string("C"),string("set")
};

Scanner::Scanner(istream* in):
  inStream(in),
  lineCount(1),
  colCount(-1),
  needToken(true),
  lastToken(0)
{}

Scanner::~Scanner() {
  try {
    delete inStream;
  } catch (...) {}
}

void Scanner::putBackToken() {
  needToken = false;
}

Token* Scanner::getToken() {
  if (!needToken) {
    needToken=true;
    return lastToken;
  }

  Token* t;
  int state=0;
  bool foundOne=false;
  int c;
  string lex;
  TokenType type;
  int k;
  int column, line;

  c = inStream->get();

  while (!foundOne) {
    colCount++;
    switch (state) {
    case 0 : 
      lex = "";
      column=colCount;
      line = lineCount;
      if (isalpha(c)) state=1;
      else if (isdigit(c)) state=2;
      else if (c=='+') state=3;
      else if (c=='-') state=4;
      else if (c=='*') state=5;
      else if (c=='/') state=6;
      else if (c=='(') state=7;
      else if (c==')') state=8;
      else if (c=='%') state=9;
      else if (c=='<'){
	c = inStream->get();
	if(c=='<'){
	  state=10;
	}else{
	  cout << "*scanner error" << endl;
	  throw UnrecognizedToken;
	}
      }else if (c=='>'){	
	c = inStream->get();
	if(c=='>') {
	  state=11;
	}
      else{
	  cout << "*scanner error" << endl;
	  throw UnrecognizedToken;
	  
      }
      }else if(c=='='){
	state=12;

      }else if (c=='\n') {
	colCount=-1;
	lineCount++;
      }
      else if (isspace(c));
      else if (inStream->eof() || c == EOF) {
	foundOne=true;
	type=eof;
      }
      else {
	cout << "*scanner error" << endl;
	throw UnrecognizedToken;
      }
      break;
    case 1 :
      if (isalnum(c)) state=1;
      else {
	for (k=0;k<numberOfKeywords;k++)
	  if (lex == keywd[k]) {
	    foundOne = true;
	    type = keyword;
	  }
	if (!foundOne) {
	  type = identifier;
	  foundOne = true;
	}
      }
      break;
    case 2 :
      if (isdigit(c)) state=2;
      else {
	type = number;
	foundOne=true;
      }
      break;
    case 3 :
      type = add;
      foundOne = true;
      break;
    case 4 :
      type = sub;
      foundOne = true;
      break;
    case 5 :
      type = times;
      foundOne=true;
      break;
    case 6 :
      type = divide;
      foundOne=true;
      break;
    case 7 :
      type = lparen;
      foundOne=true;
      break;
    case 8 :
      type = rparen;
      foundOne=true;
      break;
    case 9 :
      type = modulo;
      foundOne = true;
      break;
    case 10:
      type = bitIz;
      foundOne = true;
      break;
    case 11:
      type = bitDer;
      foundOne = true;
      break;
    case 12:
      type = equals;
      foundOne =true;
      break;
    }
      
    if (!foundOne) {
      lex = lex + static_cast<char>(c);
      c = inStream->get();
    }
  }

  inStream->putback(c);
  colCount--;
  if (type == number || type == identifier || type == keyword) {
    t = new LexicalToken(type,new string(lex), line, column);
  }
  else {
    t = new Token(type,line,column);
  }

#ifdef debug
  cout << "just found " << lex << " with type " << type << endl;
#endif 

  lastToken = t;
  return t;

}
         
  








