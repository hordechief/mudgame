// MUD Programming
// Ron Penton
// (C)2003
// Databases.h - Stores the entity databases for the SimpleEditor
// 
// 


#ifndef SIMPLEMUDDATABASES_H
#define SIMPLEMUDDATABASES_H

#include <map>
#include "Entity.h"
#include "Item.h"
#include "Player.h"
#include "Room.h"
#include "Store.h"
#include "Enemy.h"
using std::map;

namespace SimpleEdit
{
map<entityid, Item>          g_items;
map<entityid, Player>        g_players;
map<entityid, Room>          g_rooms;
map<entityid, Store>         g_stores;
map<entityid, EnemyTemplate> g_enemytemplates;

using std::ofstream;
using std::ifstream;
using std::ios;


template< class db >
entityid FindOpenID( db& p_db )
{
    if( p_db.size() == 0 )
        return 1;

    if( p_db.size() == p_db.rend()->first )
        return p_db.size() + 1;

    entityid openid = 0;
    entityid previous = 0;
    db::iterator itr = p_db.begin();

    while( !openid )
    {
        if( itr->first != previous + 1 )
            openid = previous + 1;
        else
            previous = itr->first;
        ++itr;
    }

    return openid;
}



void LoadItems()
{
    ifstream f( "items/items.itm", ios::binary );
    std::string temp;
    entityid id;

    f >> std::ws;
    while( f.good() )
    {
        f >> temp >> id;
        f >> g_items[id];
        f >> std::ws;
    }
}

void SaveItems()
{
    ofstream f( "items/items.itm", ios::binary );

    map<entityid, Item>::iterator itr = g_items.begin();
    while( itr != g_items.end() )
    {
        f << "[ID]            " << itr->first << "\n";
        f << itr->second << "\n";
        ++itr;
    }
}

void LoadPlayers()
{
    ifstream listtxt( "players/players.txt", ios::binary );

    std::string temp;
    entityid id;

    listtxt >> std::ws;
    while( listtxt.good() )
    {
        listtxt >> temp >> std::ws;     // read name
        std::string name = "players/" + temp + ".plr";
        ifstream f( name.c_str() );

        f >> temp >> id;                // read ID
        f >> g_players[id];             // read player
    }
}

void SavePlayers()
{
    ofstream listtxt( "players/players.txt", ios::binary );

    std::map<entityid, Player>::iterator itr = g_players.begin();

    while( itr != g_players.end() )
    {
        listtxt << itr->second.m_name << "\n";

        std::string name = "players/" + itr->second.m_name + ".plr";
        ofstream f( name.c_str(), ios::binary );

        f << "[ID]             " << itr->first << "\n";
        f << itr->second << "\n";

        ++itr;
    }
}

void LoadRooms();
void SaveRooms();

void LoadStores();
void SaveStores();

void LoadEnemyTemplates();
void SaveEnemyTemplates();

}   // end namespace SimpleEdit

using namespace SimpleEdit;

#endif