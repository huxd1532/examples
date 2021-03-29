#include <QDebug>
#include <QProcess>
#include <QObject>
#include <QTemporaryFile>


bool command(const QString &cmd, const QStringList &args, QString &output) {
    QProcess *proc = new QProcess;
    proc->setProcessChannelMode(QProcess::MergedChannels);

    QObject::connect(proc, &QProcess::readyReadStandardOutput, [&]() {
        QString out = proc->readAllStandardOutput();
        //qDebug() << "comand out:" << out;
        output += out;
    });
    proc->start(cmd, args);
    proc->waitForStarted(-1);
    proc->waitForFinished();
    if ( QProcess::NormalExit != proc->exitStatus()  || proc->error() < QProcess::UnknownError){
        qWarning("Excute the comand(%s) failed!", qPrintable(cmd));
        qWarning() << "Error:" << proc->error();
        qWarning() << "Status:" << proc->exitStatus();
        return false;
    }
    return true;
}


int main()
{
    qWarning()<<"@@@@@";
    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    QStringList args{"-c", "ps aux | grep /usr/lib/deepin-graphics-driver-manager |grep -v grep"};
    //QStringList args{"-c", "ps aux"};
    process.start("/bin/bash", args);
    process.waitForFinished(-1);
    qInfo() << process.error();
    qInfo() <<"@@@exitCode: " << process.exitCode();
    qInfo() << process.readAllStandardOutput();
    qInfo() << "@@@@" <<process.readAllStandardError();
//    if (!process.exitCode()){
//        return -1;
//    }
    return 0;
}
