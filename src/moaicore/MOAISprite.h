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

class MOAIProp;
class MOAITexture;

class MOAISprite : public MOAIGlobalClass <MOAISprite, MOAILuaObject>  {
	
private:
	static int				_getAssetSuffix		( lua_State* L );
	static int				_newWithFileName	( lua_State* L );
	static int				_newWithName		( lua_State* L );
	static int				_newWithTexture		( lua_State* L );
	static int				_setAssetSuffix		( lua_State* L );
	
	//----------------------------------------------------------------//
	
	STLString mAssetSuffix;
	
public:
	DECL_LUA_SINGLETON ( MOAISprite )
	
	GET(STLString, AssetSuffix, mAssetSuffix);
	
	
	//----------------------------------------------------------------//
	MOAITexture*		CreateTextureWithFilename( cc8* name );
						MOAISprite			();
						~MOAISprite			();
	MOAIProp*			NewWithTexture		( MOAITexture* texture );
	void				RegisterLuaClass	( MOAILuaState& state );
	void				SetAssetSuffix		(cc8 *suffix);
};

#endif /* defined(MOAISPRITE_H) */
