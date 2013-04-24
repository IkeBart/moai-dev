// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <contrib/utf8.h>
#include <moaicore/MOAIDataBuffer.h>
#include <moaicore/MOAIGlyphCacheBase.h>
#include <moaicore/MOAIFont.h>
#include <moaicore/MOAIFontReader.h>
#include <moaicore/MOAIGfxDevice.h>
#include <moaicore/MOAIGlyphCacheBase.h>
#include <moaicore/MOAIImage.h>
#include <moaicore/MOAIImageTexture.h>
#include <moaicore/MOAILogMessages.h>
#include <moaicore/MOAIStaticGlyphCache.h>
#include <moaicore/MOAITextureBase.h>
#include <moaicore/MOAITextBox.h>
#include <moaicore/MOAITextStyle.h>

//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//
/**	@name	getFilename
	@text	Returns the filename of the font.
	
	@in		MOAIFont self
	@out	name
*/
int MOAIFont::_getFilename ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIFont, "U" )
	state.Push ( self->mFilename );
	return 1;
}

//----------------------------------------------------------------//
/**	@name	getFlags
	@text	Returns the current flags.
	
	@in		MOAIFont self
	@out	flags
*/
int MOAIFont::_getFlags ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIFont, "U" )
	state.Push ( self->mFlags );
	return 1;
}

//----------------------------------------------------------------//
/**	@name	getImage
	@text	Requests a 'glyph map image' from the glyph cache currently
			attached to the font. The glyph map image stiches together the
			texture pages used by the glyph cache to produce a single image
			that represents a snapshot of all of the texture memory being
			used by the font.
	
	@in		MOAIFont self
	@out	MOAIImage image
*/
int MOAIFont::_getImage ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIFont, "U" )

	if ( self->mCache ) {
		MOAIImage* image = self->mCache->GetImage ();
		if ( image ) {
			state.Push ( image );
			return 1;
		}
	}
	return 0;
}

//----------------------------------------------------------------//
/**	@name	load
	@text	Sets the filename of the font for use when loading glyphs.

	@in		MOAIFont self
	@in		string filename			The path to the font file to load.
	@out	nil
*/
int MOAIFont::_load ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIFont, "US" )

	cc8* filename	= state.GetValue < cc8* >( 2, "" );
	self->Init ( filename );
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	loadFromBMFont
	@text	Sets the filename of the font for use when loading a BMFont.
 
	@in		MOAIFont self
	@in		string filename			The path to the BMFont file to load.
	@out	nil
*/
int	MOAIFont::_loadFromBMFont ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIFont, "US" )
	
	cc8* filename	= state.GetValue < cc8* >( 2, "" );
	self->InitWithBMFont ( filename );
	return 0;
}
//----------------------------------------------------------------//
/**	@name	optimalSize
	@text   Determines the optimal size of the font for a text box of the given dimensions and font size constraints.
	@in		string text
	@in		number width				The width of the text box
	@in		number height				The height of the text box
	@opt	number minSize				The minimum font size to allow (default zero)
	@opt	number maxSize				The maximum font size to allow (default to min(width, height) * 2.0)
	@opt	boolean allowMultiline		Whether to allow the text to span multiple lines (default true)
	@opt	number adjustmentFactor		The factor to multiply the result by before bound checking (default 0.98)
	@out    number optimalSize			nil when unable to determine.
 */
int MOAIFont::_optimalSize(lua_State *L){
	MOAI_LUA_SETUP( MOAIFont, "USNN"); // "USNN"
	
	cc8* text = state.GetValue < cc8* >( 2, "" );
	float width = state.GetValue < float >( 3, 0.0f );
	float height   = state.GetValue < float >( 4, 0.0f );
	float minSize = 0.0f;
	float maxSize = (width > height)? width * 2 : height * 2;
	bool allowMultiline = true;
	
	if (state.GetTop() >= 5) {
		minSize = state.GetValue < float >(5, 0.0f);
	}
	if (state.GetTop() >= 6) {
		maxSize = state.GetValue < float >(6, 0.0f);
	}
	if (state.GetTop() >= 7) {
		allowMultiline = state.GetValue < bool > (7, true);
	}
	
	float adjustmentFactor = 0.98f;
	if (state.GetTop() >= 8) {
		adjustmentFactor = state.GetValue < float >(8, adjustmentFactor);
	}
	
	float optSize = self->OptimalSize(text, width, height, minSize, maxSize, allowMultiline, adjustmentFactor);
	//if (optSize >= 0.0f) {
		lua_pushnumber(L, optSize);
		return 1;
	//}
	
	//return 0;
}


