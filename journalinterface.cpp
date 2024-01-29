#include "journalinterface.h"
#include <utility>
#include <sstream>


JournalInterface::JournalInterface() {

    m_JournalIndex = 0;
    sd_journal * working_journal;

    sd_journal_open(&working_journal, SD_JOURNAL_LOCAL_ONLY);

    m_Journal.reset(working_journal);   //Congrats we have taken control of the Journal.
}

JournalInterface::~JournalInterface() {

}

int JournalInterface::getIndex() const {
    return m_JournalIndex;
}

bool JournalInterface::nextEntry() {
    ++m_JournalIndex;
    auto ret = sd_journal_next(m_Journal.get());

    if(ret == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool JournalInterface::filterOnField(const Fields &field, const std::string & entry)
{
    std::string command = JournalFields::getCommandText(field);

    std::stringstream command_stream;

    command_stream << command << '=' << entry;

    auto result = sd_journal_add_match(m_Journal.get(), command_stream.str().c_str(), 0);

    if(result == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool JournalInterface::filterOnUniqueField(const Fields &field)
{
    std::string command = JournalFields::getCommandText(field);

    auto result = sd_journal_query_unique(m_Journal.get(), command.c_str());

    if(result == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

const std::string JournalInterface::readEntry(const std::string & field) {

    const char * data;
    size_t length = 0;

    auto response = sd_journal_get_data(m_Journal.get(),field.c_str(),(const void **)&data,&length);

    std::string output;

    if(response >= 0)
    {
        output = data;

        if(output.empty() == false)
        {
            //nuke the beginning text on the field which is the field + '='
            auto begin = field.size() + 1;

            output = output.substr(begin, std::string::npos);
        }
    }
    return std::move(output);
}

const std::tuple<std::string, bool> JournalInterface::readUniqueEntry(const Fields &field)
{
    std::string command = JournalFields::getCommandText(field);

    const char * data;
    size_t length = 0;

    auto response = sd_journal_enumerate_unique(m_Journal.get(),(const void **)&data,&length);

    std::string output;

    bool more_entries_available;

    if(response >= 0)
    {
        output = data;

        if(output.empty() == false)
        {
            //nuke the beginning text on the field which is the field + '='
            auto begin = command.size() + 1;

            output = output.substr(begin, std::string::npos);
        }
    }

    if(response <= 0)
    {
        more_entries_available = false;
    }
    else
    {
        more_entries_available = true;
    }
    return std::move(std::make_tuple(output, more_entries_available));
}

std::vector<std::string> JournalInterface::retrieveFields() {

    std::vector<std::string> fields;

    const char * field_ptr;

    while( 0 < sd_journal_enumerate_fields(m_Journal.get(), &field_ptr))
    {
        std::string field = field_ptr;
        fields.push_back(field);
    }

    return std::move(fields);

}
