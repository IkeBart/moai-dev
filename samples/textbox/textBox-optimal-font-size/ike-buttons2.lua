-- ike-buttons2.lua
-- written by Isaac D. Barrett
-- Created 2013-04-03
-- Last updated 2013-04-05
--[[ It references several different fonts that I decided not to include here.  
    I think many of these fonts can be found in either the Moai SDK or in Cocos2D.
    Also the graphic the buttons use is found at '<moai root>/samples/contrib/moaigui/resources/media/moai.png'
]]
MOAISim.openWindow ( "test", 320, 480 )


-- Set up the viewport
viewport = MOAIViewport.new ()
viewport:setSize ( 320, 480 )
viewport:setScale ( 320, -480 )
layer = MOAILayer2D.new ()
layer:setViewport ( viewport )
MOAISim.pushRenderPass ( layer )

charcodes = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 .,:;!?()&/-@#$%^*_+={}|[]~`<>'

local stringOne = "M Button One Clicked"
--local stringOne = "M"
local stringTwo = "Button Two Clicked. Now this one is longer by a long shot."
--[[
    Max sizes for fonts to fill 100 pixel height box.
    
    Thonburi.ttf: 87.6
    Abduction.ttf: 100.2
    American Typewriter: 85.0
    Bastarda-K: 78.2 (78.3)
    Courier New: 88.7 (88.8)
]]

-- Set up the styles to use.  Change the value of size1 to see how the 
size1 = 40
font = MOAIFont.new ()
--font:loadFromTTF ('Abduction.ttf', charcodes, 15, 72)
font:load('Courier New.ttf')
font:preloadGlyphs(charcodes, size1, 72)

size2 = 20
font2 = MOAIFont.new ()
font2:load('Thonburi.ttf')
font2:preloadGlyphs(charcodes, size2, 72)

textStyle = MOAITextStyle.new()
textStyle:setFont(font)
textStyle:setColor(0.99,0.99,0.49,1.0)
textStyle:setSize(size1, 72)


textStyle2 = MOAITextStyle.new()
textStyle2:setFont(font2)
textStyle2:setColor(0.5,0.99,0.5,1.0)
textStyle2:setSize(size2, 72)


button = nil

tbX = -150
tbY = -230
tbWidth = 300
tbHeight = 100
tbX2 = tbX + tbWidth
tbY2 = tbY + tbHeight


-- Create the text box
textBox = MOAITextBox.new()
textBox:setString ("No buttons clicked yet")
--textBox:setFont (font)
--textBox:setTextSize (25, 72)
textBox:setStyle(textStyle)
textBox:setRect (tbX, tbY, tbX2, tbY2)
textBox:setYFlip ( false )
textBox:setAlignment(MOAITextBox.CENTER_JUSTIFY, MOAITextBox.LEFT_JUSTIFY)
layer:insertProp(textBox)

-- Coordinates for the first button
b1X = -64
b1Y = -64
b1X2 = b1X + 128
b1Y2 = b1Y + 128

-- Graphics for first 
gfxQuad = MOAIGfxQuad2D.new ()
gfxQuad:setTexture ( "./moaigui/resources/media/moai.png" )
gfxQuad:setRect (b1X, b1Y, b1X2, b1Y2 )
gfxQuad:setUVRect ( 0, 0, 1, 1 )

-- A transform to move the first button
bTransform = MOAITransform2D.new ()
bTransform:setLoc(-64,0)

button = MOAIProp2D.new ()
button:setParent(bTransform)
button:setDeck(gfxQuad)
layer:insertProp ( button )


-- Coordinates for the second button
b2X = -64
b2Y = -64
b2X2 = b2X + 128
b2Y2 = b2Y + 128

gfxQuad2 = MOAIGfxQuad2D.new ()
gfxQuad2:setTexture ( "./moaigui/resources/media/moai.png")
gfxQuad2:setRect (b2X, b2Y, b2X2, b2Y2)
gfxQuad2:setUVRect ( 1, 1, 0, 0 )

