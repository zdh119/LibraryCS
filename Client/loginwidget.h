#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include "messagestruct.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QTcpSocket>
#include <QHostAddress>

class LoginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LoginWidget(QWidget *parent = 0);

signals:

private:
    QLabel *accountLabel;
    QLabel *passwordLabel;
    QLineEdit *accountLineEdit;
    QLineEdit *passwordLineEdit;
    QPushButton *loginButton;
    QPushButton *registerButton;
    QTcpSocket *tcpClient;
public slots:
    //用户登录
    void userLoginButtonClick();
    //注册
    void registerButtonClick();
};

#endif // LOGINWIDGET_H
