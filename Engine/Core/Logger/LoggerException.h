#include "logger_config.h"
#include <exception>
namespace Machi {


	namespace Logger {



		class MACHI_LOGGER_API MLoggerException : public std::exception {
			const char* m_str;
		public :
			MLoggerException(const char* str) : m_str(str) {};
			const char* what() const noexcept override { return m_str; }
		};



		class MLOGGER_NOT_SELECTED_ERROR : public MLoggerException {

		};
	}
}