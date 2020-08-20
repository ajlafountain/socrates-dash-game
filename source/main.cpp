#include <iostream>
#include "AppClass.hpp"

int 
main(int argc, char** argv)
{
   std::cout << "Hello world!" << std::endl;
   App thisApp;
   thisApp.Run();
   return 0;
}