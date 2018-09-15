// MUD Programming
// Ron Penton
// (C)2003
// Room.h - The class defining Rooms in the SimpleEditor
// 
// 


#ifndef SIMPLEMUDROOM_H
#define SIMPLEMUDROOM_H

#include <string>
#include <iostream>
#include <list>
#include "BasicLib/BasicLib.h"

#include "Entity.h"
#include "Attributes.h"
#include "Item.h"

using std::ostream;
using std::istream;
using std::list;

namespace SimpleEdit
{


// --------------------------------------------------------------------
//  Class that stores information about rooms
// --------------------------------------------------------------------
class Room : public Entity
{
public:
    Room();


    void LoadTemplate( istream& p_stream );
    void SaveTemplate( ostream& p_stream );
    void LoadData( istream& p_stream );
    void SaveData( ostream& p_stream );


    // -----------------------------------------
    //  template information
    // -----------------------------------------
    RoomType m_type;
    int m_data;         // auxilliary data defined by room type
    string m_description;
    entityid m_rooms[NUMDIRECTIONS];

    entityid m_spawnwhich;
    int m_maxenemies;


    // -----------------------------------------
    //  volatile data (save to disk)
    // -----------------------------------------
    list<entityid> m_items;
    money m_money;

};  // end class Room






}   // end namespace SimpleEdit


#endif
