#include "lcdscreen.h"
#include <QDebug>
LcdScreen::LcdScreen(QWidget *parent, QColor background_colour)
    : QWidget(parent), m_background_colour(background_colour)
{

    m_height = 10;
    m_width = 10;
    m_screen_buffer =  QImage(m_width, m_height, QImage::Format_RGB16);
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
    QRgb colour = qRgb(r,g,b);
    writeBuffer(x,y, colour);
}

void LcdScreen::writeBuffer(int x, int y, QRgb colour){
    m_screen_buffer.setPixel(x,y,colour);
}

void LcdScreen::blankScreen(){
    qDebug() << "blanking screen";
    for( int x = 0;  x < m_width; x++){
        for (int y = 0; y < m_height; y++) {
            m_screen_buffer.setPixel(x,y,m_background_colour.rgb());
        }
    }
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
