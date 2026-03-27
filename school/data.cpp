#include "data.h"
#include <exception>

std::vector<std::string> get_data(std::filesystem::path in) {
	std::ifstream file;
	file.open(in);
	if (!file.is_open())
		throw std::runtime_error("File not opened");
	std::vector<std::string>input_data;
	while (!file.eof()) {
		std::string cur;
		std::getline(file, cur);
		input_data.emplace_back(cur);
	}
	file.close();
	return input_data;
}

void set_data(std::filesystem::path folder, std::string file_name, std::vector<std::string> str) {
	std::filesystem::path file = folder.string() + "/" + file_name + ".fil";
	if (!folder.empty() && !std::filesystem::exists(folder)) {
		std::filesystem::create_directories(folder);
	}
	std::ofstream out(file);
	for (auto& line : str) {
		out << line << '\n';
	}
	out.close();
}