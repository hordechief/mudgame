// MUD Programming
// Ron Penton
// (C)2003
// Databases.h - Stores the entity databases for the SimpleEditor
// 
// 



#include <map>
#include <fstream>

#include "Entity.h"
#include "Item.h"
#include "Player.h"
#include "Room.h"
#include "Store.h"
#include "Enemy.h"
#include "BasicLib/BasicLib.h"

using namespace BasicLib;
using std::map;

namespace SimpleEdit
{
    extern map<entityid, Item>          g_items;
    extern map<entityid, Player>        g_players;
    extern map<entityid, Room>          g_rooms;
    extern map<entityid, Store>         g_stores;
    extern map<entityid, EnemyTemplate> g_enemytemplates;

    void LoadItems();
    void SaveItems();

    void LoadPlayers();
    void SavePlayer( std::string p_player );

    void LoadRooms();
    void SaveRooms();

    void LoadStores();
    void SaveStores();

    void LoadEnemyTemplates();
    void SaveEnemyTemplates();

}   // end namespace SimpleEdit