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


int MOAIRootProp::_insertProp(lua_State *L){
	UNUSED(L);
	return 0;
}

int MOAIRootProp::_removeProp( lua_State* L ){
	UNUSED(L);
	return 0;
}

int MOAIRootProp::_setViewport( lua_State* L ){
	UNUSED(L);
	return 0;
}

void MOAIRootProp::Draw(int subPrimID){
	UNUSED( subPrimID );
}

MOAIRootProp::MOAIRootProp(){
	RTTI_BEGIN
		RTTI_EXTEND ( MOAIProp )
		RTTI_EXTEND ( MOAIClearableView )
	RTTI_END
}

MOAIRootProp::~MOAIRootProp(){
	this->mViewport.Set ( *this, 0 );
}

void MOAIRootProp::RegisterLuaClass( MOAILuaState &state ){
	MOAIProp::RegisterLuaClass ( state );
	MOAIClearableView::RegisterLuaClass ( state );
	
	
}

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