//
//  MOAISprite.cpp
//  libmoai
//
//  Created by Isaac Barrett on 9/23/13.
//
//

#include "pch.h"
#include "MOAISprite.h"


int MOAISprite::_newWithFileName(lua_State *L){
	UNUSED(L);
	return 0;
}


int MOAISprite::_newWithName(lua_State *L){
	UNUSED(L);
	
	return 0;
}

MOAISprite::MOAISprite(){
	// register all classes MOAIFooMgr derives from
	// we need this for custom RTTI implementation
RTTI_BEGIN
	RTTI_EXTEND ( MOAILuaObject )
	
	// and any other objects from multiple inheritance...
	// RTTI_EXTEND ( MOAIFooMgrBase )
RTTI_END
}

MOAISprite::~MOAISprite(){
	
}

void MOAISprite::RegisterLuaClass(MOAILuaState &state){
	luaL_Reg regTable [] = {
		{NULL, NULL}
	};
	
	luaL_register(state, 0, regTable );
}