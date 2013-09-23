//
//  MOAISprite.cpp
//  libmoai
//
//  Created by Isaac Barrett on 9/23/13.
//
//

#include "MOAISprite.h"

MOAISprite::_newWithName(int *L){
	UNUSED(L);
	
	return 0;
}

MOAISprite::MOAISprite(){
	
}

MOAISprite::~MOAISprite(){
	
}

void MOAISprite::RegisterLuaClass(MOAILuaState &state){
	luaL_Reg regTable [] = {
		{NULL, NULL}
	};
	
	luaL_register(state, 0, regTable );
}