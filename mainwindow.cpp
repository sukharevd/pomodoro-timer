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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
    time_left = 0;
    timer = new QTimer();
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(timer_ticked()));

    timeLine = new QLabel(this);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(timeLine);
    //setLayout(mainLayout);

    createActions();
    createTrayIcon();
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(wake_up(QSystemTrayIcon::ActivationReason)));
    QIcon icon = QIcon(":/images/tomato.png");
    trayIcon->setIcon(icon);
    trayIcon->show();
    setWindowIcon(icon);
    setWindowTitle("Pomodoro Timer");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createActions()
 {
    startPomodoroAction = new QAction(QIcon(":/images/tomato.png"), tr("Start &pomodoro"), this);
    connect(startPomodoroAction, SIGNAL(triggered()), this, SLOT(start_pomodoro()));

    startCoffeeBreakAction = new QAction(QIcon(":/images/coffee_break.png"), tr("Start coffee &break"), this);
    connect(startCoffeeBreakAction, SIGNAL(triggered()), this, SLOT(start_coffee_break()));

    startLongBreakAction = new QAction(QIcon(":/images/hamburger.png"), tr("Start &long break"), this);
    connect(startLongBreakAction, SIGNAL(triggered()), this, SLOT(start_long_break()));

//    minimizeAction = new QAction(tr("Mi&nimize"), this);
//    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

//    maximizeAction = new QAction(tr("Ma&ximize"), this);
//    connect(maximizeAction, SIGNAL(triggered()), this, SLOT(showMaximized()));

//    restoreAction = new QAction(tr("&Restore"), this);
//    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
 }

void MainWindow::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(startPomodoroAction);
    trayIconMenu->addAction(startCoffeeBreakAction);
    trayIconMenu->addAction(startLongBreakAction);
    trayIconMenu->addSeparator();
    //trayIconMenu->addAction(minimizeAction);
    //trayIconMenu->addAction(maximizeAction);
    //trayIconMenu->addAction(restoreAction);
    //trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
}

QString formatTime(int seconds) {
    return QString("%1:%2").arg(seconds / 60, 2, 10, QChar('0')).arg(seconds % 60, 2, 10, QChar('0'));
}

void MainWindow::timer_ticked()
{
    time_left--;
    QString timeString;
    timeString.append(QString("%1").arg(time_left));
    timeLine->setText(formatTime(time_left));
    if (!time_left) {
        timer->stop();
        time_left = 0;
        trayIcon->setIcon(QIcon(":/images/alarm.png"));
        showMessage();
    }
}

void MainWindow::start_coffee_break() {
    trayIcon->setIcon(QIcon(":/images/coffee_break.png"));
    timer->stop();
    time_left = 5 * 60;
    timer->start();
}

void MainWindow::start_long_break() {
    trayIcon->setIcon(QIcon(":/images/hamburger.png"));
    timer->stop();
    time_left = 30 * 60;
    timer->start();
}

void MainWindow::start_pomodoro() {
    trayIcon->setIcon(QIcon(":/images/tomato.png"));
    timer->stop();
    time_left = 25 * 60;
    timer->start();
}

void MainWindow::wake_up(QSystemTrayIcon::ActivationReason reason) {
    if (reason == QSystemTrayIcon::Trigger) {
        QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Information);
        trayIcon->showMessage("Time left information", formatTime(time_left), icon, 3 * 1000);
    } else if (reason == QSystemTrayIcon::DoubleClick) {
        pause();
    }
}

void MainWindow::showMessage()
{
    QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Information);
    trayIcon->showMessage("Time out", "Time out", icon, 60 * 1000);
}

void MainWindow::pause() {
    static QIcon lastIcon;
    if (timer->isActive()) {
        timer->stop();
        lastIcon = trayIcon->icon();
        trayIcon->setIcon(QIcon(":/images/pause.png"));
    } else if (time_left > 0){
        timer->start();
        trayIcon->setIcon(lastIcon);
    }
}
