#ifndef GLOBAL_H
#define GLOBAL_H

#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <cstdio>

#include <random>
#include <sstream>
#include <iomanip>
#include <fstream>

typedef uint32_t ui32;
typedef uint16_t ui16;

typedef struct {
    ui32 start;
    ui32 end;

    ui32 length;
} UI32_Range;

namespace Engine {
    namespace file {
        inline void parse( const char* filePath, const char* errMsg, auto&& handler ) {
            std::ifstream stream(filePath);
            std::string line;

            if (!stream.good())
                throw std::runtime_error(errMsg != nullptr ? errMsg : "Failed to open file");

            while (std::getline(stream, line)) {
                std::stringstream ss(line);
                handler(ss, line);
            }
        }

        inline void read ( const char* filePath, char* r_buf ) {}
        
        inline void write ( const char* filePath, char* w_buf ) {}
    }


    namespace string {
        inline void split( std::string &Data, const char DELIMITER, std::vector<std::string> &output ) {
            
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
    }


    namespace log {
        template<typename ...Args>
        inline void print( const std::string& header, const auto& message, const Args& ...args ) {
            std::cout << header << message << " ";

            if (sizeof...(args) > 0) {
                ((std::cout << args << " "), ...);
            }

            std::cout << std::endl;
        }
    }

    namespace crypto {
        
    }
}

#endif // GLOBAL_H