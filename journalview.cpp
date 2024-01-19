#include "journalview.h"

JournalView::JournalView(QObject * parent) :
    QAbstractTableModel(parent) {

    JournalInterface journal;

    m_ColumnHeaders = journal.retrieveFields();

}

int JournalView::rowCount(const QModelIndex & index) const
{
    return 200;
}

int JournalView::columnCount(const QModelIndex & index) const
{
    return m_ColumnHeaders.size();
}

QVariant JournalView::data(const QModelIndex & index, int role) const
{
    switch (role) {
    case Qt::DisplayRole:
        return QString("%1, %2").arg(m_ColumnHeaders[index.column()].c_str()).arg(index.row());
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> JournalView::roleNames() const
{
    return { {Qt::DisplayRole, "display"} };
}

