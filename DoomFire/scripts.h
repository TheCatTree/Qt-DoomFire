#ifndef SCRIPTS_H
#define SCRIPTS_H
#include <string>
static std::string RandomBackgorundScript =R"(screen = Lua_LcdScreen_Adapter(LcdScreen)
                                           screenHeight = screen:getHeight()
                                           screen:toQdebug(screenHeight)
                                           screenWidth = screen:getWidth()
                                           screen:toQdebug(screenWidth)
                                           math.randomseed( os.time() )
                                           math.random(); math.random(); math.random()
                                           r = math.random(0,255)
                                           g = math.random(0,255)
                                           b = math.random(0,255)
                                           for x=0,screenWidth - 1,1 do
                                            for y=0,screenHeight -1,1 do
                                                screen:writeBuffer(x,y,r,g,b)
                                            end
                                           end
                                           )";

#endif // SCRIPTS_H
