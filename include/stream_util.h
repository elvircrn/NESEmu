#pragma once

#include <string>
#include <fstream>
#include <iterator>
#include <tuple>

#include "rom.h"
#include "core.h"

using std::vector;
using std::tuple;
using std::string;

class StreamUtil {
public:
	/**
		Returns the header, prg banks, and chr banks respectively.
	*/
	static vector<u8> toVectorU8(std::ifstream &);
};

