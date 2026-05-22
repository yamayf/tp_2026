#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <functional>
#include <limits>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "polygon.hpp"
#include "commands.hpp"

void load_from_file(const std::string &filename, std::vector<Polygon> &polygons)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file." << std::endl;
        std::exit(1);
    }
    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        Polygon poly;
        if (ss >> poly)
        {
            polygons.push_back(poly);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Error: filename is not provided" << std::endl;
        return 1;
    }

    std::vector<Polygon> polygons;
    load_from_file(argv[1], polygons);

    std::map<std::string, std::function<void()>> cmds;

    cmds["AREA"] = std::bind(Commands::cmd_AREA, std::cref(polygons), std::ref(std::cin), std::ref(std::cout));
    cmds["MAX"] = std::bind(Commands::cmd_MAX, std::cref(polygons), std::ref(std::cin), std::ref(std::cout));
    cmds["MIN"] = std::bind(Commands::cmd_MIN, std::cref(polygons), std::ref(std::cin), std::ref(std::cout));
    cmds["COUNT"] = std::bind(Commands::cmd_COUNT, std::cref(polygons), std::ref(std::cin), std::ref(std::cout));
    cmds["LESSAREA"] = std::bind(Commands::cmd_LESSAREA, std::cref(polygons), std::ref(std::cin), std::ref(std::cout));
    cmds["MAXSEQ"] = std::bind(Commands::cmd_MAXSEQ, std::cref(polygons), std::ref(std::cin), std::ref(std::cout));

    std::string command;
    while (std::cin >> command)
    {
        try
        {
            cmds.at(command)();
        }
        catch (const std::exception &e)
        {
            std::cout << "<INVALID COMMAND>" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    return 0;
}