b2Transform = MOAITransform2D.new ()
b2Transform:setLoc(64,128)

button2 = MOAIProp2D.new ()
button2:setParent(b2Transform)
button2:setDeck(gfxQuad2)
layer:insertProp ( button2)


function onButtonOneClick(event,data)

    textBox:setString(stringOne)
    textBox:setStyle(textStyle)
end


-- print the value of optimalFontSize for stringOne and textBox's bounding box
function onButtonTwoClick(event,data)
    textBox:setString(stringTwo)
    --textBox:setStyle(textStyle2)
    
    local q, r = textBox:optimalFontSize(stringOne, tbX, tbY, tbX2, tbY2)
    if q then
        if r then
            print(string.format("ofs == %s, %s", q, r))
        else
            print(string.format("ofs == %s", q))
        end
    end
end


-- button press handling
function isInButton1Rect(x,y)
    local dX, dY = bTransform:getLoc ()
    local xInRect = (x >= b1X + dX) and (x <= b1X2 + dX);
    local yInRect = (y >= b1Y + dY) and (y <= b1Y2 + dY);
    
    return xInRect and yInRect

end

function isInButton2Rect(x,y)
    local dX, dY = b2Transform:getLoc ()
    local xInRect = (x >= b2X + dX) and (x <= b2X2 + dX);
    local yInRect = (y >= b2Y + dY) and (y <= b2Y2 + dY);
    
    return xInRect and yInRect
end

function handleClickOrTouch(x,y)
    local x2, y2 = layer:wndToWorld(x,y)
    print (string.format("touched screen at (%d, %d) translated to (%d, %d) ", x,y,x2,y2))
    -- find out if coordinates are in button one's rect
    if isInButton1Rect(x2,y2) then
        --print ("in bounds of Button 1")
        onButtonOneClick()
    -- find out if coordinates are in button two's rect
    elseif isInButton2Rect(x2,y2) then
        --print ("in bounds of Button 2")
        onButtonTwoClick()
    end
end

-- Copied from another source
if MOAIInputMgr.device.pointer then
    MOAIInputMgr.device.mouseLeft:setCallback(
        function(isMouseDown)
            if(isMouseDown) then
                handleClickOrTouch(MOAIInputMgr.device.pointer:getLoc())
            end
            -- Do nothing on mouseUp
        end
    )
    MOAIInputMgr.device.mouseRight:setCallback(
        function(isMouseDown)
            if(isMouseDown) then
                MOAIGfxDevice.getFrameBuffer():setClearColor(math.random(0,255)/255, math.random(0,255)/255, math.random(0,255)/255,1)
            end
        end
    )
else
-- Touch screen handler
    MOAIInputMgr.device.touch:setCallback(
        function ( eventType, idx, x, y, tapCount )
            if (tapCount > 1) then
                 MOAIGfxDevice.getFrameBuffer():setClearColor(math.random(0,255)/255, math.random(0,255)/255, math.random(0,255)/255,1)
            elseif eventType == MOAITouchSensor.TOUCH_DOWN then
                handleClickOrTouch(x,y)
            end

        end
    )
end

runAdditionalTest = false
if runAdditionalTest then
    local strHeight = textBox:getStyle():getSize()
    local boxHeight = tbHeight
    local boxWidth = tbWidth
    local idx = #stringOne

    testTB = MOAITextBox.new()
    testTB:setRect(0, 0, idx * strHeight * 2, strHeight * 2)
    testTB:setString(stringOne)
    testTB:setStyle(textBox:getStyle())
    
    local a, b, c, d = testTB:getStringBounds(1, idx)
    if a then
        print(string.format("testTB stringBounds == [%.1f, %.1f, %.1f, %.1f]",a,b,c,d))
    else
        print("testTB stringBounds == nil")
    end
end
