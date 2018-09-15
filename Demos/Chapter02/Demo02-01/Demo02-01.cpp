// MUD Programming
// Ron Penton
// (C)2003
// Demo02-01.cpp - Hello Internet! Server
// This program will start up a server on port 4000, listen for a connection,
// then wait for 128 bytes of data, and print it out as a string.



// Code Block 2.1 - Header Includes
// This code block includes all of the standard Sockets API/Winsock headers
#ifdef WIN32                // windows 95 and above
    #include "winsock2.h"
    #include "Ws2tcpip.h"

#else                       // UNIX/Linux
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <unistd.h>
    #include <netdb.h>
    #include <arpa/inet.h>
#endif
// End Code Block 2.1 - Header Includes

#include <memory.h>

// Code Block 2.2 - Redefinitions and globals For Cross-Compatibility
#ifdef WIN32                // windows 95 and above
    WSADATA g_wsadata;      // winsock data holder
    #define CloseSocket closesocket
    #define GetSocketError WSAGetLastError
    #define StartSocketLib WSAStartup( MAKEWORD( 2, 2 ), &g_wsadata );
    #define CloseSocketLib WSACleanup();

    #ifndef socklen_t
        typedef int socklen_t;
    #endif
#else                       // Unix/Linux
    #define CloseSocket close
    #define GetSocketError errno
    #define StartSocketLib {}
    #define CloseSocketLib {}
#endif

// End Code Block 2.2 - Redefinitions and globals For Cross-Compatibility



#include <iostream>             // load the iostream library
using namespace std;            // use the std namespace

int main()
{
    int err;                    // for getting errors


    // start the socket library
    StartSocketLib;

    // BEGIN CODE BLOCK 2.3 - Create a Listening Socket on port 4000
    // create a socket
    int sock = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

    // check if socket was created
    if( sock == -1 )
    {
        cout << "Socket creation error!" << endl;
        return 0;
    }
    cout << "Socket created!" << endl;

    // create a sockaddr_in for binding, listening on port 4000
    struct sockaddr_in socketaddress;
    socklen_t sa_size = sizeof( struct sockaddr_in );
    socketaddress.sin_family = AF_INET;
    socketaddress.sin_port = htons( 4000 );
    socketaddress.sin_addr.s_addr = htonl( INADDR_ANY );
    memset( &(socketaddress.sin_zero), 0, 8 );

    // bind the socket
    err = bind( sock, (struct sockaddr*)&socketaddress, sa_size );

    if( err == -1 )
    {
        cout << "Socket binding error!" << endl;
        return 0;
    }
    cout << "Socket bound!" << endl;


    // listen on the socket
    err = listen( sock, 16 );

    if( err == -1 )
    {
        cout << "Socket listening error!" << endl;
        return 0;
    }
    cout << "Socket listening, waiting for connection..." << endl;
    // END CODE BLOCK 2.3 - Create a Listening Socket on port 4000


    // wait for an incomming connection now
    int datasock;
    datasock = accept( sock, (struct sockaddr*)&socketaddress, &sa_size );

    if( datasock == -1 )
    {
        cout << "Socket accepting error!" << endl;
        return 0;
    }
    cout << "Socket accepted, waiting for data..." << endl;


    // receive data
    char buffer[128];
    err = recv( datasock, buffer, 128, 0 );

    if( err == -1 )
    {
        cout << "Socket receiving error!" << endl;
        return 0;
    }

    cout << "Data received:" << endl;
    cout << buffer << endl;
    
    shutdown( datasock, 2 );
    CloseSocket( datasock );

    shutdown( sock, 2 );
    CloseSocket( sock );

    CloseSocketLib;
}







