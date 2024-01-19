#include "journalinterface.h"
#include <utility>


JournalInterface::JournalInterface() {

}

JournalInterface::~JournalInterface() {

}

std::vector<std::string> JournalInterface::retrieveFields() {

    std::vector<std::string> fields;

    sd_journal * working_journal;

    sd_journal_open(&working_journal, SD_JOURNAL_LOCAL_ONLY);

    const char * field_ptr;

    while( 0 < sd_journal_enumerate_fields(working_journal, &field_ptr))
    {
        std::string field = field_ptr;
        fields.push_back(field);
    }

    sd_journal_close(working_journal);

    return std::move(fields);

}
