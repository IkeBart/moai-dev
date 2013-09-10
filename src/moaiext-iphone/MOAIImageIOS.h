//
//  MOAIImageIOS.h
//  libmoai
//
//  Created by Isaac Barrett on 9/6/13.
//
//

#ifndef __libmoai__MOAIImageIOS__
#define __libmoai__MOAIImageIOS__

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <moaicore/moaicore.h>


class MOAIImageIOS :
public MOAIImage {
private:
	
	void				LoadCGImage				( CGImageRef cgImage, u32 transform );
	void				LoadJpg					( USStream& stream, u32 transform );
	void				LoadPng					( USStream& stream, u32 transform );
	
	
public:
	
	DECL_LUA_FACTORY (MOAIImageIOS);
	
	void				Load					( USStream& stream, u32 transform );
	void				RegisterLuaClass		( MOAILuaState& state );
	void				RegisterLuaFuncs		( MOAILuaState& state );
};

#endif /* defined(__libmoai__MOAIImageIOS__) */
