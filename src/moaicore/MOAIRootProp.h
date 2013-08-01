// Copyright (c) 2010-2013 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

//
//  MOAIRootProp.h
//  libmoai
//
//  Created by Isaac Barrett on 7/30/13.
//
//

#ifndef	MOAIROOTPROP_H
#define	MOAIROOTPROP_H


#include <moaicore/MOAIFrameBuffer.h>
#include <moaicore/MOAILua.h>
#include <moaicore/MOAIProp.h>
#include <moaicore/MOAIViewport.h>


//================================================================//
// MOAIRootProp
//================================================================//
/**	@name	MOAIRootProp
	@text	Prop subclass with some features of MOAILayer, but lacking the 
			partitions.
 */


class MOAIRootProp :
	public virtual MOAIProp,
	public MOAIClearableView
{
private:
	MOAILuaSharedPtr < MOAIViewport >		mViewport;
	
	//----------------------------------------------------------------//
	static int	_insertProp			( lua_State* L );
	static int	_removeProp			( lua_State* L );
	static int  _setViewport		( lua_State* L );
	
	//----------------------------------------------------------------//
	
	
public:
	DECL_LUA_FACTORY ( MOAIRootProp )

	//----------------------------------------------------------------//
	virtual void		Draw					( int subPrimID );
						MOAIRootProp			();
	virtual				~MOAIRootProp			();
	void				RegisterLuaClass		( MOAILuaState& state );
	void				RegisterLuaFuncs		( MOAILuaState& state );
	void				Render					();
	
};


#endif
