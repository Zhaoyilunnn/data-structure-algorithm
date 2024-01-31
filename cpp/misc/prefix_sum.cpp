// Reference
//  Blelloch G E. Prefix sums and their applications[J]. 1990.

#include <cassert>
#include <chrono>
#include <cmath>
#include <iostream>
#include <omp.h>
#include <random>
#include <vector>

std::vector<int> prefix_sum(const std::vector<int> &nums) {
  if (nums.empty()) {
    return {};
  }
  std::vector<int> res(nums.size(), 0);
  res[0] = nums[0];
  for (size_t i = 1; i < nums.size(); ++i) {
    res[i] = res[i - 1] + nums[i];
  }
  return res;
}

inline bool is_power_of_two(size_t n) { return n > 0 && (n & (n - 1)) == 0; }

void extend_to_next_power_of_two(std::vector<int> &nums) {
  if (is_power_of_two(nums.size())) {
    return;
  }

  size_t next_power_of_two = 1;
  while (next_power_of_two < nums.size()) {
    next_power_of_two *= 2;
  }

  nums.resize(next_power_of_two, 0);
}

// Up sweep
int reduce(std::vector<int> &nums) {
  if (nums.empty()) {
    return 0;
  }

  extend_to_next_power_of_two(nums);

  int n = std::log2(nums.size());

  for (size_t d = 0; d < n; ++d) {
    size_t stride = 1ULL << (d + 1);
    // #pragma omp parallel for
    for (size_t i = 0; i < nums.size(); i += stride) {
      // a[i + 2^{d+1} - 1] = a[i + 2^d - 1] + a[i + 2^{d+1} - 1]
      size_t left_idx = i + (1ULL << d) - 1;
      size_t right_idx = i + stride - 1;
      nums[right_idx] += nums[left_idx];
    }
  }

  return nums[nums.size() - 1];
}

// Down sweep
void down_sweep(std::vector<int> &nums) {
  if (nums.empty()) {
    return;
  }

  extend_to_next_power_of_two(nums);

  int n = std::log2(nums.size());

  nums[nums.size() - 1] = 0;
  for (int d = n - 1; d >= 0; --d) {
    size_t stride = 1ULL << (d + 1);
#pragma omp parallel for
    for (int i = nums.size() - 1; i > 0; i -= stride) {
      // a[i] = a[i - 2^d] + a[i]
      size_t left_idx = i - (1ULL << d);
      size_t right_idx = i;
      auto tmp = nums[right_idx];
      nums[right_idx] += nums[left_idx];
      nums[left_idx] = tmp;
    }
  }
}

void test_prefix_sum() {
  std::vector<int> nums = {3, 1, 7, 0, 4, 1, 6, 3};
  std::vector<int> expected = {3, 4, 11, 11, 15, 16, 22, 25};
  auto res = prefix_sum(nums);
  assert(std::equal(res.begin(), res.end(), expected.begin()));

  nums = {0};
  expected = {0};
  res = prefix_sum(nums);
  assert(std::equal(res.begin(), res.end(), expected.begin()));

  nums = {};
  expected = {};
  res = prefix_sum(nums);
  assert(std::equal(res.begin(), res.end(), expected.begin()));
}

void test_up_and_down() {
  std::vector<int> nums = {3, 1, 7, 0, 4, 1, 6, 3};
  int expected = 25;
  int res = reduce(nums);
  assert(res == expected);
  std::vector<int> down_sweep_res = {0, 3, 4, 11, 11, 15, 16, 22};
  down_sweep(nums);
  assert(std::equal(nums.begin(), nums.end(), down_sweep_res.begin()));

  nums = {3, 1, 7, 0, 4, 1, 6};
  expected = 22;
  res = reduce(nums);
  assert(res == expected);
  down_sweep(nums);
  assert(std::equal(nums.begin(), nums.end(), down_sweep_res.begin()));

  nums = {3, 1, 7, 0, 4};
  expected = 15;
  res = reduce(nums);
  assert(res == expected);
  down_sweep_res = {0, 3, 4, 11, 11, 15, 15, 15};
  down_sweep(nums);
  assert(std::equal(nums.begin(), nums.end(), down_sweep_res.begin()));
}

int main() {
  test_prefix_sum();
  test_up_and_down();

  int seed = 2024;
  int length = 1000;

  std::cout << "Please input a seed:" << std::endl;
  std::cin >> seed;
  std::cout << "Please input a vector size:" << std::endl;
  std::cin >> length;

  assert(length > 0);
  std::vector<int> nums(length, 0);

  // std::random_device rd;
  std::default_random_engine el(seed);
  std::uniform_int_distribution<int> uniform_dist(0, 100);

#pragma omp parallel for
  for (size_t i = 0; i < length; ++i) {
    auto num = uniform_dist(el);
    nums[i] = num;
  }

  auto start = std::chrono::high_resolution_clock::now();
  std::cout << reduce(nums) << std::endl;
  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << "Time taken: " << duration.count() << " milliseconds"
            << std::endl;
  return 0;
}
