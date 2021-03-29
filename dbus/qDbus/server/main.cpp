#include "qdbus_server.h"
#include "QDebug"
#include <QCoreApplication>
#include <QDBusConnection>
#include <QDBusError>

const QString QDbusServerName = "com.deepin.qdbusserver";
const QString QDbusServerPath = "/com/deepin/qdbusserver";

int	main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    app.setOrganizationName("deepin");
    app.setApplicationName("dbus-server");

    QDBusConnection connection = QDBusConnection::systemBus();

    QDbusServer qdbus_server;
    QDbusServer adaptor(&qdbus_server);

    if (!connection.registerService(QDbusServerName))
    {
        qDebug() << connection.lastError().message();
        exit(1);
    }

    connection.registerObject(QDbusServerPath, &qdbus_server, QDBusConnection::ExportAllContents);

    return app.exec();

}