//----------------------------------------------------------------//
/**	@name	preloadGlyphs
	@text	Loads and caches glyphs for quick access later.

	@in		MOAIFont self
	@in		string charCodes		A string which defines the characters found in the this->
	@in		number points			The point size to be rendered onto the internal texture.
	@opt	number dpi				The device DPI (dots per inch of device screen). Default value is 72 (points same as pixels).
	@out	nil
*/
int MOAIFont::_preloadGlyphs ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIFont, "USN" )

	cc8* charCodes	= state.GetValue < cc8* >( 2, "" );
	float points	= state.GetValue < float >( 3, 0 );
	float dpi		= state.GetValue < float >( 4, DPI );
	
	float size = POINTS_TO_PIXELS ( points, dpi );
	
	int idx = 0;
	while ( charCodes [ idx ]) {
		u32 c = u8_nextchar ( charCodes, &idx );
		self->AffirmGlyph ( size, c );
	}
	self->ProcessGlyphs ();
	return 0;
}

//----------------------------------------------------------------//
/**	@name	rebuildKerningTables
	@text	Forces a full reload of the kerning tables for either a single
			glyph set within the font (if a size is specified) or for all
			glyph sets in the font.
	
	@overload
	
		@in		MOAIFont self
		@out	nil
	
	@overload
	
		@in		MOAIFont self
		@in		number points			The point size to be rendered onto the internal texture.
		@opt	number dpi				The device DPI (dots per inch of device screen). Default value is 72 (points same as pixels).
		@out	nil
*/
int MOAIFont::_rebuildKerningTables ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIFont, "U" )
	
	if ( self->mReader ) {
	
		if ( state.IsType ( 2, LUA_TNUMBER )) {
			
			float points	= state.GetValue < float >( 2, 0 );
			float dpi		= state.GetValue < float >( 3, DPI );
			
			float size = POINTS_TO_PIXELS ( points, dpi );
			self->RebuildKerning ( size );
		}
		else {
			self->RebuildKerning ();
		}
	}
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setCache
	@text	Attaches or cloears the glyph cache associated with the font.
			The cache is an object derived from MOAIGlyphCacheBase and may be
			a dynamic cache that can allocate space for new glyphs on an
			as-needed basis or a static cache that only supports direct
			loading of glyphs and glyph textures through MOAIFont's
			setImage () command.

	@in		MOAIFont self
	@opt	MOAIGlyphCacheBase cache		Default value is nil.
	@out	nil
*/
int MOAIFont::_setCache ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIFont, "U" )
	self->mCache.Set ( *self, state.GetLuaObject < MOAIGlyphCacheBase >( 2, true ));
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setDefaultSize
	@text	Selects a glyph set size to use as the default size when no
			other size is specified by objects wishing to use MOAIFont to
			render text.

	@in		MOAIFont self
	@in		number points			The point size to be rendered onto the internal texture.
	@opt	number dpi				The device DPI (dots per inch of device screen). Default value is 72 (points same as pixels).
	@out	nil
*/
int MOAIFont::_setDefaultSize ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIFont, "U" )
	
	float points	= state.GetValue < float >( 2, 0 );
	float dpi		= state.GetValue < float >( 3, DPI );
			
	self->mDefaultSize = POINTS_TO_PIXELS ( points, dpi );
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setFlags
	@text	Set flags to control font loading behavior. Right now the
			only supported flag is FONT_AUTOLOAD_KERNING which may be used
			to enable automatic loading of kern tables. This flag is initially
			true by default.

	@in		MOAIFont self
	@opt	number flags			Flags are FONT_AUTOLOAD_KERNING or DEFAULT_FLAGS. DEFAULT_FLAGS is the same as FONT_AUTOLOAD_KERNING.
									Alternatively, pass '0' to clear the flags.
	@out	nil
*/
int MOAIFont::_setFlags ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIFont, "U" )
	self->mFlags = state.GetValue < u32 >( 2, DEFAULT_FLAGS );
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setImage
	@text	Passes an image to the glyph cache currently attached to the font.
			The image will be used to recreate and initialize the texture memory
			managed by the glyph cache and used by the font. It will not affect
			any glyph entires that have already been laid out and stored in
			the glyph cache.
			
			If no cache is attached to the font, an instance of MOAIStaticGlyphCache
			will automatically be allocated.
	
	@in		MOAIFont self
	@in		MOAIImage image
	@out	nil
