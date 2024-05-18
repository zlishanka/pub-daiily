#include "Logger.h"
#include "version.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/tcp_sink.h"
#include "spdlog/async.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>

using namespace std;


LogLevel Logger::loglevel = LogLevel::info;
vector<const std::string> Logger::logLevelName = { "trace", "debug", "info", "warn", "error", "critical", "off" };

// Generate logger module JSON configuration file
//
bool Logger::saveConfig(const string &myJson)
{
    nlohmann::json jobj;
    jobj["level"]= getLevel();
    jobj["logfile"]= logFile;
    jobj["proxyServerUrl"]= proxyServerUrl;
    jobj["console_sink"]= console_sink;
    jobj["logfile_sink"]= logfile_sink;
    jobj["tcp_sink"] = tcp_sink;
    jobj["http_sink"]= http_sink;
    
    ofstream ofile(myJson.c_str());
    if (ofile.fail()) {
        cerr << "ERROR: Can not open logger module output json file: " << myJson.c_str() << endl;
        return false;
    }

    ofile << jobj.dump(4) << endl;
    ofile.close();
    return true;
}

// Read master JSON configuration file and set up logger module configuration parameters
//
bool Logger::readMasterConfig(const string &masterJson)
{
    nlohmann::json jobj;

    ifstream ifile(masterJson);
    if (ifile.fail()) {
        cerr << "ERROR: Can not open input master json file: " << masterJson.c_str() << endl;
        return false;
    }

    ifile >> jobj;

    // Search module's json object with the key = myModule!
    bool found = false;
    for (auto& [key1, val1] : jobj.items())
    {
        if( 0 == key1.compare(myModule.c_str())) {
            found = true;

            // Decode my module's json object myModule now
            for (auto& [key2, val2] : val1.items())
            {
                if( 0 == key2.compare("level") ) {
                    setLevel(static_cast<LogLevel>(val2));
                }
                if( 0 == key2.compare("logfile") ) {
                    logFile = val2;
                }
                if( 0 == key2.compare("proxyServerUrl") ) {
                    proxyServerUrl = val2;
                }
                if (0 == key2.compare("console_sink")) {
                    console_sink = val2;
                }
                if (0 == key2.compare("logfile_sink")) {
                    logfile_sink = val2;
                }
                if (0 == key2.compare("tcp_sink")) {
                    tcp_sink = val2;
                }
                if (0 == key2.compare("http_sink")) {
                    http_sink = val2;
                }               
            }
        }
    }

    if (!found) {
        cerr << "ERROR: My module json object " << myModule.c_str()
             << " was missing in the master " << masterJson.c_str() << endl;
        ifile.close();
        return false;
    }

    ifile.close();
    return true;
}

// Validate and check logger module configuration parameters
//
bool Logger::checkConfig()
{
    if (logFile.empty()) {
        cout << "INFO: logFile not specified: " << endl;
        cout << "LogFile will be set to the default one" << endl;
        logFile = "/logs/logfile.json";
    }

    if (proxyServerUrl.empty()) {
        cout << "INFO: proxy server URL not specified: " << endl;
        cout << "Proxy server URL will be set to the default one" << endl;
        proxyServerUrl = "http://localhost:3030/logger";
    }

    if (console_sink || logfile_sink || tcp_sink || http_sink) {
    	return true;
    }

    cerr << "ERROR: No sinks are selected!" << endl;
    return false;
}

// Print out logger module configuration parameters for debugging
//
void Logger::printConfig()
{
	printf("INFO: Logger Config:\n");
    printf("INFO: loglevel: %s\n", getLevelName().c_str());
    printf("INFO: logFile: %s\n", logFile.c_str());
    printf("INFO: proxy server URL: %s\n", proxyServerUrl.c_str());
    printf("INFO: console_sink: %s\n", (console_sink ? "true" : "false"));
    printf("INFO: logfile_sink: %s\n", (logfile_sink ? "true" : "false"));
    printf("INFO: tcp_sink: %s\n", (tcp_sink ? "true" : "false"));
    printf("INFO: http_sink: %s\n", (http_sink ? "true" : "false"));  
}

string Logger::makeJsonString()
{
    string res;
    nlohmann::json jobj;

    // Avail mandatory/common log message fields
    jobj["callSessionId"] = callSessionId;
    jobj["consoleId"] = consoleId;
    jobj["env"] = env;
    jobj["method"] = method;
    jobj["profileId"] = profileId;

    jobj["component"] = component;
    jobj["subcomponent"] = subcomponent;
    jobj["buildVersion"] = buildVersion;

    return jobj.dump();
}

bool Logger::getSystemConfig(const string& proxyServerUrl)
{
	subcomponent = Subcomponent::name;
	buildVersion = Subcomponent::getBuildVerStr();

	// Get other system config parameters from splunk proxy server

	return true;
}

void Logger::printLoggerInit()
{
	printf("INFO: loglevel: %s\n", getLevelName().c_str());
    printf("INFO: subcomponent: %s\n", subcomponent.c_str());
    printf("INFO: buildVersion: %s\n", buildVersion.c_str());
    printf("INFO: console_connected: %d\n", console_connected);
    printf("INFO: logfile_connected: %d\n", logfile_connected);
    printf("INFO: tcp_client_connected: %d\n", tcp_client_connected);
    printf("INFO: http_client_connected: %d\n", http_client_connected);
}

