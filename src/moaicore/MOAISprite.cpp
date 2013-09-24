//
//  MOAISprite.cpp
//  libmoai
//
//  Created by Isaac Barrett on 9/23/13.
//
//

#include "pch.h"
#include <moaicore/MOAISprite.h>
#include <moaicore/MOAIProp.h>
#include <moaicore/MOAITexture.h>
#include <moaicore/MOAIGfxQuad2D.h>


//----------------------------------------------------------------//
/** @name	getAssetSuffix
	@text	Returns the suffix used when loading resources.
 
	@in		nil
	@out	string suffix
 
 */
int MOAISprite::_getAssetSuffix	( lua_State* L ){
	MOAILuaState state ( L );
	
	cc8 *suffix = MOAISprite::Get().GetAssetSuffix().str();
	
	state.Push(suffix);
	return 1;
}

//----------------------------------------------------------------//
/** @name	newWithDeck
	@text
 
	@in		MOAIDeck deck
	@opt	number index
	@out	MOAIProp sprite
 */
int MOAISprite::_newWithDeck(lua_State *L){
	MOAILuaState state ( L );
	MOAIDeck *deck = state.GetLuaObject<MOAIDeck >(1, true);
	u32 index = state.GetValue < u32 > (1, 1);
	
	MOAIProp *sprite = MOAISprite::NewWithDeck(deck, index);
	if (sprite) {
		sprite->PushLuaUserdata(state);
		return 1;
	}
	
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	newWithFilename
	@text	
 
	@in		string name
	@out	MOAIProp sprite
 */
int MOAISprite::_newWithFileName(lua_State *L){
	MOAILuaState state ( L );
	
	cc8 *name = state.GetValue < cc8* >(1, NULL);
	
	
	MOAITexture  *texture = MOAISprite::Get().CreateTextureWithFilename( name );
	MOAIProp *sprite = MOAISprite::Get().NewWithTexture( texture );
	
	
	if (sprite) {
		sprite->PushLuaUserdata(state);
		return 1;
	}
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
/** @name	newWithTexture
	@text
	
	@in		MOAITexture texture
	@out	MOAIProp sprite
 */
int MOAISprite::_newWithTexture(lua_State *L){
	MOAILuaState state ( L );
	
	MOAITexture *texture = state.GetLuaObject < MOAITexture >(1, true);
	
	MOAIProp *sprite = MOAISprite::Get().NewWithTexture(texture);
	
	sprite->PushLuaUserdata(state);
	
	return 1;
}

//----------------------------------------------------------------//
/** @name	setAssetSuffix
	@text	Sets the suffix to use when using newWithName when creating
			sprites with newWithFileName().
 
	@in		string suffix
	@out	nil
 */
int MOAISprite::_setAssetSuffix(lua_State *L){
	MOAILuaState state ( L );
	
	cc8 *suffix = state.GetValue < cc8 * >(1, NULL);
	MOAISprite::Get().SetAssetSuffix(suffix);
	return 0;
}

//----------------------------------------------------------------//

MOAITexture* MOAISprite::CreateTextureWithFilename(cc8 *name){
	MOAITexture *texture = new MOAITexture();
	STLString fullName = name;
	fullName.append(this->mAssetSuffix);
	
	texture->Init(fullName, MOAITexture::DEFAULT_TRANSFORM);
	
	return texture;
}


MOAISprite::MOAISprite():
mAssetSuffix(""){
	
	RTTI_BEGIN
		RTTI_EXTEND ( MOAILuaObject )
	RTTI_END
}

MOAISprite::~MOAISprite(){
	
}

MOAIProp* MOAISprite::NewWithDeck(MOAIDeck *deck, u32 index){
	if (!deck) {
		return NULL;
	}
	
	MOAIProp *sprite = new MOAIProp();
	
	sprite->mDeck.Set(*sprite, deck);
	sprite->mIndex = index;
	
	
	return sprite;
}

MOAIProp* MOAISprite::NewWithTexture(MOAITexture *texture){
	MOAIProp *sprite = new MOAIProp();
	
	MOAIGfxQuad2D *gfxQuad = new MOAIGfxQuad2D();
	gfxQuad->mTexture.Set (*gfxQuad, texture);
	
	sprite->mDeck.Set(*sprite, gfxQuad);
	
	return sprite;
}

void MOAISprite::RegisterLuaClass(MOAILuaState &state){
	luaL_Reg regTable [] = {
		{ "getAssetSuffix",		_getAssetSuffix },
		{ "newWithDeck",		_newWithDeck },
		{ "newWithFilename",	_newWithFileName },
		{ "newWithName",		_newWithName },
		{ "newWithTexture",		_newWithTexture },
		{ "setAssetSuffix",		_setAssetSuffix },
		{ NULL, NULL }
	};
	
	luaL_register(state, 0, regTable );
}


void MOAISprite::SetAssetSuffix(cc8 *suffix){
	if (!suffix) {
		suffix = "";
	}
	mAssetSuffix = suffix;
}
