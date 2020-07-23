#include "clientwidget.h"
#include "ui_clientwidget.h"

#include <QGridLayout>
#include <QMessageBox>
#include <QDebug>
ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
{
    ui->setupUi(this);

    tcpClient = new QTcpSocket(this);

    tcpClient->connectToHost(QHostAddress("127.0.0.1"), 8888);

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
    loginButton = new QPushButton("用户登录");
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(accountLabel, 2, 0);
    gridLayout->addWidget(accountLineEdit, 2, 1, 1, 2);
    gridLayout->addWidget(passwordLabel, 3, 0);
    gridLayout->addWidget(passwordLineEdit, 3, 1, 1, 2);
    gridLayout->addWidget(loginButton, 4, 1);
    setLayout(gridLayout);
    connect(loginButton, &QPushButton::clicked, this, &ClientWidget::loginButtonClick);

}

ClientWidget::~ClientWidget()
{
    delete ui;
}
void ClientWidget::loginButtonClick(){
    SendMessage *m = new SendMessage;
    m->type = Login;

    QString account = accountLineEdit->text();
    m->length.fill('0',10);
    m->data = "";
    m->length.push_back(QString::number(account.length()));
    m->length = m->length.right(10);
    m->data.append(m->length+account);
    qDebug()<<m->data.toUtf8();
    QString password = passwordLineEdit->text();
    m->length.fill('0',10);
    m->length.push_back(QString::number(password.length()));
    m->length = m->length.right(10);
    m->data.append(m->length+password);
    qDebug()<<m->data.toUtf8();
    tcpClient->write(m->data.toLatin1());
    connect(tcpClient, &QTcpSocket::readyRead,[=](){
        QByteArray temp = tcpClient->readAll();
        if(temp=="1"){
            QMessageBox::information(this, tr("登录失败"), tr("账户不存在或密码不正确。"));
        }
        else{
            QMessageBox::information(this, tr("登录成功"), tr("正确。"));
        }
    });
}
bool ClientWidget::readData(){


}
