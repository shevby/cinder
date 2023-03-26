#ifndef RESNODE_H
#define RESNODE_H

#include <QVariant>

class ResNode
{
public:
    explicit ResNode(const QList<QVariant> &data, ResNode *parentNode = nullptr);
    ~ResNode();

    void appendChild(ResNode *child);

    ResNode *child(int row);
    int childCount() const;
    Q_INVOKABLE int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    ResNode *parentItem();

private:
    QList<ResNode *> _childNodes;
    QList<QVariant> _nodeData;
    ResNode *_parentNode;
};

#endif // RESNODE_H
