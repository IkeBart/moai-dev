//
//  MOAISpriteCache.cpp
//  libmoai
//
//  Created by Isaac Barrett on 9/24/13.
//
//

#include "pch.h"
#include <moaicore/MOAISpriteCache.h>

//----------------------------------------------------------------//
/** @name	loadSpritesheetWithName
	@text
	
	@in		string name
	@out	nil
 */
int MOAISpriteCache::_loadSpritesheetWithName(lua_State *L){
	MOAILuaState state( L );
	cc8 *name = state.GetValue < cc8* > (1, "");
	
	return 0;
}

//----------------------------------------------------------------//
/** @name	loadTextureWithFilename
	@text
 
	@in		string filename
	@out	nil
 */
int MOAISpriteCache::_loadTextureWithFilename(lua_State *L){
	MOAILuaState state( L );
	return 0;
}

//----------------------------------------------------------------//
/** @name	uncacheSpritesheetWithName
	@text 
 
	@in		string name
	@out	nil
 */
int MOAISpriteCache::_uncacheSpritesheetWithName(lua_State *L){
	MOAILuaState state( L );
	return 0;
}

//----------------------------------------------------------------//
/** @name	uncacheTextureWithFilename
	@text	Remove the texture indexed with the filename from the cache.
 
	@in		string filename
	@out	nil
 */
int MOAISpriteCache::_uncacheTextureWithFilename(lua_State *L){
	MOAILuaState state( L );
	return 0;
}

//----------------------------------------------------------------//


MOAISpriteCache::MOAISpriteCache(){
	RTTI_BEGIN
		RTTI_EXTEND ( MOAILuaObject )
	RTTI_END
}


MOAISpriteCache::~MOAISpriteCache(){
	
}


void MOAISpriteCache::RegisterLuaClass(MOAILuaState &state){
	luaL_Reg regTable [] = {
		{ "loadSpritesheeetWithName", _loadSpritesheetWithName },
		{ "loadTextureWithFilename", _loadTextureWithFilename },
		{ "uncacheSpritesheetWithName", _uncacheSpritesheetWithName },
		{ "uncacheTextureWithFilename", _uncacheTextureWithFilename },
		{ NULL, NULL }
	};
	
	luaL_register(state, 0, regTable );
}
