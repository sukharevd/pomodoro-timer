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

#include "pomodoro.h"

Pomodoro::Pomodoro(QObject *parent) :
    QObject(parent)
{
    time_left = 0;
    timer = new QTimer();
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(timer_ticked()));
}

Pomodoro::~Pomodoro()
{
    delete timer;
}

void Pomodoro::startPomodoro()
{
    timer->stop();
    time_left = 25 * 60;
    timer->start();
}

void Pomodoro::startShortBreak()
{
    timer->stop();
    time_left = 5 * 60;
    timer->start();
}

void Pomodoro::startLongBreak()
{
    timer->stop();
    time_left = 30 * 60;
    timer->start();
}

void Pomodoro::pause()
{
    timer->stop();
}

void Pomodoro::resume()
{
    timer->start();
}

void Pomodoro::timer_ticked()
{
    time_left--;
    emit tick();
    if (!time_left) {
        timer->stop();
        emit timeout();
    }
}

time_t Pomodoro::getTimeLeft()
{
    return time_left;
}

bool Pomodoro::isActive()
{
    return timer->isActive();
}
