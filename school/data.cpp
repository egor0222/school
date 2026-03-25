#include "data.h"

data* getdata(std::filesystem::path in) {
	std::ifstream file;
	file.open(in);
	if (!file.is_open())
		return nullptr;
	std::vector<std::string>input_data;
	while (file.eof()) {
		std::string cur;
		std::getline(file, cur);
		input_data.emplace_back(cur);
	}
	file.close();
	data* dt = new data(input_data);
	return dt;
}

void set_data(std::filesystem::path folder, std::string file_name, std::vector<std::string> str) {
	std::filesystem::path file = folder.string() + "/" + file_name + ".txt";
	if (!folder.empty() && !std::filesystem::exists(folder)) {
		std::filesystem::create_directories(folder);
	}
	std::ofstream out(file);
	for (auto& line : str) {
		out << line << '\n';
	}
	out.close();
}