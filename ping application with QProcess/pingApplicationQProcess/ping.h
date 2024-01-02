#ifndef PING_H
#define PING_H

#include <QObject>
#include <QProcess>
#include <QDebug>
#include <QSysInfo>

class Ping : public QObject
{
    Q_OBJECT
public:
    explicit Ping(QObject *parent = nullptr);
    QString operatingSystem() const;
    QString getAddress() const;
    void setAddress(const QString &address);
signals:
    void output(QString data);
public slots:
    void start();
    void stop();
private slots:
    void errorOccured(QProcess::ProcessError error);
    void finished(int exitCode, QProcess::ExitStatus exitStatus);
    void readyReadStandardError();
    void readyReadStandardOutput();
    void started();
    void stateChanged(QProcess::ProcessState newState);
    void readyRead();
private:
    QProcess m_process;
    QString m_address;
    bool m_listening;
    QString getProcess();
    void startPing();
};

#endif // PING_H
