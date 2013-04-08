-- ike-textBox.lua
-- written by Isaac D. Barrett
-- Created 2013-04-08
-- Last updated 2013-04-08

-- Set up the viewport
viewport = MOAIViewport.new ()
viewport:setSize ( 320, 480 )
viewport:setScale ( 320, -480 )
layer = MOAILayer2D.new ()
layer:setViewport ( viewport )
MOAISim.pushRenderPass ( layer )

-- arguments for MOAITextBox:initialize()
local width = 150
local height = 80
local text = "Testing out the new method."
local fontName = "Thonburi.ttf"
local minSize = 12
local desiredSize = 40
local multiline = false

charcodes = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 .,:;!?()&/-@#$%^*_+={}|[]~`<>'

-- Create the text box
textBox = MOAITextBox.new()

textBox:initialize( width, height, text, fontName, minSize, desiredSize, multiline )


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
]]

layer:insertProp(textBox)