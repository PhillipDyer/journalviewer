#include "journalmodel.h"
#include "journalinterface.h"
#include <iostream>

JournalModel::JournalModel(QObject * parent) :
    QAbstractTableModel(parent) {

    this->update();
}

int JournalModel::rowCount(const QModelIndex & index) const
{
    return m_Data.size();
}

int JournalModel::columnCount(const QModelIndex & index) const
{

    auto res = JournalFields::getNumberOfFields();
    return res;
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

void JournalModel::filterOnBootID(const QString boot_id)
{
    emit layoutAboutToBeChanged();

    m_Journal.filterOnField(Fields::BOOTID, boot_id.toStdString());
    this->update();

    emit layoutChanged();
}

void JournalModel::update()
{
    int number = 0;
    m_Data.clear();
    m_Data.insert(std::make_pair(number,JournalFields::getFieldList()));

    while(m_Journal.nextEntry() == true)
    {
        ++number;

        if(number > 5000)
        {
            break;
        }

        //Pull out all the fields
        std::vector<std::string> data_row;
        for(auto & item : m_Data.at(0))
        {
            auto data = m_Journal.readEntry(JournalFields::getCommandText(item));
            data_row.push_back(data);
        }
        m_Data.insert(std::make_pair(number,data_row));
    }
}

QHash<int, QByteArray> JournalModel::roleNames() const
{
    return { {Qt::DisplayRole, "display"} };
}

void JournalModel::updateQueryBootID(QString boot_id)
{
    this->filterOnBootID(boot_id);
}

