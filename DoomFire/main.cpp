#include "mainwindow.h"

#include <lua.hpp>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iostream>
#include <QApplication>

const char Lua_LcdScreen_Adapter::className[] = "Lua_LcdScreen_Adapter";

// Define the methods we will expose to Lua
#define method(class, name) {#name, &class::name}
Luna<Lua_LcdScreen_Adapter>::RegType Lua_LcdScreen_Adapter::methods[] = {
   method(Lua_LcdScreen_Adapter, getWidth),
   method(Lua_LcdScreen_Adapter, getHeight),
   method(Lua_LcdScreen_Adapter, writeBuffer),
   method(Lua_LcdScreen_Adapter, writeBufferLine),
   method(Lua_LcdScreen_Adapter, writeBufferLineSetPixel),
   method(Lua_LcdScreen_Adapter, writeBufferScreenSetPixel),
   method(Lua_LcdScreen_Adapter, toQdebug),
   method(Lua_LcdScreen_Adapter, sleepMs),
   method(Lua_LcdScreen_Adapter, refresh),
   {0,0}
};


int main(int argc, char *argv[])
{
    std::istringstream f("x = 5 return (x > 7)");
    std::string line;
    char buff[256];
    int error;
    lua_State *L = luaL_newstate(); //Set up the state
    luaL_openlibs(L); //call all the libraries
    while (std::getline(f, line)){
        error = luaL_loadbuffer(L, line.c_str(), line.length(), "line") || // load buffer as chunk returns 0 if no error;
                lua_pcall(L, 0, LUA_MULTRET, 0); // pop chunck off stack and run in protected mode.(anki this pattern)
        if (error){
            fprintf(stderr, "%s", lua_tostring(L, -1)); // return value from top of the stack as string
            lua_pop(L,1); /* pop error message from the stack */
        }
    }
    int iret = (int) lua_toboolean(L, -1);
    if(iret == 1){std::cout << "Door opened!" << std::endl;}
    else{std::cout << "Door closed!" << std::endl;}
    lua_close(L);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    int qt_return = a.exec();
    return qt_return;
}
