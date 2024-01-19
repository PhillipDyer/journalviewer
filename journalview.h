#ifndef JOURNALVIEW_H
#define JOURNALVIEW_H

#include <qqml.h>
#include <QAbstractTableModel>
#include <vector>
#include <string>
#include "journalinterface.h"

class JournalView : public QAbstractTableModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_ADDED_IN_VERSION(1,1)

public:
    JournalView(QObject * parent = nullptr);

    int rowCount(const QModelIndex & index = QModelIndex()) const override;

    int columnCount(const QModelIndex & index = QModelIndex()) const override;

    QVariant data(const QModelIndex & index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

private:

    std::shared_ptr<sd_journal> m_Journal;
    std::vector<std::string> m_ColumnHeaders;
};

#endif // JOURNALVIEW_H
