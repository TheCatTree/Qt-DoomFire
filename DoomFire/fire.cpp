#include "fire.h"

Fire::Fire(LcdScreen* screen)
    : m_screen(screen)
{
    m_fire_width =screen->getWidth();
    m_fire_height = screen->getHeight();
    m_screen_refresher = new QTimer(this);
    connect(m_screen_refresher, &QTimer::timeout,
            this, &Fire::drawFire);

}

void Fire::initializeFire(){
    size_firevalues = m_fire_width * m_fire_height;
    firevalues = new float[size_firevalues];
    for(int i = 0; i < size_firevalues; i++ ){
        firevalues[i] = 0;
    }
    for(int y = m_fire_height - 1; y >= m_fire_height - (int)(m_fire_height * 0.1); y --){
        for(int x = 0; x < m_fire_width; x++){
            firevalues[(y * m_fire_width) + x ] = 36;
        }
    }
}

void Fire::startStop()
{
    qDebug() << "Started";
    if(m_Started == false){
        qDebug() << "Started";
        initializeFire();
        m_Started = true;
        m_screen_refresher->start(33);
    }
    else{
        qDebug() << "Stoped";
        m_screen_refresher->stop();
        m_Started = false;
        delete firevalues;
        //Stop thread
    }

}
void Fire::drawFire(){
    for(int y = m_fire_height - 1; y > 0; y --){
        for(int x = 0; x < m_fire_width; x++){
           spreadFire((y * m_fire_width) + x );

        }
    }

    updateBuffer();
}

void Fire::spreadFire(int src){
    int dst = src - m_fire_width + ((rand() & 7) -3);
    if(dst < 0){dst = 0;}
    if(dst > size_firevalues - 1){dst = size_firevalues - 1;}
    if(firevalues[src] > 0){
    firevalues[dst] = firevalues[src] - (static_cast <float> (rand()) / static_cast <float> (RAND_MAX/2));
     if(firevalues[dst] < 0){firevalues[dst] = 0;}
    }
}

void Fire::updateBuffer(){
    int value = 0;
    for(int y = m_fire_height - 1; y >= 0; y --){
        for(int x = 0; x < m_fire_width; x++){
           value = static_cast<int>(round(firevalues[(y * m_fire_width) + x ])) * 3;
           m_screen->writeBuffer(x , y , m_height_map[value], m_height_map[value + 1], m_height_map[value + 2]);
        }
    }
}
