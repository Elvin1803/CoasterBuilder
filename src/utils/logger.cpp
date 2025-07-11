#include <pch.h>
#include "logger.h"

namespace utils
{

    logger* logger::m_instance = nullptr;

    logger::logger(){
        m_outputFile = &std::cout;
    }

    logger& logger::GetLogger() {
        if (!m_instance)
        {
            m_instance = new logger();
        }

        return *m_instance;
    }

    void logger::SetOutputFile(const std::string& filename) {
        static std::ofstream fileStream;
        if (fileStream.is_open()) {
            fileStream.close();
        }

        if (filename == "stdout") {
            m_outputFile = &std::cout;
        } else {
            fileStream.open(filename, std::ios::app);
            if (fileStream.is_open()) {
                m_outputFile = &fileStream;
            } else {
                m_outputFile = &std::cout;
                LOG_ERROR("Failed to open log file: {}", filename)
            }
        }
    }

    void logger::WriteLog(const logLevel level, const std::string &msg) {
        (*m_outputFile) << "[" << GetTimestamp() << "] "
                        << "[" << LogLevelToString(level) << "] "
                        << msg << std::endl;
    }

    std::string logger::GetTimestamp() {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);

        std::tm tm;
#if defined(_WIN32) || defined(_WIN64)
        localtime_s(&tm, &now_time);
#else
        localtime_r(&now_time, &tm);
#endif

        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

    std::string logger::LogLevelToString(const logLevel level) {
        switch (level) {
        case logLevel::LOG_INFO:  return "INFO";
        case logLevel::LOG_TRACE: return "TRACE";
        case logLevel::LOG_DEBUG: return "DEBUG";
        case logLevel::LOG_WARN:  return "WARN";
        case logLevel::LOG_ERROR: return "ERROR";
        case logLevel::LOG_FATAL: return "FATAL";
        default:                  return "UNKNOWN";
        }
    }

}
