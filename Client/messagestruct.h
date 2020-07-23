#ifndef MESSAGESTRUCT_H
#define MESSAGESTRUCT_H

#include <QString>

enum Type{Login=0, Register=1};
struct SendMessage{
    Type type;
    QString length;
    QString data;

};
#endif // MESSAGESTRUCT_H
