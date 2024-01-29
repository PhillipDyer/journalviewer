#include "navmodel.h"

NavModel::NavModel(QObject * parent) : QAbstractListModel(parent){

    int number = 0;

    m_Journal.filterOnUniqueField(Fields::BOOTID);

    bool available;
    do
    {
        auto entry = m_Journal.readUniqueEntry(Fields::BOOTID);
        std::string data;

        //Rip the data out of the tuple
        std::tie(data,available) = entry;
        m_Data.insert(std::make_pair(number,data));
        ++number;
    }while(available == true);
}

int NavModel::rowCount(const QModelIndex &index) const
{
    return m_Data.size();
}

QVariant NavModel::data(const QModelIndex &index, int role) const
{
    auto item = m_Data.at(index.row());

    QString data = QString::fromUtf8(item.c_str());

    return data;

}

QHash<int, QByteArray> NavModel::roleNames() const
{
    return { {Qt::DisplayRole, "display"} };
}
