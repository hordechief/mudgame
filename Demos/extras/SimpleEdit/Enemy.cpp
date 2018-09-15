// MUD Programming
// Ron Penton
// (C)2003
// Enemy.cpp - The class defining Enemies in the SimpleEditor
// 
// 

#include "Enemy.h"
#include "Player.h"
#include "Item.h"
#include "BasicLib/BasicLib.h"

namespace SimpleEdit
{



EnemyTemplate::EnemyTemplate()
{
    m_hitpoints = 0;
    m_accuracy = 0;
    m_dodging = 0;
    m_strikedamage = 0;
    m_damageabsorb = 0;
    m_experience = 0;
    m_weapon = 0;
    m_moneymin = 0;
    m_moneymax = 0;
}


ostream& operator<<( ostream& p_stream, EnemyTemplate& t )
{
    p_stream << "[NAME]          " << t.m_name << "\n";
    p_stream << "[HITPOINTS]     " << t.m_hitpoints << "\n";
    p_stream << "[ACCURACY]      " << t.m_accuracy << "\n";
    p_stream << "[DODGING]       " << t.m_dodging << "\n";
    p_stream << "[STRIKEDAMAGE]  " << t.m_strikedamage << "\n";
    p_stream << "[DAMAGEABSORB]  " << t.m_damageabsorb << "\n";
    p_stream << "[EXPERIENCE]    " << t.m_experience << "\n";
    p_stream << "[WEAPON]        " << t.m_weapon << "\n";
    p_stream << "[MONEYMIN]      " << t.m_moneymin << "\n";
    p_stream << "[MONEYMAX]      " << t.m_moneymax << "\n";

    std::list<loot>::iterator itr = t.m_loot.begin();
    while( itr != t.m_loot.end() )
    {
        p_stream << "[LOOT]          " << itr->first << itr->second << "\n";
        ++itr;
    }

    p_stream << "[ENDLOOT]\n\n";

    return p_stream;
}



// --------------------------------------------------------------------
//  reads an enemy template from a stream
// --------------------------------------------------------------------
istream& operator>>( istream& p_stream, EnemyTemplate& t )
{
    std::string temp;

    p_stream >> temp >> std::ws;  std::getline( p_stream, t.m_name );
    p_stream >> temp >> t.m_hitpoints;
    p_stream >> temp >> t.m_accuracy;
    p_stream >> temp >> t.m_dodging;
    p_stream >> temp >> t.m_strikedamage;
    p_stream >> temp >> t.m_damageabsorb;
    p_stream >> temp >> t.m_experience;
    p_stream >> temp >> t.m_weapon;
    p_stream >> temp >> t.m_moneymin;
    p_stream >> temp >> t.m_moneymax;

    t.m_loot.clear();
    while( extract( p_stream, temp ) != "[ENDLOOT]" )
    {
        entityid id;
        int chance;
        p_stream >> id >> chance;
        t.m_loot.push_back( loot( id, chance ) );
    }

    return p_stream;
}


}   // end namespace SimpleEdit
