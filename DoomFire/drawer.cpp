#include "drawer.h"

Drawer::Drawer(LcdScreen *screen, lua_State *L)
    :m_screen(screen), m_lua_state(L)
{
 luaL_openlibs(m_lua_state);
 qDebug() << "Checking B:" << lua_checkstack(m_lua_state, 1);
 qDebug() << "State Address:" << m_lua_state;
 m_lua_script = RandomBackgorundScript;
 qDebug() << m_lua_script.c_str();
 Luna<Lua_LcdScreen_Adapter>::Register(m_lua_state);
 lua_pushlightuserdata(m_lua_state, (void*)m_screen);
 lua_setglobal(m_lua_state, "LcdScreen");
}


void Drawer::linkScreen()
{
    fire = new Fire(m_screen);
}

void Drawer::linkScript()
{
     qDebug() << "linking script";
    if(m_lua_state == NULL){
        m_lua_state = luaL_newstate();
        m_lua_script = RandomBackgorundScript;
        qDebug() << m_lua_script.c_str();
        luaopen_base(m_lua_state);
        //Luna<Lua_LcdScreen_Adapter>::Register(m_lua_state);
        //lua_pushlightuserdata(m_lua_state, (void*)&m_screen);
        //lua_setglobal(m_lua_state, "LcdScreen");
    }
}
void Drawer::runScript()
{
     qDebug() << "runing script";
    int error = 0;
    std::string line;
    line = "x = 5 return (x > 7)";
    if(m_lua_state == NULL){
        qDebug() << "m_lua_state = Null.";
    }
    else{
        qDebug() << "loading string";
        emit requestText();
        qDebug() << "State Address run context:" << m_lua_state;
        error = luaL_dostring(m_lua_state,m_lua_script.c_str());
        //error = luaL_dostring(m_lua_state,"x = 8");
        //error = luaL_loadbuffer(m_lua_state, line.c_str(), line.length(), "line") ||   lua_pcall(m_lua_state, 0, LUA_MULTRET, 0);

        //int b =  lua_checkstack(m_lua_state, 1);
        qDebug() << "finished script";
        if(error){
        qDebug() << lua_tostring(m_lua_state, -1);
        lua_pop(m_lua_state, 1);  /* pop error message from the stack */
        }
    }
}
Drawer::~Drawer()
{
    delete fire;
    if(m_lua_state != NULL){
        //lua_close(m_lua_state);
    }
}

void Drawer::start(){
 qDebug() << "Drawer Start.";
    //if(m_screen_linked == false){
        //linkScreen();
        //linkScript();
        //m_screen_linked = true;
    //}
    //if(m_started == false){
        //m_started = true;
    //}
    //fire->startStop();
    //Run Script
    runScript();
}

void Drawer::reciveText(QString plain_text)
{
    m_lua_script = plain_text.toStdString();
    qDebug() << "New Zcript from Text box:" << '\n' << m_lua_script.c_str();
}
