#include "ip_lib.h"
// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<int> split_to_int(const std::string &str, char d)
{
    std::vector<int> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(std::stoi(str.substr(start, stop - start)));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(std::stoi(str.substr(start)));

    return r;
}

std::vector<std::string> split_to_str(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

bool ip_comparator(std::vector<int>& a, std::vector<int>& b) {
    //TODO: check a, b size first
    for (int i=0; i<4; i++) {
        int ip_part_a = a[i];
        int ip_part_b = b[i];
        if (ip_part_a != ip_part_b) {
            return ip_part_a > ip_part_b;
        }
    }
    return false;
}

std::vector<std::vector<int>> filter(const std::vector<std::vector<int>>& ip_pool, int number)
{
    std::vector<std::vector<int>> ip_filtered;
    std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(ip_filtered), [number](auto& ip){ return (ip[0] == number); });
    return ip_filtered;
}

std::vector<std::vector<int>> filter_any(const std::vector<std::vector<int>>& ip_pool, int number)
{
    std::vector<std::vector<int>> ip_filtered;
    std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(ip_filtered), [number](auto& ip){ return std::find(ip.begin(), ip.end(), number) != ip.end(); });
    return ip_filtered;
}

void ip_pool_print(std::vector<std::vector<int>>& ip_pool)
{
    for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
    {
        for(auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
        {
            if (ip_part != ip->cbegin())
            {
                std::cout << ".";

            }
            std::cout << *ip_part;
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<int>> ip_pool_read(std::string path)
{
    std::vector<std::vector<int>> ip_pool;
    std::ifstream input;
    input.open(path, std::ifstream::in);
    for(std::string line; std::getline(input, line);)
    {
        std::vector<std::string> v = split_to_str(line, '\t');
        ip_pool.push_back(split_to_int(v.at(0), '.'));
    }
    input.close();
    return ip_pool;
}