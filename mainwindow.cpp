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

MainWindow::MainWindow(QWidget *parent, Presenter* presenter) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    presenter(presenter)
{
    presenter->init(this);

    setFixedSize(400, 250);
    timeLine = new QTimeLabel(this);
    timeLine->setText("Start pomodoro");
    timeLine->setFixedSize(this->size());
    timeLine->setAlignment(Qt::AlignCenter);

    //QVBoxLayout *mainLayout = new QVBoxLayout;
    //mainLayout->addWidget(timeLine);
    setStyleSheet("background-color: #222; color: white");
    //setLayout(mainLayout);

    setWindowTitle("Pomodoro Timer");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete presenter;
}

void MainWindow::createActions()
 {
    startPomodoroAction = new QAction(QIcon(":/images/tomato.png"), tr("Start &pomodoro"), this);
    startShortBreakAction = new QAction(QIcon(":/images/coffee_break.png"), tr("Start coffee &break"), this);
    startLongBreakAction = new QAction(QIcon(":/images/hamburger.png"), tr("Start &long break"), this);
    pauseAction = new QAction(QIcon(":/images/pause.png"), tr("Pause"), this);
    resumeAction = new QAction(QIcon(":/images/pause.png"), tr("Resume"), this);
    quitAction = new QAction(tr("&Quit"), this);
    connect(startPomodoroAction, SIGNAL(triggered()), presenter, SLOT(startPomodoro()));
    connect(startShortBreakAction, SIGNAL(triggered()), presenter, SLOT(startShortBreak()));
    connect(startLongBreakAction, SIGNAL(triggered()), presenter, SLOT(startLongBreak()));
    connect(pauseAction, SIGNAL(triggered()), presenter, SLOT(pause()));
    connect(resumeAction, SIGNAL(triggered()), presenter, SLOT(resume()));
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
 }

void MainWindow::createTrayIcon()
{
    QMenu* trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(startPomodoroAction);
    trayIconMenu->addAction(startShortBreakAction);
    trayIconMenu->addAction(startLongBreakAction);
    trayIconMenu->addAction(pauseAction);
    trayIconMenu->addAction(resumeAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
    pauseAction->setVisible(false);
    resumeAction->setVisible(false);
}

void MainWindow::updateTime(time_t time)
{
    timeLine->setTime(time);
}

void MainWindow::setStartShortBreakIcon()
{
    trayIcon->setIcon(QIcon(":/images/coffee_break.png"));
}

void MainWindow::setStartLongBreakIcon()
{
    trayIcon->setIcon(QIcon(":/images/hamburger.png"));
}

void MainWindow::setStartPomodoroIcon()
{
    trayIcon->setIcon(QIcon(":/images/tomato.png"));
}

void MainWindow::showTimeOutMessage()
{
    QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Information);
    trayIcon->showMessage("Time out", "Time out", icon, 60 * 1000);
    trayIcon->setIcon(QIcon(":/images/alarm.png"));
    timeLine->setText("Time out");
    pauseAction->setVisible(false);
    show();
}

void MainWindow::setPauseState()
{
    lastIcon = trayIcon->icon();
    pauseAction->setVisible(false);
    resumeAction->setVisible(true);
    trayIcon->setIcon(QIcon(":/images/pause.png"));
}

void MainWindow::setResumeState()
{
    pauseAction->setVisible(true);
    resumeAction->setVisible(false);
    trayIcon->setIcon(lastIcon);
}
