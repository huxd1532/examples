#ifndef QDBUS_SERVER_H_
#define QDBUS_SERVER_H_

#include <QObject>

class QDbusServer : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.deepin.daemon.DbusServer")

public:
    explicit QDbusServer(QObject* parent = nullptr);

    ~QDbusServer();

public slots:
    QString GetDevice();

};

#endif
