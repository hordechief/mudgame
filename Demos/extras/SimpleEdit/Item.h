// MUD Programming
// Ron Penton
// (C)2003
// Item.h - The class defining Items in the SimpleEditor
// 
// 


#ifndef SIMPLEMUDITEM_H
#define SIMPLEMUDITEM_H

#include <string>
#include <iostream>
#include "BasicLib/BasicLib.h"
#include "Entity.h"
#include "Attributes.h"

using std::ostream;
using std::istream;

namespace SimpleEdit
{

typedef unsigned long int money;

// --------------------------------------------------------------------
//  Class that stores information about items
// --------------------------------------------------------------------
class Item : public Entity
{
public:
    Item()
    {
        m_type = WEAPON;
        m_min = 0;
        m_max = 0;
        m_speed = 0;
        m_price = 0;
    }


    ItemType m_type;

    // item attributes
    int m_min;
    int m_max;
    int m_speed;
    money m_price;

    // player modification attributes
    AttributeSet m_attributes;

};  // end class Item

inline ostream& operator<<( ostream& p_stream, const Item& i )
{
    p_stream << "[NAME]           " << i.m_name << "\n";
    p_stream << "[TYPE]           " << GetItemTypeString( i.m_type ) << "\n";
    p_stream << "[MIN]            " << i.m_min << "\n";
    p_stream << "[MAX]            " << i.m_max << "\n";
    p_stream << "[SPEED]          " << i.m_speed << "\n";
    p_stream << "[PRICE]          " << i.m_price <<"\n";
    p_stream << i.m_attributes << "\n";


    return p_stream;
}

inline istream& operator>>( istream& p_stream, Item& i )
{
    std::string temp;

    p_stream >> temp >> std::ws;     std::getline( p_stream, i.m_name );
    p_stream >> temp >> temp;         i.m_type = GetItemType( temp );
    p_stream >> temp >> i.m_min;
    p_stream >> temp >> i.m_max;
    p_stream >> temp >> i.m_speed;
    p_stream >> temp >> i.m_price;
    p_stream >> i.m_attributes;

    return p_stream;
}


}   // end namespace SimpleEdit


#endif