*/
int MOAIFont::_setImage ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIFont, "UU" )

	if ( !self->mCache ) {
		MOAIGlyphCacheBase* glyphCache = new MOAIStaticGlyphCache ();
		self->mCache.Set ( *self, glyphCache );
	}

	assert ( self->mCache );

	MOAIImage* image = state.GetLuaObject < MOAIImage >( 2, true );
	if ( image ) {
		self->mCache->SetImage ( *self, *image );
	}
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setReader
	@text	Attaches or clears the MOAIFontReader associated withthe font.
			MOAIFontReader is responsible for loading and rendering glyphs from
			a font file on demand. If you are using a static font and do not
			need a reader, set this field to nil.

	@in		MOAIFont self
	@opt	MOAIFontReader reader		Default value is nil.
	@out	nil
*/
int MOAIFont::_setReader ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIFont, "U" )
	self->mReader.Set ( *self, state.GetLuaObject < MOAIFontReader >( 2, true ));
	return 0;
}

//================================================================//
// DOXYGEN
//================================================================//

#ifdef DOXYGEN

	//----------------------------------------------------------------//
	/**	@name	loadFromTTF
		@text	Preloads a set of glyphs from a TTF or OTF. Included for
				backward compatibility. May be removed in a future release.
		
		@in		MOAIFont self
		@in		string filename
		@in		string charcodes
		@in		number points			The point size to be loaded from the TTF.
		@opt	number dpi				The device DPI (dots per inch of device screen). Default value is 72 (points same as pixels).
		@out	nil
	*/
	int MOAIFont::_loadFromTTF ( lua_State* L ) {
	}

#endif

//================================================================//
// MOAIFont
//================================================================//

//----------------------------------------------------------------//
void MOAIFont::AffirmGlyph ( float size, u32 c ) {

	if ( this->mCache && this->mCache->IsDynamic ()) {
		MOAIGlyphSet& glyphSet = this->AffirmGlyphSet ( size );
		glyphSet.AffirmGlyph ( c );
	}
}

//----------------------------------------------------------------//
MOAIGlyphSet& MOAIFont::AffirmGlyphSet ( float size ) {

	MOAIGlyphSet& glyphSet = this->mGlyphSets [ size ];
	glyphSet.mSize = size;
	
	if ( this->mDefaultSize <= 0.0f ) {
		this->mDefaultSize = size;
	}
	return glyphSet;
}

