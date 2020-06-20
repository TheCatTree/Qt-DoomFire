#ifndef LUA_LCDSCREEN_ADAPTER_H
#define LUA_LCDSCREEN_ADAPTER_H

#include <lua.hpp>
#include <QDebug>

#include "lcdscreen.h"



class Lua_LcdScreen_Adapter
{
public:
    // constants
    static const char className[];
    static Luna<Lua_LcdScreen_Adapter>::RegType methods[];
    // Initialize the pointer
    Lua_LcdScreen_Adapter(lua_State *L);
    ~Lua_LcdScreen_Adapter();
    void setObject(lua_State *L);

    // Method Schims
    int writeBuffer(lua_State *L);
    int writeBufferLine(lua_State *L);
    int writeBufferLineSetPixel(lua_State *L);
    int writeBufferScreenSetPixel(lua_State *L);
    int getHeight(lua_State *L);
    int getWidth(lua_State *L);
    int toQdebug(lua_State *L);
    int sleepMs(lua_State *L);
    int refresh(lua_State *L);

private:
    LcdScreen* m_real_screen;
};


#endif // LUA_LCDSCREEN_ADAPTER_H
