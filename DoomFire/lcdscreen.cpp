#include "lcdscreen.h"
#include <iostream>
LcdScreen::LcdScreen(QWidget *parent, QColor background_colour)
    : QWidget(parent), m_background_colour(background_colour)
{

    m_height = 10;
    m_width = 10;
    m_screen_buffer =  QImage(m_width, m_height, QImage::Format_RGB32);
    qDebug() << "background_colour: " << m_background_colour.name();
    m_screen_refresher = new QTimer(this);
    connect(m_screen_refresher, &QTimer::timeout,
            this, &LcdScreen::refresh);
    m_screen_refresher->start(2);

}

void LcdScreen::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.drawImage(QPoint(0,0),m_screen_buffer);
}


void LcdScreen::writeBuffer(int x, int y, int r, int g, int b){
    //qDebug() << "screen writeBuffer";
    QRgb colour = qRgb(r,g,b);
    writeBuffer(x,y, colour);
}

void LcdScreen::writeBuffer(int x, int y, QRgb colour){
    m_screen_buffer.setPixel(x,y,colour);
}

void LcdScreen::writeBufferLine(int lwidth, int y, int *values, int pcount){
     QRgb *line = reinterpret_cast<QRgb*>(m_screen_buffer.scanLine(y));
    QRgb colour;
    //qDebug() << lwidth;
    int x = 0;
    for(int i = 0; i< lwidth;i++){
        if(pcount <= i){
            colour = qRgb(255,255,255);

        }else{
            x = x + 3;
            colour = qRgb(values[x],values[x + 1], values[x + 2]);


        }
        if((i==0 || i== 100)&& *line != colour){
            qDebug() << "pixil" << i;
            qDebug() << "colour";
            qDebug() <<std::hex << colour;
            qDebug() << "line before";
            qDebug() <<std::hex << *line;
            *line = colour;
            qDebug() << "line after";
            qDebug() <<std::hex << *line;
            ++line;
        }else{
        *line = colour;
        ++line;
        }
    }

}
void LcdScreen::blankScreen(){
    qDebug() << "blanking screen";
    for( int x = 0;  x < m_width; x++){
        for (int y = 0; y < m_height; y++) {
            m_screen_buffer.setPixel(x,y,m_background_colour.rgb());
        }
    }
}

int LcdScreen::lua_blankScreen(lua_State *luaState ){
    qDebug() << "Lua blank screen.";
    blankScreen();
    return 0;
}

int LcdScreen::lua_changeBackground(lua_State * luaState){
    qDebug() << "Lua randomBackground.";
    randomBackground();
    return 0;
}
void LcdScreen::showEvent(QShowEvent *event){
    m_height = this->height();
    m_width = this->width();
    try {
        m_height >= 0;
        m_width >= 0;
    } catch (...) {
        qDebug() << "screen width and hight can not be negative values." << '\n'
                 << "hight = " << m_height << " width = " << m_width << '.';
    }
    qDebug() << "width:" << m_width << " hight:" << m_height;
    m_screen_buffer =  QImage(m_width, m_height, QImage::Format_RGB16);
    blankScreen();
}

void LcdScreen::randomBackground()
{
    qDebug() << "randomBackground";
    QColor oldbackground = m_background_colour;
    while (oldbackground == m_background_colour) {
        int background = rand() % 3;
        switch (background){
         case 0:
            m_background_colour = QColorConstants::DarkMagenta;
            break;
        case 1:
            m_background_colour = QColorConstants::DarkBlue;
            break;
        case 2:
            m_background_colour = QColorConstants::Black;
            break;
        }
    }


    blankScreen();
}

void LcdScreen::refresh(){
    repaint();
}
