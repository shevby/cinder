#ifndef RESMAN_H
#define RESMAN_H

#include <QObject>
#include <QString>
#include <qqml.h>
#include <iostream>

#include "fs.h"

class Resman : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit Resman(QObject *parent = nullptr);
public slots:
    void open(const QString &path);

signals:

};

#endif // RESMAN_H
