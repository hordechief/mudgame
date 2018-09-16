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

#include "SocketLib/SocketLibSocket.h"
#include "SocketLib/SocketSet.h"
using namespace SocketLib;

#include "SocketLib/SocketLibSystem.h"

int main()
{	
    int err;                    // for getting errors
    
	ListeningSocket lsock;
	lsock.Listen(4000);
	DataSocket dsock;
	
	char buffer[128] = "Hello There!"; 
    
    bool done = false;          // used for quitting
    vector<DataSocket>::iterator itr;
    vector<DataSocket> socketlist;     // list of sockets
    
    while( !done ){
    	
        SocketSet sset;
		    	
    	// add listen sockets
    	sset.AddSocket( lsock );
    	
        // add all of the data sockets
        for( itr = socketlist.begin(); itr != socketlist.end(); itr++ )
        {
            sset.AddSocket( *itr );
//            cout << "add all of the data sockets " << itr->GetSock() << "..." << endl;
        }
        
        int active = sset.Poll( 1000 );
        if(active)
		{
        	if(sset.HasActivity(lsock))
			{
			    DataSocket dsock;
			    dsock = lsock.Accept();
			    socketlist.push_back( dsock );
            }		
		
            // loop through each socket and see if it has any activity
            for( itr = socketlist.begin(); itr != socketlist.end(); itr++ )
            {
            	if(sset.HasActivity(*itr))
            	{
	            	// incomming data
	                cout << "receiving data from socket " << itr->GetSock() << "..." << endl;

	                try
					{					
		                err = itr->Receive(buffer, 128);
		                if(err){
		                	cout << "Data: " << buffer << endl;
						}
		            }
		            catch(Exception& e)
					{				
		            	cout << "Exception Error: " << err << endl;
		            	socketlist.erase( itr );
		            	itr--;
		            }
	
	                // if the message was "servquit", then quit the server.
	                if( strcmp( buffer, "servquit" ) == 0 )
	                    done = true;
                }
            }
		}	
	}

	return 0;

}







