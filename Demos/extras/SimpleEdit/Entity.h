// MUD Programming
// Ron Penton
// (C)2003
// Entity.h - This is a base class defining classes in SimpleMUD that may be
//             matched by name either partially or fully, and have ID's
// 
// 


#ifndef SIMPLEMUDENTITY_H
#define SIMPLEMUDENTITY_H

#include <string>
#include "BasicLib/BasicLib.h"


namespace SimpleEdit
{

typedef unsigned int entityid;
using std::string;

// --------------------------------------------------------------------
//  This class has a given name, and will allow you to match
//  the name with any other names either partially or fully.
//  It also has ID's
// --------------------------------------------------------------------
class Entity
{
public:

    // --------------------------------------------------------------------
    //  Constructor
    // --------------------------------------------------------------------
    inline Entity()
    {
        m_name = "UNDEFINED";
        m_id = 0;
    }

    string m_name;
    entityid m_id;

};  // end class Entity










}   // end namespace SimpleEdit


#endif
