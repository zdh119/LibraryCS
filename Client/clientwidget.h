#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H
#include "messagestruct.h"
#include <QWidget>
#include <QHostAddress>
#include <QTcpSocket>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class ClientWidget;
}

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWidget(QWidget *parent = 0);
    ~ClientWidget();
public slots:
    //用户登录
    void loginButtonClick();
    //读取服务器信息
    bool readData();
private:
    Ui::ClientWidget *ui;
    QLabel *accountLabel;
    QLabel *passwordLabel;
    QLineEdit *accountLineEdit;
    QLineEdit *passwordLineEdit;
    QPushButton *loginButton;
    QTcpSocket *tcpClient;
};

#endif // CLIENTWIDGET_H
