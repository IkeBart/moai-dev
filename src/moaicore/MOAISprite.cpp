//
//  MOAISprite.cpp
//  libmoai
//
//  Created by Isaac Barrett on 9/23/13.
//
//

#include "pch.h"
#include "MOAISprite.h"

//----------------------------------------------------------------//
/** @name	getAssetSuffix
	@text	Returns the suffix used when loading resources.
 
	@in		nil
	@out	string suffix
 
 */
int MOAISprite::_getAssetSuffix	( lua_State* L ){
	UNUSED(L);
	return 0;
}


//----------------------------------------------------------------//
/**	@name	newWithFileName
	@text	
 
	@in		string name
	@out	MOAIProp sprite
 */
int MOAISprite::_newWithFileName(lua_State *L){
	UNUSED(L);
	return 0;
}

//----------------------------------------------------------------//
/** @name	newWithName
	@text
 
	@in		string name
	@out	MOAIProp sprite
 */
int MOAISprite::_newWithName(lua_State *L){
	UNUSED(L);
	
	return 0;
}

//----------------------------------------------------------------//
/** @name	setAssetSuffix
	@text	Sets the suffix to use when using newWithName when creating
			sprites with newWithFileName().
 
	@in		string suffix
	@out	nil
 */
int MOAISprite::_setAssetSuffix(lua_State *L){
	UNUSED(L);
	return 0;
}

//----------------------------------------------------------------//

MOAISprite::MOAISprite(){
	
	RTTI_BEGIN
		RTTI_EXTEND ( MOAILuaObject )
	RTTI_END
}

MOAISprite::~MOAISprite(){
	
}

void MOAISprite::RegisterLuaClass(MOAILuaState &state){
	luaL_Reg regTable [] = {
		{ "getAssetSuffix",		_getAssetSuffix },
		{ "newWithFileName",	_newWithFileName },
		{ "newWithName",		_newWithName },
		{ "setAssetSuffix",		_setAssetSuffix },
		{ NULL, NULL }
	};
	
	luaL_register(state, 0, regTable );
}