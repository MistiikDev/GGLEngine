#include "Log.h"

template<typename... Args>
void Log::Print(const std::string& Message, const Args&... args) {
    std::cout << "[GGLENGINE LOG]: " << Message;

    auto print_args = [](const auto& arg) {
        std::cout << " " << arg;
    };

    (print_args(args), ...); 
    
    std::cout << "\n";
}