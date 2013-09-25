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

// a class that holds cached sprites
class MOAISpriteCache : public MOAIGlobalClass <MOAISpriteCache, MOAILuaObject> {
	
private:
	
//----------------------------------------------------------------//
	
public:
	
//----------------------------------------------------------------//
						MOAISpriteCache		();
						~MOAISpriteCache	();
	void				RegisterLuaClass	( MOAILuaState& state );
	
};



#endif /* defined(MOAISPRITECACHE_H) */
