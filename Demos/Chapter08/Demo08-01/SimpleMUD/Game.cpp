// MUD Programming
// Ron Penton
// (C)2003
// Game.cpp - This class is the game handler for SimpleMUD.
// 
// 

#include "Logon.h"
#include "Game.h"
#include "Train.h"
#include "ItemDatabase.h"
#include "PlayerDatabase.h"
#include "BasicLib/BasicLib.h"

using namespace SocketLib;
using namespace BasicLib;
using std::string;

namespace SimpleMUD
{


// declare the static instance of the timer
BasicLib::Timer Game::s_timer;
bool Game::s_running = false;

// ------------------------------------------------------------------------
//  This handles incomming commands. Anything passed into this function
//  is assumed to be a complete command from a client.
// ------------------------------------------------------------------------
void Game::Handle( string p_data )
{
    Player& p = *m_player;

    // check if the player wants to repeat a command
    if( p_data == "/" )
    {
        p_data = m_lastcommand;
    }
    else
    {
        // if not, record the command.
        m_lastcommand = p_data;
    }

    // get the first word and lowercase it.
    string firstword = BasicLib::LowerCase( ParseWord( p_data, 0 ) );


    // ------------------------------------------------------------------------
    //  REGULAR access commands
    // ------------------------------------------------------------------------
    if( firstword == "chat" || firstword == ":" )
    {
        string text = RemoveWord( p_data, 0 );
        SendGame( white + bold + p.Name() + " chats: " + text );
        return;
    }

    if( firstword == "experience" || firstword == "exp" )
    {
        p.SendString( PrintExperience() );
        return;
    }

    if( firstword == "help" || firstword == "commands" )
    {
        p.SendString( PrintHelp( p.Rank() ) );
        return;
    }

    if( firstword == "inventory" || firstword == "inv" )
    {
        p.SendString( PrintInventory() );
        return;
    }

    if( firstword == "quit" )
    {
        m_connection->Close();
        LogoutMessage( p.Name() + " has left the realm." );
        return;
    }

    if( firstword == "remove" )
    {
        RemoveItem( ParseWord( p_data, 1 ) );
        return;
    }

    if( firstword == "stats" || firstword == "st" )
    {
        p.SendString( PrintStats() );
        return;
    }

    if( firstword == "time" )
    {
        p.SendString( bold + cyan + 
                      "The current system time is: " + BasicLib::TimeStamp() + 
                      " on " + BasicLib::DateStamp() + 
                      "\r\nThe system has been up for: " 
                      + s_timer.GetString() + "." );
        return;
    }

    if( firstword == "use" )
    {
        UseItem( RemoveWord( p_data, 0 ) );
        return;
    }

    if( firstword == "whisper" )
    {
        // get the players name
        string name = ParseWord( p_data, 1 );
        string message = RemoveWord( RemoveWord( p_data, 0 ), 0 );

        Whisper( message, name );
        return;
    }

    if( firstword == "who" )
    {
        p.SendString( WhoList( BasicLib::LowerCase( ParseWord( p_data, 1 ) ) ) );
        return;
    }


    // ------------------------------------------------------------------------
    //  GOD access commands
    // ------------------------------------------------------------------------
    if( firstword == "kick" && p.Rank() >= GOD )
    {
        // find a player to kick
        PlayerDatabase::iterator itr = 
            PlayerDatabase::findloggedin( ParseWord( p_data, 1 ) );

        if( itr == PlayerDatabase::end() )
        {
            p.SendString( red + bold + "Player could not be found." );
            return;
        }

        if( itr->Rank() > p.Rank() )
        {
            p.SendString( red + bold + "You can't kick that player!" );
            return;
        }
            
        itr->Conn()->Close();
        LogoutMessage( itr->Name() + " has been kicked by " + 
                        p.Name() + "!!!" );

        return;
    }


    // ------------------------------------------------------------------------
    //  ADMIN access commands
    // ------------------------------------------------------------------------
    if( firstword == "announce" && p.Rank() >= ADMIN )
    {
        Announce( RemoveWord( p_data, 0 ) );
        return;
    }

    if( firstword == "changerank" && p.Rank() >= ADMIN )
    {
        string name = ParseWord( p_data, 1 );

        PlayerDatabase::iterator itr = PlayerDatabase::find( name );

        if( itr == PlayerDatabase::end() )
        {
            p.SendString( red + bold + "Error: Could not find user " +
                          name );
            return;
        }

        PlayerRank rank = GetRank( ParseWord( p_data, 2 ) );

        itr->Rank() = rank;
        SendGame( green + bold + itr->Name() + 
                  "'s rank has been changed to: " +
                  GetRankString( rank ) );
        return;
    }


    if( firstword == "reload" && p.Rank() >= ADMIN )
    {
        string db = BasicLib::LowerCase( ParseWord( p_data, 1 ) );

        if( db == "items" )
        {
            ItemDatabase::Load();
            p.SendString( bold + cyan + "Item Database Reloaded!" );
        }
        else
        {
            p.SendString( bold + red + "Invalid Database Name" );
        }
        return;
    }

    if( firstword == "shutdown" && p.Rank() >= ADMIN )
    {
        Announce( "SYSTEM IS SHUTTING DOWN" );
        Game::Running() = false;
        return;
    }


    // ------------------------------------------------------------------------
    //  Command not recognized, send to room
    // ------------------------------------------------------------------------
    SendGame( bold + p.Name() + " chats: " + p_data );
}


// ------------------------------------------------------------------------
//  This notifies the handler that there is a new connection
// ------------------------------------------------------------------------
void Game::Enter()
{
    USERLOG.Log(  GetIPString( m_connection->GetRemoteAddress() ) + 
                  " - User " + m_player->Name() + 
                  " entering Game state." );

    m_lastcommand = "";

    Player& p = *m_player;
    p.Active() = true;
    p.LoggedIn() = true;

    SendGame( bold + green + p.Name() + " has entered the realm." );

    if( p.Newbie() )
        GotoTrain();
}

void Game::Leave()
{
    // deactivate player
    m_player->Active() = false;

    // log out the player from the database if the connection has been closed
    if( m_connection->Closed() )
    {
        PlayerDatabase::Logout( m_player );
    }
}

// ------------------------------------------------------------------------
//  This notifies the handler that a connection has unexpectedly hung up.
// ------------------------------------------------------------------------
void Game::Hungup()
{
    Player& p = *m_player;
    LogoutMessage( p.Name() + " has suddenly disappeared from the realm." );
}

// ------------------------------------------------------------------------
//  This notifies the handler that a connection is being kicked due to 
//  flooding the server.
// ------------------------------------------------------------------------
void Game::Flooded()
{
    Player& p = *m_player;
    LogoutMessage( p.Name() + " has been kicked for flooding!" );
}

// ------------------------------------------------------------------------
//  Sends a string to everyone connected.
// ------------------------------------------------------------------------
void Game::SendGlobal( const string& p_str )
{
    operate_on_if( PlayerDatabase::begin(),
                   PlayerDatabase::end(),
                   playersend( p_str ),
                   playerloggedin() );
}

// ------------------------------------------------------------------------
//  Sends a string to everyone "within the game"
// ------------------------------------------------------------------------
void Game::SendGame( const std::string& p_str )
{
    operate_on_if( PlayerDatabase::begin(),
                   PlayerDatabase::end(),
                   playersend( p_str ),
                   playeractive() );
}

// ------------------------------------------------------------------------
//  Sends a logout message
// ------------------------------------------------------------------------
void Game::LogoutMessage( const string& p_reason )
{
    SendGame( SocketLib::red + SocketLib::bold + p_reason );
}

// ------------------------------------------------------------------------
//  Sends a system announcement
// ------------------------------------------------------------------------
void Game::Announce( const string& p_announcement )
{
    SendGlobal( SocketLib::cyan + SocketLib::bold + 
                "System Announcement: " + p_announcement );
}

// ------------------------------------------------------------------------
//  Sends a whisper string to the requested player
// ------------------------------------------------------------------------
void Game::Whisper( std::string p_str, std::string p_player )
{
    // find the player
    PlayerDatabase::iterator itr = PlayerDatabase::findactive( p_player );
    
    // if no match was found
    if( itr == PlayerDatabase::end() )
    {
        m_player->SendString( red + bold + "Error, cannot find user." );
    }
    else
    {
        itr->SendString( yellow + m_player->Name() + " whispers to you: " + 
                         reset + p_str );

        m_player->SendString( yellow + "You whisper to " + itr->Name() + 
                              ": " + reset + p_str );
    }
}

// ------------------------------------------------------------------------
//  Functor that generates a who-listing for a single player
// ------------------------------------------------------------------------
struct wholist
{
    string str;

