#include "journalmodel.h"
#include "journalinterface.h"

JournalModel::JournalModel(QObject * parent) :
    QAbstractTableModel(parent) {

    auto headers = m_Journal.retrieveFields();

    int number = 0;
    m_Data.insert(std::make_pair(number,headers));

    while(m_Journal.nextEntry() == true)
    {
        ++number;

        if(number > 5000)
        {
            break;
        }

        //Pull out all the fields
        std::vector<std::string> data_row;
        for(auto item : m_Data.at(0))
        {
            auto data = m_Journal.readEntry(item.c_str());
            data_row.push_back(data);
        }
        m_Data.insert(std::make_pair(number,data_row));
    }
    (nullptr);
}

int JournalModel::rowCount(const QModelIndex & index) const
{
    return m_Data.size();
}

int JournalModel::columnCount(const QModelIndex & index) const
{
    return m_Data.at(0).size();
}

QVariant JournalModel::data(const QModelIndex & index, int role) const
{
    switch (role) {
    case Qt::DisplayRole:
    {

        return QString("%1").arg(m_Data.at(index.row())[index.column()].c_str());

    }

    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> JournalModel::roleNames() const
{
    return { {Qt::DisplayRole, "display"} };
}

