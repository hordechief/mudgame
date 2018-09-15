// MUD Programming
// Ron Penton
// (C)2003
// Demo02-03.cpp - Hello Internet! Server v2
// This program will start up a server on port 4000, listen for connections, 
// receive data until the other side quits, and then close the connection, and
// wait for more data; all the while simulation other game functions.


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
#include <vector>
#include <string.h>             // for string manipulations
using namespace std;            // use the std namespace


int main()
{
    int err;                    // for getting errors
    int lsock;                  // listening socket
    vector<int> socketlist;     // list of sockets

    // start the socket library
    StartSocketLib;

    // BEGIN CODE BLOCK 2.3 - Create a Listening Socket on port 4000
    // create a socket
    lsock = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

    // check if socket was created
    if( lsock == -1 )
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
    err = bind( lsock, (struct sockaddr*)&socketaddress, sa_size );

    if( err == -1 )
    {
        cout << "Socket binding error!" << endl;
        return 0;
    }
    cout << "Socket bound!" << endl;


    // listen on the socket
    err = listen( lsock, 16 );

    if( err == -1 )
    {
        cout << "Socket listening error!" << endl;
        return 0;
    }
    cout << "Socket listening, waiting for connection..." << endl;
    // END CODE BLOCK 2.3 - Create a Listening Socket on port 4000


    fd_set rset;
    int i;

    struct timeval zerotime;
    zerotime.tv_usec = 0;
    zerotime.tv_sec = 0;

    char buffer[128];           // used for getting messages
    bool done = false;          // used for quitting
    vector<int>::iterator itr;

    // now begin the main loop.
    while( !done )
    {
        // clear the set
        FD_ZERO( &rset );

        // add the listening socket
        FD_SET( lsock, &rset );

        // add all of the data sockets
        for( itr = socketlist.begin(); itr != socketlist.end(); itr++ )
        {
            FD_SET( *itr, &rset );
        }
        
        // find out if there is any activity on any of the sockets.
        i = select( 0x7FFFFFFF, &rset, NULL, NULL, &zerotime );

        if( i > 0 )
        {
            if( FD_ISSET( lsock, &rset ) )
            {
                // incomming connection
                cout << "Incomming connection..." << endl;
                int dsock = accept( lsock, 
                                    (struct sockaddr*)&socketaddress, 
                                    &sa_size );
                if( dsock == -1 )
                {
                    cout << "Socket accepting error!" << endl;
                    return 0;
                }
                cout << "Socket " << dsock << " accepted." << endl;
                
                // add the socket to the list
                socketlist.push_back( dsock );
            }

            // loop through each socket and see if it has any activity
            for( itr = socketlist.begin(); itr != socketlist.end(); itr++ )
            {
                if( FD_ISSET( *itr, &rset ) )
                {
                    // incomming data
                    cout << "receiving data from socket ";
                    cout << *itr << "..." << endl;
                    err = recv( *itr, buffer, 128, 0 );

                    if( err == -1 )
                    {
                        cout << "Socket receiving error!" << endl;
                        return 0;
                    }
                    if( err == 0 )
                    {
                        cout << "Socket " << *itr << " closed" << endl;
                        shutdown( *itr, 2 );
                        CloseSocket( *itr );
                        socketlist.erase( itr );
                        itr--;
                    }
                    else
                    {

                        cout << "Data: " << buffer << endl;

                        // if the message was "servquit", then quit the server.
                        if( strcmp( buffer, "servquit" ) == 0 )
                            done = true;
                    }
                }
            }
        }

    }


    shutdown( lsock, 2 );
    CloseSocket( lsock );

    for( i = 0; i < socketlist.size(); i++ )
    {
        shutdown( socketlist[i], 2 );
        CloseSocket( socketlist[i] );
    }

    CloseSocketLib;
}







