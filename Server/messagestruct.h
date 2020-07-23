#ifndef MESSAGESTRUCT_H
#define MESSAGESTRUCT_H

#include <QList>
#include <QString>

enum Type{Login=0, Register=1};
struct ReceiveMessage{
    Type type;
    int length;
    QList<QString> data;

};
#endif // MESSAGESTRUCT_H
