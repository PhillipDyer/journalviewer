#include "journalinterface.h"
#include <utility>


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