//----------------------------------------------------------------//
// iterate through the pending glyphs in each set and attempt to
// update them to match target - i.e. metrics or metrics and bitmap
void MOAIFont::BuildKerning ( MOAIGlyph* glyphs, MOAIGlyph* pendingGlyphs ) {

	if ( !this->mReader->HasKerning ()) return;
	MOAIKernVec kernTable [ MOAIGlyph::MAX_KERN_TABLE_SIZE ]; // TODO: handle overflow cases

	// iterate over the orignal glyphs and add kerning info for new glyphs
	for ( MOAIGlyph* glyphIt = glyphs; glyphIt; glyphIt = glyphIt->mNext ) {
		MOAIGlyph& glyph = *glyphIt;
		
		u32 kernTableSize = 0;
		u32 oldTableSize = glyph.mKernTable.Size ();
		
		// iterate over just the new glyphs; check each one against olf glyphs for kerning info
		for ( MOAIGlyph* glyphIt2 = pendingGlyphs; glyphIt2; glyphIt2 = glyphIt2->mNext ) {
			MOAIGlyph& glyph2 = *glyphIt2;
			
			// skip if glyph is already in old glyph's kerning table
			// may happen if glyphs are purged and then re-added
			bool unknown = true;
			for ( u32 i = 0; i < oldTableSize; ++i ) {
				if ( glyph.mKernTable [ i ].mName == glyph2.mCode ) {
					unknown = false;
					break;
				}
			} 
			
			if ( unknown ) {
				MOAIKernVec kernVec;
				if ( this->mReader->GetKernVec ( glyph, glyph2, kernVec )) {
					assert ( kernTableSize < MOAIGlyph::MAX_KERN_TABLE_SIZE );
					kernTable [ kernTableSize++ ] = kernVec;
				}
			}
		}
		
		// resize the old kerning table and copy in the new kern vecs (if any)
		if ( kernTableSize ) {
			glyph.mKernTable.Resize ( oldTableSize + kernTableSize );
			memcpy ( &glyph.mKernTable [ oldTableSize ], kernTable, sizeof ( MOAIKernVec ) * kernTableSize );
		}
	}
	
	// iterate over the new glyphs and add kerning info for all glyphs
	for ( MOAIGlyph* glyphIt = pendingGlyphs; glyphIt; glyphIt = glyphIt->mNext ) {
		MOAIGlyph& glyph = *glyphIt;
		
		u32 kernTableSize = 0;
		
		// iterate over the original glyphs
		for ( MOAIGlyph* glyphIt2 = glyphs; glyphIt2; glyphIt2 = glyphIt2->mNext ) {
			MOAIGlyph& glyph2 = *glyphIt2;
			
			MOAIKernVec kernVec;
			if ( this->mReader->GetKernVec ( glyph, glyph2, kernVec )) {
				assert ( kernTableSize < MOAIGlyph::MAX_KERN_TABLE_SIZE );
				kernTable [ kernTableSize++ ] = kernVec;
			}
		}
		
		// iterate over the new glyphs
		for ( MOAIGlyph* glyphIt2 = pendingGlyphs; glyphIt2; glyphIt2 = glyphIt2->mNext ) {
			MOAIGlyph& glyph2 = *glyphIt2;
			
			MOAIKernVec kernVec;
			if ( this->mReader->GetKernVec ( glyph, glyph2, kernVec )) {
				assert ( kernTableSize < MOAIGlyph::MAX_KERN_TABLE_SIZE );
				kernTable [ kernTableSize++ ] = kernVec;
			}
		}
		
		// init the kern table
		if ( kernTableSize ) {
			glyph.mKernTable.Init ( kernTableSize );
			memcpy ( glyph.mKernTable, kernTable, sizeof ( MOAIKernVec ) * kernTableSize );
		}
	}
}

//----------------------------------------------------------------//
MOAIGlyphSet* MOAIFont::GetGlyphSet ( float size ) {

	if (( size > 0.0f ) && this->mGlyphSets.contains ( size )) {
		return &this->mGlyphSets [ size ];
	}
	else if ( size == 0.0f ) {
		if ( this->mDefaultSize <= 0.0f ) return 0;
		return &this->mGlyphSets [ this->mDefaultSize ];
	}
	else if ( this->mGlyphSets.size ()) {
		
		MOAIFont::GlyphSetsIt glyphSetsIt = this->mGlyphSets.begin ();
		MOAIGlyphSet* bestMatch = &( glyphSetsIt++ )->second;
		float bestSizeDiff = ABS ( size - bestMatch->mSize );
		
		for ( ; glyphSetsIt != this->mGlyphSets.end (); ++glyphSetsIt ) {
			MOAIGlyphSet& glyphSet = glyphSetsIt->second;
			float sizeDiff = ABS ( size - glyphSet.mSize );
			
			if ( sizeDiff < bestSizeDiff ) {
				bestMatch = &glyphSet;
				bestSizeDiff = sizeDiff;
			}
		}
		return bestMatch;
	}
	return 0;
}

//----------------------------------------------------------------//
MOAITextureBase* MOAIFont::GetGlyphTexture ( MOAIGlyph& glyph ) {

	assert ( this->mCache );
	return this->mCache->GetGlyphTexture ( glyph );
}

//----------------------------------------------------------------//
void MOAIFont::Init ( cc8* filename ) {

	if ( MOAILogMessages::CheckFileExists ( filename )) {
		this->mFilename = USFileSys::GetAbsoluteFilePath ( filename );
	}
}

//----------------------------------------------------------------//
bool MOAIFont::IsControl ( u32 c ) {

	if ( !c ) return true;
	if ( c == '\t' ) return true;
	if ( c == '\r' ) return true;
	if ( c == '\n' ) return true;
	
	return false;
}

//----------------------------------------------------------------//
bool MOAIFont::IsWhitespace ( u32 c ) {

	if ( c == ' ' ) return true;
	
	return false;
}

//----------------------------------------------------------------//
MOAIFont::MOAIFont () :
	mFlags ( DEFAULT_FLAGS ),
	mDefaultSize ( 0.0f ) {
	
	RTTI_BEGIN
		RTTI_EXTEND ( MOAILuaObject )
	RTTI_END
}

