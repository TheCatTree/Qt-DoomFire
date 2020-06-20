screen = Lua_LcdScreen_Adapter(LcdScreen)
                                           screenHeight = screen:getHeight()
                                           screen:toQdebug(screenHeight)
                                           screenWidth = screen:getWidth()
                                           screen:toQdebug(screenWidth)
										   for x=1,10,1 do
											   math.randomseed( os.time() )
											   math.random(); math.random(); math.random()
											   r = math.random(0,255)
											   g = math.random(0,255)
											   b = math.random(0,255)
											   for y=0,screenHeight - 1,1 do
											   linevalues={}
											   index = 1
												for x=0,screenWidth -1,1 do
													linevalues[index] = r
													linevalues[index + 1] = g
													linevalues[index + 2] = b
													index = index + 3
												end
												screen:writeBufferLineSetPixel(screenWidth,y,screenWidth,linevalues)
											   end
											   screen:refresh()
											   screen:sleepMs(1000)
										   end