#ifndef LCDSCREEN_H
#define LCDSCREEN_H

#include <QObject>
#include <QWidget>
#include <QVariant>
#include <QImage>
#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <QColor>
#include "luna.h"



class LcdScreen : public QWidget
{
    Q_OBJECT
public:
    LcdScreen(QWidget *parent = nullptr, QColor background_colour = QColorConstants::Black);


    void writeBuffer(int x, int y, QRgb colour);
    void writeBuffer(int x, int y, int r, int g, int b);
    void writeBufferLine(int lwidth, int y, int values[], int pcount);

    int getHeight(){int x = m_height;qDebug() << "screen getHeight: " << x/*m_height*/;return x;}
    int getWidth(){int x = m_width;qDebug() << "screen getWidth: " << x/*m_width*/;return x;}
    int lua_blankScreen(lua_State*);
    int lua_changeBackground(lua_State*);

private:
    void blankScreen();
    void paintEvent(QPaintEvent *event) override;
    void showEvent(QShowEvent *event) override;

public slots:
    void randomBackground();
    void refresh();

private:
    int m_height;
    int m_width;
    QColor m_background_colour;
    QImage m_screen_buffer;
    QTimer *m_screen_refresher;
};

typedef int (LcdScreen::*mem_fuc)(lua_State * L);
template <mem_fuc func>
int dispatch(lua_State * L){
    LcdScreen * ptr = *static_cast<LcdScreen**>(lua_getextraspace(L));
    return ((*ptr).*func)(L);
}
#endif // LCDSCREEN_H