//----------------------------------------------------------------//
MOAIFont::~MOAIFont () {

	this->mReader.Set ( *this, 0 );
	this->mCache.Set ( *this, 0 );
}
//----------------------------------------------------------------//
float MOAIFont::OptimalSize (cc8* text, float width, float height, float minSize, float maxSize, bool allowMultiLine, float adjustmentFactor){
	float optimumSize = 0.0f;
	
	// if either width or height are negative, multiply by -1
	if (width < 0.0f) {
		width *= -1.0f;
	}
	if (height < 0.0f) {
		height *= -1.0f;
	}
	
	if (height == 0.0f || width == 0.0f) {
		return -1.0f;
	}
	
	int textLength = strlen(text);
	if (textLength == 0) {
		return -2.0f;
	}
	
	// sanity checks for minSize and maxSize
	if (minSize < 0.0f) {
		minSize = 0.0f;
	}
	if (maxSize < minSize) {
		maxSize = minSize;
	}
	
	// create a temporary text box and text style
	MOAITextStyle *style = new MOAITextStyle();
	style->SetFont(this);
	style->SetSize(maxSize);
	style->ScheduleUpdate();
	
	
	MOAITextBox *textBox = new MOAITextBox ();
	textBox -> SetRect(0.0f, 0.0f, textLength * maxSize * 2, maxSize * 2);
	
	
	textBox -> SetText(text);
	textBox -> SetStyle(style);
	textBox -> ResetStyleMap(); // private methods that I called in previous implementation
	textBox -> ScheduleLayout();
	//textBox->mNeedsLayout = true;
	//textBox -> ScheduleUpdate();
	
	USRect boxRect;
	boxRect.Init(0.0f,0.0f,0.0f,0.0f);
	if (! textBox->GetBoundsForRange(0, textLength, boxRect)) {
		//textBox->Release();
		//style->Release();
		return -4.0f;
	}
	
	float boxWidth = boxRect.Width();
	float boxHeight = boxRect.Height();
	if (boxWidth == 0.0f) {
		//textBox->Release();
		//style->Release();
		return -5.0f;
	}
	if (boxHeight == 0.0f) {
		//textBox->Release();
		//style->Release();
		return -6.0f;
	}
	if (allowMultiLine) {
		float wRatio = width / boxWidth;
		float hRatio = height / boxHeight;
		//float minRatio = (wRatio < hRatio) ? wRatio : hRatio;
		
		float maxVSize = hRatio * maxSize;
		// make sure the calculated size is less than or equal to maxSize
		float calcSize = (maxVSize < maxSize)?maxVSize : maxSize; 
		
		
		// calculate the number of lines needed at the maximum font size that can fit in the box's height.
		float lines = 1.0f;
		
		// calculate the new width of the box by multiplying by the ratio of the calculated size to the maximum size parameter
		float calcWidth = boxWidth * (calcSize / maxSize);
		
		// find out number of lines needed at the calculated size
		float hLines = ceilf(calcWidth / width);
		// make sure that this does not exceed the number of characters in the string
		if (hLines > (float)textLength){
			hLines = textLength;
		}
		
		// calculate vertical line capacity of text box at calculated size (should be at least one)
		float calcHeight = boxHeight * (calcSize / maxSize);
		float vLines = floorf(height / calcHeight);
		
		
		// if this number is less than or equal to the line capacity at the calculated size
		if (hLines <= vLines) {
			// use this font size as the optimal size
			optimumSize = calcSize / adjustmentFactor;
		}
		else {
			// else, try finding a new calculated size that fits
			
			
			// find new calculated size with vLines
			float newVLines = vLines, newHLines = hLines, newCalcSize, newCalcWidth, newCalcHeight;
			lines = 2.0f;
			do {
				// find font size that can fill x lines in the text box using the previously calculated maxVSize variable divided by number of lines to attempt
				newCalcSize = maxVSize / lines;
				
				if (newCalcSize > maxSize) {
					newCalcSize = maxSize; // make sure this new calculated size is less than or equal to maxSize
				}
				
				// calculate a new string bound width using newCalcSize
				newCalcWidth = boxWidth * (newCalcSize / maxSize);
				// find out number of lines needed at the new calculated size based on width
				newHLines = ceilf(newCalcWidth / width);
				if (newHLines > (float)textLength){
					newHLines = textLength;
				}
				
				// calculate new vertical line capacity using newCalcSize
				newCalcHeight = boxHeight * (newCalcSize / maxSize);
				newVLines = floorf(height / newCalcHeight);
				
				lines += 1.0f; // add an extra line and try again
			} while (newHLines > newVLines);
			
			// first, try shrinking the font size so the string's width will fit in (vLines * width)
			// multiply calculated size by factor
			/*
			bool foundOptimum = false;
			float shrinkFactor = 1.0f, newVLines = vLines, newHLines = hLines, newBoxWidth = boxWidth;
			int i = 0; // number of times loop has completed, abort after 20th iteration.
			do {
				// determine the number to divide using
				shrinkFactor = (newHLines * width) / boxWidth;
				if (shrinkFactor < 1.0) { // set to its reciprocal if below one
					shrinkFactor = 1.0 / shrinkFactor;
				}
				// divide calcSize by shrinkFactor
				calcSize /= shrinkFactor;
				
				// recalculate calcHeight and calcWidth using new value of calcSize.
				calcHeight = boxHeight * (calcSize / maxSize);
				calcWidth = boxWidth * (calcSize / maxSize);
				
				// calculate newVLines and newHLines
				newVLines = floorf(height / calcHeight); // this should go up or remain the same
				newHLines = ceilf(calcWidth / width); // this should go down or remain the same
				if (newHLines > (float)textLength){
					newHLines = textLength;
				}
				
				foundOptimum = (newHLines <= newVLines) || (i >= 20);
				i = i+1;
			} while (!foundOptimum);
			 
			 */
			optimumSize = newCalcSize / adjustmentFactor;
			// remember that cutting font size in half will quadruple text box capacity.
			
		}
		
		
		// calculate the number of lines needed at maximum font size
		//float lines = 1.0f; //ceilf(boxWidth / width);
		
		// minimum number of lines needed to fit text's bounding box width within text box with maximum font size
		//float hLines = ceilf(boxWidth / width);
		
		/*
		// make sure that this does not exceed the number of characters in the string
		if (hLines > (float)textLength){
			hLines = textLength;
		}
		
		// maximum number of lines of text that can fit in text box's height
		float vLines = floorf(height / boxHeight);
		
		// take whichever of the two numbers is smaller
		float new_lines = (hLines < vLines) ? hLines : vLines;
		
		// make sure the number is greater or equal to one.
		if (new_lines > lines) {
			lines = new_lines;
		}
		*/
		
		
		/*
		// calculate the number of lines needed at maximum font size
		float lines = 1.0f; //ceilf(boxWidth / width);
		
		// minimum number of lines needed to fit text's bounding box width within text box
		float hLines = ceilf(boxWidth / width);
		
		// make sure that this does not exceed the number of characters in the string
		if (hLines > (float)textLength){
			hLines = textLength;
		}
		
		// maximum number of lines of text that can fit in text box's height
		float vLines = floorf(height / boxHeight);
		
		// take whichever of the two numbers is greater
		float new_lines = (hLines > vLines) ? hLines : vLines;
		
		// make sure the number is greater or equal to one.
		if (new_lines > lines) {
			lines = new_lines;
		}
		
		style->SetFont(this);
		style->SetSize(maxSize);
		style->ScheduleUpdate();
		
		//textBox -> SetRect(0.0f,0.0f, (maxSize * 2 * textLength) / lines, maxSize * 2 * lines);
		//textBox -> SetRect(0.0f,0.0f, width ,maxSize * 2 * lines);
		
		// set bounding box's width to previously determined width width divided by number of lines.
		
		if (lines > 1) {
			textBox -> SetRect(0.0f, 0.0f, boxWidth / lines, maxSize * 2 * lines);
		}
		else{
			textBox -> SetRect(0.0f, 0.0f, maxSize * 2 * textLength, maxSize * 2);
		}
		
		textBox -> SetText(text);
		textBox -> SetStyle(style);
		textBox -> ResetStyleMap(); // private methods that I called in previous implementation
		textBox -> ScheduleLayout();
		
		if (! textBox -> GetBoundsForRange(0, textLength, boxRect)) {
			return -7.0f;
		}
		boxWidth = boxRect.Width();
		boxHeight = boxRect.Height();
		if (boxWidth == 0.0f) {
			return -8.0f;
		}
		if (boxHeight == 0.0f) {
			return -9.0f;
		}
		 */
	}
	else{
	
		float wRatio = width / boxWidth;
		float hRatio = height / boxHeight;
		float minRatio = (wRatio < hRatio) ? wRatio : hRatio;
		
		// get optimumSize by multiplying the maximum size by the smaller of the two ratios
		optimumSize = maxSize * minRatio;
	}
	
	// multiply result by adjustmentFactor
	optimumSize *= adjustmentFactor;
	
	// make sure return value is between minSize and maxSize
	if (optimumSize < minSize) {
		optimumSize = minSize;
	}
	if (optimumSize > maxSize) {
		optimumSize = maxSize;
	}
	
	// TODO: implement multi-line optimal sizing
	if (allowMultiLine) {
		
	}
	
	// clean-up
	// TODO: find a way to clean-up the objects without getting errors.
	// Perhaps it is done automatically for all MOAIObjects or MOAILuaObjects.
	//delete textBox;
	//delete style;
	
	//textBox->Release();
	//style->Release();
	
	
	return optimumSize;
}

