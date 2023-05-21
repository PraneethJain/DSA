#include <ios>
#include <iostream>
#include <vector>

using ll = long long;

void print_vector(std::vector<int> v)
{
  for (const auto &el : v)
    std::cout << el << " ";
  std::cout << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false); // Removes c and c++ input compatability
  std::cin.tie(NULL);                    // Doesn't cout until flushed

  std::vector<int> x{1, 2, 3, 4};

  print_vector(x);

  std::vector<int>::iterator it = x.begin();
  for (auto cur = x.begin(); cur != x.end(); ++cur)
    std::cout << *cur << " ";
  std::cout << std::endl;

  return 0;
}
