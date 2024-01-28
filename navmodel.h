#ifndef NAVMODEL_H
#define NAVMODEL_H

#include <QObject>
#include <QQuickItem>
#include <QAbstractListModel>
#include "journalinterface.h"

class NavModel : public QAbstractListModel
{
    Q_OBJECT
public:

    NavModel(QObject * parent = nullptr);

    int rowCount(const QModelIndex & index = QModelIndex()) const override;

    QVariant data(const QModelIndex & index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

private:

    JournalInterface m_Journal;
    std::map<int, std::string> m_Data;

 public slots:

    void itemSelected(QQuickItem * item, QObject * sender);

};

#endif // NAVMODEL_H
