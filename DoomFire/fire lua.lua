    hm = {
        0x07,0x07,0x07,
        0x1F,0x07,0x07,
        0x2F,0x0F,0x07,
        0x47,0x0F,0x07,
        0x57,0x17,0x07,
        0x67,0x1F,0x07,
        0x77,0x1F,0x07,
        0x8F,0x27,0x07,
        0x9F,0x2F,0x07,
        0xAF,0x3F,0x07,
        0xBF,0x47,0x07,
        0xC7,0x47,0x07,
        0xDF,0x4F,0x07,
        0xDF,0x57,0x07,
        0xDF,0x57,0x07,
        0xD7,0x5F,0x07,
        0xD7,0x5F,0x07,
        0xD7,0x67,0x0F,
        0xCF,0x6F,0x0F,
        0xCF,0x77,0x0F,
        0xCF,0x7F,0x0F,
        0xCF,0x87,0x17,
        0xC7,0x87,0x17,
        0xC7,0x8F,0x17,
        0xC7,0x97,0x1F,
        0xBF,0x9F,0x1F,
        0xBF,0x9F,0x1F,
        0xBF,0xA7,0x27,
        0xBF,0xA7,0x27,
        0xBF,0xAF,0x2F,
        0xB7,0xAF,0x2F,
        0xB7,0xB7,0x2F,
        0xB7,0xB7,0x37,
        0xCF,0xCF,0x6F,
        0xDF,0xDF,0x9F,
        0xEF,0xEF,0xC7,
        0xFF,0xFF,0xFF
    }

screen = Lua_LcdScreen_Adapter(LcdScreen)
screenHeight = screen:getHeight()
screen:toQdebug(screenHeight)
screenWidth = screen:getWidth()
screen:toQdebug(screenWidth)
math.randomseed( os.time() )
math.random(); math.random(); math.random()
firevalues = {}
for i = 1, (screenHeight*screenWidth), 1 do
	firevalues[i] = 0;
end 
for i = screenHeight, (screenHeight - (screenHeight*0.1)), -1 do
    for j = 1, screenWidth,1 do
        firevalues[(i*screenWidth)+j] = 36;
    end
end					

function spreadFire(src)
	dst = src - screenWidth + (math.random(0,6)-3)
	if dst < 0 then
		dst = 0
	end
	if dst > (screenHeight*screenWidth) then
		dst = (screenHeight*screenWidth)
	end
	if firevalues[src] > 0 then
		firevalues[dst] = firevalues[src] - (math.random(100)/100);
		if firevalues[dst]< 0 then
			firevalues[dst] = 0
		end
	end

end

function drawFire()
	for y=screenHeight,1,-1 do
		for x=1, screenWidth, 1 do
			spreadFire((y * screenWidth)+x)
		end
	end

	value = 0
	screenvalues = {}
	index = 1;
	for y=screenHeight,1,-1 do
		for x=1, screenWidth, 1 do
			val = math.floor(firevalues[(y * screenWidth) + x ]) * 3
			val = val+1
			screenvalues[index] = hm[val]
			screenvalues[index + 1] = hm[val + 1]
			screenvalues[index + 2] = hm[val + 2]
			index = index + 3
		end				
	end
	screen:writeBufferScreenSetPixel(screenWidth,screenHeight,screenvalues)

end

for i = 0, (10*5), 1 do
	drawFire()
	screen:refresh()
	screen:sleepMs(1)
end 