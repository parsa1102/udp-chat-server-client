#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QShortcut>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void readyRead();




private slots:
    void on_sendButton_clicked();

private:
    Ui::Widget *ui;

    QUdpSocket socket;
    int prt;

    void sendToServer(QString message);
};
#endif // WIDGET_H
