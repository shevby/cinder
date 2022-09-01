#ifndef RESMAN_H
#define RESMAN_H

#include <QObject>
#include <QString>
#include <qqml.h>
#include <iostream>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <sin.h>

#include "ResModel.h"
#include "ResourceManager.h"


class Resman : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit Resman(QObject *parent = nullptr, QQmlApplicationEngine * engine = nullptr);
public slots:
    void open(const QString &path);
    void defaults();
signals:
    void modelUpdated(QString path);
private:
    QQmlApplicationEngine * _engine;
    ResModel * _model;
    ResourceManager manager;
};

#endif // RESMAN_H
