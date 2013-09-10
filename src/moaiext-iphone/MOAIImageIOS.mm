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
	
	// get pixel format and color format
	
	USPixel::Format pngPixelFormat = USPixel::TRUECOLOR;
	USColor::Format pngColorFormat ;
	
	CGImageAlphaInfo info = CGImageGetAlphaInfo(cgImage);
	bool hasAlpha = (info == kCGImageAlphaPremultipliedLast)
					|| (info == kCGImageAlphaPremultipliedFirst)
					|| (info == kCGImageAlphaLast)
					|| (info == kCGImageAlphaFirst);
	
	CGColorSpaceRef colorSpace = CGImageGetColorSpace(cgImage);
	if (colorSpace) {
		if (hasAlpha) {
			info = kCGImageAlphaPremultipliedLast;
			pngColorFormat = USColor::RGBA_8888;
			
		}
		else{
			info = kCGImageAlphaNoneSkipLast;
			pngColorFormat = USColor::RGBA_8888; //USColor::RGB_888;
		}
	}
	else{
		// print warning
		return;
	}
	this->mPixelFormat = pngPixelFormat;
	this->mColorFormat = pngColorFormat;
	
	this->Alloc();
	
	int bitsPerComponent = 8;
	
	colorSpace = CGColorSpaceCreateDeviceRGB();
	CGContextRef context = CGBitmapContextCreate(this->mData,
												 this->mWidth,
												 this->mHeight,
												 bitsPerComponent,
												 4 * this->mWidth,
												 colorSpace,
												 info | kCGBitmapByteOrder32Big
												 );
	CGContextClearRect(context, CGRectMake(0, 0, this->mWidth, this->mHeight));
	CGContextDrawImage(context, CGRectMake(0, 0, this->mWidth, this->mHeight), cgImage);
	
	CGContextRelease(context);
    CFRelease(colorSpace);
}

void MOAIImageIOS::RegisterLuaClass(MOAILuaState &state){
	MOAIImage::RegisterLuaClass(state);
}

void MOAIImageIOS::RegisterLuaFuncs(MOAILuaState &state){
	MOAIImage::RegisterLuaFuncs(state);
}