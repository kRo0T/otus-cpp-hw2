#include "ip_lib.h"

int main()
{
    try
    {
        std::vector<std::vector<int>> ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            auto v = split_to_str(line, '\t');
            ip_pool.push_back(split_to_int(v.at(0), '.'));
        }

        std::sort(ip_pool.begin(), ip_pool.end(), ip_comparator);
        ip_pool_print(ip_pool);

        auto filtered_pool_1 = filter(ip_pool, 1);
        ip_pool_print(filtered_pool_1);

        auto filtered_pool_2 = filter(ip_pool, 70, 46);
        ip_pool_print(filtered_pool_2);

        auto filtered_pool_3 = filter_any(ip_pool, 46);
        ip_pool_print(filtered_pool_3);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
