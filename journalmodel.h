#ifndef JOURNALMODEL_H
#define JOURNALMODEL_H

#include <qqml.h>
#include <QAbstractTableModel>
#include <vector>
#include <string>
#include <map>
#include "journalinterface.h"
class JournalModel : public QAbstractTableModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_ADDED_IN_VERSION(1,1)

public:
    JournalModel(QObject * parent = nullptr);

    int rowCount(const QModelIndex & index = QModelIndex()) const override;

    int columnCount(const QModelIndex & index = QModelIndex()) const override;

    QVariant data(const QModelIndex & index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

private:

    JournalInterface m_Journal;
    std::map<int, std::vector<std::string>> m_Data;
};

#endif // JOURNALMODEL_H
