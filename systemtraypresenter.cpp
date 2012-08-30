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

#include "systemtraypresenter.h"

SystemTrayPresenter::SystemTrayPresenter(QObject *parent, Pomodoro* pomodoro) :
    QObject(parent),
    pomodoro(pomodoro)
{
    connect(this->pomodoro, SIGNAL(timeout()), this, SLOT(timeOut()));
}

void SystemTrayPresenter::init(SystemTray* systemTray)
{
    this->systemTray = systemTray;
}

void SystemTrayPresenter::timeOut()
{
    systemTray->showTimeOutMessage();
}

void SystemTrayPresenter::startShortBreak()
{
    systemTray->setResumeState();
    systemTray->setStartShortBreakIcon();
    pomodoro->startShortBreak();
}

void SystemTrayPresenter::startLongBreak()
{
    systemTray->setResumeState();
    systemTray->setStartLongBreakIcon();
    pomodoro->startLongBreak();
}

void SystemTrayPresenter::startPomodoro()
{
    systemTray->setResumeState();
    systemTray->setStartPomodoroIcon();
    pomodoro->startPomodoro();
}

void SystemTrayPresenter::pause()
{
    pomodoro->pause();
    systemTray->setPauseState();
}

void SystemTrayPresenter::resume()
{
    pomodoro->resume();
    systemTray->setResumeState();
}

void SystemTrayPresenter::quit()
{
    exit(0);
}
