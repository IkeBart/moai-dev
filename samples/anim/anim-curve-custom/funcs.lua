-- funcs.lua
-- written by Isaac D. Barrett
-- Created 2013-04-2
-- Last updated 2013-04-12
-- A bunch of functions adopted from Cocos2d for custom animation curves.

print("loading anim/anim-curve-custom/funcs.lua")

function easeBackIn( t )
    overshoot = 1.70158
    return t * t * ((overshoot + 1) * t - overshoot)
end

function easeBackOut( t )
    overshoot = 1.70158
    t = t - 1
    return t * t * ((overshoot + 1) * t + overshoot) + 1
end

function easeBackInOut( t )
    overshoot = 1.70158 * 1.525
    t = t * 2
    if t < 1 then
        return (t * t * ((overshoot + 1) * t - overshoot)) / 2
    else
        t = t - 2
        return (t * t * ((overshoot + 1) * t + overshoot)) / 2 + 1
    end
end

function easeSineIn( t )
    return -1 * math.cos(t * math.pi / 2) + 1
end

function easeSineOut( t )
    return math.sin(t * math.pi / 2)
end

function easeSineInOut( t )
    return -0.5 * (math.cos(math.pi * t) - 1)
end

-- a composition of two functions
function easeSineInOut2( t )
    t = easeSineIn (t)
    return easeSineOut (t)
end
