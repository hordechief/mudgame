// MUD Programming
// Ron Penton
// (C)2003
// Demo06-01.cpp - Basic Telnet Server
// 
// 


#include "SocketLib/SocketLib.h"
#include <iostream>

using namespace SocketLib;

int main() 
{
    ListeningSocket lsock;              // the listening socket
    DataSocket dsock;                   // the data socket
    char buffer[128];                   // the buffer of data
    int size = 0;                       // size of data in the buffer
    int received;                       // number of bytes received
    
    lsock.Listen( 5098 );               // listen on port 5098
    dsock = lsock.Accept();             // wait for a connection

    dsock.Send( "Hello!\r\n", 8 );

    while( true ) 
    {
        // receive as much data as there is room for
        received = dsock.Receive( buffer + size, 128 - size );
        size += received;

        // process "Enter" characters
        if( buffer[size - 1] == '\n' ) 
        {
            // print out the size of the string
            std::cout << size << std::endl;

            // send the string back to the client
            dsock.Send( buffer, size );

            // reset the size
            size = 0;
        }
    }
    return 0;
}
