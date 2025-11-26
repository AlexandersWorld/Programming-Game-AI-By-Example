#include "../../Public/Utils/Clock.h"
#include <chrono>
#include <ctime>

inline double Clock::GetCurrentTime()
{
    auto now = std::chrono::system_clock::now();
    
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    
    std::tm* local_time = std::localtime(&now_c);
    
    return (double)local_time->tm_sec;
}
