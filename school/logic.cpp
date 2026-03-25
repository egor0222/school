#include "logic.h"
#include <random>

size_t rand_gen(size_t mn, size_t mx) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dis(mn, mx);
    return dis(gen);
}

std::vector<std::vector<size_t>> get_values(std::vector<Comand>& com, size_t test_cnt) {
    std::vector<std::vector<size_t>>res(test_cnt);

    auto len = com.size();
    std::vector<size_t>min_values(len);
    std::vector<size_t>max_values(len);
    for (size_t i = 0; i < len; i++) {
        min_values[i] = com[i].min_lenght;
        max_values[i] = com[i].max_lenght;
    }
    
    res.emplace_back(max_values);
    res.emplace_back(min_values);

    if (test_cnt <= 2)
        return res;

    for (size_t t = 0; t < test_cnt - 2; t++) {
        std::vector<size_t>cur_test(len);
        for (size_t i = 0; i < len; i++) {
            if (com[i].max_lenght == com[i].min_lenght)
                cur_test[i] = com[i].max_lenght;
            else
                cur_test[i] = rand_gen(com[i].min_lenght, com[i].max_lenght);
        }
        res.emplace_back(cur_test);
    }

    res.resize(test_cnt);
    return res;
}

std::vector<std::string> set_values(std::vector<std::vector<size_t>>& values, std::vector<Comand>& com) {
    
}
