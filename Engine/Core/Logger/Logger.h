#pragma once
#include "logger_config.h"
#include <Platform/types.h>
#include <utility>
#include <iostream>
#include <spdlog/spdlog.h>
#include <vector>
#define MACHI_DEFAULT_FILE_LOGGER_NAME "machi_file_logger"
#define MACHI_DEFAULT_CONSOLE_LOGGER_NAME "machi_console_logger"
#define MACHI_DEFAULT_COMPOSITE_LOGGER_NAME "machi_composite_logger"


#define MACHI_DEFALUT_LOGGING_PATTERN "[%H:%M:%S.%e][thread %t][%n]%^[%L]%$ %v"

namespace Machi {

	namespace Logger {
		
		// this is compile time size check function.
		// it is used to implement to MDEBUG, MINFO.
		//https://stackoverflow.com/questions/2124339/c-preprocessor-va-args-number-of-arguments
		template<typename ...T> 
		inline constexpr size_t number_of_args(T ... a) { return sizeof...(a); }

		class MACHI_LOGGER_API MLogger {
			static MLogger* _instance;
			MLogger();



		public:
			~MLogger();
			MLogger(MLogger&&) = delete;
			MLogger(MLogger&) = delete; // 
			MLogger(const MLogger& other) = delete;// default copy ctor

			MLogger& operator=(MLogger& other) = delete;


			enum class level { INFO, DEBUG };
			enum class logger_type { FILE_LOGGER, COMPOSITE_LOGGER, CONSOLE_LOGGER };


			static MLogger& get_instance() {

				if (_instance == NULL) {
					_instance = new MLogger();
				}
				return *_instance;
			}

			MLogger& set_global_pattern(const char* pattern);
			MLogger& set_logger_pattern(const char* logger_name, const char* pattern);


			MLogger& init_file_logging(const MSTRING& filename);
			MLogger& init_console_logging();
			MLogger& init_composite_logging(const MSTRING& filename);


			MLogger& make_console_logger(const char* logger_name);

			MLogger& make_file_logger(const char* logger_name, const MCHAR* filename);

			MLogger& make_composite_logger(const char* logger_name, std::vector<std::string> reference_logger, bool clean_reference_logger = true);

			MLogger& remove_logger(const char* logger_name);

			MLogger& remove_all_logger();



			void set_level(const char* logger_name, MLogger::level lv);

			template<typename T, typename ...A>
			void debug(const char* logger_name, T fmt, A... msg) {
				get_logger(logger_name)->debug(fmt,msg...);

			}
			template<typename T>
			void debug(const char* logger_name, const T& msg) {
				get_logger(logger_name)->debug(msg);
			}

			template<typename... Args>
			void debug(const char* logger_name, spdlog::format_string_t<Args...> fmt, Args &&... args) {

				get_logger(logger_name)->debug(std::forward<format_string_t<Args...>>(fmt), std::fowoard<Args &&...>(args));
			}


			template<typename... Args>
			inline void info(const char* logger_name, spdlog::format_string_t<Args...> fmt, Args &&... args) {
				get_logger(logger_name)->info(std::forward<format_string_t<Args...>(fmt), std::forward<Args>(args)...);
			}

			template<typename T, typename ...A>
			void info(const char* logger_name, T fmt, A... data) {
				get_logger(logger_name)->info(std::forward<T>(fmt), std::forward<A>(data)...);
			}

			template<typename T>
			void info(const char* logger_name, const T& msg) {
				get_logger(logger_name)->info(msg);
			}

			std::shared_ptr<spdlog::logger> get_logger(const char* logger_name);

			inline MLogger::level get_level(const char* logger_name);
		};



	}
}