#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <iterator>
#include <limits>
#include "Polygon.hpp"

void handleArea(const std::vector<Polygon>& polygons, std::istream& is)
{
  std::string arg;
  if (!(is >> arg))
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  double totalArea = 0.0;
  if (arg == "EVEN")
  {
    totalArea = std::accumulate(polygons.begin(),
      polygons.end(), 0.0,
      [](double sum, const Polygon& p)
      {
        return sum + (p.points.size() % 2 == 0 ? getArea(p) : 0.0);
      });
  }
  else if (arg == "ODD")
  {
    totalArea = std::accumulate(polygons.begin(),
      polygons.end(), 0.0,
      [](double sum, const Polygon& p)
      {
        return sum + (p.points.size() % 2 != 0 ? getArea(p) : 0.0);
      });
  }
  else if (arg == "MEAN")
  {
    if (polygons.empty())
    {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
    totalArea = std::accumulate(polygons.begin(),
      polygons.end(), 0.0,
      [](double sum, const Polygon& p)
      {
        return sum + getArea(p);
      });
    totalArea /= polygons.size();
  }
  else
  {
    try
    {
      size_t numVertexes = std::stoull(arg);
      if (numVertexes < 3)
        throw std::invalid_argument("");
      totalArea = std::accumulate(polygons.begin(),
        polygons.end(), 0.0,
        [numVertexes](double sum, const Polygon& p)
        {
          return sum + (p.points.size() == numVertexes ? getArea(p) : 0.0);
        });
    }
    catch (...)
    {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
  }

  // Проверяем, что в строке команды не осталось лишнего мусора
  char dummy;
  if (is >> dummy)
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  std::cout << std::fixed << std::setprecision(1) << totalArea << "\n";
}

// Реализация MAX
void handleMax(const std::vector<Polygon>& polygons, std::istream& is)
{
  std::string arg;
  if (!(is >> arg))
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  if (polygons.empty())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  char dummy;
  if (arg == "AREA")
  {
    if (is >> dummy) { std::cout << "<INVALID COMMAND>\n"; return; }
    auto it = std::max_element(polygons.begin(),
      polygons.end(), [](const Polygon& a, const Polygon& b)
      { return getArea(a) < getArea(b); });
    std::cout << std::fixed << std::setprecision(1) << getArea(*it) << "\n";
  }
  else if (arg == "VERTEXES")
  {
    if (is >> dummy) { std::cout << "<INVALID COMMAND>\n"; return; }
    auto it = std::max_element(polygons.begin(),
      polygons.end(), [](const Polygon& a, const Polygon& b)
      { return a.points.size() < b.points.size(); });
    std::cout << it->points.size() << "\n";
  }
  else
  {
    std::cout << "<INVALID COMMAND>\n";
  }
}

// Реализация MIN
void handleMin(const std::vector<Polygon>& polygons, std::istream& is)
{
  std::string arg;
  if (!(is >> arg))
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  if (polygons.empty())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  char dummy;
  if (arg == "AREA")
  {
    if (is >> dummy) { std::cout << "<INVALID COMMAND>\n"; return; }
    auto it = std::min_element(polygons.begin(),
      polygons.end(), [](const Polygon& a, const Polygon& b)
      { return getArea(a) < getArea(b); });
    std::cout << std::fixed << std::setprecision(1) << getArea(*it) << "\n";
  }
  else if (arg == "VERTEXES")
  {
    if (is >> dummy) { std::cout << "<INVALID COMMAND>\n"; return; }
    auto it = std::min_element(polygons.begin(),
      polygons.end(), [](const Polygon& a, const Polygon& b)
      { return a.points.size() < b.points.size(); });
    std::cout << it->points.size() << "\n";
  }
  else
  {
    std::cout << "<INVALID COMMAND>\n";
  }
}

// Реализация COUNT
void handleCount(const std::vector<Polygon>& polygons, std::istream& is)
{
  std::string arg;
  if (!(is >> arg))
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  long long count = 0;
  if (arg == "EVEN")
  {
    count = std::count_if(polygons.begin(),
      polygons.end(), [](const Polygon& p)
      { return p.points.size() % 2 == 0; });
  }
  else if (arg == "ODD")
  {
    count = std::count_if(polygons.begin(),
      polygons.end(), [](const Polygon& p)
      { return p.points.size() % 2 != 0; });
  }
  else
  {
    try
    {
      size_t numVertexes = std::stoull(arg);
      if (numVertexes < 3) throw std::invalid_argument("");
      count = std::count_if(polygons.begin(),
        polygons.end(), [numVertexes](const Polygon& p)
        { return p.points.size() == numVertexes; });
    }
    catch (...)
    {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
  }

  char dummy;
  if (is >> dummy)
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  std::cout << count << "\n";
}

// Реализация ECHO
void handleEcho(std::vector<Polygon>& polygons, std::istream& is)
{
  Polygon target;
  char dummy;

  // Читаем полигон и проверяем, что в текущей строке нет лишнего мусора
  if (!(is >> target) || (is >> dummy))
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  std::vector<Polygon> updatedCollection;
  updatedCollection.reserve(polygons.size() * 2);
  size_t addedCount = 0;

  std::for_each(polygons.begin(),
    polygons.end(), [&](const Polygon& p)
    {
      updatedCollection.push_back(p);
      if (isPolygonEqual(p, target))
      {
        updatedCollection.push_back(p);
        addedCount++;
      }
    });

  polygons = std::move(updatedCollection);
  std::cout << addedCount << "\n";
}

// Реализация INFRAME
void handleInFrame(const std::vector<Polygon>& polygons, std::istream& is)
{
  Polygon target;
  char dummy;

  // Читаем полигон и проверяем на ошибки/лишний мусор/пустую коллекцию
  if (!(is >> target) || (is >> dummy) || polygons.empty())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  Frame currentFrame = getCollectionFrame(polygons);
  if (isPolygonInFrame(target, currentFrame))
  {
    std::cout << "<TRUE>\n";
  }
  else
  {
    std::cout << "<FALSE>\n";
  }
}

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Error: filename parameter is missing.\n";
    return 1;
  }

  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "Error: cannot open file.\n";
    return 1;
  }

  std::vector<Polygon> polygons;
  std::string line;

  while (std::getline(file, line))
  {
    if (line.empty()) continue;
    std::stringstream ss(line);
    Polygon poly;
    if (ss >> poly)
    {
      char dummy;
      // Если полигон прочитался, но в строке файла остался мусор — строка невалидна
      if (!(ss >> dummy))
      {
        polygons.push_back(poly);
      }
    }
  }
  file.close();

  // Главный цикл обработки команд (построчный)
  while (std::getline(std::cin, line))
  {
    if (line.empty()) continue;

    std::stringstream ss(line);
    std::string command;
    if (!(ss >> command)) continue;

    if (command == "AREA")
    {
      handleArea(polygons, ss);
    }
    else if (command == "MAX")
    {
      handleMax(polygons, ss);
    }
    else if (command == "MIN")
    {
      handleMin(polygons, ss);
    }
    else if (command == "COUNT")
    {
      handleCount(polygons, ss);
    }
    else if (command == "ECHO")
    {
      handleEcho(polygons, ss);
    }
    else if (command == "INFRAME")
    {
      handleInFrame(polygons, ss);
    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
    }
  }

  return 0;
}
