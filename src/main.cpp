//
//  main.cpp

//

#include <iomanip>
#include <cstdlib>
#include <iomanip>
#include "Header/Controller_Mngr.h"

int main(int argc, const char * argv[])
{
  // Initiating Object 'control' of Controller_Mngr class 
  Controller_Mngr control;
  
  control._task_Mngr(); //calling the _task_Mngr function of control object 
  
  cin.sync();
  cin.get();
  
  return 0;
}
