#ifndef LCDSCREEN_H
#define LCDSCREEN_H

#include <QObject>
#include <QWidget>
#include <QVariant>
#include <QImage>
#include <QPainter>
#include <QTimer>

class LcdScreen : public QWidget
{
    Q_OBJECT
public:
    LcdScreen(QWidget *parent = nullptr, QColor background_colour = QColorConstants::DarkMagenta);


    void writeBuffer(int x, int y, QRgb colour);
    void writeBuffer(int x, int y, int r, int g, int b);

    int getHeight(){return m_height;};
    int getWidth(){return m_width;};

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

#endif // LCDSCREEN_H
