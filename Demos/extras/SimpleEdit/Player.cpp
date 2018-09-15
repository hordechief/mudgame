// MUD Programming
// Ron Penton
// (C)2003
// Player.cpp - The class defining Players in the SimpleEditor
// 
// 

#include <cmath>
#include <string>
#include <fstream>
#include <vector>

#include "Player.h"
#include "Item.h"

namespace SimpleEdit
{



Player::Player()
{
    m_pass = "UNDEFINED";
    m_rank = REGULAR;

    m_experience = 0;
    m_level = 1;
    m_room = 1;
    m_money = 0;

    m_nextattacktime = 0;

    m_baseattributes[STRENGTH] = 1;
    m_baseattributes[HEALTH]   = 1;
    m_baseattributes[AGILITY]  = 1;

    m_items = 0;
    m_weapon = -1;
    m_armor = -1;

    m_statpoints = 18;

    m_hitpoints = 0;

    for( int i = 0; i < 16; i++ )
        m_inventory[i] = 0;
}

void Player::RecalculateStats()
{
    m_attributes[MAXHITPOINTS] = 
        10 + ( (int)(m_level * ( GetAttr( HEALTH ) / 1.5 )) );

    m_attributes[HPREGEN] = 
        ( GetAttr( HEALTH ) / 5 ) + m_level;

    m_attributes[ACCURACY] = GetAttr( AGILITY ) * 3;
    m_attributes[DODGING] = GetAttr( AGILITY ) * 3;
    m_attributes[DAMAGEABSORB] = GetAttr( STRENGTH ) / 5;
    m_attributes[STRIKEDAMAGE] = GetAttr( STRENGTH ) / 5;
}

// --------------------------------------------------------------------
//  Inserts an item in text form into a stream
// --------------------------------------------------------------------
ostream& operator<<( ostream& p_stream, const Player& p )
{
    p_stream << "[NAME]           " << p.m_name << "\n";
    p_stream << "[PASS]           " << p.m_pass << "\n";
    p_stream << "[RANK]           " << GetRankString( p.m_rank ) << "\n";
    p_stream << "[STATPOINTS]     " << p.m_statpoints << "\n";
    p_stream << "[EXPERIENCE]     " << p.m_experience << "\n";
    p_stream << "[LEVEL]          " << p.m_level << "\n";
    p_stream << "[ROOM]           " << p.m_room << "\n";
    p_stream << "[MONEY]          " << p.m_money << "\n";
    p_stream << "[HITPOINTS]      " << p.m_hitpoints << "\n";
    p_stream << "[NEXTATTACKTIME] "; insert( p_stream, p.m_nextattacktime );
    p_stream << "\n";
    p_stream << p.m_baseattributes;

    p_stream << "[INVENTORY]      ";
    for( int i = 0; i < 16; i++ )
    {
        p_stream << p.m_inventory[i] << " ";
    }
    p_stream << "\n";


    p_stream << "[WEAPON]         " << p.m_weapon << "\n";
    p_stream << "[ARMOR]          " << p.m_armor << "\n";

    return p_stream;
}


// --------------------------------------------------------------------
//  Extracts an item in text form from a stream
// --------------------------------------------------------------------
istream& operator>>( istream& p_stream, Player& p )
{
    std::string temp;
    p_stream >> temp >> std::ws;
    std::getline( p_stream, p.m_name );
    p_stream >> temp >> p.m_pass;
    p_stream >> temp >> temp;
    p.m_rank = GetRank( temp );
    p_stream >> temp >> p.m_statpoints;
    p_stream >> temp >> p.m_experience;
    p_stream >> temp >> p.m_level;
    p_stream >> temp >> p.m_room;
    p_stream >> temp >> p.m_money;
    p_stream >> temp >> p.m_hitpoints;
    p_stream >> temp; extract( p_stream, p.m_nextattacktime );
    p_stream >> p.m_baseattributes;

    p_stream >> temp;
    p.m_items = 0;
    for( int i = 0; i < 16; i++ )
    {
        p_stream >> p.m_inventory[i];
        if( p.m_inventory[i] != 0 )   
            p.m_items++;
    }

    p_stream >> temp >> p.m_weapon;
    p_stream >> temp >> p.m_armor;

    return p_stream;
}




}   // end namespace SimpleMUD
