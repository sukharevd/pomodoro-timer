#ifndef QTIMELABEL_H
#define QTIMELABEL_H

#include <QLabel>

class QTimeLabel : public QLabel
{
    Q_OBJECT

public:
    QTimeLabel(QWidget* parent = 0);
    ~QTimeLabel();

    void setTime(int time);
    void setText(const QString &);

private:
    QFont* font;
};

#endif // QTIMELABEL_H
