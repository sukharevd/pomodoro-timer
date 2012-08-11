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

#include "presenter.h"

Presenter::Presenter(QObject *parent) :
    QObject(parent)
{
    pomodoro = new Pomodoro(this);
    connect(pomodoro, SIGNAL(tick()), this, SLOT(updateTime()));
    connect(pomodoro, SIGNAL(timeout()), this, SLOT(timeOut()));
}

void Presenter::init(MainWindow* mainWindow)
{
    this->mainWindow = mainWindow;
}

void Presenter::updateTime()
{
    mainWindow->updateTime(pomodoro->getTimeLeft());
}

void Presenter::timeOut()
{
    mainWindow->showTimeOutMessage();
}

void Presenter::startShortBreak()
{
    mainWindow->setResumeState();
    mainWindow->setStartShortBreakIcon();
    pomodoro->startShortBreak();
}

void Presenter::startLongBreak()
{
    mainWindow->setResumeState();
    mainWindow->setStartLongBreakIcon();
    pomodoro->startLongBreak();
}

void Presenter::startPomodoro()
{
    mainWindow->setResumeState();
    mainWindow->setStartPomodoroIcon();
    pomodoro->startPomodoro();
}

void Presenter::handleTrayIconActivation(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger) {
        if (mainWindow->isHidden()) {
            mainWindow->show();
        } else {
            mainWindow->hide();
        }
    }
}

void Presenter::pause()
{
    pomodoro->pause();
    mainWindow->setPauseState();
}

void Presenter::resume()
{
    pomodoro->resume();
    mainWindow->setResumeState();
}
