// Copyright (c) 2010-2013 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

//
//  MOAIRootProp.cpp
//  libmoai
//
//  Created by Isaac Barrett on 7/30/13.
//
//

#include "pch.h"
#include <moaicore/MOAIGfxDevice.h>
#include <moaicore/MOAIRootProp.h>

//----------------------------------------------------------------//
/**	@name	insertProp
	@text	Adds a prop the root prop's children.
 
	@in		MOAIRootProp self
	@in		MOAIProp prop
	@opt	number zOrder
	@out	nil
 */
int MOAIRootProp::_insertProp(lua_State *L){
	
	MOAI_LUA_SETUP( MOAIRootProp, "UU" )
	
	MOAIProp *child = state.GetLuaObject< MOAIProp >(2, true);
	int zOrder = state.GetValue <int > (3, child->GetZOrder());
	
	self->AddChild(child, zOrder);
	return 0;
}

//----------------------------------------------------------------//
/** @name	removeProp
	@text	Removes a prop from the root prop's children.
 
	@in		MOAIRootProp self
	@in		MOAIProp prop
	@out	nil
 */
int MOAIRootProp::_removeProp( lua_State* L ){
	MOAI_LUA_SETUP( MOAIRootProp, "UU" )
	
	MOAIProp *child = state.GetLuaObject< MOAIProp >(2, true);
	self->RemoveChild(child);
	
	return 0;
}

//----------------------------------------------------------------//
/** @name	setViewport
	@text	Set the root prop's viewport.
 
	@in		MOAIRootProp self
	@in		MOAIViewport viewport
	@out	nil
 */

int MOAIRootProp::_setViewport( lua_State* L ){
	MOAI_LUA_SETUP ( MOAIRootProp, "UU" )
	
	self->mViewport.Set ( *self, state.GetLuaObject < MOAIViewport >( 2, true ));
	return 0;
}

//----------------------------------------------------------------//
void MOAIRootProp::Draw(int subPrimID){
	UNUSED( subPrimID );
}

//----------------------------------------------------------------//
MOAIRootProp::MOAIRootProp(){
	RTTI_BEGIN
		RTTI_EXTEND ( MOAIProp )
		RTTI_EXTEND ( MOAIClearableView )
	RTTI_END
}

//----------------------------------------------------------------//
MOAIRootProp::~MOAIRootProp(){
	this->mViewport.Set ( *this, 0 );
}

//----------------------------------------------------------------//
void MOAIRootProp::RegisterLuaClass( MOAILuaState &state ){
	MOAIProp::RegisterLuaClass ( state );
	MOAIClearableView::RegisterLuaClass ( state );
	
	
}

//----------------------------------------------------------------//
void MOAIRootProp::RegisterLuaFuncs( MOAILuaState& state ){
	MOAIProp::RegisterLuaFuncs ( state );
	MOAIClearableView::RegisterLuaFuncs ( state );
	
	luaL_Reg regTable [] = {
		{ "insertProp",				_insertProp},
		{ "removeProp",				_removeProp },
		{ "setViewport",			_setViewport },
		{ NULL, NULL }
	};
	
	luaL_register ( state, 0, regTable );
}
//----------------------------------------------------------------//

void MOAIRootProp::Render () {
	
	this->Draw ( MOAIProp::NO_SUBPRIM_ID );
}
