
#include <algorithm>
#include "journalfields.h"


std::map<Fields, FieldTranslation> JournalFields::m_FieldMap;
std::vector<std::string> JournalFields::m_FieldList;

bool JournalFields::m_Initialized = false;


const std::string &JournalFields::getCommandText(const Fields &field)
{
    JournalFields::initialize();
    return m_FieldMap.at(field).command;
}

const std::string &JournalFields::getDisplayText(const Fields &field)
{
    JournalFields::initialize();
    return m_FieldMap.at(field).display;
}

const std::string &JournalFields::getCommandText(const std::string &display)
{
    JournalFields::initialize();
    auto result = std::find_if(m_FieldMap.begin(), m_FieldMap.end(), [&display](const auto & item) {
        if(display == item.second.display) {
            return true;
        }
        else {
            return false;
        }
    });

    return result->second.command;
}

const std::vector<std::string> &JournalFields::getFieldList()
{
    JournalFields::initialize();
    return m_FieldList;
}

const std::size_t JournalFields::getNumberOfFields()
{
    JournalFields::initialize();
    return m_FieldMap.size();
}

JournalFields::JournalFields() {}

void JournalFields::initialize()
{
    if(m_Initialized == true)
    {
        return;
    }

    m_FieldMap.insert(std::make_pair(Fields::BOOTID, FieldTranslation(Fields::BOOTID,"Boot ID" ,"_BOOT_ID")));
    m_FieldMap.insert(std::make_pair(Fields::TIMESTAMP, FieldTranslation(Fields::TIMESTAMP, "Timestamp", "_SOURCE_REALTIME_TIMESTAMP")));
    m_FieldMap.insert(std::make_pair(Fields::TRANSPORT, FieldTranslation(Fields::TRANSPORT, "Transport", "_TRANSPORT")));
    m_FieldMap.insert(std::make_pair(Fields::COMM, FieldTranslation(Fields::COMM,"Executable","_COMM")));
    m_FieldMap.insert(std::make_pair(Fields::MESSAGE, FieldTranslation(Fields::MESSAGE,"Message","MESSAGE")));
    m_FieldMap.insert(std::make_pair(Fields::MESSAGE_ID, FieldTranslation(Fields::MESSAGE_ID, "Message ID", "MESSAGE_ID")));

    for(auto & item : m_FieldMap)
    {
        m_FieldList.push_back(item.second.display);
    }

    m_Initialized = true;
}
