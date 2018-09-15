// MUD Programming
// Ron Penton
// (C)2003
// Demo17-01.cpp - A Simple Python Interpreter
// This program shows you how to integrate Python in a very basic manner


#include <iostream>
#include <string>
#include "Python.h"

int main()
{
    std::cout << "Welcome to SIMPLEPYTHON!!" << std::endl;
    std::cout << "Chapter 17, Demo 01 - MUD Game Programming" << std::endl;

    Py_Initialize();                // initialize python

    std::string str;
    std::getline( std::cin, str );
    while( str != "end" )
    {
        PyRun_SimpleString( const_cast<char*>( str.c_str() ) );
        std::getline( std::cin, str );
    }

    Py_Finalize();                  // shut down python

    return 0;
}



