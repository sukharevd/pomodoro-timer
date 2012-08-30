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

#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

#include <QSystemTrayIcon>
#include <QAction>
#include "mainwindowpresenter.h"
//#include "mainwindow.h"
class MainWindowPresenter;


class SystemTray : public QSystemTrayIcon
{
    Q_OBJECT
public:
    explicit SystemTray(QObject *parent = 0, MainWindowPresenter* presenter = 0);

    void createActions();
    void createTrayIcon();
    void setStartPomodoroIcon();
    void setStartShortBreakIcon();
    void setStartLongBreakIcon();
    void showTimeOutMessage();
    void setPauseState();
    void setResumeState();

signals:
    
public slots:
    
private:
    MainWindowPresenter* presenter;
    QAction* startPomodoroAction;
    QAction* startShortBreakAction;
    QAction* startLongBreakAction;
    QAction* pauseAction;
    QAction* resumeAction;
    QAction* quitAction;
    QIcon lastIcon;
};

#endif // SYSTEMTRAY_H
