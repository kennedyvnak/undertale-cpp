#include "logger.h"

namespace engine {
#ifdef _WIN32
#include "console_color.h"
#endif // _WIN32

	Logger* Logger::_instance;

	Logger::Logger() {}

	Logger::~Logger() {}

	void Logger::initialize_logger() {
		_instance = new Logger();
	}

	void Logger::log(const std::string& message) {
		ilog({ 0, message, get_current_time() });
	}

	void Logger::log_warning(const std::string& message) {
		ilog({ 1, message, get_current_time() });
	}

	void Logger::log_error(const std::string& message) {
		ilog({ 2, message, get_current_time() });
	}

	void Logger::ilog(const Log& log) {
		switch (log.level) {
		case 0:
			// INFO/DEBUG
			std::cout << std::vformat("LOG({:%T}): {}", std::make_format_args(log.time, log.message)) << std::endl;
			break;
		case 1:
			// WARNING
#ifdef _WIN32
			std::cout << dye::yellow(std::vformat("WAR({:%T}): {}", std::make_format_args(log.time, log.message))) << std::endl;
#else
			std::cout << std::vformat("WAR({:%T}): {}", std::make_format_args(log.time, log.message)) << std::endl;
#endif // _WIN32
			break;
		case 2:
			// ERROR
#ifdef _WIN32
			std::cout << dye::red(std::vformat("ERR({:%T}): {}", std::make_format_args(log.time, log.message))) << std::endl;
#else 
			std::cout << std::vformat("ERR({:%T}): {}", std::make_format_args(log.time, log.message)) << std::endl;
#endif // _WIN32
			break;
		}
	}
}
