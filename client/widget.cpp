#include "widget.h"
#include "ui_widget.h"
#include <QSettings>
#include <bits/stdc++.h>
using namespace std;


void Widget::sendToServer(QString message){
    qInfo()<<"sending : "<<message << "to server";
    QByteArray data = message.toLatin1();
    QNetworkDatagram datagram(data , QHostAddress::Broadcast , 1499);
    //qInfo()<<"send : " << data;
    socket.writeDatagram(datagram);
}


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QSettings settings(QCoreApplication::organizationName() , QCoreApplication::applicationName());
    settings.beginGroup("Ports");
    prt = settings.value("port").toInt();
    qInfo()<<QString::number(prt);

    //QString date = QDateTime::currentDateTime().toString();
    //QByteArray data = date.toLatin1();

    QString startMessage = "Client " + QString::number(prt) + " says : "+"I just joined";
    sendToServer(startMessage);

    connect(&socket , &QUdpSocket::readyRead , this , &Widget::readyRead);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::readyRead()
{
    while(socket.hasPendingDatagrams()){
        QNetworkDatagram datagram = socket.receiveDatagram();
        //qInfo()<<"Read:" << datagram.data();
        //qInfo() << "from :" << datagram.senderAddress() << ":" << datagram.senderPort();
        QString message = datagram.data();
        if(message == "Received"){
            ui->status->setText("Status : Last message sent");
        }else{
            ui->textBrowser->append(message);
        }
    }
}


void Widget::on_sendButton_clicked()
{
    string tmp = ui->message->text().toStdString();
    /*if(!tmp.find_first_not_of(' ') != std::string::npos)
    {
        qInfo()<<QString::fromStdString(tmp);
        ui->message->setText("");
        return;
    }*/
    QString message = "Client " + QString::number(prt) + " says : "+ui->message->text();
    ui->message->setText("");
    ui->status->setText("Status : sending");
    sendToServer(message);
}

