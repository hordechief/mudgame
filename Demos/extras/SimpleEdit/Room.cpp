// MUD Programming
// Ron Penton
// (C)2003
// Room.cpp - The class defining Rooms in the SimpleEdit
// 
// 



#include <string>
#include <iostream>

#include "Room.h"
#include "Enemy.h"
#include "BasicLib/BasicLib.h"

using std::ostream;
using std::istream;
using BasicLib::extract;

namespace SimpleEdit
{

Room::Room()
{
    m_type = PLAINROOM;
    m_data = 0;
    
    m_description = "UNDEFINED";

    for( int d = 0; d < NUMDIRECTIONS; d++ )
        m_rooms[d] = 0;

    m_spawnwhich = 0;
    m_maxenemies = 0;
    m_money = 0;
}



void Room::LoadTemplate( istream& p_stream )
{
    string temp;

    p_stream >> temp >> std::ws;    std::getline( p_stream, m_name );
    p_stream >> temp >> std::ws;    std::getline( p_stream, m_description );
    p_stream >> temp >> temp;       m_type = GetRoomType( temp );
    p_stream >> temp >> m_data;

    for( int d = 0; d < NUMDIRECTIONS; d++ )
        p_stream >> temp >> m_rooms[d];

    p_stream >> temp >> m_spawnwhich;
    p_stream >> temp >> m_maxenemies;
}

void Room::SaveTemplate( ostream& p_stream )
{
    p_stream << "[NAME]          " << m_name << "\n";
    p_stream << "[DESCRIPTION]   " << m_description << "\n";
    p_stream << "[TYPE]          " << GetRoomTypeString( m_type ) << "\n";
    p_stream << "[DATA]          " << m_data << "\n";
    p_stream << "[NORTH]         " << m_rooms[NORTH] << "\n";
    p_stream << "[EAST]          " << m_rooms[EAST] << "\n";
    p_stream << "[SOUTH]         " << m_rooms[SOUTH] << "\n";
    p_stream << "[WEST]          " << m_rooms[WEST] << "\n";
    p_stream << "[ENEMY]         " << m_spawnwhich << "\n";
    p_stream << "[MAXENEMIES]    " << m_maxenemies << "\n";
}



void Room::LoadData( istream& p_stream )
{
    string temp;
    p_stream >> temp;

    // clear all the existing items, then load in all the new items
    m_items.clear();        
    entityid last;
    while( extract( p_stream, last ) != 0 )
        m_items.push_back( last );

    // load in the money
    p_stream >> temp;   p_stream >> m_money;
}

void Room::SaveData( ostream& p_stream )
{
    p_stream << "[ITEMS] ";
    
    std::list<entityid>::iterator itr = m_items.begin();
    while( itr != m_items.end() )
    {
        p_stream << *itr << " ";
        ++itr;
    }

    p_stream << "0\n";

    p_stream << "[MONEY] " << m_money << "\n";
}



}   // end namespace SimpleMUD

