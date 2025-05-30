#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>
#include <mutex>

class Logger {
public:
    // Obține instanța unică a loggerului
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    // Pentru a scrie un mesaj în fișierul de log
    void log(const std::string& message) {
        std::lock_guard<std::mutex> lock(mtx);
        logfile << message << std::endl;
    }

    // Asigurarea ca e singleton
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

private:
    std::ofstream logfile; // obiect de tip output file stream din biblioteca standard C++ (<fstream>)
    std::mutex mtx; // asa previn ca mesajele să se amestece sau să corup fișierul de log.
    // Mutex-ul proteja accesul la o resursă partajată între mai multe fire de execuție (threads).

    
    // Constructor privat: deschide fișierul de log
    Logger() : logfile("log.txt", std::ios_base::app) {}

    // Destructor: închide fișierul la final
    ~Logger() {
        if (logfile.is_open())
            logfile.close();
    }
};

#endif // LOGGER_H
