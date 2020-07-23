#include "loginwidget.h"

#include <QGridLayout>
#include <QMessageBox>
LoginWidget::LoginWidget(QWidget *parent) : QWidget(parent)
{

    resize(600,400);
    accountLabel = new QLabel("账户：");
    accountLabel->setAlignment(Qt::AlignCenter);
    accountLineEdit = new QLineEdit(this);
    accountLineEdit->setPlaceholderText("请输入账户名");
    accountLineEdit->setMinimumSize(400,50);
    passwordLabel = new QLabel("密码：");
    passwordLabel->setAlignment(Qt::AlignCenter);
    passwordLineEdit = new QLineEdit(this);
    passwordLineEdit->setPlaceholderText("请输入密码");
    passwordLineEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    passwordLineEdit->setMinimumSize(400,50);
    //按钮
    loginButton = new QPushButton("登录");
    registerButton = new QPushButton("注册");

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(accountLabel, 2, 0);
    gridLayout->addWidget(accountLineEdit, 2, 1, 1, 2);
    gridLayout->addWidget(passwordLabel, 3, 0);
    gridLayout->addWidget(passwordLineEdit, 3, 1, 1, 2);
    gridLayout->addWidget(registerButton, 4, 0);
    gridLayout->addWidget(loginButton, 4, 1);
    setLayout(gridLayout);
//    setWindowIcon(QIcon("D:\\Desktop\\图标\\system.ico"));
    setWindowTitle("图书管理系统用户登录");
    //设置背景图片
//    setAutoFillBackground(true);
//    QPalette palette;
//    palette.setBrush(this->backgroundRole(), QBrush(QPixmap("D:\\Desktop\\项目图片\\绿色圆环.png")));
//    this->setPalette(palette);

    connect(loginButton, &QPushButton::clicked, this, &LoginWidget::userLoginButtonClick);
    connect(registerButton, &QPushButton::clicked, this, &LoginWidget::registerButtonClick);
}
//用户登录
void LoginWidget::userLoginButtonClick(){
    tcpClient = new QTcpSocket(this);
    tcpClient->connectToHost(QHostAddress("127.0.0.1"), 8888);

    SendMessage *m = new SendMessage;
    m->data = "";
    m->type = Login;
    QString account = accountLineEdit->text();
    m->length.fill('0',10);
    m->length.push_back(QString::number(account.length()));
    m->length = m->length.right(10);
    m->data.append(m->length+account);
    QString password = passwordLineEdit->text();
    m->length.fill('0',10);
    m->length.push_back(QString::number(password.length()));
    m->length = m->length.right(10);
    m->data.append(m->length+password);
    tcpClient->write((QString::number(m->type)+m->data).toLatin1());

    connect(tcpClient, &QTcpSocket::readyRead,[=](){
        QByteArray temp = tcpClient->readAll();
        if(temp=="1"){
            QMessageBox::information(this, tr("登录成功"), tr("正确。"));
        }
        else{
            QMessageBox::information(this, tr("登录失败"), tr("账户不存在或密码不正确。"));
//            close();
//            UserWindow *userwindow = new UserWindow(account, password);
//            userwindow->show();
        }
    });

}
//注册
void LoginWidget::registerButtonClick(){

}
