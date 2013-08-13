// Copyright (c) 2010-2013 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

//  MOAIPropResultMgr.h
//  libmoai
//
//  Created by Isaac Barrett on 8/12/13.
//
//

#ifndef MOAIPROPRESULTMGR_H
#define MOAIPROPRESULTMGR_H

#include <moaicore/MOAIGlobals.h>
#include <moaicore/MOAIPropResultBuffer.h>

//================================================================//
// MOAIPropResultMgr
//================================================================//

class MOAIPropResultMgr :
	public MOAIGlobalClass < MOAIPropResultMgr >{
private:
	
	MOAIPropResultBuffer	mBuffer;

public:
	
	GET ( MOAIPropResultBuffer&, Buffer, mBuffer )
	
	//----------------------------------------------------------------//
		MOAIPropResultMgr		();
		~MOAIPropResultMgr		();
	
};

#endif /* defined(MOAIPROPRESULTMGR_H) */
