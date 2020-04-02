#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    drawer = new Drawer(ui->screen);
    qDebug() << "drawer created";
    connect(ui->startButton, &QPushButton::clicked,
            drawer, &Drawer::start);
    qDebug() << "connection made";

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateFrame()
{
    qDebug() << "updating frame";
}

