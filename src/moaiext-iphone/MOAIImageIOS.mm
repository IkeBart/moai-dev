//
//  MOAIImageIOS.cpp
//  libmoai
//
//  Created by Isaac Barrett on 9/6/13.
//
//

#include "MOAIImageIOS.h"


void MOAIImageIOS::LoadJpg(USStream &stream, u32 transform){
	UNUSED(stream);
	UNUSED(transform);
}

void MOAIImageIOS::LoadPng(USStream &stream, u32 transform){
	UNUSED(stream);
	UNUSED(transform);
	
	// get data from the stream
	size_t size = stream.GetLength();
	if (!size || size == 0) {
		// print warning
		return;
	}
	void *buffer = malloc(size);
	stream.ReadBytes(buffer, size);
	
	// load PNG with the data using iOS library.
	NSData *data = [NSData dataWithBytes:buffer length:size];
	CGImageRef cgImage = [[UIImage imageWithData:data] CGImage];
	
	if (cgImage == NULL){
		// print warning
		return;
	}
	
	// get image info
	unsigned int width = CGImageGetWidth(cgImage);
	unsigned int height = CGImageGetHeight(cgImage);
	
	bool isPadded = false;
	if (transform & MOAIImageTransform::POW_TWO) {
		this->mWidth = this->GetMinPowerOfTwo(width);
		this->mHeight = this->GetMinPowerOfTwo(height);
		isPadded = true;
	}
	else{
		this->mWidth = width;
		this->mHeight = height;
	}
	
	
}