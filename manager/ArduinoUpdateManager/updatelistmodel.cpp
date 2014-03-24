#include "updatelistmodel.h"

UpdateListModel::UpdateListModel(QObject *parent):
    QAbstractTableModel(parent)
{
}
int UpdateListModel::rowCount(const QModelIndex &parent) const
{
    return 3;
}
int UpdateListModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}
QVariant UpdateListModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        return QString("Row%1, Column%2")
            .arg(index.row() + 1)
            .arg(index.column() +1);
    }

    return QVariant();
}
