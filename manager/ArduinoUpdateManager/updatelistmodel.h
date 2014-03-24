#include <QAbstractTableModel>

class UpdateListModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    UpdateListModel(QObject *parent);
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
};
