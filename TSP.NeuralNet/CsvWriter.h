#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

namespace csv {

	class Writer {
	public:
		typedef std::vector<std::vector<std::vector<double>>> DataFormat;
		Writer(const char* fileName, const DataFormat& data);
		Writer(const Writer&) = delete;
		Writer& operator=(const Writer&) = delete;
	private:
		const int bufferSize = 10000;
	};
}

