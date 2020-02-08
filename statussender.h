#ifndef STATUSSENDER_H
#define STATUSSENDER_H

#include <QObject>

class StatusSender : public QObject
{
    Q_OBJECT

signals:
    void newStatus(QString &);

public:
    void status(QString &);
    void status(QString);
};

class StatusSenderBearer
{
public:
    StatusSender *s;
    StatusSenderBearer();
    ~StatusSenderBearer();
};

#endif // STATUSSENDER_H
