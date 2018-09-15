// MUD Programming
// Ron Penton
// (C)2003
// Store.h - The class defining Stores in the SimpleEditor
// 
// 


#ifndef SIMPLEMUDSTORE_H
#define SIMPLEMUDSTORE_H

#include <string>
#include <iostream>
#include <list>
#include <utility>
#include "BasicLib/BasicLib.h"

#include "Entity.h"
#include "Item.h"

using std::ostream;
using std::istream;
using namespace BasicLib;

namespace SimpleEdit
{

// --------------------------------------------------------------------
//  Class that stores information about stores
// --------------------------------------------------------------------
class Store : public Entity
{
public:
    std::list<entityid> m_items;
};  // end class Room




inline ostream& operator<<( ostream& p_stream, Store& s )
{
    // read name
    p_stream << "[ID]        " << s.m_name << "\n";
    p_stream << "[ITEMS]     ";

    std::list<entityid>::iterator itr = s.m_items.begin();
    while( itr != s.m_items.end() )
    {
        p_stream << *itr << " ";
    }

    p_stream << "\n\n";
   
    return p_stream;
}



inline istream& operator>>( istream& p_stream, Store& s )
{
    string temp;

    // read name
    p_stream >> temp >> std::ws;    std::getline( p_stream, s.m_name );

    // clear the item listing on load, in case this is being reloaded
    s.m_items.clear();      

    // now load in the item listing.
    entityid last;
    p_stream >> temp;                           // chew up "[ITEMS]" tag

    while( extract( p_stream, last ) != 0 )     // loop while item ID's valid
        s.m_items.push_back( last );            // add item
    
    return p_stream;
}




}   // end namespace SimpleEdit


#endif
