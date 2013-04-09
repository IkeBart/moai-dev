-- ike-textBox.lua
-- written by Isaac D. Barrett
-- Created 2013-04-08
-- Last updated 2013-04-09

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
-- note: using "Testing out the new method." for the text will cause it to render on two lines without the adjustment.
local text = "Testing out the newt method."
local fontName = "Thonburi.ttf"
local minSize = 12
local desiredSize = 100
local multiline = false

charcodes = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 .,:;!?()&/-@#$%^*_+={}|[]~`<>'

-- Create the text box
textBox = MOAITextBox.new()

font = MOAIFont.new()
font:load(fontName)

--style = MOAITextStyle.new()
--style:setFont(font)
--style:setSize(desiredSize)

textBox:initialize( width, height, text, font, minSize, desiredSize, multiline )
textBox:setLoc(-150,-200)

--[[
style = MOAITextStyle.new()
font = MOAIFont.new()
font:load(fontName)
--font:preloadGlyphs(charcodes, desiredSize, 72)

style:setFont(font)
style:setSize(desiredSize)

textBox:setString (text)
textBox:setStyle(style)
textBox:setRect(0,0,width,height)

--print(string.format("About to call textBox:optimalFontSize(%s, 0.0, 0.0, %.1f, %.1f)", text, width, height))
local optSize = textBox:optimalFontSize(text, 0,0,width,height)
--print(string.format("optSize == %.3f", optSize))
local newSize = optSize
if optSize < minSize then newSize = minSize end
if optSize > desiredSize then newSize = desiredSize end

style:setSize(newSize)

--print(string.format("newSize == %.3f", newSize))
]]

layer:insertProp(textBox)