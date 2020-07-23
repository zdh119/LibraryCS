#include "serverwidget.h"
#include "ui_serverwidget.h"
#include <QDebug>
#include <QHBoxLayout>
#include <QTextEdit>
ServerWidget::ServerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWidget)
{
    ui->setupUi(this);

    tcpServer = new QTcpServer(this);
    tcpServer->listen(QHostAddress::Any, 8888);

    connect(tcpServer, &QTcpServer::newConnection, this, &ServerWidget::newConnectionSlot);

    text = new QTextEdit(this);
    lineEdit = new QLineEdit;

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(text);
    layout->addWidget(lineEdit);
    setLayout(layout);

}

ServerWidget::~ServerWidget()
{
    delete ui;
}
void ServerWidget::newConnectionSlot(){
    currentClient = tcpServer->nextPendingConnection();
    text->setText("connect success");
    qDebug()<<"connect success";
    connect(currentClient, &QTcpSocket::readyRead, [=]{
        ReceiveMessage *m = new ReceiveMessage;
        m->type =Type(currentClient->read(1).toInt());
        while(currentClient->bytesAvailable()>0){

            m->length = currentClient->read(10).toInt();
            qDebug()<<"current length:"<<m->length;
            m->data.append(currentClient->read(m->length));
        }
        qDebug()<<m->data.length();
        switch (m->type) {
        case Login:
            if(DatabaseOperation::checkAccount(m->data.at(0), m->data.at(1), "user")){
                currentClient->write(QString("1").toLatin1());
            }
            else{
                currentClient->write(QString("0").toLatin1());
            }
            break;
        case Register:
            if(!DatabaseOperation::selectAccount(m->data.at(0))){
                qDebug()<<m->data.at(0)<<" "<<m->data.at(1);
                if(DatabaseOperation::addAccount(m->data.at(0), m->data.at(1), "user"))
                    currentClient->write(QString("1").toLatin1());
                else
                    currentClient->write(QString("0").toLatin1());
            }
            else{
                currentClient->write(QString("0").toLatin1());
            }
            break;
        default:
            break;
        }

    });

}
