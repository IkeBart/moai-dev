-- draw.lua
-- written by Isaac D. Barrett
-- Created 2013-04-2
-- Last updated 2013-04-12
-- based on code from samples/anim/anim-curve-draw/main.lua

----------------------------------------------------------------
-- Copyright (c) 2010-2011 Zipline Games, Inc. 
-- All Rights Reserved. 
-- http://getmoai.com
----------------------------------------------------------------

print("loading anim/anim-curve-custom/draw.lua")

MOAISim.openWindow ( "test", 320, 480 )

viewport = MOAIViewport.new ()
viewport:setSize ( 320, 480 )
viewport:setScale ( 320, 480 )

layer = MOAILayer2D.new ()
layer:setViewport ( viewport )
MOAISim.pushRenderPass ( layer )

-- refer to funcs.lua for the list of interpolation functions available
require( "anim/anim-curve-custom/funcs" )

function makeCurve ( ease )

	local curve = MOAIAnimCurve.new ()
    if ease == MOAIEaseType.CUSTOM then
        curve:setCallback( easeSineOut )
    end

	curve:reserveKeys ( 2 )
	curve:setKey ( 1, 0, 0, ease )
	curve:setKey ( 2, 256, 256 )
	
	return curve
end

local curves = {
    makeCurve ( MOAIEaseType.CUSTOM ),
	makeCurve ( MOAIEaseType.EASE_IN ),
	makeCurve ( MOAIEaseType.EASE_OUT ),
	makeCurve ( MOAIEaseType.LINEAR ),
	makeCurve ( MOAIEaseType.SHARP_EASE_IN ),
	makeCurve ( MOAIEaseType.SHARP_EASE_OUT ),
	makeCurve ( MOAIEaseType.SHARP_SMOOTH ),
	makeCurve ( MOAIEaseType.SMOOTH ),
	makeCurve ( MOAIEaseType.SOFT_EASE_IN ),
	makeCurve ( MOAIEaseType.SOFT_EASE_OUT ),
	makeCurve ( MOAIEaseType.SOFT_SMOOTH ),
    
}

local names = {
    'CUSTOM',
	'EASE_IN',
	'EASE_OUT',
	'LINEAR',
	'SHARP_EASE_IN',
	'SHARP_EASE_OUT',
	'SHARP_SMOOTH',
	'SMOOTH',
	'SOFT_EASE_IN',
	'SOFT_EASE_OUT',
	'SOFT_SMOOTH',
}

local prevID = 0
local curveID = 1

function onDraw ( index, xOff, yOff, xFlip, yFlip )

	MOAIGfxDevice.setPenColor ( 1, 0, 0, 1 )
	MOAIDraw.drawAnimCurve ( curves [ curveID ], 100 )
	if prevID ~= curveID then
		print ( names [ curveID ])
		prevID = curveID
	end
end

scriptDeck = MOAIScriptDeck.new ()
scriptDeck:setRect ( -128, -128, 128, 128 )
scriptDeck:setDrawCallback ( onDraw )

prop = MOAIProp2D.new ()
prop:setDeck ( scriptDeck )
prop:setLoc ( -128, -128 )
layer:insertProp ( prop )

function onKeyboardEvent ( key, down )

	if down == true then
		curveID = curveID + 1
		if #curves < curveID then curveID = 1 end
	end
end

function onTouchEvent ( eventType, idx, x, y, tapCount )
    if eventType == MOAITouchSensor.TOUCH_DOWN then
        onKeyboardEvent( 0, true )
    end
end

if MOAIInputMgr.device.keyboard then
    MOAIInputMgr.device.keyboard:setCallback ( onKeyboardEvent )
elseif MOAIInputMgr.device.touch then
    MOAIInputMgr.device.touch:setCallback (onTouchEvent)
end
