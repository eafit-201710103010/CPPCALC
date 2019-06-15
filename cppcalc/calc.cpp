#include <iostream>
#include <sstream>
#include <string>
#include "calcex.h"
#include "calculator.h"
using namespace std;

Calculator* calc;

int main(int argc, char* argv[]){
  string line;
   
  calc = new Calculator();
  
  while(true){

    cout << "> ";

    if(getline(cin, line) && !cin.eof()){
      // line + '\n';


      try{

	int result = calc->eval(line);
      
	cout << "= " << result << endl;
      }catch(Exception ex)
	  {
	  
	  }
	

    }else{
      break;
	}	 
      
  }
     
  delete calc;
}
   
