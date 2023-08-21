#pragma once
#include <fstream>
#include <string>
#include <Platform/types.h>
#include "io_config.h"
namespace Machi {

	namespace IO {

	void MACHI_IO_API read_str_from_file(const MSTRING& filename, MSTRING& result);

	long MACHI_IO_API get_file_size(const MSTRING& filename);
	}
}