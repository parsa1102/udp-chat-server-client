#ifndef RUNNER_H
#define RUNNER_H

#include <QObject>
#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QDateTime>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QSet>

class runner : public QObject
{
    Q_OBJECT
public:
    explicit runner(QObject *parent = nullptr);
    QUdpSocket socket;
    quint16 port = 1499;
    void start();
    QSet<int> clientports;

signals:


public slots:
    void readyRead();

};

#endif // RUNNER_H
