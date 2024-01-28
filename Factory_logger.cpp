#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <memory>

class Logger{
public:
    virtual ~Logger() = default;
    virtual void log(std::string msg) = 0;
};


class ConsoleLogger : public Logger
{
public:
    void log(std::string msg) override
    {
        std::cout << "CONSOLE LOGGER: " << msg << "\n";
    }
};
 
class FileLogger : public Logger
{
public :

    FileLogger(std::string filename) : m_file_name(filename){}

    void log(std::string msg) override {
        // Open the file in append mode
        std::ofstream file(m_file_name, std::ios::app);
        if (!file.is_open()) {
            std::cerr << "Failed to open log file: " << m_file_name << std::endl;
            return;
        }

        // Get current time
        auto now = std::chrono::system_clock::now();
        auto nowTimeT = std::chrono::system_clock::to_time_t(now);
        
        // Write timestamp and message to the file
        file << std::put_time(std::localtime(&nowTimeT), "%Y-%m-%d %H:%M:%S") << " - " << msg << std::endl;
        
        // File is closed automatically when the function returns (RAII)
    }

private:
    std::string m_file_name;
};


class LogFactory
{
public:
    virtual ~LogFactory() = default;
    LogFactory(std::shared_ptr<Logger> logger): m_logger(logger){}
    std::shared_ptr<Logger> getLogger()
    {
        return m_logger;
    }

    void Log(std::string msg)
    {
        m_logger->log(msg);
    }

protected:
    std::shared_ptr<Logger> m_logger;
};

class ConsoleLoggerFactory : public LogFactory
{
public:
    ConsoleLoggerFactory(): LogFactory(std::make_shared<ConsoleLogger>()){}
};

class FileLoggerFactory : public LogFactory
{
public:
    FileLoggerFactory(std::string filename): LogFactory(std::make_shared<FileLogger>(filename)){}
};


int main()
{
    auto file_factory = std::make_shared<FileLoggerFactory>("app.log");
    auto console_factory = std::make_shared<ConsoleLoggerFactory>();

    auto file_logger = file_factory->getLogger();
    auto consle_logger = console_factory->getLogger();

    file_logger->log("Hi");
    consle_logger->log("Hello World");
}