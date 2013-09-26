//
//  MOAISpriteCache.cpp
//  libmoai
//
//  Created by Isaac Barrett on 9/24/13.
//
//

#include "pch.h"
#include <moaicore/MOAISpriteCache.h>
#include <moaicore/MOAIDeck.h>

//----------------------------------------------------------------//
/** @name	getDeckOfSpriteWithName
	@text
 
	@in		string name
	@out	MOAIDeck deck
 */
int MOAISpriteCache::_getDeckOfSpriteWithName(lua_State *L){
	MOAILuaState state( L );
	if ( !state.CheckParams ( 1, "S" )) return 0;
	cc8 *name = state.GetValue < cc8* > (1, "");
	
	MOAIDeck *deck = MOAISpriteCache::Get().CachedSpriteDeckForName(name);
	
	if (deck) {
		deck->PushLuaUserdata(state);
		return 1;
	}
	
	return 0;
}

//----------------------------------------------------------------//
/** @name	getIndexOfSpriteWithName
	@text
 
	@in		string name
	@out	number index
 */
int MOAISpriteCache::_getIndexOfSpriteWithName(lua_State *L){
	MOAILuaState state( L );
	if ( !state.CheckParams ( 1, "S" )) return 0;
	
	cc8 *name = state.GetValue < cc8* > (1, "");
	u32 index = MOAISpriteCache::Get().CachedSpriteIndexForName(name);
	
	state.Push(index);
	
	return 1;
}

//----------------------------------------------------------------//
/** @name	loadSpritesheetWithName
	@text
	
	@in		string name
	@out	nil
 */
int MOAISpriteCache::_loadSpritesheetWithName(lua_State *L){
	MOAILuaState state( L );
	if ( !state.CheckParams ( 1, "S" )) return 0;
	cc8 *name = state.GetValue < cc8* > (1, "");
	
	return 0;
}

//----------------------------------------------------------------//
/** @name	loadTextureWithFilename
	@text
 
	@in		string filename
	@opt	number index  default to 1
	@out	nil
 */
int MOAISpriteCache::_loadTextureWithFilename(lua_State *L){
	MOAILuaState state( L );
	if ( !state.CheckParams ( 1, "S" )) return 0;
	cc8 *name = state.GetValue < cc8* > (1, "");
	u32 index = state.GetValue < u32 > (2, 1);
	
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
	if ( !state.CheckParams ( 1, "S" )) return 0;
	
	
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
	if ( !state.CheckParams ( 1, "S" )) return 0;
	return 0;
}

//----------------------------------------------------------------//

MOAIDeck* MOAISpriteCache::CachedSpriteDeckForName(STLString name){
	
	MOAIDeck* deck = this->mCachedSpriteDefinitons.value_for_key(name);
	
	return deck;
}

u32	MOAISpriteCache::CachedSpriteIndexForName(STLString name){
	std::map<STLString, u32>::iterator it;
	it = this->mCachedSpriteIndices.find(name);
	
	if (it != this->mCachedSpriteIndices.end() ) {
		return it->second;
	}
	
	return INDEX_NOT_FOUND;
}

void MOAISpriteCache::InsertDeckAndIndexInCache( STLString key, MOAIDeck *deck, u32 index){
	
	this->mCachedSpriteDefinitons.insert(std::pair<STLString, MOAIDeck*>(key, deck) );
	this->mCachedSpriteIndices.insert(std::pair<STLString, u32>(key, index));
	
}

MOAISpriteCache::MOAISpriteCache(){
	RTTI_BEGIN
		RTTI_EXTEND ( MOAILuaObject )
	RTTI_END
}


MOAISpriteCache::~MOAISpriteCache(){
	
}


void MOAISpriteCache::RegisterLuaClass(MOAILuaState &state){
	luaL_Reg regTable [] = {
		{ "getDeckOfSpriteWithName", _getDeckOfSpriteWithName },
		{ "getIndexOfSpriteWithName", _getIndexOfSpriteWithName },
		{ "loadSpritesheeetWithName", _loadSpritesheetWithName },
		{ "loadTextureWithFilename", _loadTextureWithFilename },
		{ "uncacheSpritesheetWithName", _uncacheSpritesheetWithName },
		{ "uncacheTextureWithFilename", _uncacheTextureWithFilename },
		{ NULL, NULL }
	};
	
	luaL_register(state, 0, regTable );
}
