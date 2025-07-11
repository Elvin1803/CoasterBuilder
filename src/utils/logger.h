#ifndef LOGGER_H
#define LOGGER_H

#define LOG_CHANGE_OUTPUT(FILEOUT) utils::logger::GetLogger().SetOutputFile(FILEOUT);

#define LOG_INFO(...)  utils::logger::GetLogger().Log(utils::logLevel::LOG_INFO,  __VA_ARGS__);
#define LOG_TRACE(...) utils::logger::GetLogger().Log(utils::logLevel::LOG_TRACE, __VA_ARGS__);
#define LOG_DEBUG(...) utils::logger::GetLogger().Log(utils::logLevel::LOG_DEBUG, __VA_ARGS__);
#define LOG_WARN(...)  utils::logger::GetLogger().Log(utils::logLevel::LOG_WARN,  __VA_ARGS__);
#define LOG_ERROR(...) utils::logger::GetLogger().Log(utils::logLevel::LOG_ERROR, __VA_ARGS__);
#define LOG_FATAL(...) utils::logger::GetLogger().Log(utils::logLevel::LOG_FATAL, __VA_ARGS__);

namespace utils
{

    enum class logLevel
    {
        LOG_INFO = 0,
        LOG_TRACE,
        LOG_DEBUG,
        LOG_WARN,
        LOG_ERROR,
        LOG_FATAL
    };

    class logger
    {
    public:
        static logger& GetLogger();
        void SetOutputFile(const std::string& filename);

        template<typename... Args>
        void Log(const logLevel level, const std::string& format_str, Args... args)
        {
            WriteLog(level, std::vformat(format_str, std::make_format_args(args...)));
        }

    private:
        static logger *m_instance;

        std::ostream *m_outputFile;

    private:
        logger();
        ~logger() = default;

        std::string GetTimestamp();
        std::string LogLevelToString(const logLevel level);
        void WriteLog(const logLevel level, const std::string &msg);
    };

}

#endif /* LOGGER_H */
