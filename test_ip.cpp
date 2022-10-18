#include <gtest/gtest.h>
#include "ip_lib.h"

TEST(TestIp, TestSorting) {
  auto ip_pool = ip_pool_read("test_data/ip_filter_small.tsv");
  auto ip_pool_sorted = ip_pool_read("test_data/ip_filter_small_sorted.tsv");

  EXPECT_GT(ip_pool.size(), 0);

  std::sort(ip_pool.begin(), ip_pool.end(), ip_comparator);
  
  EXPECT_EQ(ip_pool, ip_pool_sorted);
}

TEST(TestIp, TestFilterFirst) {
  auto ip_pool = ip_pool_read("test_data/ip_filter.tsv");
  auto ip_pool_filtered_ref = ip_pool_read("test_data/ip_filter_first.tsv");

  EXPECT_GT(ip_pool.size(), 0);

  std::sort(ip_pool.begin(), ip_pool.end(), ip_comparator);
  
  auto ip_pool_filtered = filter(ip_pool, 1);
  
  EXPECT_EQ(ip_pool_filtered, ip_pool_filtered_ref);
}

TEST(TestIp, TestFilterOneTwo) {
  auto ip_pool = ip_pool_read("test_data/ip_filter.tsv");
  auto ip_pool_filtered_ref = ip_pool_read("test_data/ip_filter_onetwo.tsv");

  EXPECT_GT(ip_pool.size(), 0);

  std::sort(ip_pool.begin(), ip_pool.end(), ip_comparator);
  
  auto ip_pool_filtered = filter(ip_pool, 70, 46);
  
  EXPECT_EQ(ip_pool_filtered, ip_pool_filtered_ref);
}

TEST(TestIp, TestFilterAny) {
  auto ip_pool = ip_pool_read("test_data/ip_filter.tsv");
  auto ip_pool_filtered_ref = ip_pool_read("test_data/ip_filter_any.tsv");

  EXPECT_GT(ip_pool.size(), 0);

  std::sort(ip_pool.begin(), ip_pool.end(), ip_comparator);
  
  auto ip_pool_filtered = filter_any(ip_pool, 46);
  
  EXPECT_EQ(ip_pool_filtered, ip_pool_filtered_ref);
}
