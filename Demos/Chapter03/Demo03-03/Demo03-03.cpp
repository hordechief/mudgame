// MUD Programming
// Ron Penton
// (C)2003
// Demo03-03.cpp - Mutexes
// This program runs three threads, one which manages two child threads, 
// and two child threads that alternate printing a letter.


#include <iostream>
using namespace std;

#include "ThreadLib/ThreadLib.h"

ThreadLib::Mutex m;

void PrintThread( void* data )
{
    // convert the data passed in into a character.
    char c = (int)data;

    for( int i = 0; i < 200; i++ )
    {
        m.Lock();
        for( int j = 0; j < 50; j++ )
        {
            cout << c;
            cout.flush();
        }
        m.Unlock();
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



