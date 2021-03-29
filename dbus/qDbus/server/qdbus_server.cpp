#include "qdbus_server.h"
#include <QDebug>
#include <QString>


QDbusServer::QDbusServer(QObject *parent)
    :QObject (parent)
{

}

QDbusServer::~QDbusServer()
{

}

QString QDbusServer::GetDevice()
{
    QString str="Call get device";
    qDebug()<<str;
    return str;
}