bool Logger::init()
{
    cout << "INFO: Logger::init(): Started:" << endl;

    //if (!readMasterConfig(masterJson)) {
    //    cout << " INFO: Logger::init(): The master configuration json reading failed and use logger default one!" << endl;
    //    saveConfig(myJsonfile);
    //}

    if (!checkConfig()) {
        cerr << "ERROR: Logger::init() failed on checking configuration!" << endl;
        return false;
    }
    printConfig();

    if (!getSystemConfig(proxyServerUrl)) {
    	cerr << "ERROR: Logger::init() failed on getting config parameters from splunk proxy server!" << endl;
    	return false;
    }

    try {      
    vector<spdlog::sink_ptr> sinks;

    // Set up console sink with colors
    if (console_sink) {
        cout << "INFO: Logger::init(): Create output console sink." << endl;
        try {
            auto console_sink = make_shared<spdlog::sinks::stdout_color_sink_mt>();
            console_sink->set_level(spdlog::level::trace);
            string textpattern = "[%Y-%m-%d %T.%e] [%^%l%$] (%E.%f) %!(): %s:%#, \"message\": %v";
            console_sink->set_pattern(textpattern.c_str());
            console_connected = true;

            sinks.push_back(console_sink);
        }
        catch (const spdlog::spdlog_ex& ex) {
        	console_connected = false;
            cerr << "ERROR: Logger::init() failed: exception on console_sink: " << ex.what() << endl;
        }
    }
    else {
    	console_connected = false;
        cout << "INFO: Logger::init(): No output console sink." << endl;
    }

    // Set up rotating file sink in JSON with its file size to a maximum of 5MB and a maximum of 3 rotated files
    if (logfile_sink) {
        cout << "INFO: Logger::init(): Create output logfile sink." << endl;
        try {
            auto rotating_file_sink = make_shared<spdlog::sinks::rotating_file_sink_mt> (logFile.c_str(), 1024*1024, 5, 3);
            rotating_file_sink->set_level(spdlog::level::trace);
            string jsonpattern = { "{\"dateTime\": \"%Y-%m-%d %T.%e\", \"timestamp\": %E.%f, \"level\": \"%^%l%$\", \"functionName\": \"%!()\", \"fileName\": \"%s\", \"lineNumber\": %#, \"processId\": %P, \"threadId\": %t, \"message\": \"%v\"}," };
            rotating_file_sink->set_pattern(jsonpattern.c_str());
            logfile_connected = true;

            sinks.push_back(rotating_file_sink);
        }
        catch (const spdlog::spdlog_ex& ex) {
        	logfile_connected = false;
            cerr << "ERROR: Logger::init() failed: exception on logfile_sink: " << ex.what() << endl;
        }
    }
    else {
    	logfile_connected = false;
        cout << "INFO: Logger::init(): No output logfile sink." << endl;
    }

    // Set up TCP sink
    if (tcp_sink) {
        cout << "INFO: Logger::init(): Create output tcp sink." << endl;
        try {
        	spdlog::sinks::tcp_sink_config config(tcpHost, tcpPort);
        	auto tcp_sink = make_shared<spdlog::sinks::tcp_sink_mt>(config);
        	tcp_sink->set_level(spdlog::level::trace);
        	string tcppattern = { "{\"dateTime\": \"%Y-%m-%d %T.%e\", \"timestamp\": %E.%f, \"level\": \"%^%l%$\", \"functionName\": \"%!()\", \"fileName\": \"%s\", \"lineNumber\": %#, \"processId\": %P, \"threadId\": %t, \"message\": \"%v\"}," };
        	tcp_sink->set_pattern(tcppattern.c_str());
            tcp_client_connected = true;

        	sinks.push_back(tcp_sink);
        }
        catch (const spdlog::spdlog_ex& ex) {
            tcp_client_connected = false;
            cerr << "ERROR: Logger::init() failed: exception on tcp_sink(tcp_client_connected = " << tcp_client_connected << "): " << ex.what() << endl;
        }
    }
    else {
        tcp_client_connected = false;
        cout << "INFO: Logger::init(): No output tcp sink." << endl;
    }

    // Set up HTTP sink
    if (http_sink) {
        cout << "INFO: Logger::init(): Create output http sink." << endl;
        try {
            cout << "INFO: Logger::init(): http_sink Not implemented yet!" << endl;
        }
        catch (const spdlog::spdlog_ex& ex) {
            http_client_connected = false;
            cerr << "ERROR: Logger::init() failed: exception on http_sink(http_client_connected = " << http_client_connected << "): " << ex.what() << endl;
        }
    }
    else {
        http_client_connected = false;
        cout << "INFO: Logger::init(): No output http sink." << endl;
    }

    if (sinks.empty()) {
        cout << "ERROR: Logger::init() failed: No output sinks found!" << endl;
        return false;
    }

    cout << "INFO: Logger::init(): Create input logger." << endl;

    // Now set up Asynchronous logger with queue of 8K items and 1 backing thread.
    // Note: The default thread pool settings can be modified *before* creating the async logger.
    spdlog::init_thread_pool(1024 * 8, 1);
    auto mlogger = make_shared<spdlog::async_logger>("module_logger", sinks.begin(), sinks.end(),
        spdlog::thread_pool(), spdlog::async_overflow_policy::block);
    mlogger->set_level(spdlog::level::trace);
    spdlog::register_logger(mlogger);
    spdlog::set_default_logger(mlogger);

    } // try

    // Catch other spdlog related exceptions:
    catch (const spdlog::spdlog_ex& ex) {
        cerr << "ERROR: Logger::init() failed: exception: " << ex.what() << endl;
    }

    setLevel(loglevel);
    cout << "INFO: Logger::init(): Finished:" << endl;
    printLoggerInit();
    return true;
}

void Logger::close()
{
    spdlog::drop_all();		// drop all references from the registry
    spdlog::shutdown();		// stop any running threads started by spdlog and clean registry loggers
}

