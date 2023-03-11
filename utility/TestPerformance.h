#ifndef TEST_PERFORMANCE_H
#define TEST_PERFORMANCE_H

#include <chrono>
#include <map>
#include <string>
#include <vector>

namespace Sindy {

using TimePoint    = std::chrono::steady_clock::time_point;
using DurationTime = std::chrono::steady_clock::duration;

class RunTime
{
    TimePoint                           m_firstTime;
    TimePoint                           m_lastTime;
    std::map<std::string, DurationTime> m_mapLog2Time;
    std::vector<std::string>            m_arrLog;

    void        _addRunTime(const std::string &strCatalog, DurationTime offset);
    std::string _write(const std::string &strTitle);
    std::string _catalog(const std::string &strInput = "");

public:
    RunTime();
    void reset();
    // 获取上一个log到当前log流逝的时间
    long addTimePoint(const std::string &strLog = "");
    void write(const std::string &strFileFullPath, const std::string &strTitle = "");

    void printTime(long time, bool bClear = true);
    void printTime(const std::string &strTitle = "", bool bClear = true);
};

}  // namespace Sindy

#endif // !TEST_PERFORMANCE_H
