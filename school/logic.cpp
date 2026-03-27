#include "logic.h"
#include <random>
#include <map>
#include <utility>

void Point::add_bit(Direction d) {
    const std::map<Direction, size_t>move_bit = {
        std::make_pair(Direction::LEFT, 0),
        std::make_pair(Direction::RIGHT, 1),
        std::make_pair(Direction::DOWN, 2),
        std::make_pair(Direction::UP, 3)
    };

    auto ptr = move_bit.find(d);
    size_t pos = ptr->second;

    mask[pos] = 1;
}

size_t Point::get_value() { return mask.to_ullong(); }

std::string to_str(size_t x, size_t y, size_t val) {
    static const std::string base = " 0 0.000000 0.000000 $ $";
    
    std::string result = std::to_string(x) + std::to_string(y) + std::to_string(val);
    
    return result + base;
}

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
    for (int i = 0; i < len; i++) {
        min_values[i] = com[i].min_lenght;
        max_values[i] = com[i].max_lenght;
    }
    
    res.emplace_back(max_values);
    res.emplace_back(min_values);

    if (test_cnt <= 2)
        return res;

    for (int t = 0; t < test_cnt - 2; t++) {
        std::vector<size_t>cur_test(len);
        for (int i = 0; i < len; i++) {
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

std::vector<std::string> set_values(std::vector<size_t>& values, std::vector<Comand>& com) {
    size_t len = com.size();

    int x = 0;
    int y = 0;

    int mn_x = 0;
    int mn_y = 0;
    int mx_x = 0;
    int mx_y = 0;

    for (int i = 0; i < len; i++) {
        switch (com[i].dir) {
        case Direction::LEFT:
            x -= values[i];
            break;
        case Direction::RIGHT:
            x += values[i];
            break;
        case Direction::DOWN:
            y += values[i];
            break;
        case Direction::UP:
            y -= values[i];
            break;
        }

        mn_x = std::min(mn_x, x);
        mn_y = std::min(mn_y, y);

        mx_x = std::max(mx_x, x);
        mx_y = std::max(mx_y, y);
    }

    constexpr int extra_len = 2;

    int lenx = mx_x + 2 * extra_len;
    if (mn_x < 0)
        lenx += -mn_x;

    int leny = mx_y + 2 * extra_len;
    if (mn_y < 0)
        leny += -mn_y;
    
    std::vector<std::string>res;

    res.push_back("; Field size: x, y");
    res.push_back(std::to_string(lenx) + " " + std::to_string(leny));
    res.push_back("; Robot position: x, y");
    res.push_back("2 2");

    int cur_x = 2, cur_y = 2;
    for (int i = 0; i < len; i++) {
        std::pair<int, int>delta = { 0, 0 };

        switch (com[i].dir) {
        case Direction::LEFT:
            delta = std::make_pair(-1, 0);
            break;
        case Direction::RIGHT:
            delta = std::make_pair(1, 0);
            break;
        case Direction::DOWN:
            delta = std::make_pair(0, 1);
            break;
        case Direction::UP:
            delta = std::make_pair(0, -1);
            break;
        }

        for (int j = 0; j < values[i]; j++) {
            cur_x += delta.first;
            cur_y += delta.second;

            Point tmp;
            tmp.add_bit(com[i].dir);

            std::string line = to_str(cur_x, cur_y, tmp.get_value());
            res.push_back(line);
        }
    }

    return res;
}
