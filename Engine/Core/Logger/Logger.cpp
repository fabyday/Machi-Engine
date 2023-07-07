#include "Logger.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>


#include <algorithm>
#include <memory>

#include <cstdarg>

using namespace Machi::Logger;
MLogger* MLogger::_instance = nullptr;



MLogger::MLogger() {
	spdlog::drop_all();
	//setup default pattern
	set_global_pattern(MACHI_DEFALUT_LOGGING_PATTERN);
}
MLogger::~MLogger() {
	spdlog::shutdown();



};

void MLogger::set_level(const char* logger_name, MLogger::level lv) {
	switch (lv)
	{
	case Machi::Logger::MLogger::level::INFO:

		spdlog::get(logger_name)->set_level(spdlog::level::level_enum::info);
		break;
	case Machi::Logger::MLogger::level::DEBUG:
		spdlog::get(logger_name)->set_level(spdlog::level::level_enum::debug);
		break;
	default:
		spdlog::get(logger_name)->set_level(spdlog::level::level_enum::info);
		break;
	}
}

MLogger& Machi::Logger::MLogger::init_file_logging(const MSTRING& filename)
{

	auto& ret = make_file_logger(MACHI_DEFAULT_FILE_LOGGER_NAME, filename.c_str());
	auto k = spdlog::get(MACHI_DEFAULT_FILE_LOGGER_NAME);
	return ret;


}
MLogger& Machi::Logger::MLogger::init_console_logging()
{
	auto& ret = make_console_logger(MACHI_DEFAULT_CONSOLE_LOGGER_NAME);
	return ret;
}

MLogger& Machi::Logger::MLogger::init_composite_logging(const MSTRING& filename) {

	//auto& ret = make_composite_logger(MACHI_DEFAULT_COMPOSITE_LOGGER_NAME, { m_console_logger->name(), m_file_logger->name() });
	//return ret;
	return *this;
}
std::shared_ptr<spdlog::logger> Machi::Logger::MLogger::get_logger(const char* logger_name)
{
	return spdlog::get(logger_name);
}



MLogger& MLogger::make_console_logger(const char* logger_name) {
	try {
		std::shared_ptr<spdlog::logger> t = spdlog::stdout_color_mt(logger_name);
		t->set_error_handler([](const std::string& msg) {
			spdlog::get(MACHI_DEFAULT_FILE_LOGGER_NAME)->debug("error occured" + msg);
			throw std::runtime_error(msg);
			});
	}
	catch (const spdlog::spdlog_ex& ex) {
		std::cerr << "Console Log init failed ..." << std::endl;
		std::cerr << ex.what() << std::endl;
	}
	return *this;
}

MLogger& MLogger::make_file_logger(const char* logger_name, const MCHAR* filename) {



		try {
			std::shared_ptr<spdlog::logger> t = spdlog::basic_logger_mt(logger_name, filename);
		}
		catch (const spdlog::spdlog_ex& ex) {
			std::cerr << "Log init failed" << std::endl;
			std::cerr << ex.what() << std::endl;
		}

	return *this;
}

MLogger& MLogger::make_composite_logger(const char* logger_name, std::vector<std::string> reference_logger, bool clean_reference_logger) {

	std::vector<std::shared_ptr<spdlog::sinks::sink>> sinks;
	for (const std::string& name : reference_logger) {

		auto t = spdlog::get(name)->sinks();
		std::copy(t.begin(), t.end(), std::back_inserter(sinks));

		if (clean_reference_logger) {
			remove_logger(name.c_str());
		}

	}

	//auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	//console_sink->set_level(m_console_logger->level());
	//auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(MTEXT("logs/multisink.txt"), true);
	//file_sink->set_level(m_file_logger->level());

	//m_composite_logger = std::shared_ptr<spdlog::logger>(new spdlog::logger("composite_sink", { console_sink, file_sink }));
	auto composite_logger = std::make_shared<spdlog::logger>(logger_name, std::begin(sinks), std::end(sinks));
	spdlog::register_logger(composite_logger);
	return *this;

}

//
//
//void MLogger::debug(const char* logger_name, const char* msg) {
//	spdlog::get(logger_name)->debug(msg);
//}
//void MLogger::debug(const char* logger_name, const char* fmt, const char* msg) {
//	spdlog::get(logger_name)->debug(fmt, msg);
//
//}
//
//
//void MLogger::debug(const char* logger_name, const MCHAR* msg) {
//	spdlog::get(logger_name)->debug(msg);
//}
//void MLogger::debug(const char* logger_name, const MCHAR* fmt, const MCHAR* msg) {
//	spdlog::get(logger_name)->debug(fmt, msg);
//
//}
//void MLogger::info(const char* logger_name, const char* msg) {
//	spdlog::get(logger_name)->info( msg);
//}
//void MLogger::info(const char* logger_name, const MCHAR* fmt, const MCHAR* msg) {
//	spdlog::get(logger_name)->info(fmt, msg);
//}
//void MLogger::info(const char* logger_name, const MCHAR* msg) {
//	spdlog::get(logger_name)->info(msg);
//}
//void MLogger::info(const char* logger_name, const MCHAR* fmt, const MCHAR* msg) {
//	spdlog::get(logger_name)->info(fmt, msg);
//}
//
//void MLogger::debug(const char* logger_name, MUINT size, ...) {
//	va_list ap;
//
//	va_start(ap, size);
//
//	for (int i = 0; i < size;);
//	switch
//	spdlog::get(logger_name)->info(ap);
//	va_arg(ap, char*);
//
//
//	va_end(ap);
//
//
//}
//
//void MLogger::info(const char* logger_name, MUINT size, ...) {
//	va_list ap;
//	va_start(ap, size);
//
//
//
//
//
//
//	va_end(ap);
//}


MLogger& MLogger::remove_all_logger() {
	spdlog::drop_all();
	return *this;
}

MLogger& MLogger::remove_logger(const char* logger_name) {

	spdlog::drop(logger_name);
	return *this;
}
MLogger& Machi::Logger::MLogger::set_logger_pattern(const char* logger_name, const char* pattern)
{
	spdlog::get(logger_name)->set_pattern(pattern);
	return *this;
}


MLogger& Machi::Logger::MLogger::set_global_pattern(const char* pattern)
{
	spdlog::set_pattern(pattern);
	return *this;
}


inline MLogger::level MLogger::get_level(const char* logger_name) {
	auto ptr = spdlog::get(logger_name);
	switch (ptr->level())
	{
	case spdlog::level::debug:
		return  MLogger::level::DEBUG;
	case spdlog::level::info:
		return MLogger::level::INFO;
	default:
		break;
	}
}
