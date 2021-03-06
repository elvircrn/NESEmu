#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <sstream>

#include "core.h"
#include <array>

using std::vector;
using std::array;

class ROM {
public:
	ROM();
	ROM(std::ifstream &kernalFile, std::ifstream &basicFile);
	ROM(vector<u8> kernal, vector<u8> basic, vector<u8> chargen, vector<u8> io);
	ROM(vector<u8> kernal, vector<u8> basic, vector<u8> chargen, vector<u8> io, vector<u8> customROM);

	vector<u8> kernal;
	vector<u8> basic;
	vector<u8> chargen;
	vector<u8> io;
	vector<u8> customROM;
	u32 prgROMOffset;
};


