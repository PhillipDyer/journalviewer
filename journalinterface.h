#ifndef JOURNALINTERFACE_H
#define JOURNALINTERFACE_H

#include <string>
#include <vector>
#include <systemd/sd-journal.h>

class JournalInterface
{
public:
    JournalInterface();
    ~JournalInterface();

    std::vector<std::string> retrieveFields();
};

#endif // JOURNALINTERFACE_H
