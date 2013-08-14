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
class MOAIPropResult :
	public USRadixKey32Base {
public:
	MOAIProp*	mProp;
	s32			mZOrder;
	
	USVec3D		mLoc;
	USBox		mBounds;
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
	
	static const u32 SORT_FLAG_DESCENDING		= 0x80000000;
	static const u32 SORT_MODE_MASK				= 0x7fffffff;
	
	enum {
		SORT_NONE,
		
		SORT_ISO,
		
		SORT_KEY_ASCENDING,
		SORT_PRIORITY_ASCENDING,
		SORT_X_ASCENDING,
		SORT_Y_ASCENDING,
		SORT_Z_ASCENDING,
		SORT_VECTOR_ASCENDING,
		
		SORT_KEY_DESCENDING			= SORT_KEY_ASCENDING | SORT_FLAG_DESCENDING,
		SORT_PRIORITY_DESCENDING	= SORT_PRIORITY_ASCENDING | SORT_FLAG_DESCENDING,
		SORT_X_DESCENDING			= SORT_X_ASCENDING | SORT_FLAG_DESCENDING,
		SORT_Y_DESCENDING			= SORT_Y_ASCENDING | SORT_FLAG_DESCENDING,
		SORT_Z_DESCENDING			= SORT_Z_ASCENDING | SORT_FLAG_DESCENDING,
		SORT_VECTOR_DESCENDING		= SORT_VECTOR_ASCENDING | SORT_FLAG_DESCENDING,
	};
	
	
	GET ( u32, TotalResults, mTotalResults )
	
	//----------------------------------------------------------------//
	void						Clear					();
	MOAIProp*					FindBest				();
	void						GenerateKeys			(u32 mode, float xScale, float yScale, float zScale, float zOrder );
								MOAIPropResultBuffer	();
								~MOAIPropResultBuffer	();
	void						PushProps				( lua_State* L );
	void						PushResult				(  MOAIProp& prop, u32 key, int subPrimID, s32 zOrder, const USVec3D& loc, const USBox& bounds );
	void						Reset					();
	
	
	
};

#endif /* defined(MOAIPROPRESULTBUFFER_H) */
