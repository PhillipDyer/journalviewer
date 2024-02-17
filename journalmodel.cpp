#include "journalmodel.h"
#include "journalinterface.h"
#include <iostream>

JournalModel::JournalModel(QObject * parent) :
    QAbstractTableModel(parent) {

    this->update();
}

JournalModel::~JournalModel()
{
    if(m_DataFillThread)
    {
        m_DataFillThread->join();
    }
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

        auto row = index.row();
        auto column = index.column();

        auto data_string = m_Data.at(row)[column];

        return QString("%1").arg(data_string.c_str());

    }

    default:
        break;
    }

    return QVariant();
}

QVariant JournalModel::headerData(const int section, const Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal)
    {
        return QString("%1").arg(m_Headers[section].c_str());
    }

    return QVariant();
}

void JournalModel::filterOnBootID(const QString boot_id)
{
    m_Journal.filterOnField(Fields::BOOTID, boot_id.toStdString());
    this->update();
}

void JournalModel::update()
{
    m_DataFillThread.reset(new std::thread(std::bind(&JournalModel::updateThreadEntry, this)));
}

void JournalModel::updateThreadEntry()
{
    int number = 0;
    m_Data.clear();
    m_Headers = JournalFields::getFieldList();

    while(true)
    {
        auto start_index = number;

        //Pull out all the fields
        std::map<int, std::vector<std::string> > temp_holder;

        bool next_entry;

        for(auto x = 0; x < 100; ++x)
        {
            next_entry = m_Journal.nextEntry();

            if(next_entry == false)
            {
                break;  //We are done.
            }

            std::vector<std::string> data_row;
            for(auto & item : m_Headers)
            {
                auto data = m_Journal.readEntry(JournalFields::getCommandText(item));
                data_row.push_back(data);
            }
            temp_holder.insert(std::make_pair(number, data_row));
            ++number;
        }

        this->beginInsertColumns(QModelIndex(), start_index, number);

        {
            std::scoped_lock<std::mutex> scoped_lock(m_DataProtector);
            m_Data.merge(temp_holder);
        }

        this->endInsertRows();

        if(next_entry == false)
        {
            break;
        }
    }

    std::cout << "Written: " << m_Data.size() << " entries to screen." << std::endl;

}

QHash<int, QByteArray> JournalModel::roleNames() const
{
    return { {Qt::DisplayRole, "display"} };
}

void JournalModel::updateQueryBootID(QString boot_id)
{
    this->filterOnBootID(boot_id);
}

void JournalModel::addRows()
{
    std::map<int, std::vector<std::string>> temp_data;

    {
        std::scoped_lock<std::mutex> scoped_lock(m_DataProtector);
        temp_data.swap(m_Data);
    }


}

