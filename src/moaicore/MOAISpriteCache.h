//
//  MOAISpriteCache.h
//  libmoai
//
//  Created by Isaac Barrett on 9/24/13.
//
//

#ifndef MOAISPRITECACHE_H
#define MOAISPRITECACHE_H

#include <moaicore/MOAILua.h>

class MOAIDeck;

// a class that holds cached sprites
class MOAISpriteCache : public MOAIGlobalClass <MOAISpriteCache, MOAILuaObject> {
	
private:
	static int _getDeckOfSpriteWithName ( lua_State *L );
	static int _getIndexOfSpriteWithName ( lua_State *L );
	
	static int _loadSpritesheetWithName ( lua_State *L );
	static int _loadTextureWithFilename ( lua_State *L );
	
	static int _uncacheSpritesheetWithName ( lua_State *L );
	static int _uncacheTextureWithFilename ( lua_State *L );
	
	
//----------------------------------------------------------------//
	
	STLMap <STLString, MOAIDeck * > mCachedSpriteDefinitons;
	std::map <STLString, u32 > mCachedSpriteIndices;
	
public:
	
	static const u32 INDEX_NOT_FOUND = 0xffffffff;
	
//----------------------------------------------------------------//
	MOAIDeck *			CachedSpriteDeckForName		( STLString name );
	u32					CachedSpriteIndexForName	( STLString name );
	void				InsertDeckAndIndexInCache	( STLString key, MOAIDeck *deck, u32 index );
						MOAISpriteCache				();
						~MOAISpriteCache			();
	void				RegisterLuaClass			( MOAILuaState& state );
	
};



#endif /* defined(MOAISPRITECACHE_H) */
