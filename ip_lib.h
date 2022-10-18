#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <fstream>

std::vector<int> split_to_int(const std::string &str, char d);
std::vector<std::string> split_to_str(const std::string &str, char d);

bool ip_comparator(std::vector<int>& a, std::vector<int>& b);

std::vector<std::vector<int>> filter(const std::vector<std::vector<int>>& ip_pool, int number);

template<typename... Args>
std::vector<std::vector<int>> filter(const std::vector<std::vector<int>>& ip_pool, int number, Args... args)
{
    std::vector<std::vector<int>> ip_filtered;
    int index = sizeof...(args);
    std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(ip_filtered), [index, number](auto& ip){ return ip[index] == number; });
    return filter(ip_filtered, args...);
}

std::vector<std::vector<int>> filter_any(const std::vector<std::vector<int>>& ip_pool, int number);

void ip_pool_print(std::vector<std::vector<int>>& ip_pool);
std::vector<std::vector<int>> ip_pool_read(std::string path);