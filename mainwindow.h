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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qtimelabel.h"
#include <QSystemTrayIcon>
#include <QTimer>
#include <time.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void createActions();
    void createTrayIcon();
    void showMessage();
    void pause();

    time_t time_left;
    QTimer* timer;

    Ui::MainWindow *ui;

    QAction* startPomodoroAction;
    QAction* startCoffeeBreakAction;
    QAction* startLongBreakAction;
//    QAction *minimizeAction;
//    QAction *maximizeAction;
//    QAction *restoreAction;
    QAction *quitAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    QTimeLabel* timeLine;

private slots:
    void timer_ticked();
    void start_pomodoro();
    void start_coffee_break();
    void start_long_break();
    void wake_up(QSystemTrayIcon::ActivationReason);
};

#endif // MAINWINDOW_H