//----------------------------------------------------------------//
// iterate through the pending glyphs in each set and attempt to
// update them to match target - i.e. metrics or metrics and bitmap
void MOAIFont::ProcessGlyphs () {

	if ( !this->mReader ) return;

	bool fontIsOpen = false;
	
	MOAIFont::GlyphSetsIt glyphSetsIt = this->mGlyphSets.begin ();
	for ( ; glyphSetsIt != this->mGlyphSets.end (); ++glyphSetsIt ) {
		MOAIGlyphSet& glyphSet = glyphSetsIt->second;
		
		// save pointers to the two glyph lists
		MOAIGlyph* glyphs = glyphSet.mGlyphs;
		MOAIGlyph* pendingGlyphs = glyphSet.mPending;
		
		// all pending glyphs will be moved to the processed glyphs list
		// so clear the pending glyphs list
		glyphSet.mPending = 0;
		
		// if no pending glyphs, move on to the next deck
		if ( !pendingGlyphs ) continue;
		
		if ( !fontIsOpen ) {
			this->mReader->OpenFont ( *this );
			fontIsOpen = true;
		}
		
		// get the face metrics
		this->mReader->SetFaceSize ( glyphSet.mSize );
		this->mReader->GetFaceMetrics ( glyphSet );
		
		// build kerning tables (if face has kerning info)
		if (( this->mFlags & FONT_AUTOLOAD_KERNING ) && this->mReader->HasKerning ()) {
			this->BuildKerning ( glyphs, pendingGlyphs );
		}
		
		//----------------------------------------------------------------//
		// render the new glyphs and move them to the processed list
		for ( MOAIGlyph* glyphIt = pendingGlyphs; glyphIt; ) {
			MOAIGlyph& glyph = *glyphIt;
			glyphIt = glyphIt->mNext;
			
			// move the glyph into the processed glyphs list
			glyph.mNext = glyphSet.mGlyphs;
			glyphSet.mGlyphs = &glyph;
			
			this->mReader->RenderGlyph ( *this, glyph );
		}
	}

	if ( fontIsOpen ) {
		this->mReader->CloseFont ();
	}
}

