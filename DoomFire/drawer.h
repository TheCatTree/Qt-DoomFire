#ifndef DRAWER_H
#define DRAWER_H
#include <stdint.h>
#include "lcdscreen.h"
#include "fire.h"
#include <QDebug>

class Drawer : public QObject
{
    Q_OBJECT
public:
    Drawer(LcdScreen* screen);
    ~Drawer();

public slots:
    void start();

private:
    void linkScreen();
    void run();
private:
    LcdScreen* m_screen;
    Fire* fire;
    bool m_screen_linked = false;
    bool m_started = false;
};

#endif // DRAWER_H
