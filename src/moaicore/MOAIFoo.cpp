// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moaicore/MOAIFoo.h>

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/**	@name	classHello
	@text	Class (a.k.a. static) method. Prints the string 'MOAIFoo class foo!' to the console.

	@out	nil
*/
int MOAIFoo::_classHello ( lua_State* L ) {
	UNUSED ( L );
	
	printf ( "MOAIFoo class foo!\n" );
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	instanceHello
	@text	Prints the string 'MOAIFoo instance foo!' to the console.

	@out	nil
*/
int MOAIFoo::_instanceHello ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIFoo, "U" ) // this macro initializes the 'self' variable and type checks arguments
	
	printf ( "MOAIFoo instance foo!\n" );
	
	return 0;
}

//----------------------------------------------------------------//
/** @name	makeTable
	@text	Creates a new table with integers for the values.
 
	@in		integer elements		The first thing
	@in		number	startValue
 
	@out	table
 */
int MOAIFoo::_makeTable(lua_State *L){
	MOAILuaState state(L);
	
	u32 elements = state.GetValue <u32> (1, 1);
	float startValue = state.GetValue <float> (2, 0.0);
	
	MOAIFoo::MakeTable(state, elements, startValue);
	
	
	return 1;
}


//================================================================//
// MOAIFoo
//================================================================//

//----------------------------------------------------------------//
void MOAIFoo::MakeTable(MOAILuaState state, u32 elements, float startValue){
	u32 i;
	
	// create main table
	lua_createtable(state, elements, 0);
	float val = startValue;
	
	for (i = 1; i <= elements; i++) {
		//state.Push(val);
		
		// create a sub-table with two elements for the value of the element
		lua_createtable(state, 2, 0);
		
		{
			// make the float val be the first element of the sub-table with index of integer 1
			state.Push(val);
			lua_rawseti(state, -2, 1);
			
			// make the square of val be the second element of the sub-table with the index of string "sqr"
			state.Push(val * val);
			//lua_rawseti(state, -2, 2);
			cc8 *key = "sqr";
			lua_setfield(state, -2, key);
		}
		
		// set the index for sub-table value in main table to the integer i
		val = val + 1.0;
		lua_rawseti(state, -2, i);
	}
	
}

//----------------------------------------------------------------//
MOAIFoo::MOAIFoo () {
	
	// register all classes MOAIFoo derives from
	// we need this for custom RTTI implementation
	RTTI_BEGIN
		RTTI_EXTEND ( MOAILuaObject )
		
		// and any other objects from multiple inheritance...
		// RTTI_EXTEND ( MOAIFooBase )
	RTTI_END
}

//----------------------------------------------------------------//
MOAIFoo::~MOAIFoo () {
}

//----------------------------------------------------------------//
void MOAIFoo::RegisterLuaClass ( MOAILuaState& state ) {

	// call any initializers for base classes here:
	// MOAIFooBase::RegisterLuaClass ( state );

	// also register constants:
	// state.SetField ( -1, "FOO_CONST", ( u32 )FOO_CONST );

	// here are the class methods:
	luaL_Reg regTable [] = {
		{ "classHello",		_classHello },
		{ "makeTable",		_makeTable },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAIFoo::RegisterLuaFuncs ( MOAILuaState& state ) {

	// call any initializers for base classes here:
	// MOAIFooBase::RegisterLuaFuncs ( state );

	// here are the instance methods:
	luaL_Reg regTable [] = {
		{ "instanceHello",	_instanceHello },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