//----------------------------------------------------------------//
void MOAIFont::RebuildKerning () {

	if ( !this->mReader ) return;
	if ( !this->mGlyphSets.size ()) return;
	
	this->mReader->OpenFont ( *this );
	
	if ( this->mReader->HasKerning ()) {
	
		MOAIFont::GlyphSetsIt glyphSetsIt = this->mGlyphSets.begin ();
		for ( ; glyphSetsIt != this->mGlyphSets.end (); ++glyphSetsIt ) {
			MOAIGlyphSet& glyphSet = glyphSetsIt->second;
			this->RebuildKerning ( glyphSet );
		}
	}
	this->mReader->CloseFont ();
}

//----------------------------------------------------------------//
void MOAIFont::RebuildKerning ( float size ) {

	if ( !this->mReader ) return;
	if ( !this->mReader->HasKerning ()) return;
	if ( !this->mGlyphSets.contains ( size )) return;
	
	this->mReader->OpenFont ( *this );
	
	MOAIGlyphSet& glyphSet = this->mGlyphSets [ size ];
	this->RebuildKerning ( glyphSet );
	
	this->mReader->CloseFont ();
}

//----------------------------------------------------------------//
void MOAIFont::RebuildKerning ( MOAIGlyphSet& glyphSet ) {
	
	MOAIKernVec kernTable [ MOAIGlyph::MAX_KERN_TABLE_SIZE ];
	
	// get the face metrics
	this->mReader->SetFaceSize ( glyphSet.mSize );

	u32 kernTableSize = 0;

	// iterate over the orignal glyphs and add kerning info for new glyphs
	for ( MOAIGlyph* glyphIt = glyphSet.mGlyphs; glyphIt; glyphIt = glyphIt->mNext ) {
		MOAIGlyph& glyph = *glyphIt;
		
		// iterate over just the new glyphs; check each one against old glyphs for kerning info
		for ( MOAIGlyph* glyphIt2 = glyphSet.mGlyphs; glyphIt2; glyphIt2 = glyphIt2->mNext ) {
			MOAIGlyph& glyph2 = *glyphIt2;
			
			MOAIKernVec kernVec;
			if ( this->mReader->GetKernVec ( glyph, glyph2, kernVec )) {
				assert ( kernTableSize < MOAIGlyph::MAX_KERN_TABLE_SIZE );
				kernTable [ kernTableSize++ ] = kernVec;
			}
		}
		
		// init (or clear) the kern table
		glyph.mKernTable.Resize ( kernTableSize );
		
		// copy in the new kern vecs (if any)
		if ( kernTableSize ) {
			memcpy ( glyph.mKernTable, kernTable, sizeof ( MOAIKernVec ) * kernTableSize );
		}
	}
}

