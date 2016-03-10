#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "parser.cpp"
using namespace std;

void listInput(string fileLocation);
void treePrint(string fileLocation, bool debugMode);

int main(int argc, char** argv) {  

  if (argc <= 2 || argc>4)  exit(1); //only allow 3 or 4 parameters (fn,switch+,fileLocation)

  string switch1=argv[1];	
  if(argc==3){
    string fileLocation=argv[2];
    if(switch1=="-l")  // if 3 parameters with -l switch -> Print input and return
    {
      listInput(fileLocation);  
    }
    else if(switch1=="-ast")   // if 3 parameters with -ast switch -> Print Tree and return
    {
      treePrint(fileLocation,false);
    }
    return 0;
  }

  // if 4 parameters
  string switch2=argv[2];
  string fileLocation=argv[3];
  bool debugMode=false;
  if(switch1=="-l" || switch2=="-l")  
  {
    listInput(fileLocation);
  }
  if(switch1=="-debug" || switch2=="-debug")  
  {
    debugMode=true;
  }
  if(switch1=="-ast" || switch2=="-ast"){
    treePrint(fileLocation,debugMode);
  }
  else
    exit(1);
}

void listInput(string fileLocation)   // List the input from the file
{
  string inputLine;
  ifstream fin;
  fin.open(fileLocation.c_str());
  if (fin.is_open())
  {
    while ( getline (fin,inputLine) )
      cout << inputLine << '\n';
    fin.close();
  }
  else 
  {
    cout << "Could not open file"; 
  }
}

void treePrint(string fileLocation, bool debugMode)     // Produce and print the AST for the input
{
  RPALparser *rp=new RPALparser(fileLocation, debugMode);
  StackHelper *sp=rp->sp;  
  rp->startParsing();
  sp->printTree();
}