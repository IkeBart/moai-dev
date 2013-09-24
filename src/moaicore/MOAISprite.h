//
//  MOAISprite.h
//  libmoai
//
//  Created by Isaac Barrett on 9/23/13.
//
//

#ifndef MOAISPRITE_H
#define MOAISPRITE_H

#include <moaicore/MOAILua.h>

class MOAISprite : public MOAIGlobalClass <MOAISprite, MOAILuaObject>  {
	
private:
	int					_newWithFileName	( lua_State* L );
	int					_newWithName		( lua_State* L );
	
	//----------------------------------------------------------------//
	
	
public:
	DECL_LUA_SINGLETON ( MOAISprite )
	
	//----------------------------------------------------------------//
	MOAISprite			();
	~MOAISprite			();
	void				RegisterLuaClass	( MOAILuaState& state );
};

#endif /* defined(MOAISPRITE_H) */
