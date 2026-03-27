#include "comands.h"
#include <algorithm>

std::pair<size_t, size_t> get_nums(std::string str) {
	size_t mn, mx;
	mn = std::stoull(str);
	
	std::reverse(str.begin(), str.end());
	while (!str.empty() && str.back() != '-')
		str.pop_back();
	str.pop_back();

	reverse(str.begin(), str.end());

	mx = std::stoull(str);
	return std::make_pair(mn, mx);
}

Comand parse_str(std::string str) {
	static const std::map<std::string, Direction>dir_map = {
		std::make_pair(std::string("up"), Direction::UP),
		std::make_pair(std::string("down"), Direction::DOWN),
		std::make_pair(std::string("right"), Direction::RIGHT),
		std::make_pair(std::string("left"), Direction::LEFT)
	};

	std::string tmp;
	int pos = 0;
	while (pos < str.size() && str[pos] != ' ') 
		tmp.push_back(str[pos++]);

	auto ptr = dir_map.find(tmp);
	if (ptr == dir_map.end())
		throw std::runtime_error("String is not in map");

	pos++;
	tmp.clear();
	while (pos < str.size() && (str[pos] != ' ' || str[pos] != '\n')) 
		tmp.push_back(str[pos++]);

	auto pr = get_nums(tmp);

	if (pr.first == 0 || pr.second == 0 || pr.first > pr.second)
		throw std::runtime_error("Uncorrect numbers");

	constexpr size_t mx_value = 100;

	return Comand{
		.dir = ptr->second,
		.min_lenght = std::min(pr.first, mx_value),
		.max_lenght = std::min(pr.second, mx_value)
	};
}

std::vector<Comand> parser(std::vector<std::string>& in) {
	std::vector<Comand>result;
	result.reserve(in.size());
	for (auto& s : in) {
		Comand com = parse_str(s);
		result.push_back(com);
	}
	return result;
}