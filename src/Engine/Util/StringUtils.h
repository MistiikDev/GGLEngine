#ifndef GGLENGINE_STRINGUTILS_H
#define GGLENGINE_STRINGUTILS_H

#include "string"
#include "vector"
#include "iostream"

struct StringUtils {
    static void split( std::string& data, const char DELIMITER, std::vector<std::string>& output );
};

#endif