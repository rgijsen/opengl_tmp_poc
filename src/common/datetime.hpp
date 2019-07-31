#pragma once

#include <chrono>
#include <sstream>
#include <iostream>
#include <iomanip>

#define DATE_FORMAT std::string("%Y%m%d")
#define TIME_FORMAT std::string("%H%M%S")
#define DATETIME_FORMAT std::string(DATE_FORMAT + "-" + TIME_FORMAT)

class datetime
{
public:
  static std::string get_datetime(std::string format, bool useMilliSeconds = false)
  {
    auto time_point = std::chrono::system_clock::now();
    auto in_time = std::chrono::system_clock::to_time_t(time_point);

    struct tm timeinfo;
#ifdef _WIN32
    localtime_s(&timeinfo, &in_time);
#else
    timeinfo = *std::localtime(&in_time);
#endif
    std::stringstream ss;
    ss << std::put_time(&timeinfo, format.c_str());

    if(!useMilliSeconds)
      return ss.str();

    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(time_point.time_since_epoch());
    auto ms_str = std::to_string(ms.count() % 1000);
    return std::string(ss.str().c_str()) + "." + std::string("000").replace(3 - ms_str.length(), ms_str.length(), ms_str);
  }
};