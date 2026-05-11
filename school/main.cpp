#include <iostream>
#include "logic.h"
#include "data.h"
#include "comands.h"

/*std::vector<std::string> parce_input(int argc, char* argv[]) {
	std::vector<std::string>res;
	res.reserve(argc);
	for (int i = 0; i < argc; i++) {
		std::string cur(argv[i]);
		res.push_back(cur);
	}
	return res;
}*/

int main(int argc, char* argv[]) {
	//auto in = parce_input(argc, argv);
	//std::vector<std::string>in = { "abc", "C:\\All\\Examples\\Example.txt", "5" };

	std::vector<std::string>in(2);

	const size_t path_in = 0;
	const size_t num_in = 1;

	std::cout << "HELLO\nPlease enter the path to the template file and the number of tests:" << std::endl;

	std::getline(std::cin, in[path_in]);
	std::getline(std::cin, in[num_in]);

	/*std::cout << "It works" << std::endl;
	for (auto& str : data) {
		std::cout << str << std::endl;
	}*/
	/*if (in.size() < 3) {
		std::cout << "Too few arguments" << std::endl;
		return 0;
	}*/

	std::filesystem::path p = in[0];
	size_t tests = std::stoull(in[1]);

	std::vector<Comand>com;
	std::vector<std::vector<size_t>>val;
	std::filesystem::path out_path;

	try {
		std::vector<std::string>dt = get_data(p);

		com = parser(dt);

		val = get_values(com, tests);

		out_path = p.parent_path();
		out_path.append("tests");
	}
	catch (std::exception& e) {
		std::cerr << e.what() << '\n';
		return 0;
	}

	for (int i = 0; i < tests; i++) {
		auto test = set_values(val[i], com);

		set_data(out_path, "test" + std::to_string(i + 1), test);
	}

	std::cout << "Success!" << std::endl;
	system("pause");
	return 0;
}