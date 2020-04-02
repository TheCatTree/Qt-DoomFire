#include "drawer.h"

Drawer::Drawer(LcdScreen *screen)
    :m_screen(screen)
{

}


void Drawer::linkScreen()
{
    fire = new Fire(m_screen);
}

Drawer::~Drawer()
{
    delete fire;
}

void Drawer::start(){
 qDebug() << "Draer Start.";
    if(m_screen_linked == false){
        linkScreen();
        m_screen_linked = true;
    }
    if(m_started == false){
        m_started = true;
    }
    fire->startStop();
}
