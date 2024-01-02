#include "ping.h"

Ping::Ping(QObject *parent)
    : QObject{parent}
{

    connect(&m_process,&QProcess::errorOccurred,this,&Ping::errorOccured);
    connect(&m_process,&QProcess::readyReadStandardError,this,&Ping::readyReadStandardError);
    connect(&m_process,&QProcess::readyReadStandardOutput,this,&Ping::readyReadStandardOutput);
    connect(&m_process,&QProcess::started,this,&Ping::started);
    connect(&m_process,&QProcess::stateChanged,this,&Ping::stateChanged);
    connect(&m_process,&QProcess::readyRead,this,&Ping::readyRead);

    connect(&m_process,QOverload<int,QProcess::ExitStatus>::of(&QProcess::finished),this,&Ping::finished);

    m_listening = false;
    m_address = "";
}

QString Ping::operatingSystem() const
{
    return QSysInfo::prettyProductName();
}

QString Ping::getAddress() const
{
    return m_address;
}

void Ping::setAddress(const QString &address)
{
    m_address = address;
}

void Ping::start()
{
    qInfo() << Q_FUNC_INFO;
    m_listening = true;
    m_process.start(getProcess());
}

void Ping::stop()
{
    qInfo() << Q_FUNC_INFO;
    m_listening = false;
    m_process.close();
}

void Ping::errorOccured(QProcess::ProcessError error)
{
    qInfo() << Q_FUNC_INFO << error;
    if(!m_listening)return;
    emit output("error");
}

void Ping::finished(int exitCode, QProcess::ExitStatus exitStatus)
{
    qInfo() << Q_FUNC_INFO;
    if(!m_listening)return;
    emit output("complete");
    Q_UNUSED(exitCode);
    Q_UNUSED(exitStatus);
}

void Ping::readyReadStandardError()
{
    qInfo() << Q_FUNC_INFO;
    if(!m_listening)return;
    QByteArray data = m_process.readAllStandardError();
    QString message = "standard error: ";
    message.append(data);
    emit output(message);
}

void Ping::readyReadStandardOutput()
{
    qInfo() << Q_FUNC_INFO;
    if(!m_listening)return;
    QByteArray data = m_process.readAllStandardOutput();
    emit output(QString(data.trimmed()));
}

void Ping::started()
{
    qInfo() << Q_FUNC_INFO;
}

void Ping::stateChanged(QProcess::ProcessState newState)
{
    qInfo() << Q_FUNC_INFO;
    switch (newState) {
    case QProcess::NotRunning:
        emit output(QString("Not running"));
        break;
    case QProcess::Starting:
        emit output(QString("Starting"));
        break;
    case QProcess::Running:
        emit output(QString("Running"));
        startPing();
        break;
    default:
        break;
    }
}

void Ping::readyRead()
{
    qInfo() << Q_FUNC_INFO;
    if(!m_listening)return;
    QByteArray data = m_process.readAll().trimmed();
    qInfo() << data;
    emit output(data);
}

QString Ping::getProcess()
{
    qInfo() << Q_FUNC_INFO;

    if(QSysInfo::productType() == "windows")return "cmd";
    if(QSysInfo::productType() == "osx")return "/bin/zsh";
    return "bash";
}

void Ping::startPing()
{
    qInfo() << Q_FUNC_INFO;
    QByteArray command;
    command.append("ping " + m_address.toStdString());
    qInfo() << Q_FUNC_INFO << command;
    if(QSysInfo::productType() == "windows")command.append("\r");
    command.append("\n");
    m_process.write(command);
}
