#ifndef JOURNALFIELDS_H
#define JOURNALFIELDS_H

#include <map>
#include <vector>
#include <cstdint>
#include <string>

/** \brief Primary fields I care about will be put in an Enum */
enum class Fields {
    BOOTID,
    TRANSPORT,
    MESSAGE,
    MESSAGE_ID,
    COMM,
    TIMESTAMP
};

struct FieldTranslation
{
    Fields field;                   //Enum describing the field.
    std::string display;            //Text to display in a header
    std::string command;            //Command to send to the Journal API

    FieldTranslation(Fields _field, std::string _display, std::string _command)
    {
        field = _field;
        display = _display;
        command = _command;
    }
};

class JournalFields
{
public:

    static const std::string &getCommandText(const Fields & field);

    static const std::string &getDisplayText(const Fields & field);

    static const std::string &getCommandText(const std::string & display);

    static const std::size_t getNumberOfFields();

    static const std::vector<std::string> &getFieldList();

private:
    JournalFields();

    static void initialize();

    static std::map<Fields, FieldTranslation> m_FieldMap;

    static std::vector<std::string> m_FieldList;

    static bool m_Initialized;
};

#endif // JOURNALFIELDS_H
