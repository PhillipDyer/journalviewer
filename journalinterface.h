#ifndef JOURNALINTERFACE_H
#define JOURNALINTERFACE_H

#include <memory>
#include <string>
#include <vector>
#include <journalfields.h>
#include <systemd/sd-journal.h>
#include <tuple>

//Forward Declaration to JournalDeletor Functor
//Use an empty Namespace to keep it only useable
//in this file.
namespace {
    struct JournalDeleter {
        void operator()(sd_journal * ptr) {
            sd_journal_close(ptr);
        }
    };
}
/** \brief Represents the Journal */
class JournalInterface
{
public:
    /** \brief Opens the Journal */
    JournalInterface();
    /** \brief Closes the Journal */
    ~JournalInterface();

    int getIndex() const;

    bool nextEntry();

    bool filterOnField(const Fields & field);

    bool filterOnUniqueField(const Fields & field);

    const std::string readEntry(const std::string & field);

    const std::tuple<std::string, bool> readUniqueEntry(const Fields &field);

    std::vector<std::string> retrieveFields();
private:

    /** \brief Represents the Open Journal */
    std::unique_ptr<sd_journal,JournalDeleter> m_Journal;

    /** \brief Keep track of the Index we are currently viewing */
    int m_JournalIndex;
};



#endif // JOURNALINTERFACE_H
