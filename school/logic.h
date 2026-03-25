#pragma once

#include <bitset>
#include <vector>
#include "comands.h"

#define MAX_BITS 4

struct Point {
	std::bitset<MAX_BITS>mask;
	//bool filled = false;
};

size_t rand_gen(size_t mn, size_t mx);

std::vector<std::vector<size_t>> get_values(std::vector<Comand>& com, size_t test_cnt);

std::vector<std::string> set_values(std::vector<std::vector<size_t>>& values, std::vector<Comand>& com);