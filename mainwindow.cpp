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
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent, MainWindowPresenter* apresenter) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    presenter(apresenter)
{
    presenter->initWindow(this);

    setFixedSize(400, 250);
    timeLine = new QTimeLabel(this);
    timeLine->setText("Start pomodoro");
    timeLine->setFixedSize(this->size());
    timeLine->setAlignment(Qt::AlignCenter);

    setStyleSheet("background-color: #222; color: white");
    setWindowTitle("Pomodoro Timer");
    setWindowIcon(QIcon(":/images/tomato.png"));
    new QShortcut(Qt::Key_P, this, SLOT(startPomodoro()));
    new QShortcut(Qt::Key_S, this, SLOT(startLongBreak()));
    new QShortcut(Qt::Key_L, this, SLOT(startShortBreak()));
    new QShortcut(Qt::Key_Space, this, SLOT(pause()));
    new QShortcut(Qt::Key_Q, this, SLOT(quit()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete presenter;
}

void MainWindow::updateTime(time_t time)
{
    timeLine->setTime(time);
}

void MainWindow::showTimeOutMessage()
{
    timeLine->setText("Time out");
    show();
}

void MainWindow::startPomodoro() {
    presenter->startPomodoro();
}

void MainWindow::startShortBreak() {
    presenter->startShortBreak();
}

void MainWindow::startLongBreak() {
    presenter->startLongBreak();
}

void MainWindow::pause() {
    presenter->pause();
}

void MainWindow::resume() {
    presenter->resume();
}

void MainWindow::quit() {
    presenter->quit();
}
