#include "read_file.h"
#include <Platform/types.h>

long Machi::get_file_size(const MSTRING& filename) {

	std::string tmp(filename.begin(), filename.end());
	struct stat stat_buf;
	int rc = stat(tmp.c_str(), &stat_buf);
	return rc == 0 ? stat_buf.st_size : -1;
}

void Machi::read_str_from_file(const MSTRING& filename, MSTRING& result){


	 std::ifstream readFile;

	 readFile.open(filename);
	 const long file_size = get_file_size(filename);
	 result.reserve(file_size);

	 if (readFile.is_open())
	 {

		 while (!readFile.eof())
		 {

			 char arr[256];
			 readFile.getline(arr, 256);
			 result += reinterpret_cast<MCHAR>(arr);
		 }

	 }

	 readFile.close();


}