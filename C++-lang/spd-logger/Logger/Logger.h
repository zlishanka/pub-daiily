#pragma once

// Simple Instruction on Using this Splunk Logger in your C++ Application

// Configuration 1: Select logger output sinks in your master JSON config file: console_sink, logfile_sink or http_sink.
// Configuration 2: Select your log level in this header file in compile time.
// Integration: Please follow the three steps: (see my unit test example: test_logger.cpp)
// Step 1: Initialize the Splunk Logger instance;
// Step 2: Start to log whatever you want;
// Step 3: Close the Splunk Logger to release the resources used by splunk logger.

// Current limitation: Define SPDLOG_ACTIVE_LEVEL to the desired log level *before * including "spdlog.h".
// Set up the log level at compile time in order to use SPDLOG_XXX() with pattern flags %@,%s,%g,%# and %!
// to capture source function name, source file name and line number.
// For details, please see the following spdlog document, chapter 3. Custom formatting:
// https://github.com/gabime/spdlog/wiki/3.-Custom-formatting.

// Splunk Logger API Interface

// Log level setting in dynamic or static
//#define LOG_LEVEL_DYNAMIC_SET		1

// The available log levels in static setting
// #define SPDLOG_LEVEL_TRACE		0
// #define SPDLOG_LEVEL_DEBUG		1
// #define SPDLOG_LEVEL_INFO		2
// #define SPDLOG_LEVEL_WARN		3
// #define SPDLOG_LEVEL_ERROR		4
// #define SPDLOG_LEVEL_CRITICAL	5
// #define SPDLOG_LEVEL_OFF			6

#define SPDLOG_ACTIVE_LEVEL			SPDLOG_LEVEL_TRACE
#include "spdlog/spdlog.h"

// The available log levels in dynamic setting
enum class LogLevel
{
    trace, debug, info, warn, error, critical, off, n_levels
};

// Variadic MACRO: log severity levels from low to high
#ifdef LOG_LEVEL_DYNAMIC_SET
#define log_trace(fmt, ...)			(spdlog::trace(fmt, ##__VA_ARGS__))
#define log_debug(fmt, ...)			(spdlog::debug(fmt, ##__VA_ARGS__))
#define log_info(fmt, ...)			(spdlog::info(fmt, ##__VA_ARGS__))
#define log_warn(fmt, ...)			(spdlog::warn(fmt, ##__VA_ARGS__))
#define log_error(fmt, ...)			(spdlog::error(fmt, ##__VA_ARGS__))
#define log_critical(fmt, ...)		(spdlog::critical(fmt, ##__VA_ARGS__))

#define log_level_set(level)		(Logger::setLevel(level))

#else
#define log_trace(fmt, ...)			(SPDLOG_TRACE(fmt, ##__VA_ARGS__))
#define log_debug(fmt, ...)			(SPDLOG_DEBUG(fmt, ##__VA_ARGS__))
#define log_info(fmt, ...)			(SPDLOG_INFO(fmt, ##__VA_ARGS__))
#define log_warn(fmt, ...)			(SPDLOG_WARN(fmt, ##__VA_ARGS__))
#define log_error(fmt, ...)			(SPDLOG_ERROR(fmt, ##__VA_ARGS__))
#define log_critical(fmt, ...)		(SPDLOG_CRITICAL(fmt, ##__VA_ARGS__))
#endif

#define log_level_get()				(Logger::getLevel())
#define log_level_name()			(Logger::getLevelName())


// Singleton design pattern for only one instance!
class Logger
{
public:
    static Logger& instance() {
        static Logger logger;
        return logger;
    }

    bool init();
    void close();

    static void setLevel(LogLevel level) {
        loglevel = level;
        spdlog::set_level(static_cast<spdlog::level::level_enum>(loglevel));
    }

    static LogLevel getLevel() {
        loglevel = static_cast<LogLevel>(spdlog::get_level());
        return loglevel;
    }

    static std::string getLevelName() {
    	return logLevelName[static_cast<int>(getLevel())];
    }

private:
    Logger() {}							// ctor private
    Logger& operator = (const Logger&);	// assignment operator disallowed
    Logger(const Logger&);				// copy-ctor disallowed

    std::string myModule = "logger";

    std::string logFile = "logs/logfile.json";
    std::string proxyServerUrl = "http://localhost:3030/logger";

    // Try tcp_sink
    std::string tcpHost = "127.0.0.1"; //"Dereks-MacBook-Pro.local";
    int tcpPort = 5050;

    std::string callSessionId = "";
    std::string consoleId = "";
    std::string env = "";
    std::string method = "";
    std::string profileId = "";

    const std::string component = "media";
    std::string subcomponent = "";
    std::string buildVersion = "";

    bool console_sink = true;
    bool console_connected = false;
    bool logfile_sink = true;
    bool logfile_connected = false;
    bool tcp_sink = true;
    bool tcp_client_connected = false;
    bool http_sink = false;
    bool http_client_connected = false;

    static LogLevel loglevel ;
    static std::vector<const std::string> logLevelName;

    bool readMasterConfig(const std::string &masterJson);
    bool saveConfig(const std::string &myJson);
    bool checkConfig();
    void printConfig();

    bool getSystemConfig(const std::string& proxyServerUrl);
    void printLoggerInit();
    std::string makeJsonString();

};

