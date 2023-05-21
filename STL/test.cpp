#include <ios>
#include <iostream>
#include <vector>

using ll = long long;

int main()
{
  std::ios_base::sync_with_stdio(false); // Removes c and c++ input compatability
  std::cin.tie(NULL);                    // Doesn't cout until flushed

  std::cout << "Test" << std::endl;

  // ll x{};
  // std::cin >> x;
  // std::cout << x << std::endl;

  std::vector<int> x{1, 2, 3, 4};

  for (const auto &y : x)
    std::cout << y << " ";
  std::cout << std::endl;

  return 0;
}
