/******************************************************
  > File Name: ni_spdlog.h
  > Author: NilRaven
  > 
  > Created Time: 2023年04月05日 星期三 22时04分28秒
 *****************************************************/

#ifndef __NI_SPDLOG_H__
#define __NI_SPDLOG_H__

#include "spdlog/common.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/spdlog.h"

#include <cstddef>

class CSpdLogger
{
   public:
    CSpdLogger()
    {
        const char *strPattern = "[%Y%m%d %H:%M:%S %z][%^%l%$] [thread %t] %v";
        spdlog::set_pattern(strPattern);

//debug模式，要加打印
#ifndef NDEBUG
        spdlog::set_level(spdlog::level::debug);
#else
        spdlog::set_level(spdlog::level::off);
#endif

        size_t max_size = 500 * 1024;
        size_t max_files = 5;
        spdlog::rotating_logger_mt("file", "./ni.log", max_size, max_files);
        spdlog::get("file")->set_pattern(strPattern);
        spdlog::get("file")->set_level(spdlog::level::info);
        spdlog::flush_every(std::chrono::seconds(2));
    }
    void Info(const std::string &msg)
    {
        spdlog::info(msg);
        spdlog::get("file")->info(msg);
    }
    void Debug(const std::string &msg)
    {
        spdlog::debug(msg);
        spdlog::get("file")->debug(msg);
    }
    void Warn(const std::string &msg)
    {
        spdlog::warn(msg);
        spdlog::get("file")->warn(msg);
    }
    void Error(const std::string &msg)
    {
        spdlog::error(msg);
        spdlog::get("file")->error(msg);
    }
};
#endif
