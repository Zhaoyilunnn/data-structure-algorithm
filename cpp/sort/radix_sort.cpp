// A rough impl of Radix Sort

#include <cassert>
#include <cmath>
#include <iostream>
#include <queue>
#include <vector>

#define BUCKET_NUM 10

// Get the k-th digit of a number
inline int get_digit(uint32_t num, uint32_t k) {
  int residual = num / std::pow(10, k);
  return residual % 10;
}

bool bucket_update(std::vector<uint32_t> *nums,
                   std::vector<std::queue<uint32_t>> *bucket,
                   const uint32_t k) {
  bool all_zero = true;
  for (const auto n : *nums) {
    int d = get_digit(n, k);
    (*bucket)[d].push(n);
    if (d > 0) {
      all_zero = false;
    }
  }
  size_t idx = 0;
  for (size_t i = 0; i < BUCKET_NUM; ++i) {
    while (!(*bucket)[i].empty()) {
      (*nums)[idx] = (*bucket)[i].front();
      (*bucket)[i].pop();
      idx++;
    }
  }
  return all_zero;
}

void radix_sort(std::vector<uint32_t> *nums) {
  size_t bucket_size = nums->size();
  std::vector<std::queue<uint32_t>> bucket(BUCKET_NUM, std::queue<uint32_t>());

  uint32_t k = 0;
  while (!bucket_update(nums, &bucket, k)) {
    k++;
  }
}

void debug(const std::vector<uint32_t> &nums) {
  for (const auto n : nums) {
    std::cout << n << " ";
  }
  std::cout << std::endl;
}

void test_get_digit() {
  int d = get_digit(12312, 2);
  assert(d == 3);
}

void test_radix_sort() {
  std::vector<uint32_t> nums = {3, 4, 11, 2, 88, 9, 11211, 2, 4, 9};
  radix_sort(&nums);
  assert(std::equal(
      nums.begin(), nums.end(),
      std::vector<uint32_t>({2, 2, 3, 4, 4, 9, 9, 11, 88, 11211}).begin()));
}

void test() {
  test_get_digit();
  test_radix_sort();
}

int main() {
  test();
  std::vector<uint32_t> nums;
  uint32_t input_num;

  std::cout << "Enter numbers (type any non-numeric value to stop):"
            << std::endl;
  while (std::cin >> input_num) {
    nums.push_back(input_num);
  }
  radix_sort(&nums);

  std::cout << "Sorted result is:" << std::endl;
  debug(nums);
  return 0;
}
