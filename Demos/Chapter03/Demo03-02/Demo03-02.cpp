// MUD Programming
// Ron Penton
// (C)2003
// Demo03-02.cpp - Yielding
// This program runs three threads, one which manages two child threads, 
// and two child threads that alternate printing a letter.


#include <iostream>
using namespace std;

#include "ThreadLib/ThreadLib.h"

void PrintThread( void* data )
{
    // convert the data passed in into a character.
    char c = (int)data;

    for( int i = 0; i < 10000; i++ )
    {
        cout << c;
        cout.flush();
        ThreadLib::YieldThread();
    }
}


int main()
{
    ThreadLib::ThreadID a, b;

    a = ThreadLib::Create( PrintThread, (void*)'a' );
    b = ThreadLib::Create( PrintThread, (void*)'b' );


    ThreadLib::WaitForFinish( b );
    ThreadLib::WaitForFinish( a );

    char c;
    cin >> c;

    return 0;
}



