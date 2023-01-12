#pragma once

#include <string>
#include <chrono>
#include <format>

#define LOG(message) Logger::get_instance()->log(message)
#define LOG_FORMAT(fmt, ...) Logger::get_instance()->log_format(fmt, ##__VA_ARGS__)

#define LOG_WARNING(message) Logger::get_instance()->log_warning(message)
#define LOG_WARNING_FORMAT(fmt, ...) Logger::get_instance()->log_warning_format(fmt, ##__VA_ARGS__)

#define LOG_ERROR(message) Logger::get_instance()->log_error(message)
#define LOG_ERROR_FORMAT(fmt, ...) Logger::get_instance()->log_error_format(fmt, ##__VA_ARGS__)

#define ASSERT(cond, message)\
if(!(cond)) {\
	LOG_ERROR(message);\
	__debugbreak();\
}\

#define ASSERT_FORMAT(cond, fmt, ...)\
if(!(cond)) {\
	LOG_ERROR_FORMAT(fmt, ##__VA_ARGS__);\
	__debugbreak();\
}\

class Logger {
public:
	struct Log {
		int level;
		std::string message;
		std::chrono::local_time<std::chrono::system_clock::duration> time;
	};

	Logger(const Logger&) = delete;

	static void initialize_logger();

	static inline Logger* get_instance() { return _instance; }

	void log(const std::string& message);

	template<typename ... Args>
	void log_format(const std::string_view& format_str, Args&&... args) {
		ilog({ 0, std::vformat(format_str, std::make_format_args(args...)), get_current_time() });
	}

	void log_warning(const std::string& message);

	template<typename ... Args>
	void log_warning_format(const std::string_view& format_str, Args&&... args) {
		ilog({ 1, std::vformat(format_str, std::make_format_args(args...)), get_current_time() });
	}

	void log_error(const std::string& message);

	template<typename ... Args>
	void log_error_format(const std::string_view& format_str, Args&&... args) {
		ilog({ 2, std::vformat(format_str, std::make_format_args(args...)), get_current_time() });
	}
private:
	Logger();
	~Logger();

	static Logger* _instance;

	auto get_current_time() { return std::chrono::current_zone()->to_local(std::chrono::system_clock::now()); }

	void ilog(const Log& log);
};