// MUD Programming
// Ron Penton
// (C)2003
// Enemy.h - The class defining Enemies in the SimpleEditor
// 
// 


#ifndef ENEMY_H
#define ENEMY_H

#include <list>
#include "BasicLib/BasicLib.h"
#include "Item.h"

using std::ostream;
using std::istream;
using std::list;
using BasicLib::sint64;

namespace SimpleEdit
{


typedef std::pair< entityid, int > loot;

class EnemyTemplate : public Entity
{
public:

    EnemyTemplate();
    int m_hitpoints;
    int m_accuracy;
    int m_dodging;
    int m_strikedamage;
    int m_damageabsorb;
    int m_experience;
    entityid m_weapon;
    money m_moneymin;
    money m_moneymax;

    list<loot> m_loot;

};  // end class EnemyTemplate





ostream& operator<<( ostream& p_stream, EnemyTemplate& t );
istream& operator>>( istream& p_stream, EnemyTemplate& t );






}   // end namespace SimpleEdit


#endif
