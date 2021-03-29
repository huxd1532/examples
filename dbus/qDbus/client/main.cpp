#include "QDebug"
#include <QCoreApplication>
#include <QDBusConnection>
#include <QDBusError>
#include "qdbus_server_proxy.h"

const QString QDbusServerName = "com.deepin.qdbusserver";
const QString QDbusServerPath = "/com/deepin/qdbusserver";

ComDeepinDaemonDbusServerInterface *g_qdbusserver;

static void call_get_device()
{
    QDBusPendingReply<QString> reply = g_qdbusserver->GetDevice();
    reply.waitForFinished();
    if (reply.isValid()) {
        qDebug() << "reply: " << reply.value();
    }else{
        qDebug() << reply.error();
    }
}


int	main()
{

    g_qdbusserver = new ComDeepinDaemonDbusServerInterface(
                QDbusServerName,
                QDbusServerPath,
                QDBusConnection::systemBus());

    call_get_device();

    return 0;

}
