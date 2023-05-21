#include <ios>
#include <iostream>

using ll = long long;

int main()
{
  std::ios_base::sync_with_stdio(false); // Removes c and c++ input compatability
  std::cin.tie(NULL);                    // Doesn't cout until flushed

  std::cout << "Test" << std::endl;

  ll x{};
  std::cin >> x;
  std::cout << x << std::endl;

  return 0;
}
