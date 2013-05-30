// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef MOAIFREETYPETEXTBOX_H
#define MOAIFREETYPETEXTBOX_H

#include <moaicore/MOAIAction.h>
#include <moaicore/MOAILua.h>
#include <moaicore/MOAIProp.h>

class MOAIFreeTypeFont;


/** @name	MOAIFreeTypeTextBox
	@text	An alternative to MOAITextBox that uses an instance of MOAIFreeTypeFont directly.
 */

class MOAIFreeTypeTextBox :
	public MOAIProp {
private:
	float				mLineSpacing;
		
	USRect				mFrame;
		
	STLString			mText;
	u32					mTextLength;
		
	u32					mHAlign;
	u32					mVAlign;
		
	bool				mYFlip;
	float				mGlyphScale;
		
	// rule for breaking words across lines
	u32 mWordBreak;
		
	// automatically fit text in box
	bool				mAutoFit;
		
public:
	void				RegisterLuaClass		( MOAILuaState& state );
	void				RegisterLuaFuncs		( MOAILuaState& state );
};

#endif /* defined(MOAIFREETYPETEXTBOX_H) */