    void operator() ( Player& p )
    {
        str += " " + tostring( p.Name(), 17 ) + "| ";
        str += tostring( p.Level(), 10 ) + "| ";
        
        
        if( p.Active() )
            str += green + "Online  " + white;
        else if( p.LoggedIn() )
            str += yellow + "Inactive" + white;
        else
            str += red + "Offline " + white;

        str += " | ";
        switch( p.Rank() )
        {
            case REGULAR:   str += white;   break;
            case GOD:       str += yellow;  break;
            case ADMIN:     str += green;   break;
        }

        str += GetRankString( p.Rank() );

        str += white + "\r\n";
    }
};

// ------------------------------------------------------------------------
//  This prints up the who-list for the realm.
// ------------------------------------------------------------------------
string Game::WhoList( const string& p_who )
{
    using namespace BasicLib;

    string str = white + bold +
        "--------------------------------------------------------------------------------\r\n" + 
        " Name             | Level     | Activity | Rank\r\n" + 
        "--------------------------------------------------------------------------------\r\n";

    wholist who;
    if( p_who == "all" )
    {
        who = BasicLib::operate_on_if( 
                        PlayerDatabase::begin(),
                        PlayerDatabase::end(),
                        wholist(),
                        always<Player>() );
    }
    else
    {
        who = BasicLib::operate_on_if( 
                        PlayerDatabase::begin(),
                        PlayerDatabase::end(),
                        wholist(),
                        playerloggedin() );
    }

    str += who.str;

    
    str +=
        "--------------------------------------------------------------------------------";

    return str;
}

// ------------------------------------------------------------------------
//  Prints out a help listing based on a user's rank.
// ------------------------------------------------------------------------
string Game::PrintHelp( PlayerRank p_rank )
{
    static string help = white + bold + 
        "--------------------------------- Command List ---------------------------------\r\n" + 
        " /                          - Repeats your last command exactly.\r\n" +
        " chat <mesg>                - Sends message to everyone in the game\r\n" +
        " experience                 - Shows your experience statistics\r\n" +
        " help                       - Shows this menu\r\n" +
        " inventory                  - Shows a list of your items\r\n" + 
        " quit                       - Allows you to leave the realm.\r\n" + 
        " remove <'weapon'/'armor'>  - removes your weapon or armor\r\n" + 
        " stats                      - Shows all of your statistics\r\n" + 
        " time                       - shows the current system time.\r\n" +
        " use <item>                 - use an item in your inventory\r\n" +
        " whisper <who> <msg>        - Sends message to one person\r\n" +
        " who                        - Shows a list of everyone online\r\n" +
        " who all                    - Shows a list of everyone\r\n" +
        " look                       - Shows you the contents of a room\r\n" +
        " north/east/south/west      - Moves in a direction\r\n" +
        " get/drop <item>            - Picks up or drops an item on the ground\r\n" +
        " train                      - Train to the next level (TR)\r\n" +
        " editstats                  - Edit your statistics (TR)\r\n" +
        " list                       - Lists items in a store (ST)\r\n" +
        " buy/sell <item>            - Buy or Sell an item in a store (ST)\r\n" +
        " attack <enemy>             - Attack an enemy\r\n";


    static string god = yellow + bold +
        "--------------------------------- God Commands ---------------------------------\r\n" + 
        " kick <who>                 - kicks a user from the realm\r\n";

    static string admin = green + bold +
        "-------------------------------- Admin Commands --------------------------------\r\n" + 
        " announce <msg>             - Makes a global system announcement\r\n" + 
        " changerank <who> <rank>    - Changes the rank of a player\r\n" + 
        " reload <db>                - Reloads the requested database\r\n" + 
        " shutdown                   - Shuts the server down\r\n";

    static string end = white + bold + 
        "--------------------------------------------------------------------------------";


    if( p_rank == REGULAR )
        return help + end;
    else if( p_rank == GOD )
        return help + god + end;
    else if( p_rank == ADMIN )
        return help + god + admin + end;
    else return "ERROR";

}

// ------------------------------------------------------------------------
//  This prints up the stats of the player
// ------------------------------------------------------------------------
string Game::PrintStats()
{
    using namespace BasicLib;
    Player& p = *m_player;

    return white + bold +
        "---------------------------------- Your Stats ----------------------------------\r\n" + 
        " Name:          " + p.Name() + "\r\n" +
        " Rank:          " + GetRankString( p.Rank() ) + "\r\n" + 
        " HP/Max:        " + tostring( p.HitPoints() ) + "/" + tostring( p.GetAttr( MAXHITPOINTS ) ) +
        "  (" + tostring( (int)(100*p.HitPoints()/p.GetAttr( MAXHITPOINTS )) ) + "%)\r\n" +
        PrintExperience() + "\r\n" + 
        " Strength:      " + tostring( p.GetAttr( STRENGTH ), 16 ) + 
        " Accuracy:      " + tostring( p.GetAttr( ACCURACY ) ) + "\r\n" +
        " Health:        " + tostring( p.GetAttr( HEALTH ), 16 ) + 
        " Dodging:       " + tostring( p.GetAttr( DODGING ) ) + "\r\n" +
        " Agility:       " + tostring( p.GetAttr( AGILITY ), 16 ) + 
        " Strike Damage: " + tostring( p.GetAttr( STRIKEDAMAGE ) ) + "\r\n" +
        " StatPoints:    " + tostring( p.StatPoints(), 16 ) + 
        " Damage Absorb: " + tostring( p.GetAttr( DAMAGEABSORB ) ) + "\r\n" +
        "--------------------------------------------------------------------------------";
}

// ------------------------------------------------------------------------
//  This prints up the experience of the player
// ------------------------------------------------------------------------
string Game::PrintExperience()
{
    using namespace BasicLib;
    Player& p = *m_player;

    return white + bold +
        " Level:         " + tostring( p.Level() ) + "\r\n" + 
        " Experience:    " + tostring( p.Experience() ) + "/" +
        tostring( p.NeedForLevel( p.Level() + 1 ) ) + " (" + 
        tostring( (int)(100 * p.Experience() / p.NeedForLevel( p.Level() + 1 ) ) ) + 
        "%)";
}

// ------------------------------------------------------------------------
//  This prints up the inventory-list of the player
// ------------------------------------------------------------------------
string Game::PrintInventory()
{
    using namespace BasicLib;
    Player& p = *m_player;

    // Inventory
    string itemlist = white + bold +
        "-------------------------------- Your Inventory --------------------------------\r\n" +
        " Items:  ";

    for( int i = 0; i < PLAYERITEMS; i++ )
    {
        if( p.GetItem( i ) != 0 )
        {
            itemlist += p.GetItem( i )->Name() + ", ";
        }
    }

    // chop off the extraneous comma, and add a newline.
    itemlist.erase( itemlist.size() - 2, 2 );
    itemlist += "\r\n";

    // Weapon/Armor
    itemlist += " Weapon: ";
    if( p.Weapon() == 0 )
        itemlist += "NONE!";
    else
        itemlist += p.Weapon()->Name();

    itemlist += "\r\n Armor:  ";
    if( p.Armor() == 0 )
        itemlist += "NONE!";
    else
        itemlist += p.Armor()->Name();

    // Money
    itemlist += "\r\n Money:  $" + tostring( p.Money() );

    itemlist +=
        "\r\n--------------------------------------------------------------------------------";
    
    return itemlist;
}

// ------------------------------------------------------------------------
//  This finds and attempts to "use" an item in your inventory.
// ------------------------------------------------------------------------
bool Game::UseItem( const std::string& p_item )
{
    Player& p = *m_player;

    int i = p.GetItemIndex( p_item );

    if( i == -1 )
    {
        p.SendString( red + bold + "Could not find that item!" );
        return false;
    }

    Item& itm = *p.GetItem( i );
    

    switch( itm.Type() )
    {
    case WEAPON:
        p.UseWeapon( i );
        return true;

    case ARMOR:
        p.UseArmor( i );
        return true;

    case HEALING:
        p.AddBonuses( itm.ID() );
        p.AddHitpoints( BasicLib::RandomInt( itm.Min(), itm.Max() ) );
        p.DropItem( i );
        return true;
    }
    return false;
}

// ------------------------------------------------------------------------
//  This removes your weapon or your armor
// ------------------------------------------------------------------------
bool Game::RemoveItem( std::string p_item )
{
    Player& p = *m_player;

    p_item = BasicLib::LowerCase( p_item );

    if( p_item == "weapon" && p.Weapon() != 0 )
    {
        p.RemoveWeapon();
        return true;
    }

    if( p_item == "armor" && p.Armor() != 0 )
    {
        p.RemoveArmor();
        return true;
    }

    p.SendString( red + bold + "Could not Remove item!" );
    return false;
}





void Game::GotoTrain()
{
    Player& p = *m_player;
    LogoutMessage( p.Name() + " leaves to edit stats" );
    m_connection->AddHandler( new Train( *m_connection, p.ID() ) );
}




}   // end namespace SimpleMUD
