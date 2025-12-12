#include "StringUtils.h"

void StringUtils::split(std::string &Data, const char DELIMITER, std::vector<std::string> &output)
{
    std::string buf;
    for (char element : Data)
    {
        if (element == DELIMITER)
        {
            output.push_back(buf);
            buf.clear();
        }
        else
        {
            buf += element;
        }
    }

    output.push_back(buf);
}