#include "Resman.h"

Resman::Resman(QObject *parent)
    : QObject{parent}
{
}

void Resman::open(const QString &path)
{
    std::cout << path.toStdString() << std::endl;
}