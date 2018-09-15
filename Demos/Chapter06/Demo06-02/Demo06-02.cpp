// MUD Programming
// Ron Penton
// (C)2003
// Demo06-02.cpp - A simple chat server
// 
// 

#include "SocketLib/SocketLib.h"
#include "SCUserDB.h"
#include "SCLogon.h"
#include "SCChat.h"


int main()
{
    using SocketLib::Telnet;

    SocketLib::ListeningManager<Telnet, SCLogon> lm;
    SocketLib::ConnectionManager<Telnet, SCLogon> cm( 128 );

    lm.SetConnectionManager( &cm );
    lm.AddPort( 5099 );

    while( 1 )
    {
        lm.Listen();
        cm.Manage();
        ThreadLib::YieldThread();
    }
}
