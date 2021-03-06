// MUD Programming
// Ron Penton
// (C)2003
// ItemDatabase.cpp - The class that stores all of the items within the MUD
// 
// 

#include <fstream>
#include "BasicLib/BasicLib.h"
#include "SimpleMUDLogs.h"
#include "ItemDatabase.h"

using BasicLib::LowerCase;
using BasicLib::tostring;

namespace SimpleMUD
{

// declare the static map of the Item database.
std::map<entityid, Item> EntityDatabase<Item>::m_map;


bool ItemDatabase::Load()
{
    std::ifstream file( "items/items.itm" );
    entityid id;
    std::string temp;

    while( file.good() )
    {
        file >> temp >> id;
        m_map[id].ID() = id;
        file >> m_map[id] >> std::ws;
        USERLOG.Log( "Loaded Item: " + m_map[id].Name() );
    }
    return true;
}






}   // end namespace SimpleMUD
