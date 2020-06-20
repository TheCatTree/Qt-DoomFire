#ifndef DRAWER_H
#define DRAWER_H
#include <stdint.h>
#include "fire.h"
#include <QDebug>
#include "scripts.h"

class Drawer : public QObject
{
    Q_OBJECT
public:
    Drawer(LcdScreen* screen, lua_State *L);
    ~Drawer();
        lua_State *m_lua_state;
public slots:
    void start();
    void reciveText(QString plain_text);

signals:
    void requestText();

private:
    void linkScreen();
    void linkScript();
    void run();
    void runScript();
private:
    LcdScreen* m_screen;
    Fire* fire;
    bool m_screen_linked = false;
    bool m_started = false;
    std::string m_lua_script = "";


};

#endif // DRAWER_H
