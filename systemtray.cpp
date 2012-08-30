#include "systemtray.h"

SystemTray::SystemTray(QObject *parent, SystemTrayPresenter *systemTrayPresenter) :
    QSystemTrayIcon(parent),
    presenter(systemTrayPresenter)
{
    presenter->init(this);
    createActions();
    createTrayIcon();
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), presenter, SLOT(handleTrayIconActivation(QSystemTrayIcon::ActivationReason)));
    QIcon icon = QIcon(":/images/tomato.png");
    setIcon(icon);
    setWindowIcon(icon);
}

void SystemTray::createActions()
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

void SystemTray::createTrayIcon()
{
    QMenu* trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(startPomodoroAction);
    trayIconMenu->addAction(startShortBreakAction);
    trayIconMenu->addAction(startLongBreakAction);
    trayIconMenu->addAction(pauseAction);
    trayIconMenu->addAction(resumeAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    setContextMenu(trayIconMenu);
    pauseAction->setVisible(false);
    resumeAction->setVisible(false);
}

void SystemTray::updateTime(time_t time)
{
    setTime(time);
}

void SystemTray::setStartShortBreakIcon()
{
    setIcon(QIcon(":/images/coffee_break.png"));
}

void SystemTray::setStartLongBreakIcon()
{
    setIcon(QIcon(":/images/hamburger.png"));
}

void SystemTray::setStartPomodoroIcon()
{
    setIcon(QIcon(":/images/tomato.png"));
}

void SystemTray::showTimeOutMessage()
{
    QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Information);
    setIcon(QIcon(":/images/alarm.png"));
    showMessage("Time out", "Time out", icon, 60 * 1000);
    pauseAction->setVisible(false);
}

void SystemTray::setPauseState()
{
    lastIcon = trayIcon->icon();
    pauseAction->setVisible(false);
    resumeAction->setVisible(true);
    setIcon(QIcon(":/images/pause.png"));
}

void SystemTray::setResumeState()
{
    pauseAction->setVisible(true);
    resumeAction->setVisible(false);
    setIcon(lastIcon);
}
