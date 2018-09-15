// MUD Programming
// Ron Penton
// (C)2003
// Player.h - The class defining Players in the SimpleEditor
// 
// 


#ifndef PLAYER_H
#define PLAYER_H

#include <math.h>
#include <string>
#include "BasicLib/BasicLib.h"

#include "Entity.h"
#include "Attributes.h"
#include "Item.h"

using namespace BasicLib;
using std::ostream;
using std::istream;
using std::string;

namespace SimpleEdit
{

const int PLAYERITEMS = 16;

class Player : public Entity
{
public:

    Player();

    // -----------------------------------------
    //  Player Information
    // -----------------------------------------
    string m_pass;
    PlayerRank m_rank;

    // -----------------------------------------
    //  Player attributes
    // -----------------------------------------
    int m_statpoints;
    int m_experience;
    int m_level;
    entityid m_room;
    money m_money;
    int m_hitpoints;

    AttributeSet m_attributes;
    AttributeSet m_baseattributes;

    BasicLib::sint64 m_nextattacktime;

    // -----------------------------------------
    //  Player Inventory
    // -----------------------------------------
    entityid m_inventory[PLAYERITEMS];
    int m_items;
    int m_weapon;
    int m_armor;

    void RecalculateStats();

    inline int GetAttr( int p_attr )
    {
        // calculate the base value plus the temporary calculated value:
        int val = m_attributes[p_attr] + m_baseattributes[p_attr];

        if( p_attr == STRENGTH || p_attr == AGILITY || p_attr == HEALTH )
        {
            // return 1 if the value is less than 1
            if( val < 1 )
                return 1;
        }
        
        return val;
    }

};  // end class Player



ostream& operator<<( ostream& p_stream, const Player& p );
istream& operator>>( istream& p_stream, Player& p );


}   // end namespace SimpleEdit


#endif
