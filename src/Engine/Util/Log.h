#ifndef GGLENGINE_LOG_H
#define GGLENGINE_LOG_H

#include <iostream>
#include <string>

struct Log {
    template<typename... Args>
    static void Print(const std::string& Message, const Args&... args);

    template<typename... Args>
    static void Warn(const std::string& Message, const Args&... args);

    template<typename... Args>
    static void Error(const std::string& Message, const Args&... args);
};

#endif