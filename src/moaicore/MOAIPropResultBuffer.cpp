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
void MOAIPropResultBuffer::GenerateKeys(u32 mode, float xScale, float yScale, float zScale, float mZOrder){
	UNUSED(xScale);
	UNUSED(yScale);
	UNUSED(zScale);
	UNUSED(mZOrder);
	
	// TODO: implement the sort modes
	float floatSign = mode & SORT_FLAG_DESCENDING ? -1.0f : 1.0f;
	s32 intSign = ( int )floatSign;
	
	// case SORT_PRIORITY_ASCENDING:
	for (u32 i = 0; i < this->mTotalResults; ++i) {
		s32 p = this->mMainBuffer [i].mZOrder * intSign;
		this->mMainBuffer[i].mKey = ( u32 )(( p ^ 0x80000000 ) | ( p & 0x7fffffff ));
	}
	
}

//----------------------------------------------------------------//
MOAIPropResultBuffer::MOAIPropResultBuffer() :
	mResults(0),
	mTotalResults(0){
}

//----------------------------------------------------------------//
MOAIPropResultBuffer::~MOAIPropResultBuffer(){
}

//----------------------------------------------------------------//
void MOAIPropResultBuffer::PushProps(lua_State *L){
	MOAILuaState state ( L );
	
	u32 total = this->mTotalResults;
	
	for (u32 i = 0; i < total; ++i) {
		this->mResults [i].mProp->PushLuaUserdata( state );
	}
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

//----------------------------------------------------------------//
u32 MOAIPropResultBuffer::SortResults(){
	this->mResults = this->mMainBuffer;
	
	// affirm the swap buffer
	if ( this->mSwapBuffer.Size () < this->mMainBuffer.Size ()) {
		this->mSwapBuffer.Init ( this->mMainBuffer.Size ());
	}
	
	// sort
	this->mResults = RadixSort32 < MOAIPropResult >( this->mMainBuffer, this->mSwapBuffer, this->mTotalResults );
	
	return this->mTotalResults;
}