#include "qmlregister.h"

QHash<QString, void*> QMLRegister::qmlRegister = QHash<QString, void*>();

void QMLRegister::regQMLObject(QString name, void* object) {
    qmlRegister.insert(name, object);
}

void* QMLRegister::getQMLObject(QString name) {
    return qmlRegister[name];
}
