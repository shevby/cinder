#include "ResNode.h"
#include <iostream>
ResNode::ResNode(const QList<QVariant> &data, ResNode *parentNode) : _nodeData(data), _parentNode(parentNode)
{

}

ResNode::~ResNode()
{
    qDeleteAll(_childNodes);
}

void ResNode::appendChild(ResNode *child)
{
    _childNodes.append(child);
}

ResNode *ResNode::child(int row)
{
    if (row < 0 || row >= _childNodes.size())
        return nullptr;

    return _childNodes.at(row);
}

int ResNode::childCount() const
{
    return _childNodes.count();
}

int ResNode::columnCount() const
{
    if(this == nullptr) {
        return 0;
    }

    return _nodeData.count();
}

QVariant ResNode::data(int column) const
{
    if (column < 0 || column >= _nodeData.size())
        return QVariant();

    return _nodeData.at(column);
}

int ResNode::row() const
{
    if (_parentNode)
        return _parentNode->_childNodes.indexOf(const_cast<ResNode*>(this));

    return 0;
}

ResNode *ResNode::parentItem()
{
    return _parentNode;
}
