#ifndef RESMODEL_H
#define RESMODEL_H

#include <QAbstractItemModel>

#include "ResNode.h"
#include "sin.h"

class ResModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit ResModel(Sin &model, QObject *parent = nullptr);
    ~ResModel();

    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

private:
    void _setupModelData(Sin &model, ResNode *parent);

    ResNode *_addType(QString name, Sin &data);
    ResNode *_addNamespace(QString name, Sin &data, ResNode *parent);
    ResNode *_addResource(QString name, QString filepath, ResNode *parent);

    ResNode *_rootItem;
};

#endif // RESMODEL_H
