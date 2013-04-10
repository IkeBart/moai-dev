-- ike-textBox3.lua
-- written by Isaac D. Barrett
-- Created 2013-04-10
-- Last updated 2013-04-10

-- Set up the viewport
viewport = MOAIViewport.new ()
viewport:setSize ( 320, 480 )
viewport:setScale ( 320, -480 )
layer = MOAILayer2D.new ()
layer:setViewport ( viewport )
MOAISim.pushRenderPass ( layer )


-- arguments for MOAITextBox:initialize()
local width = 300
local height = 80
text = "Touch the graphic for new text."
text2 = "A new string for the text box that is longer."
text3 = "Short string"
currentText = 0
local fontName = "Thonburi.ttf"
local minSize = 12
local desiredSize = 100
local multiline = false

-- Create the text box
textBox = MOAITextBox.new()

font = MOAIFont.new()
font:load(fontName)

textBox:initialize( width, height, text, font, minSize, desiredSize, multiline )
textBox:setLoc(-150,-200)
textBox:setWordBreak(MOAITextBox.WORD_BREAK_CHAR)
layer:insertProp(textBox)

-- coordinates for button
b1X = -64
b1Y = -64
b1X2 = b1X + 128
b1Y2 = b1Y + 128

bLocX = 0
bLocY = 0

-- Graphics for button
gfxQuad = MOAIGfxQuad2D.new ()
gfxQuad:setTexture ( "./moaigui/resources/media/moai.png" )
gfxQuad:setRect (b1X, b1Y, b1X2, b1Y2 )
gfxQuad:setUVRect ( 0, 0, 1, 1 )


button = MOAIProp2D.new ()
button:setDeck(gfxQuad)
button:setLoc(bLocX,bLocY)
layer:insertProp ( button )



-- button press handling
function onButtonOneClick(event,data)
    local newString = "The hidden fourth string."
    if currentText == 0 then
        newString = text2
    elseif currentText == 1 then
        newString = text3
    end
    
    currentText = currentText + 1
    if currentText > 2 then
        currentText = 0
    end

    textBox:setString(newString, true)
end



function isInButton1Rect(x,y)
    local dX, dY = button:getLoc ()
    local xInRect = (x >= b1X + dX) and (x <= b1X2 + dX);
    local yInRect = (y >= b1Y + dY) and (y <= b1Y2 + dY);
    
    return xInRect and yInRect

end

function handleClickOrTouch(x,y)
    local x2, y2 = layer:wndToWorld(x,y)
    --print (string.format("touched screen at (%d, %d) translated to (%d, %d) ", x,y,x2,y2))
    -- find out if coordinates are in button one's rect
    if isInButton1Rect(x2,y2) then
        --print ("in bounds of Button 1")
        onButtonOneClick()
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
else
-- Touch screen handler
    MOAIInputMgr.device.touch:setCallback(
        function ( eventType, idx, x, y, tapCount )
            if eventType == MOAITouchSensor.TOUCH_UP then
                handleClickOrTouch(x,y)
            end
        end
    )
end