// MUD Programming
// Ron Penton
// (C)2003
// Demo17-03.cpp - SWIGGY
// This program shows you how to use SWIG to let Python know about a 
// C++ class or function

#include "SWIGME.h"
#include "SWIGME_wrap.cxx"

int main()
{
    std::cout << "Exporting C++!" << std::endl;
    std::cout << "Chapter 17, Demo 03 - MUD Game Programming" << std::endl;

    Py_Initialize();                // initialize python


    // initialize SWIGME module:
    init_SWIGME();

    // Import and run swiggy:
    PyRun_SimpleString( "import swiggy" );

    Py_Finalize();                  // shut down python

    return 0;
}



