////////////////////////////////////////////////////////////////////////////////
// -------------------------------------------------------------------------- //
//                                                                            //
//                       (C) 2010-2015 Robot Developers                       //
//                       See LICENSE for licensing info                       //
//                                                                            //
// -------------------------------------------------------------------------- //
////////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------//
// Prefaces                                                                   //
//----------------------------------------------------------------------------//

#ifndef ROBOT_ENUM_H
#define ROBOT_ENUM_H

#include "Global.h"
#include <string>
#include <unordered_map>
namespace Robot {

#ifdef ROBOT_OS_WIN
	#pragma warning (push)
	// Ignore the VS C4251 warning
	#pragma warning (disable:4251)
#endif



//----------------------------------------------------------------------------//
// Macros                                                                     //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////

#define ROBOT_ENUM( type ) template<> std::unordered_map<std::string, type>    \
			Robot::Enum<type>::mMap = std::unordered_map<std::string, type>(); \
			template<> Robot::Enum<type>::Enum (void)

////////////////////////////////////////////////////////////////////////////////

#define _ROBOT_ENUM_MAP_1( value      ) mMap[#value] = value
#define _ROBOT_ENUM_MAP_2( value, key ) mMap[ key  ] = value

#define _ROBOT_ENUM_SELECT( _1, _2, NAME, ...) NAME
#define _ROBOT_ENUM_EXPAND( expression ) expression

#define ROBOT_ENUM_MAP( ... ) _ROBOT_ENUM_EXPAND (_ROBOT_ENUM_SELECT \
	(__VA_ARGS__, _ROBOT_ENUM_MAP_2, _ROBOT_ENUM_MAP_1) (__VA_ARGS__))



//----------------------------------------------------------------------------//
// Classes                                                                    //
//----------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////

template <typename Type> class Enum
{
private:
	//----------------------------------------------------------------------------//
	// Constructors                                                               //
	//----------------------------------------------------------------------------//

	////////////////////////////////////////////////////////////////////////////////

	Enum (void);



public:
	//----------------------------------------------------------------------------//
	// Functions                                                                  //
	//----------------------------------------------------------------------------//

	////////////////////////////////////////////////////////////////////////////////

	static uintptr Size (void)
	{
		// Initialize the static parser
		if (mMap.empty()) Enum<Type>();

		// Return map size
		return mMap.size();
	}

	////////////////////////////////////////////////////////////////////////////////

	static Type Parse (const std::string& key)
	{
		// Initialize the static parser
		if (mMap.empty()) Enum<Type>();

		// Search for a matching key
		return mMap.find (key) != mMap.end()
			   ? mMap.at (key) : (Type) -1;
	}

	////////////////////////////////////////////////////////////////////////////////

	static std::string Parse (Type value)
	{
		// Initialize the static parser
		if (mMap.empty()) Enum<Type>();

		// Search for a matching value
		for (auto i = mMap.begin();
			 i != mMap.end(); ++i)
		{
			if (i->second == value) return i->first;
		}

		// Nothing was found
		return std::string();
	}



private:
	//----------------------------------------------------------------------------//
	// Fields                                                                     //
	//----------------------------------------------------------------------------//

	static std::unordered_map<std::string, Type> mMap;
};

#ifdef ROBOT_OS_WIN
	#pragma warning (pop)
#endif

}
#endif // ROBOT_ENUM_H
