/***********************************************************
 Copyright (C) 2013 AndreBotelho(andrebotelhomail@gmail.com)
 
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
See the GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the
 Free Software Foundation, Inc.,
 51 Franklin Street, Fifth Floor, Boston, MA 02111-1307 USA.
 ***********************************************************/
 
#include <QtGui/QApplication>
#include <QDebug>
#include <QSystemScreenSaver>
QTM_USE_NAMESPACE
#include "mainwindow.h"
#include <QDebug>
#include <QDeclarativeView>
#include <QDeclarativeContext>
#include <QDEclarativeEngine>
MainWindow* emuWindow;
QDeclarativeView *menuView;
QGraphicsObject *rootObj;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    emuWindow = new MainWindow;
    emuWindow->setAttribute(Qt::WA_LockLandscapeOrientation);
    menuView = new QDeclarativeView(emuWindow);
    menuView->setAttribute(Qt::WA_LockLandscapeOrientation);
    menuView->engine()->addImageProvider("saves", (QDeclarativeImageProvider*)emuWindow);
    menuView->rootContext()->setContextProperty("emu", emuWindow);
    menuView->setSource(QUrl("qrc:/app/data/emuui.qml"));
    if( menuView->status() != 1)
        qDebug()<< menuView->errors();
    rootObj = menuView->rootObject();
    emuWindow->init();
    emuWindow->showFullScreen();
    emuWindow->loadConfig();
    QSystemScreenSaver *sss=new QSystemScreenSaver(emuWindow);
    sss->setScreenSaverInhibit();

    return a.exec();
}
