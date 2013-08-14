//
//  MOAIPropResultBuffer.cpp
//  libmoai
//
//  Created by Isaac Barrett on 8/12/13.
//
//

#include "pch.h"
#include <moaicore/MOAIPropResultBuffer.h>
#include <moaicore/MOAIProp.h>


//================================================================//
// MOAIPartitionResultBuffer
//================================================================//

//----------------------------------------------------------------//
void MOAIPropResultBuffer::Clear(){
	this->mMainBuffer.Clear ();
	this->mSwapBuffer.Clear ();
	
	this->mResults = 0;
	this->mTotalResults = 0;
}

//----------------------------------------------------------------//
MOAIProp* MOAIPropResultBuffer::FindBest () {
	if ( !this->mTotalResults ) return 0;
	
	MOAIPropResult* best = &this->mMainBuffer [0];
	
	u32 bestKey = best->mKey;
	
	for ( u32 i = 1; i < this->mTotalResults; ++i ){
		MOAIPropResult *compare = &this->mMainBuffer [ i ];
		
		u32 compKey = compare->mKey;
		if ( bestKey < compKey) {
			best = compare;
			bestKey = compKey;
		}
	}
	
	return best->mProp;
}

//----------------------------------------------------------------//
void MOAIPropResultBuffer::PushResult(MOAIProp &prop, u32 key, int subPrimID, s32 zOrder, const USVec3D &loc, const USBox &bounds){
	UNUSED(subPrimID);
	
	u32 idx = this->mTotalResults++;
	
	if (idx >= this->mMainBuffer.Size()) {
		this->mMainBuffer.Grow( idx + 1, BLOCK_SIZE );
	}
	
	MOAIPropResult& result = this->mMainBuffer [ idx ];
	
	result.mKey = key;
	
	result.mProp = &prop;
	
	result.mZOrder = zOrder;
	result.mLoc = loc;
	result.mBounds = bounds;
	
}

//----------------------------------------------------------------//

void MOAIPropResultBuffer::Reset(){
	this->mResults = 0;
	this->mTotalResults = 0;
}