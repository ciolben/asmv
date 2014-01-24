#ifndef QMLREGISTER_H
#define QMLREGISTER_H

#include <QHash>
#include <QObject>

class QMLRegister
{
public:
    static void regQMLObject(QString name, void* object);
    static void* getQMLObject(QString name);

private:
    static QHash<QString, void*> qmlRegister;
};

#endif // QMLREGISTER_H
