#pragma once

#include <map>
#include "data.h"

enum Direction {
	UP, DOWN, LEFT, RIGHT, NONE
};

struct Comand {
	Direction dir;
	size_t min_lenght;
	size_t max_lenght;
};

std::vector<Comand> parser(std::vector<std::string>& in);