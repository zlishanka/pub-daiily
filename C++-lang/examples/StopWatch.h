// Written By : Chaman Singh Verma

#pragma once

#include <chrono>
#include <unistd.h>
#include <iomanip> 
#include <sstream>
class StopWatch
{
    using Clock    = std::chrono::high_resolution_clock;
    using Duration = std::chrono::duration<double>;
public:

    StopWatch()
    {
         reset();
    }

    void start()
    {
        reset();
    }

    void resume()
    {
       tstart = Clock::now();
    }

    void stop()
    {
        auto tend = Clock::now();
        telapsed += (tend-tstart);
    }

    void reset()
    {
        tstart = Clock::now();
        telapsed = Duration::zero();
    }

    double getSeconds()
    {
        auto tspan = std::chrono::duration_cast<Duration>(telapsed);
        return tspan.count();
    }

    std::string getCurrentTimestamp() const
    {

            using namespace std::chrono;

            // get current time
            auto now = system_clock::now();

            // get number of milliseconds for the current second
            // (remainder after division into seconds)
            auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

            // convert to std::time_t in order to convert to std::tm (broken time)
            auto timer = system_clock::to_time_t(now);

            // convert to broken time
            std::tm bt = *std::localtime(&timer);

            std::ostringstream oss;

            oss << std::put_time(&bt, "%H:%M:%S"); // HH:MM:SS
            oss << '.' << std::setfill('0') << std::setw(3) << ms.count();

            return oss.str();
    }
    
private:
    Clock::time_point  tstart;
    Duration telapsed;
    long  elapsed;
};

