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

MainWindow::MainWindow(QWidget *parent, MainWindowPresenter* presenter) :
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

    setStyleSheet("background-color: #222; color: white");
    setWindowTitle("Pomodoro Timer");
    setWindowIcon(QIcon(":/images/tomato.png"));
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
