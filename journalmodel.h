#ifndef JOURNALMODEL_H
#define JOURNALMODEL_H

#include <mutex>
#include <qqml.h>
#include <QAbstractTableModel>
#include <vector>
#include <string>
#include <map>
#include <thread>
#include "journalfields.h"
#include "journalinterface.h"

class JournalModel : public QAbstractTableModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_ADDED_IN_VERSION(1,1)

public:
    JournalModel(QObject * parent = nullptr);

    virtual ~JournalModel();

    int rowCount(const QModelIndex & index = QModelIndex()) const override;

    int columnCount(const QModelIndex & index = QModelIndex()) const override;

    QVariant data(const QModelIndex & index, int role) const override;

    QVariant headerData(const int section, const Qt::Orientation orientation, int role) const override;

    void filterOnBootID(const QString boot_id);

    void update();

    void updateThreadEntry();

    QHash<int, QByteArray> roleNames() const override;

private:

    JournalInterface m_Journal;
    std::unique_ptr<std::thread> m_DataFillThread;
    std::map<int, std::vector<std::string>> m_Data;
    std::vector<std::string> m_Headers;
    std::mutex m_DataProtector;


public slots:

    void updateQueryBootID(QString boot_id);

    void addRows();

};

#endif // JOURNALMODEL_H
