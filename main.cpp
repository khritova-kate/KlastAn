#include "My_Interface.h"
#include <iostream>

int main(int argc,char*argv[])
{
    My_Interface I;
    if(argc>2) 
    {
        std::cout<<"Usage: ./a.out [file name]\n";
        return -1;
    }
    if(argc == 2) I.do_it(argv[1]);
    else          I.do_it(NULL);
    return 0;
}