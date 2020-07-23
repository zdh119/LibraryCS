#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H
#include "messagestruct.h"
#include "databaseoperation.h"
#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTextEdit>
#include <QLineEdit>
namespace Ui {
class ServerWidget;
}

class ServerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ServerWidget(QWidget *parent = 0);
    ~ServerWidget();
public slots:
    //当客户端有新链接的时候
    void newConnectionSlot();
private:
    Ui::ServerWidget *ui;
    QTextEdit *text;
    QLineEdit *lineEdit;
    QTcpServer *tcpServer;
    QTcpSocket *currentClient;

};

#endif // SERVERWIDGET_H
