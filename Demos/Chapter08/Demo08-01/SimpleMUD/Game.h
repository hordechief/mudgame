// MUD Programming
// Ron Penton
// (C)2003
// Game.h - This class is the game handler for SimpleMUD.
// 
// 

#ifndef SIMPLEMUDGAME_H
#define SIMPLEMUDGAME_H

#include "SocketLib/SocketLib.h"
#include "Player.h"
#include "PlayerDatabase.h"
#include "DatabasePointer.h"
#include "SimpleMUDLogs.h"
#include <string>

using SocketLib::Telnet;
using SocketLib::Connection;
using std::string;

namespace SimpleMUD
{



class Game : public Telnet::handler
{
    // typedef the class because MSVC6 isn't smart enough to construct
    // a "Telnet::handler" object, yet it will construct a typedef just
    // fine.  *boggle*
    typedef Telnet::handler thandler;
public:

    // ------------------------------------------------------------------------
    //  Construct the handler with a reference to the connection so that it can
    //  be used later on. Handlers are initialized only once, and cannot change
    //  connections. A flaw in MSVC6 neccessitated the typedeffing of
    //  Telnet::handler to thandler in order to call the base constructor.
    // ------------------------------------------------------------------------
    Game( Connection<Telnet>& p_conn, player p_player )
        : thandler( p_conn )
    {
        m_player = p_player;
    }

    // ------------------------------------------------------------------------
    //  Handler Functions
    // ------------------------------------------------------------------------
    void Handle( string p_data );
    void Enter();
    void Leave();
    void Hungup();
    void Flooded();
    void GotoTrain();

    // ------------------------------------------------------------------------
    //  sending functions
    // ------------------------------------------------------------------------
    static void SendGlobal( const string& p_str );
    static void SendGame( const string& p_str );
    static void LogoutMessage( const string& p_reason );
    static void Announce( const string& p_announcement );
    void Whisper( string p_str, string p_player );

    // ------------------------------------------------------------------------
    //  various status-printing functions
    // ------------------------------------------------------------------------
    static string WhoList( const string& p_who );
    static string PrintHelp( PlayerRank p_rank = REGULAR );
    string PrintStats();
    string PrintExperience();
    string PrintInventory();

    // ------------------------------------------------------------------------
    //  Inventory Functions
    // ------------------------------------------------------------------------
    bool UseItem( const string& p_item );
    bool RemoveItem( string p_item );

    // ------------------------------------------------------------------------
    //  Accessors
    // ------------------------------------------------------------------------
    inline static BasicLib::Timer& GetTimer()       { return s_timer; }
    inline static bool& Running()                   { return s_running; }



protected:

    player m_player;
    string m_lastcommand;

    static BasicLib::Timer s_timer;
    static bool s_running;


};  // end class Game



}   // end namespace SimpleMUD

#endif
