#include "ast.h"
#include <iostream>
#include "calculator.h"
#include <string>

//for debug information uncomment
//#define debug

AST::AST() {}

AST::~AST() {}

BinaryNode::BinaryNode(AST* left, AST* right):
  AST(),
  leftTree(left),
  rightTree(right)
{}

BinaryNode::~BinaryNode() {
#ifdef debug
  cout << "In BinaryNode destructor" << endl;
  
#endif

  try {
    delete leftTree;
  } catch (...) {}

  try {
    delete rightTree;
  } catch(...) {}
}
   
AST* BinaryNode::getLeftSubTree() const {
  return leftTree;
}

AST* BinaryNode::getRightSubTree() const {
  return rightTree;
}

UnaryNode::UnaryNode(AST* sub):
  AST(),
  subTree(sub)
{}

UnaryNode::~UnaryNode() {
#ifdef debug
  cout << "In UnaryNode destructor" << endl;
#endif

  try {
    delete subTree;
  } catch (...) {}
}
   
AST* UnaryNode::getSubTree() const {
  return subTree;
}

StoreNode::StoreNode(AST* sub) : UnaryNode(sub) {}

int StoreNode::evaluate(){
  int b =getSubTree()->evaluate();
  calc->store(b);
  return calc->recall();
}

PlusNode::PlusNode(AST* sub) :UnaryNode(sub) {}

int PlusNode::evaluate(){
  calc->plus(getSubTree()->evaluate());
  return calc->recall();
}

MinusNode::MinusNode(AST* sub) :UnaryNode(sub) {}

int MinusNode::evaluate(){
  calc->minus(getSubTree()->evaluate());
  return calc->recall();
}


RecallNode::RecallNode() : AST() {} 


int RecallNode::evaluate() {
  return calc->recall();
}

ClearNode::ClearNode() : AST() {}

int ClearNode::evaluate() {
  calc->clear();
  return calc ->recall();
}


AddNode::AddNode(AST* left, AST* right):
  BinaryNode(left,right)
{}

int AddNode::evaluate() {
  return getLeftSubTree()->evaluate() + getRightSubTree()->evaluate();
}

SubNode::SubNode(AST* left, AST* right):
  BinaryNode(left,right)
{}

int SubNode::evaluate() {
  return getLeftSubTree()->evaluate() - getRightSubTree()->evaluate();
}

TimesNode::TimesNode(AST* left, AST* right):
  BinaryNode(left, right)
{}

DivideNode::DivideNode(AST* left, AST* right):
  BinaryNode(left, right)
{}

int TimesNode:: evaluate() {
  return getLeftSubTree()->evaluate() * getRightSubTree()->evaluate();
}

int DivideNode:: evaluate() {
  return getLeftSubTree()->evaluate() / getRightSubTree()->evaluate();
}

BitIz::BitIz(AST* left, AST* right):
  BinaryNode(left, right)
{}

BitDer::BitDer(AST* left, AST* right):
  BinaryNode(left, right)
{}

int BitIz:: evaluate()
{
  return getLeftSubTree()->evaluate() << getRightSubTree()->evaluate();
}

int BitDer:: evaluate(){
  return getLeftSubTree()->evaluate() >> getRightSubTree()->evaluate();
}

ModuloNode::ModuloNode(AST* left, AST* right):
  BinaryNode(left, right)
{}

int ModuloNode:: evaluate() {
  return getLeftSubTree()->evaluate() % getRightSubTree()->evaluate();
}

SetNode::SetNode(AST* sub, string id):
  UnaryNode(sub),
  var(id)
{}

int SetNode::evaluate() {
  return calc->set(var,(getSubTree()->evaluate()));
}

EqualsNode::EqualsNode(AST* sub): UnaryNode(sub){}

int EqualsNode::evaluate(){
  return getSubTree()->evaluate();
}

NumNode::NumNode(int n) :
  AST(),
  val(n)
{}

int NumNode::evaluate() {
  
  return val;
}

IdNode::IdNode(string n) :
  AST(),
  nombre(n)
{}

int IdNode::evaluate() {
  return calc->getNum(nombre);
}
