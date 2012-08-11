#include "qtimelabel.h"

QTimeLabel::QTimeLabel(QWidget *parent) :
    QLabel(parent)
{
    font = new QFont("Courier New");
    font->setItalic(true);
    //setStyleSheet("background-color: #222; color: white");
}

QTimeLabel::~QTimeLabel()
{
    delete(font);
}

QString formatTime1(int seconds)
{
    return QString("%1:%2").arg(seconds / 60, 2, 10, QChar('0')).arg(seconds % 60, 2, 10, QChar('0'));
}

void QTimeLabel::setTime(int time)
{
    font->setPixelSize(48);
    setFont(*font);
    QLabel::setText(formatTime1(time));
}

void QTimeLabel::setText(const QString& text)
{
    font->setPixelSize(24);
    setFont(*font);
    QLabel::setText(text);
}
