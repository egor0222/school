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

	std::vector<Comand>com;
	std::vector<std::vector<size_t>>val;
	std::filesystem::path pp;

	try {
		std::vector<std::string>dt = get_data(p);

		com = parser(dt);

		val = get_values(com, tests);

		pp = p.parent_path();
		pp.append("tests");
	}
	catch (std::exception& e) {
		std::cerr << e.what() << '\n';
		return 0;
	}

	for (int i = 0; i < tests; i++) {
		auto test = set_values(val[i], com);

		set_data(pp, "test" + std::to_string(i + 1), test);
	}

	return 0;
}