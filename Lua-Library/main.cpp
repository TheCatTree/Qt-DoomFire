#include <iostream>
#include <lua.hpp>
using namespace std;

int main()
{
    lua_State* s = luaL_newstate();
    luaopen_base(s);
    lua_pcall(s, 0, 0, 0);


    lua_close(s);

    return 0;
}
