#include "Utils.h"

template <typename T>
void print_vec(std::vector<T> &vec, std::ofstream &outStream) {
    if (outStream.is_open()) {
        for (auto &t : vec) {
            outStream << t << ' ';
        }
        outStream << std::endl;
    }
    else {
        for (auto &t : vec) {
            std::cout << t << ' ';
        }
        std::cout << std::endl;
    }
}

template <typename K, typename V>
void print_map(std::unordered_map<K, V> &map) {
    for (auto it = map.begin(); it != map.end(); it++) {
        std::cout << it.first << ':' << it.second << ' ';
    }
    std::cout << std::endl;
}
