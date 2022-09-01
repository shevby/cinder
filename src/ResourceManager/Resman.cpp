#include "Resman.h"



Resman::Resman(QObject *parent, QQmlApplicationEngine * engine)
    : QObject{parent}
{
    _engine = engine;
    _model = nullptr;
}

void Resman::open(const QString &path)
{
    if(_model != nullptr) {
        delete _model;
    }

    manager.loadModel(path.toStdString());

    _model = new ResModel(manager.getModel());

    _engine->rootContext()->setContextProperty("fsmodel", _model);

    emit modelUpdated(path);
}

void Resman::defaults() {
    if(fs::exists("resman-config.sin")) {
        auto configStr = fs::readAll("resman-config.sin");
        auto config = Sin::parse(configStr);

        auto defaultPath = config["defaultPath"].asString();

        if(fs::exists(defaultPath) && fs::isDirectory(defaultPath)) {
            std::cout << "Opening default path: " << defaultPath << std::endl;
            this->open(QString::fromStdString(defaultPath));
        }
    }

}
