#include "ResModel.h"

ResModel::ResModel(Sin &model, QObject *parent)
    : QAbstractItemModel{parent}
{
    _rootItem = new ResNode({"Title"});
    _setupModelData(model, _rootItem);
}

ResModel::~ResModel()
{
    delete _rootItem;
}

QVariant ResModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    ResNode *item = static_cast<ResNode *>(index.internalPointer());

    return item->data(index.column());
}

Qt::ItemFlags ResModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index);
}

QVariant ResModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return _rootItem->data(section);

    return QVariant();
}

QModelIndex ResModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    ResNode *parentItem;

    if (!parent.isValid())
        parentItem = _rootItem;
    else
        parentItem = static_cast<ResNode *>(parent.internalPointer());

    ResNode *childItem = parentItem->child(row);

    if (childItem)
        return createIndex(row, column, childItem);
    return QModelIndex();
}

QModelIndex ResModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    ResNode *childItem = static_cast<ResNode *>(index.internalPointer());
    ResNode *parentItem = childItem->parentItem();

    if (parentItem == _rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int ResModel::rowCount(const QModelIndex &parent) const
{
    ResNode *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = _rootItem;
    else
        parentItem = static_cast<ResNode *>(parent.internalPointer());

    return parentItem->childCount();
}

int ResModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<ResNode *>(parent.internalPointer())->columnCount();
    return _rootItem->columnCount();
}

void ResModel::_setupModelData(Sin &model, ResNode *parent)
{
    auto object = model.asObject();

    for (auto f : object)
    {
        _rootItem->appendChild(this->_addType(QString::fromStdString(f.first), f.second));
    }
}

ResNode *ResModel::_addType(QString name, Sin &data)
{
    auto object = data.asObject();
    QList<QVariant> field;
    field.append(name);

    auto type = new ResNode(field, _rootItem);

    for(auto f : object) {
        type->appendChild(this->_addNamespace(QString::fromStdString(f.first), f.second, type));
    }

    return type;
}

ResNode *ResModel::_addNamespace(QString name, Sin &data, ResNode *parent)
{
    auto object = data.asObject();
    QList<QVariant> field;
    field.append(name);

    auto nameSpace = new ResNode(field, parent);

    for(auto f : object) {
        nameSpace->appendChild(this->_addResource(QString::fromStdString(f.first), nameSpace));
    }

    return nameSpace;
}

ResNode *ResModel::_addResource(QString name, ResNode *parent)
{
    QList<QVariant> field;
    field.append(name);

    return new ResNode(field, parent);
}
