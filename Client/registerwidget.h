#ifndef REGISTERWIDGET_H
#define REGISTERWIDGET_H
#include "messagestruct.h"
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QTcpSocket>
#include <QHostAddress>
class RegisterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RegisterWidget(QWidget *parent = 0);

signals:

private:
    QLineEdit *accountLineEdit;
    QLineEdit *passwordLineEdit;
    QLineEdit *confireLineEdit;
    QPushButton *registerButton;
    QPushButton *backToLoginButton;
    QTcpSocket *tcpClient;
public slots:
    //注册账户
    void registerButtonClick();
};

#endif // REGISTERWIDGET_H
