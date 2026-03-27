#include <iostream>
#include "logic.h"
#include "data.h"
#include "comands.h"

std::vector<std::string> parce_input(int argc, char* argv[]) {
	std::vector<std::string>res;
	res.reserve(argc);
	for (int i = 0; i < argc; i++) {
		std::string cur(argv[i]);
		res.push_back(cur);
	}
	return res;
}

int main(int argc, char* argv[]) {
	//auto data = parce_input(argc, argv);

	std::vector<std::string>in = { "abc", "C:\\All\\Examples\\Example.txt", "5" };

	/*
	std::cout << "It works" << std::endl;
	for (auto& str : data) {
		std::cout << str << std::endl;
	}*/

	if (in.size() < 3) {
		std::cout << "Too few arguments" << std::endl;
		return 0;
	}

	std::filesystem::path p = in[1];
	size_t tests = std::stoull(in[2]);

	auto dt = get_data(p);

	auto com = parser(dt);

	auto val = get_values(com, tests);

	auto pp = p.parent_path();
	pp.append("tests");

	for (int i = 0; i < tests; i++) {
		auto test = set_values(val[i], com);

		set_data(pp, "test" + std::to_string(i + 1), test);
	}

}