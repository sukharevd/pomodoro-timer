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
    pomodoro = new Pomodoro(this);
    connect(pomodoro, SIGNAL(tick()), this, SLOT(updateTime()));
    connect(pomodoro, SIGNAL(timeout()), this, SLOT(showTimeOut()));

    setFixedSize(400, 250);
    timeLine = new QTimeLabel(this);
    timeLine->setText("Start pomodoro");
    timeLine->setFixedSize(this->size());
    timeLine->setAlignment(Qt::AlignCenter);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(timeLine);
    setStyleSheet("background-color: #222; color: white");

    //setLayout(mainLayout);

    createActions();
    createTrayIcon();
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(handleTrayIconActivation(QSystemTrayIcon::ActivationReason)));
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
    connect(startPomodoroAction, SIGNAL(triggered()), this, SLOT(startPomodoro()));

    startCoffeeBreakAction = new QAction(QIcon(":/images/coffee_break.png"), tr("Start coffee &break"), this);
    connect(startCoffeeBreakAction, SIGNAL(triggered()), this, SLOT(startShortBreak()));

    startLongBreakAction = new QAction(QIcon(":/images/hamburger.png"), tr("Start &long break"), this);
    connect(startLongBreakAction, SIGNAL(triggered()), this, SLOT(startLongBreak()));

    pauseAction = new QAction(QIcon(":/images/pause.png"), tr("Pause"), this);
    connect(pauseAction, SIGNAL(triggered()), this, SLOT(pause()));

    resumeAction = new QAction(QIcon(":/images/pause.png"), tr("Resume"), this);
    connect(resumeAction, SIGNAL(triggered()), this, SLOT(resume()));

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
 }

void MainWindow::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(startPomodoroAction);
    trayIconMenu->addAction(startCoffeeBreakAction);
    trayIconMenu->addAction(startLongBreakAction);
    trayIconMenu->addAction(pauseAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
}

void MainWindow::updateTime()
{
    timeLine->setTime(pomodoro->getTimeLeft());
}

void MainWindow::startShortBreak()
{
    trayIcon->setIcon(QIcon(":/images/coffee_break.png"));
    pomodoro->startShortBreak();
}

void MainWindow::startLongBreak()
{
    trayIcon->setIcon(QIcon(":/images/hamburger.png"));
    pomodoro->startLongBreak();
}

void MainWindow::startPomodoro()
{
    trayIcon->setIcon(QIcon(":/images/tomato.png"));
    pomodoro->startPomodoro();
}

void MainWindow::handleTrayIconActivation(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger) {
        if (isHidden()) {
            show();
        } else {
            hide();
        }
    }
}

void MainWindow::showTimeOut()
{
    QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Information);
    trayIcon->setIcon(QIcon(":/images/alarm.png"));
    trayIcon->showMessage("Time out", "Time out", icon, 60 * 1000);
    timeLine->setText("Time out");
    show();
}

void MainWindow::pause()
{
    pomodoro->pause();
    lastIcon = trayIcon->icon();
    trayIconMenu->insertAction(pauseAction, resumeAction);
    trayIconMenu->removeAction(pauseAction);
    trayIcon->setIcon(QIcon(":/images/pause.png"));
}

void MainWindow::resume()
{
    pomodoro->resume();
    trayIconMenu->insertAction(resumeAction, pauseAction);
    trayIconMenu->removeAction(resumeAction);
    trayIcon->setIcon(lastIcon);
}
