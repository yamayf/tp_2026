#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>
// #include <cmath>
// #include <fstream>

#include "dataStruct.hpp"

int main()
{
  std::vector<DataStruct> data;
  while (!std::cin.eof())
  {
    std::copy(
        std::istream_iterator<DataStruct>(std::cin),
        std::istream_iterator<DataStruct>(),
        std::back_inserter(data));

    if (std::cin.fail() && !std::cin.eof())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  std::sort(data.begin(), data.end(), [](const DataStruct &a, const DataStruct &b)
            {
    const double EPS = 1e-9;

    double absA1 = std::abs(a.key1);
    double absB1 = std::abs(b.key1);
    if (std::abs(absA1 - absB1) > EPS) {
      return absA1 < absB1;
    }

    if (std::abs(a.key2 - b.key2) > EPS) {
      return a.key2 < b.key2;
    }

    return a.key3.length() < b.key3.length(); });

  // Вывод данных в консоль
  std::copy(
      data.begin(),
      data.end(),
      std::ostream_iterator<DataStruct>(std::cout, "\n"));

  return 0;
}
