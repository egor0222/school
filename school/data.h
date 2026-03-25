#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <filesystem>

struct data {
	std::vector<std::string>str;
};

data* getdata(std::filesystem::path in);

void set_data(std::filesystem::path folger, std::string file_name, std::vector<std::string> str);