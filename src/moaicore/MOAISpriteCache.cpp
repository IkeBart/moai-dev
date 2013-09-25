//
//  MOAISpriteCache.cpp
//  libmoai
//
//  Created by Isaac Barrett on 9/24/13.
//
//

#include "pch.h"
#include <moaicore/MOAISpriteCache.h>


MOAISpriteCache::MOAISpriteCache(){
	RTTI_BEGIN
		RTTI_EXTEND ( MOAILuaObject )
	RTTI_END
}


MOAISpriteCache::~MOAISpriteCache(){
	
}


void MOAISpriteCache::RegisterLuaClass(MOAILuaState &state){
	luaL_Reg regTable [] = {
		{ NULL, NULL }
	};
	
	luaL_register(state, 0, regTable );
}
