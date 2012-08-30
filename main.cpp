/****************************************************************************
 **
 ** Copyright (C) 2012 Dmitriy Sukharev.
 ** All rights reserved.
 ** Contact: Dmitriy Sukharev (ecuna@mail.ru)
 **
 ** This file is part of Pomodoro Timer.
 **
 ** Pomodoro Timer is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU Lesser General Public License as published
 ** by the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** Pomodoro Timer is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU Lesser General Public License for more details.
 **
 ** You should have received a copy of the GNU Lesser General Public License
 ** along with Pomodoro Timer.  If not, see <http://www.gnu.org/licenses/>.
 **
 ****************************************************************************/

#include <QtGui/QApplication>
#include <QMessageBox>
#include "mainwindowpresenter.h"
#include "mainwindow.h"
//#include "systemtraypresenter.h"
#include "systemtray.h"
#include <iostream>

//class SystemTrayPresenter;
class MainWindow;

int main(int argc, char *argv[])
{
    std::cout << 00 << '\n';
    QApplication a(argc, argv);
    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("Systray"), QObject::tr("I couldn't detect any system tray on this system."));
        return 1;
    }
    std::cout << 01 << '\n';
    QApplication::setQuitOnLastWindowClosed(false);
    std::cout << 0 << '\n';
    Pomodoro pomodoro;
    std::cout << 1 << '\n';
    MainWindowPresenter presenter(NULL, &pomodoro);
    std::cout << 2 << '\n';
    MainWindow w(NULL, &presenter);
    std::cout << 3 << '\n';
    //SystemTrayPresenter trayPresenter(NULL, &pomodoro);
    SystemTray tray(NULL, &presenter);
    //tray.initMainWindowPresenter(&presenter);

    tray.show();
    w.show();
    
    return a.exec();
}
