#pragma once

#include <fstream>
#include <string>

template<typename T>
class Logger {
private:
    std::ofstream logFile;

public:
    Logger(const std::string& filename) {
        logFile.open(filename, std::ios::app);
    }

    void log(const T& message) {
        if (logFile.is_open()) {
            logFile << message << std::endl;
        }
    }

    ~Logger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }
};

