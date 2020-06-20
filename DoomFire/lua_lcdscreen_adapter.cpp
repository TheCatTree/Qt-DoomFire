#include "lua_lcdscreen_adapter.h"
#include <chrono>
#include <thread>

Lua_LcdScreen_Adapter::Lua_LcdScreen_Adapter(lua_State *L)
{
    qDebug() << "Adapter made";
    m_real_screen = (LcdScreen*)lua_touserdata(L,1);
}

Lua_LcdScreen_Adapter::~Lua_LcdScreen_Adapter(){
  qDebug() << "deleted Lua Object " << this;
}

void Lua_LcdScreen_Adapter::setObject(lua_State *L){
    m_real_screen = (LcdScreen*)lua_touserdata(L,1);
}

int Lua_LcdScreen_Adapter::writeBuffer(lua_State *L){
    //qDebug() << "lua writeBuffer";
    int x = (int)luaL_checknumber(L,1);
    int y = (int)luaL_checknumber(L,2);
    int r = (int)luaL_checknumber(L,3);
    int g = (int)luaL_checknumber(L,4);
    int b = (int)luaL_checknumber(L,5);
    lua_pop(L,5);

   m_real_screen->writeBuffer(x,y,r,g,b);

   return 0;
}

int Lua_LcdScreen_Adapter::writeBufferLine(lua_State *L){
    //qDebug() << "lua writeBufferLine";
    int x = (int)luaL_checknumber(L,1);
    int y = (int)luaL_checknumber(L,2);
    int pixels = (int)luaL_checknumber(L,3);
    luaL_checktype(L, 4, LUA_TTABLE);
    int a_size = lua_rawlen(L,4);
    //qDebug() << a_size;
    //make buffer
    int *buf = new int[a_size];
    for(int i = 1; i <= a_size; i++){
        lua_pushinteger(L,i);
        lua_gettable(L,4);
        int b = lua_tointeger(L,-1);
        buf[i-1] = b;
        lua_pop(L,1);
    }
    lua_pop(L,4);
     m_real_screen->writeBufferLine(x,y,buf,pixels);

    delete[] buf;
   return 0;
}

int Lua_LcdScreen_Adapter::writeBufferLineSetPixel(lua_State *L){
    //qDebug() << "lua writeBufferLine";
    int x = (int)luaL_checknumber(L,1);
    int y = (int)luaL_checknumber(L,2);
    int pixels = (int)luaL_checknumber(L,3);
    luaL_checktype(L, 4, LUA_TTABLE);
    int a_size = lua_rawlen(L,4);
    //qDebug() << a_size;
    //make buffer
    int *buf = new int[a_size];
    for(int i = 1; i <= a_size; i++){
        lua_pushinteger(L,i);
        lua_gettable(L,4);
        int b = lua_tointeger(L,-1);
        buf[i-1] = b;
        lua_pop(L,1);
    }
    lua_pop(L,4);
    int o = 0;
    for(int i = 0;i<pixels;i++){
        m_real_screen->writeBuffer(i,y,buf[o],buf[o+1],buf[o+2]);
        o+=3;
    }
   //m_real_screen->writeBufferLine(x,y,buf,pixels);
    delete[] buf;
   return 0;
}

int Lua_LcdScreen_Adapter::writeBufferScreenSetPixel(lua_State *L){
    //qDebug() << "lua writeBufferScreen";
    int width = (int)luaL_checknumber(L,1);
    int height = (int)luaL_checknumber(L,2);
    luaL_checktype(L, 3, LUA_TTABLE);
    int a_size = lua_rawlen(L,3);
    //qDebug() << a_size;
    //make buffer
    int *buf = new int[a_size];
    for(int i = 1; i <= a_size; i++){
        lua_pushinteger(L,i);
        lua_gettable(L,3);
        int b = lua_tointeger(L,-1);
        buf[i-1] = b;
        lua_pop(L,1);
    }
    lua_pop(L,3);
    //qDebug() << "bufferMade";
    long long o = 0;
    for(int y = height - 1;y>=0;y--){
        for(int x = width -1;x >= 0;x--){
            //qDebug() << x << ' ' << y;
            m_real_screen->writeBuffer(x,y,buf[o],buf[o+1],buf[o+2]);
            o+=3;
        }
    }
    //qDebug() << "Screen buffer written";
   //m_real_screen->writeBufferLine(x,y,buf,pixels);
    delete[] buf;
   return 0;
}

int Lua_LcdScreen_Adapter::getHeight(lua_State *L){
    qDebug() << "lua getHeight";
    auto temp = m_real_screen->getHeight();
    qDebug() << temp;
    lua_pushnumber(L, temp);
    return 1;
}

int Lua_LcdScreen_Adapter::getWidth(lua_State *L){
    qDebug() << "lua getWidth";
    auto temp = m_real_screen->getWidth();
    qDebug() << temp;
    lua_pushnumber(L, temp);
    return 1;
}

int Lua_LcdScreen_Adapter::toQdebug(lua_State *L){
    qDebug() << lua_tostring(L, 1);
    return 1;
}

int Lua_LcdScreen_Adapter::sleepMs(lua_State *L){
    using namespace std::this_thread;     // sleep_for, sleep_until
    using namespace std::chrono;
    using std::chrono::system_clock;
    int x = (int)luaL_checknumber(L,1);
    lua_pop(L,1);
    sleep_for(milliseconds(x));
    return 1;
}

int Lua_LcdScreen_Adapter::refresh(lua_State *L){
    m_real_screen->refresh();
    return 1;
}
