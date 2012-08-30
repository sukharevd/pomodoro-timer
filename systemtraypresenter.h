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

#ifndef PRESENTER_H
#define PRESENTER_H

#include <QObject>
#include <QSystemTrayIcon>
#include "pomodoro.h"
#include "systemtray.h"

class SystemTray;


class SystemTrayPresenter : public QObject
{
    Q_OBJECT
public:
    explicit SystemTrayPresenter(QObject *parent = 0, Pomodoro* pomodoro = 0);
    void init(SystemTray*);

signals:
    
public slots:
    void startPomodoro();
    void startShortBreak();
    void startLongBreak();
    void timeOut();
    //void updateTime();
    void pause();
    void resume();
    void handleTrayIconActivation(QSystemTrayIcon::ActivationReason);

private:
    SystemTray* systemTray;
    Pomodoro* pomodoro;
};

#endif // PRESENTER_H
