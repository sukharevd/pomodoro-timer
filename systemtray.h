#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

#include <QSystemTrayIcon>
#include "systemtraypresenter.h"

class SystemTrayPresenter;

class SystemTray : public QSystemTrayIcon
{
    Q_OBJECT
public:
    explicit SystemTray(QObject *parent = 0, SystemTrayPresenter* presenter = 0);
    
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
    SystemTrayPresenter* presenter;
    QAction* startPomodoroAction;
    QAction* startShortBreakAction;
    QAction* startLongBreakAction;
    QAction* pauseAction;
    QAction* resumeAction;
    QAction* quitAction;
    QIcon* lastIcon;
};

#endif // SYSTEMTRAY_H
