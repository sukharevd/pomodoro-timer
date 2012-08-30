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

#include "mainwindowpresenter.h"
#include <iostream>

MainWindowPresenter::MainWindowPresenter(QObject *parent, Pomodoro* pomodoro) :
    QObject(parent)
{
    this->pomodoro = pomodoro;
    connect(this->pomodoro, SIGNAL(tick()), this, SLOT(updateTime()));
    connect(this->pomodoro, SIGNAL(timeout()), this, SLOT(timeOut()));
}

void MainWindowPresenter::init(MainWindow* mainWindow)
{
    this->mainWindow = mainWindow;
}

void MainWindowPresenter::updateTime()
{
    mainWindow->updateTime(pomodoro->getTimeLeft());
}

void MainWindowPresenter::timeOut()
{
    mainWindow->showTimeOutMessage();
}

void MainWindowPresenter::handleTrayIconActivation(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger) {
        if (mainWindow->isHidden()) {
            mainWindow->show();
        } else {
            mainWindow->hide();
        }
    }
}
