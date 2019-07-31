#pragma once

#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <condition_variable>
#include <functional>
#include "datetime.hpp"

namespace logging
{
  typedef std::function<void(std::string)> fnLogger_t;

  enum class LogLevel
  {
    QUIET = 0,
    MINIMAL = 1,
    NORMAL = 2,
    DETAILED = 3,
    DIAGNOSTIC = 4
  };

  class AsyncLogging;

  class Logging
  {
    friend AsyncLogging;

    // poor man's singleton
    static std::shared_ptr<Logging> This;

    LogLevel _logLevel;
    fnLogger_t _fnLoggerError, _fnLoggerWarning, _fnLoggerInfo = nullptr;
    std::mutex _mutex;

    inline static std::string format_msg(std::string msg)
    {
      return datetime::get_datetime(DATETIME_FORMAT, true) + ": " + msg;
    }

    void AddFnLogger(fnLogger_t newLogger, fnLogger_t& currentLogger)
    {
      if(newLogger)
      {
        if(!currentLogger)
          currentLogger = newLogger;
        else
          currentLogger = [currentLogger, newLogger](auto msg) {
            newLogger(msg);
            currentLogger(msg);
          };
      }
    }

    bool isLevel(LogLevel logLevel)
    {
      return logLevel <= _logLevel;
    }

  public:
    Logging(fnLogger_t info, fnLogger_t warning = nullptr, fnLogger_t error = nullptr, LogLevel logLevel = LogLevel::NORMAL)
        : _logLevel(logLevel),
          _fnLoggerError(nullptr),
          _fnLoggerWarning(nullptr),
          _fnLoggerInfo(nullptr)
    {
      AddLogger(info,
                warning ? warning : info,
                error ? error : info);
    }

    static bool IsValid()
    {
      return This != nullptr;
    }

    static std::shared_ptr<Logging> GetInstance()
    {
      if(!This)
      {
        auto fn = [](std::string /*msg*/) {};
        SetInstance(fn, fn, fn);
      }
      return This;
    }

    static void SetInstance(fnLogger_t info, fnLogger_t warning = nullptr, fnLogger_t error = nullptr)
    {
      This = std::make_shared<Logging>(info, warning, error);
    }

    void LogError(std::string msg, LogLevel logLevel = LogLevel::NORMAL)
    {
      std::lock_guard<std::mutex> l(_mutex);
      if(_fnLoggerError && isLevel(logLevel))
        _fnLoggerError(format_msg(msg));
    }

    void LogWarning(std::string msg, LogLevel logLevel = LogLevel::NORMAL)
    {
      std::lock_guard<std::mutex> l(_mutex);
      if(_fnLoggerWarning && isLevel(logLevel))
        _fnLoggerWarning(format_msg(msg));
    }

    void LogInfo(std::string msg, LogLevel logLevel = LogLevel::NORMAL, bool formatMsg = true)
    {
      std::lock_guard<std::mutex> l(_mutex);
      if(_fnLoggerInfo && isLevel(logLevel))
        _fnLoggerInfo(formatMsg ? format_msg(msg) : msg);
    }

    void AddLogger(fnLogger_t info, fnLogger_t warning = nullptr, fnLogger_t error = nullptr)
    {
      std::lock_guard<std::mutex> l(_mutex);
      AddFnLogger(info, _fnLoggerInfo);
      AddFnLogger(warning, _fnLoggerWarning);
      AddFnLogger(error, _fnLoggerError);
    }

    void SetLevel(LogLevel logLevel)
    {
      std::lock_guard<std::mutex> l(_mutex);
      if(logLevel >= LogLevel::QUIET && logLevel <= LogLevel::DIAGNOSTIC)
        _logLevel = logLevel;
    }
  };

  ////////////////////////////////////////////////////////////////////////////

  class AsyncLogging
  {
    typedef std::shared_ptr<Logging> logger_t;

    static std::shared_ptr<AsyncLogging> This;

    bool _stop;
    std::mutex _mutex;
    std::thread _monitor;
    std::queue<std::string> _buffer;
    std::condition_variable _notifier;
    logger_t _logger;

    static void SetInstance()
    {
      This = std::make_shared<AsyncLogging>(Logging::GetInstance());
    }

  public:
    static std::shared_ptr<AsyncLogging> GetInstance()
    {
      if(!This)
      {
        SetInstance();
      }
      return This;
    }

    AsyncLogging(logger_t logger)
        : _stop(false),
          _logger(logger)
    {
      _monitor = std::thread(&AsyncLogging::Monitor, this);
    }

    ~AsyncLogging()
    {
      if(_monitor.joinable())
      {
        _stop = true;
        _notifier.notify_one();
        _monitor.join();
      }
    }

    void LogInfo(std::string msg, LogLevel logLevel = LogLevel::NORMAL)
    {
      if(!_stop && _logger && _logger->isLevel(logLevel))
      {
        std::lock_guard<std::mutex> lock(_mutex);
        _buffer.push(Logging::format_msg(msg));
        _notifier.notify_one();
      }
    }

    void Monitor()
    {
      while(!(_stop && _buffer.empty()))
      {
        std::unique_lock<std::mutex> lock(_mutex);
        if(!_buffer.empty())
          _notifier.wait(lock, [&] { return _stop || !_buffer.empty(); });

        std::string message;
        if(_logger && !_buffer.empty())
        {
          message = _buffer.front();
          _buffer.pop();
        }
        lock.unlock();

        if(!message.empty())
          _logger->LogInfo(message, LogLevel::MINIMAL, false);
      }
    }

    void SetLevel(LogLevel logLevel)
    {
      if(_logger)
        _logger->SetLevel(logLevel);
    }

    void AddLogger(fnLogger_t info)
    {
      if(_logger)
        _logger->AddLogger(info);
    }

    void Flush()
    {
      while(!_buffer.empty())
      {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
      }
    }
  };
}

//#define Log logging::Logging::GetInstance()
#define Log logging::AsyncLogging::GetInstance()
#define AsyncLog logging::AsyncLogging::GetInstance()
