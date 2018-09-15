// MUD Programming
// Ron Penton
// (C)2003
// SWIGME.h - A Simple class and function that you want SWIGGED


#include <string>
#include <iostream>

std::string SWIGFunction()
{
    return "This has been brought to you by the letter C";
}


class SWIGClass
{
public:
    SWIGClass( int value ) : m_value( value ) {}
    void PrintValue()  { std::cout << "My Value is " << m_value << std::endl; }

protected:
    int m_value;
};