//----------------------------------------------------------------//
void MOAIFont::RegisterLuaClass ( MOAILuaState& state ) {
	
	state.SetField ( -1, "DEFAULT_FLAGS",			( u32 )DEFAULT_FLAGS );
	state.SetField ( -1, "FONT_AUTOLOAD_KERNING",	( u32 )FONT_AUTOLOAD_KERNING );
}

//----------------------------------------------------------------//
void MOAIFont::RegisterLuaFuncs ( MOAILuaState& state ) {
	
	luaL_Reg regTable [] = {
		{ "getFlags",					_getFlags },
		{ "getFilename",				_getFilename },
		{ "getImage",					_getImage },
		{ "load",						_load },
		{ "loadFromBMFont",				_loadFromBMFont },
		{ "optimalSize",				_optimalSize }, // added
		{ "preloadGlyphs",				_preloadGlyphs },	
		{ "rebuildKerningTables",		_rebuildKerningTables },
		{ "setCache",					_setCache },
		{ "setDefaultSize",				_setDefaultSize },
		{ "setFlags",					_setFlags },
		{ "setImage",					_setImage },
		{ "setReader",					_setReader },
		{ NULL, NULL }
	};
	
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAIFont::SerializeIn ( MOAILuaState& state, MOAIDeserializer& serializer ) {
	UNUSED ( serializer );

	this->mFilename = state.GetField ( -1, "mFilename", this->mFilename );
	this->mFlags = state.GetField ( -1, "mFlags", this->mFlags );
	this->mDefaultSize = state.GetField ( -1, "mDefaultSize", this->mDefaultSize );
	
	if ( state.GetFieldWithType ( -1, "mGlyphSets", LUA_TTABLE )) {

		u32 itr = state.PushTableItr ( -1 );
		while ( state.TableItrNext ( itr )) {
			float size = state.GetValue < float >( -2, 0 );
			MOAIGlyphSet& glyphSet = this->mGlyphSets [ size ];
			glyphSet.SerializeIn ( state );
		}
		state.Pop ( 1 );
	}
}

//----------------------------------------------------------------//
void MOAIFont::SerializeOut ( MOAILuaState& state, MOAISerializer& serializer ) {
	UNUSED ( serializer );

	state.SetField ( -1, "mFilename", this->mFilename );
	state.SetField ( -1, "mFlags", this->mFlags );
	state.SetField ( -1, "mDefaultSize", this->mDefaultSize );
	
	lua_newtable ( state );
	GlyphSetsIt glyphSetsIt = this->mGlyphSets.begin ();
	for ( ; glyphSetsIt != this->mGlyphSets.end (); ++glyphSetsIt ) {
	
		float size = glyphSetsIt->first;
		MOAIGlyphSet& glyphSet = glyphSetsIt->second;
	
		lua_pushnumber ( state, size );
		lua_newtable ( state );
		glyphSet.SerializeOut ( state );
		lua_settable ( state, -3 );
	}
	lua_setfield ( state, -2, "mGlyphSets" );
}

