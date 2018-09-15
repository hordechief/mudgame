// MUD Programming
// Ron Penton
// (C)2003
// Demo17-02.cpp - A Simple Python Test
// This program shows you how to load python modules and execute things
// in them.


#include <iostream>
#include <string>
#include "Python.h"

int main()
{
    std::cout << "Python Test!" << std::endl;
    std::cout << "Chapter 17, Demo 02 - MUD Game Programming" << std::endl;

    Py_Initialize();                // initialize python

    // load the module:
    PyObject* mod = PyImport_ImportModule( "pythontest" );

    PyRun_SimpleString( "import pythontest\n"
                        "pythontest.testfunc()\n" );

    PyObject* result = 
        PyObject_CallMethod( mod, "testfunc", NULL );
    Py_DECREF( result );
    result = 0;

    result = PyObject_CallMethod( mod, "printfunc", "s", "HELLO PYTHON!" );
    Py_DECREF( result );
    result = 0;

    result = PyObject_CallMethod( mod, "printfunc", "i", 42 );
    Py_DECREF( result );
    result = 0;

    result = PyObject_CallMethod( mod, "returnstring", NULL );
    std::string str = PyString_AsString( result );
    std::cout << str << std::endl;
    Py_DECREF( result );
    result = 0;

    // release my reference
    Py_DECREF( mod );

    Py_Finalize();                  // shut down python

    return 0;
}



