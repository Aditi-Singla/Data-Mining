#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

template <typename T>
void print_vec(std::vector<T> &vec, std::ofstream &outStream);

template <typename K, typename V>
void print_map(std::unordered_map<K, V> &map);