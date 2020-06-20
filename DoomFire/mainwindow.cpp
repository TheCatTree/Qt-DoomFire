#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    lua_State *luaStateGlobal = luaL_newstate(); //Set up the state
    drawer = new Drawer(ui->screen, luaStateGlobal);
    qDebug() << "drawer created";
    connect(ui->startButton, &QPushButton::clicked,
            drawer, &Drawer::start);
    connect(ui->luaTextInput, &LuaTextInput::theText,
            drawer, &Drawer::reciveText);
    connect(drawer, &Drawer::requestText,
            ui->luaTextInput, &LuaTextInput::sendText);
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

