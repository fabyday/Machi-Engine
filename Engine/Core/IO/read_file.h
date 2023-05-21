#include <fstream>
#include <string>
#include <Platform/types.h>
namespace Machi {
	void read_str_from_file(const MSTRING& filename, MSTRING& result);

	long get_file_size(const MSTRING& filename);
}