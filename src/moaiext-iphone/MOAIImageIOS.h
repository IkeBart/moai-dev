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
	void LoadJpg ( USStream& stream, u32 transform );
	void LoadPng ( USStream& stream, u32 transform );
};

#endif /* defined(__libmoai__MOAIImageIOS__) */
