// MUD Programming
// Ron Penton
// (C)2003
// StoreDatabase.cpp - The class that stores all of the stores within the MUD
// 
// 

#include <fstream>
#include "BasicLib/BasicLib.h"
#include "SimpleMUDLogs.h"
#include "StoreDatabase.h"

using BasicLib::LowerCase;
using BasicLib::tostring;

namespace SimpleMUD
{

// declare the static map of the Item database.
std::map<entityid, Store> EntityDatabase<Store>::m_map;


bool StoreDatabase::Load()
{
    std::ifstream file( "stores/stores.str" );
    entityid id;
    std::string temp;

    while( file.good() )
    {
        file >> temp >> id;                         // load ID
        m_map[id].ID() = id;
        file >> m_map[id] >> std::ws;               // load store
        USERLOG.Log( "Loaded Store: " + m_map[id].Name() );     // log it
    }
    return true;
}






}   // end namespace SimpleMUD
