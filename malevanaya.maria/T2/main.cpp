#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "data_struct.hpp"

//helper
static void skipToEndOfRecord(std::istream& in) {
    in.clear();
    char c = '\0';
    while (in.get(c)) {
        if (c == ':') {
            char next = '\0';
            if (in.get(next)) {
                if (next == ')') return;
                in.putback(next);
            }
        }
    }
}

int main() {
    std::vector<DataStruct> data;
    DataStruct ds;
    while (!std::cin.eof()) {
        if (std::cin >> ds) {
            data.push_back(ds);
        }
        else if (!std::cin.eof()) {
            skipToEndOfRecord(std::cin);
        }
    }

    std::sort(data.begin(), data.end(), compareDataStruct);

    std::copy(
        std::begin(data),
        std::end(data),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );

    return 0;
}
