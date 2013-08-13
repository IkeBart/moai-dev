// Copyright (c) 2010-2013 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com
//
//  MOAIPropResultBuffer.h
//  libmoai
//
//  Created by Isaac Barrett on 8/12/13.
//
//

#ifndef MOAIPROPRESULTBUFFER_H
#define MOAIPROPRESULTBUFFER_H

class MOAIProp;

//================================================================//
// MOAIPropResult
//================================================================//
class MOAIPropResult {
	MOAIProp*	mProp;
	s32			mZOrder;
	
	USVec3D		mLoc;
	USRect		mBounds;
};


//================================================================//
// MOAIPropResultBuffer
//================================================================//
class MOAIPropResultBuffer {
	
private:
	friend class MOAIProp;
	
	static const u32 BLOCK_SIZE = 512;
	USLeanArray < MOAIPropResult >			mMainBuffer;
	USLeanArray < MOAIPropResult >			mSwapBuffer;
	MOAIPropResult*							mResults;
	u32										mTotalResults;
	
	//----------------------------------------------------------------//
	u32							SortResults		();
	
public:
	GET ( u32, TotalResults, mTotalResults )
	
	//----------------------------------------------------------------//
	void						Clear					();
	MOAIProp*					FindBest				();
								MOAIPropResultBuffer	();
								~MOAIPropResultBuffer	();
	
	
};

#endif /* defined(MOAIPROPRESULTBUFFER_H) */
